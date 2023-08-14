
#include "acMonocularCamera.h"

#include "MonocularCamera_c_types.h"
#include <opencv2/opencv.hpp>
#include "fg3utils/trace_f.h"
#include "fg3utils/macros.h"

/* --- Activity start_camera -------------------------------------------- */

/** Validation codel check_device of activity start_camera.
 *
 * Returns genom_ok.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 * MonocularCamera_e_BAD_IMAGE_PORT, MonocularCamera_e_BAD_CONFIG.
 */
genom_event
check_device(const char device[128], bool started,
             const genom_context self)
{
  if (started)
  {
    CODEL_LOG_ERROR("Camera already started. You cannot start it twice.");
  }

  cv::VideoCapture cap(device);
  if (!cap.isOpened())
  {
    char msg[128];
    snprintf(msg, sizeof(msg), "Failed to open camera device %s", device);
    CODEL_LOG_ERROR(msg);
    MonocularCamera_e_OPENCV_ERROR_detail *d;
    snprintf(d->message, sizeof(d->message), "%s", msg);
    return MonocularCamera_e_OPENCV_ERROR(d, self);
  }

  cap.release();
  return genom_ok;
}

/* --- Function set_debug ----------------------------------------------- */

/** Codel SetDebug of function set_debug.
 *
 * Returns genom_ok.
 */
genom_event
SetDebug(bool is_debug_mode, bool *debug, const genom_context self)
{
  *debug = is_debug_mode;
  return genom_ok;
}

/* --- Function show_image_frames --------------------------------------- */

/** Codel ShowFrames of function show_image_frames.
 *
 * Returns genom_ok.
 */
genom_event
ShowFrames(bool *show_frames, const genom_context self)
{
  *show_frames = true;
  return genom_ok;
}

/* --- Function set_verbose_level --------------------------------------- */

/** Codel SetVerboseLevel of function set_verbose_level.
 *
 * Returns genom_ok.
 */
genom_event
SetVerboseLevel(uint8_t verbose_level, uint8_t *v_level,
                const genom_context self)
{
  *v_level = verbose_level;
  return genom_ok;
}

/* --- Function set_device ---------------------------------------------- */

/** Codel SetDevice of function set_device.
 *
 * Returns genom_ok.
 */
genom_event
SetDevice(const char device_id[128], char device[128],
          const genom_context self)
{
  device = const_cast<char *>(device_id);
  return genom_ok;
}

/* --- Function set_resolution ------------------------------------------ */

/** Codel SetResolution of function set_resolution.
 *
 * Returns genom_ok.
 */
genom_event
SetResolution(int16_t width, int16_t height,
              MonocularCamera_CameraInfo_size_s *size,
              const genom_context self)
{
  size->w = width;
  size->h = height;
  return genom_ok;
}

/* --- Function set_compression ----------------------------------------- */

/** Codel SetCompression of function set_compression.
 *
 * Returns genom_ok.
 */
genom_event
SetCompression(int16_t compression_percent, int16_t *compression_rate,
               const genom_context self)
{
  *compression_rate = compression_percent;
  return genom_ok;
}
