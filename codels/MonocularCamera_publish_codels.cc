
#include "acMonocularCamera.h"

#include "fg3utils/trace_f.h"
#include "fg3utils/macros.h"
#include "MonocularCamera_c_types.h"
#include <opencv2/opencv.hpp>

/* --- Setup ---------------------------------------------------------*/
cv::VideoCapture *cap;

/* --- Task publish ----------------------------------------------------- */

/* --- Activity CameraPublish ------------------------------------------- */

/** Codel camera_start of activity CameraPublish.
 *
 * Triggered by MonocularCamera_start.
 * Yields to MonocularCamera_wait, MonocularCamera_pause_start.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT.
 */
genom_event
camera_start(MonocularCamera_ids *ids,
             const MonocularCamera_ImageFrame *ImageFrame,
             const MonocularCamera_Extrinsics *Extrinsics,
             const MonocularCamera_Intrinsics *Intrinsics,
             const genom_context self)
{
  ids->info.started = false;
  cap = new cv::VideoCapture(ids->info.device);
  if (!cap->isOpened())
  {
    char msg[128];
    snprintf(msg, sizeof(msg), "Failed to open camera device %s", ids->info.device);
    CODEL_LOG_ERROR(msg);
    return MonocularCamera_pause_start;
  }

  ImageFrame->data("raw", self)->width = ids->info.size.w;
  ;
  ImageFrame->data("raw", self)->height = ids->info.size.h;
  ImageFrame->data("raw", self)->bpp = 3;
  ImageFrame->data("raw", self)->compressed = false;

  auto pixel_length = ids->info.size.w * ids->info.size.h * ImageFrame->data("raw", self)->bpp;
  if (genom_sequence_reserve(&(ImageFrame->data("raw", self)->pixels), pixel_length) == -1)
  {
    MonocularCamera_e_OUT_OF_MEM_detail d;
    snprintf(d.message, sizeof(d.message), "unable to allocate frame memory");
    CODEL_LOG_WARNING(d.message);
    return MonocularCamera_e_OUT_OF_MEM(&d, self);
  }

  ImageFrame->data("compressed", self)->width = cap->get(cv::CAP_PROP_FRAME_WIDTH);
  ImageFrame->data("compressed", self)->height = cap->get(cv::CAP_PROP_FRAME_HEIGHT);
  ImageFrame->data("compressed", self)->bpp = 3;
  ImageFrame->data("compressed", self)->compressed = true;
  if (genom_sequence_reserve(&(ImageFrame->data("compressed", self)->pixels), pixel_length) == -1)
  {
    MonocularCamera_e_OUT_OF_MEM_detail d;
    snprintf(d.message, sizeof(d.message), "unable to allocate frame memory");
    CODEL_LOG_WARNING(d.message);
    return MonocularCamera_e_OUT_OF_MEM(&d, self);
  }

  return MonocularCamera_wait;
}

/** Codel camera_wait of activity CameraPublish.
 *
 * Triggered by MonocularCamera_wait.
 * Yields to MonocularCamera_pause_wait, MonocularCamera_wait,
 *           MonocularCamera_pub.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT.
 */
genom_event
camera_wait(bool started, const genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return MonocularCamera_pub;
}

/** Codel camera_publish of activity CameraPublish.
 *
 * Triggered by MonocularCamera_pub.
 * Yields to MonocularCamera_wait.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT.
 */
genom_event
camera_publish(const MonocularCamera_CameraInfo *info,
               const MonocularCamera_ImageFrame *ImageFrame,
               const genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return MonocularCamera_wait;
}
