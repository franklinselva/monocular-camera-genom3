
#include "acMonocularCamera.h"

#include "fg3utils/trace_f.h"
#include "fg3utils/macros.h"
#include "MonocularCamera_c_types.h"
#include <opencv2/opencv.hpp>
#include <chrono>

/* --- Setup ---------------------------------------------------------*/
cv::VideoCapture *cap;

/* --- Task publish ----------------------------------------------------- */

/** Codel camera_start of task publish.
 *
 * Triggered by MonocularCamera_start.
 * Yields to MonocularCamera_pub, MonocularCamera_pause_start.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT.
 */
genom_event
camera_start(MonocularCamera_CameraInfo *info, const char device[128],
             const MonocularCamera_Frame *Frame,
             const MonocularCamera_Extrinsics *Extrinsics,
             const MonocularCamera_Intrinsics *Intrinsics, bool debug,
             const genom_context self)
{
  if (!info->started)
  {
    if (debug)
    {
      CODEL_LOG_WARNING("Camera not started");
    }
    return MonocularCamera_pause_start;
  }

  cap = new cv::VideoCapture(device);
  Frame->open("raw", self);
  Frame->open("compress", self);

  Frame->data("raw", self)->width = info->size.w;
  Frame->data("raw", self)->height = info->size.h;
  Frame->data("raw", self)->bpp = 3;
  Frame->data("raw", self)->compressed = false;

  auto pixel_length = info->size.w * info->size.h * Frame->data("raw", self)->bpp;
  if (genom_sequence_reserve(&(Frame->data("raw", self)->pixels), pixel_length) == -1)
  {
    MonocularCamera_e_OUT_OF_MEM_detail d;
    snprintf(d.message, sizeof(d.message), "unable to allocate frame memory");
    CODEL_LOG_WARNING(d.message);
    return MonocularCamera_e_OUT_OF_MEM(&d, self);
  }

  Frame->data("compress", self)->width = info->size.w;
  Frame->data("compress", self)->height = info->size.h;
  Frame->data("compress", self)->bpp = 3;
  Frame->data("compress", self)->compressed = true;
  if (genom_sequence_reserve(&(Frame->data("compress", self)->pixels), pixel_length) == -1)
  {
    MonocularCamera_e_OUT_OF_MEM_detail d;
    snprintf(d.message, sizeof(d.message), "unable to allocate frame memory");
    CODEL_LOG_WARNING(d.message);
    return MonocularCamera_e_OUT_OF_MEM(&d, self);
  }

  return MonocularCamera_pub;
}

/** Codel camera_publish of task publish.
 *
 * Triggered by MonocularCamera_pub.
 * Yields to MonocularCamera_pub, MonocularCamera_pause_pub,
 *           MonocularCamera_ether.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT.
 */
genom_event
camera_publish(const MonocularCamera_CameraInfo *info,
               const MonocularCamera_Frame *Frame,
               const MonocularCamera_Extrinsics *Extrinsics,
               const MonocularCamera_Intrinsics *Intrinsics,
               bool show_frames, bool debug, const genom_context self)
{

  if (!info->started)
  {
    if (debug)
    {
      CODEL_LOG_WARNING("Camera not started / stopped");
    }
    cv::destroyAllWindows();
    return MonocularCamera_ether;
  }

  if (info->pause_camera)
  {
    if (debug)
    {
      CODEL_LOG_WARNING("Camera paused");
    }
    return MonocularCamera_pause_pub;
  }

  or_sensor_frame *raw_frame = Frame->data("raw", self);
  or_sensor_frame *compress_frame = Frame->data("compress", self);

  if (!cap->isOpened())
  {
    CODEL_LOG_WARNING("Camera not started");
    return MonocularCamera_pause_pub;
  }

  cv::Mat frame;
  *cap >> frame;

  if (frame.empty())
  {
    CODEL_LOG_WARNING("Camera frame empty");
    return MonocularCamera_pause_pub;
  }

  if (frame.cols != raw_frame->width || frame.rows != raw_frame->height)
  {
    char msg[128];
    snprintf(msg, sizeof(msg), "Camera frame size mismatch: expected %dx%d, got %dx%d",
             raw_frame->width, raw_frame->height,
             frame.cols, frame.rows);
    CODEL_LOG_ERROR(msg);
    return MonocularCamera_pause_pub;
  }

  memcpy(raw_frame->pixels._buffer, frame.data, raw_frame->pixels._length);
  raw_frame->ts.sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  raw_frame->ts.nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000000000;
  raw_frame->compressed = false;
  raw_frame->pixels._length = frame.cols * frame.rows * frame.channels();

  if (info->compression_rate > 0)
  {
    std::vector<uchar> compressed;
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(info->compression_rate);

    cv::imencode(".jpg", frame, compressed, compression_params);

    compress_frame->width = raw_frame->width;
    compress_frame->height = raw_frame->height;
    compress_frame->bpp = raw_frame->bpp;
    compress_frame->compressed = true;
    compress_frame->pixels._length = compressed.size();
    compress_frame->pixels._buffer = compressed.data();
    compress_frame->ts.sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    compress_frame->ts.nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000000000;
  }

  // Publish intrinsics
  if (info->publish_intrinsics)
  {
    Intrinsics->data(self)->calib = info->intrinsics.calib;
    Intrinsics->data(self)->disto = info->intrinsics.disto;
    Intrinsics->write(self);
  }

  // Publish extrinsics
  if (info->publish_extrinsics)
  {
    Extrinsics->data(self)->rot = info->extrinsics.rot;
    Extrinsics->data(self)->trans = info->extrinsics.trans;
    Extrinsics->write(self);
  }

  if (show_frames)
  {
    cv::imshow("frame", frame);
    cv::waitKey(1);
  }
  else
  {
    cv::destroyAllWindows();
  }

  Frame->write("raw", self);
  Frame->write("compress", self);

  return MonocularCamera_pub;
}

/* --- Activity start_camera -------------------------------------------- */

/** Codel StartCamera of activity start_camera.
 *
 * Triggered by MonocularCamera_start.
 * Yields to MonocularCamera_ether.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT,
 *        MonocularCamera_e_BAD_CONFIG.
 */
genom_event
StartCamera(bool *started, const genom_context self)
{
  *started = true;
  return MonocularCamera_ether;
}
