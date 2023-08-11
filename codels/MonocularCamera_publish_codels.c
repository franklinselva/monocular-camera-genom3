
#include "acMonocularCamera.h"

#include "MonocularCamera_c_types.h"


/* --- Task publish ----------------------------------------------------- */


/* --- Activity publish_data -------------------------------------------- */

/** Codel InitIDS of activity publish_data.
 *
 * Triggered by MonocularCamera_start.
 * Yields to MonocularCamera_pause_start, MonocularCamera_main,
 *           MonocularCamera_ether.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT,
 *        MonocularCamera_e_OPENCV_ERROR,
 *        MonocularCamera_e_BAD_CONFIG.
 */
genom_event
InitIDS(or_sensor_frame *image_frame, or_sensor_intrinsics *intrinsics,
        or_sensor_extrinsics *extrinsics, bool debug,
        const genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return MonocularCamera_pause_start;
}

/** Codel PublishCamera of activity publish_data.
 *
 * Triggered by MonocularCamera_main.
 * Yields to MonocularCamera_main, MonocularCamera_ether.
 * Throws MonocularCamera_e_OUT_OF_MEM,
 *        MonocularCamera_e_BAD_IMAGE_PORT,
 *        MonocularCamera_e_OPENCV_ERROR,
 *        MonocularCamera_e_BAD_CONFIG.
 */
genom_event
PublishCamera(const or_sensor_frame *image_frame,
              const or_sensor_intrinsics *intrinsics,
              const or_sensor_extrinsics *extrinsics,
              const MonocularCamera_ImageFrame *ImageFrame,
              const MonocularCamera_Intrinsics *Intrinsics,
              const MonocularCamera_Extrinsics *Extrinsics, bool debug,
              bool show_frames, const genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return MonocularCamera_main;
}
