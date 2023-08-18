# This script is not tested but provides a general idea of how to use the camera module
package require genomix
package require env

set LIB_PATH $env(DRONE_VV_PATH)
set MODULE_PATH [file join $LIB_PATH "lib/genom/pocolibs/plugins" "MonocularCamera.so"]
set handle [genomix connect "localhost:8080"]

puts "Module path: $MODULE_PATH"
$handle load $MODULE_PATH

camera::set_device "/dev/video0"
camera::set_resolution 640 480

# Debug (Optional)
camera::set_debug 1
camera::show_image_frames 1

# To start the camera
camera::start_camera

# To set the compression ration
camera::set_compression 50 ;# 50%

# To set the intrinsics and extrinsics
camera::set_intrinsics ;# Only after this, the instrincs port will be available
camera::set_extrinsics ;# Only after this, the extrinsics port will be available

# To get the image
set image [camera::Frame "raw"] ;# raw image
set image [camera::Frame "compress"] ;# compressed image
set intrinsics [camera::Intrinsics] ;# camera intrinsics
set extrinsics [camera::Extrinsics] ;# camera extrinsics

# To pause / resume camera
camera::pause_camera
camera::resume_camera

# To stop the camera
camera::stop_camera