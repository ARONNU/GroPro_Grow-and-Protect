import argparse
import sys
import time
import datetime

import cv2
from tflite_support.task import core
from tflite_support.task import processor
from tflite_support.task import vision
import utils

def run(camera_id: int, width: int, height: int, num_threads: int,
        enable_edgetpu: bool) -> None:
    """Continuously run inference on images acquired from the camera.

    Args:
        camera_id: The camera id to be passed to OpenCV.
        width: The width of the frame captured from the camera.
        height: The height of the frame captured from the camera.
        num_threads: The number of CPU threads to run the model.
        enable_edgetpu: True/False whether the model is a EdgeTPU model.
    """

    # Path of the TFLite object detection model.
    model_path = "your_model.tflite"

    # Variables to calculate FPS and count objects
    counter, fps, num_objects = 0, 0, 0
    start_time = time.time()

    # Load the model and set up the object detector
    interpreter = tf.lite.Interpreter(model_path=model_path)
    interpreter.allocate_tensors()
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    # Start capturing video input from the camera
    cap = cv2.VideoCapture(camera_id)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)

    # Visualization parameters
    row_size = 20  # pixels
    left_margin = 24  # pixels
    text_color = (0, 0, 255)  # red
    font_size = 1
    font_thickness = 1
    fps_avg_frame_count = 10

    # Continuously capture images from the camera and run inference
    while cap.isOpened():
        success, image = cap.read()
        if not success:
            sys.exit(
                'ERROR: Unable to read from webcam. Please verify your webcam settings.'
            )

        counter += 1
        image = cv2.flip(image, 1)

        # Convert the image from BGR to RGB as required by the TFLite model.
        rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

        # Resize the image to match the model's input shape.
        resized_image = cv2.resize(rgb_image, (input_details[0]['shape'][2], input_details[0]['shape'][1]))

        # Normalize the input image and add a batch dimension
        input_data = np.expand_dims(resized_image, axis=0)
        input_data = (np.float32(input_data) - 127.5) / 127.5

        # Set the input tensor and run inference
        interpreter.set_tensor(input_details[0]['index'], input_data)
        interpreter.invoke()

        # Retrieve the detection results and count the number of objects
        output_data = interpreter.get_tensor(output_details[0]['index'])
        num_objects = utils.count_objects(output_data, 0.5)

        # Draw bounding boxes and labels on input image
        image = utils.visualize(image, output_data, 0.5)

        # Calculate the FPS
        if counter % fps_avg_frame_count == 0:
            end_time = time.time()
            fps = fps_avg_frame_count / (end_time - start_time)
            start_time = time.time()

        # Show the FPS and object count
        fps_text = 'FPS = {:.1f}'.format(fps)
        num_objects_text = 'Objects detected = {}'.format(num_objects)
        text_location_fps = (left_margin, row_size)
        text_location_num_objects = (left_margin, row
