import genomix
import os

LIB_PATH = os.environ.get("DRONE_VV_PATH")
MODULE_PATH = os.path.join(LIB_PATH, "lib/genom/pocolibs/plugins", "MonocularCamera.so")
handle = genomix.connect("localhost:8080")

print("Module path: {}".format(MODULE_PATH))
camera = handle.load(MODULE_PATH)

camera.set_device("/dev/video0")
camera.set_resolution(640, 480)

# Debug (Optional)
camera.set_debug(1)
camera.show_image_frames(1)

# To start the camera
camera.start_camera()

# To set the compression ration
camera.set_compression(50)  # 50%

# To set the intrinsics and extrinsics
camera.set_instrinsics()  # Only after this, the instrincs port will be available
camera.set_extrinsics()  # Only after this, the extrinsics port will be available

# To get the image
image = camera.Frame("raw")  # raw image
image = camera.Frame("compress")  # compressed image
intrinsics = camera.Intrinsics()  # camera intrinsics
extrinsics = camera.Extrinsics()  # camera extrinsics

# To pause / resume camera
camera.pause_camera()
camera.resume_camera()

# To stop the camera
camera.stop_camera()
