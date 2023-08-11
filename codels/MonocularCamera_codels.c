
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
  /* skeleton sample: insert your code */
  /* skeleton sample */ return genom_ok;
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
  /* skeleton sample: insert your code */
  /* skeleton sample */ return genom_ok;
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
  /* skeleton sample: insert your code */
  /* skeleton sample */ return genom_ok;
}


/* --- Function set_device ---------------------------------------------- */

/** Codel SetDevice of function set_device.
 *
 * Returns genom_ok.
 */
genom_event
SetDevice(const char device[128], or_sensor_frame *image_frame,
          const genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return genom_ok;
}


/* --- Function set_resolution ------------------------------------------ */

/** Codel SetResolution of function set_resolution.
 *
 * Returns genom_ok.
 */
genom_event
SetResolution(int16_t width, int16_t height,
              or_sensor_frame *image_frame, const genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return genom_ok;
}
