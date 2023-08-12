
#include "acMonocularCamera.h"

#include "MonocularCamera_c_types.h"

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
ShowFrames(bool show_cv_frames, bool *show_frames,
           const genom_context self)
{
  *show_frames = show_cv_frames;
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
  strncpy(device, device_id, sizeof(device));
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
