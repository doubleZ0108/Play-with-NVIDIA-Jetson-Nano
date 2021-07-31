"""detector.py
This script demonstrates how to do real-time object detection with
TensorRT optimized Single-Shot Multibox Detector (SSD) engine.
"""

import sys
import argparse
import cv2
import pycuda.autoinit  # This is needed for initializing CUDA driver
sys.path.append('/home/nano/Developer/TRT-yolov3')    #这里改一下
import numpy as np

from utils.yolo_classes import get_cls_dict
from utils.yolov3 import TrtYOLOv3
#from camera import add_camera_args, Camera
from utils.visualization import open_window, show_fps, record_time, show_runtime
from utils.engine import BBoxVisualization


WINDOW_NAME = 'TensorRT YOLOv3 Detector'
INPUT_HW = (300, 300)
SUPPORTED_MODELS = [
    'ssd_mobilenet_v2_coco'
]


def parse_args():
    """Parse input arguments."""
    desc = ('Capture and display live camera video, while doing '
            'real-time object detection with TensorRT optimized '
            'YOLOv3 model on Jetson Family')
    parser = argparse.ArgumentParser(description=desc)
    parser = add_camera_args(parser)
    parser.add_argument('--model', type=str, default='yolov3-416',
                        choices=['yolov3-288', 'yolov3-416', 'yolov3-608',
                                 'yolov3-tiny-288', 'yolov3-tiny-416'])
    parser.add_argument('--runtime', action='store_true',
                        help='display detailed runtime')
    args = parser.parse_args()
    return args


def loop_and_detect(img, runtime, trt_yolov3, conf_th, vis):
    timer = cv2.getTickCount()
    if img is not None:
        if runtime:
            boxes, confs, clss, _preprocess_time, _postprocess_time,_network_time = trt_yolov3.detect(img, conf_th)
            img, _visualize_time = vis.draw_bboxes(img, boxes, confs, clss)
            time_stamp = record_time(_preprocess_time, _postprocess_time, _network_time, _visualize_time)
            #show_runtime(time_stamp)
        else:
            boxes, confs, clss, _, _, _ = trt_yolov3.detect(img, conf_th)
            img, _ = vis.draw_bboxes(img, boxes, confs, clss)
        fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
        img = show_fps(img, fps)
        cv2.imshow(WINDOW_NAME, img)


def gstreamer_pipeline(
    capture_width=1280,
    capture_height=720,
    display_width=1280,
    display_height=720,
    framerate=60,
    flip_method=0,
):
    return (
        "nvarguscamerasrc ! "
        "video/x-raw(memory:NVMM), "
        "width=(int)%d, height=(int)%d, "
        "format=(string)NV12, framerate=(fraction)%d/1 ! "
        "nvvidconv flip-method=%d ! "
        "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGRx ! "
        "videoconvert ! "
        "video/x-raw, format=(string)BGR ! appsink"
        % (
            capture_width,
            capture_height,
            framerate,
            flip_method,
            display_width,
            display_height,
        )
    )


def main():
    cls_dict = get_cls_dict('coco')
    yolo_dim = 416  # 416 or 608
    trt_yolov3 = TrtYOLOv3('yolov3-tiny-416', (yolo_dim, yolo_dim))

    print('[INFO]  Camera: starting')
    cap = cv2.VideoCapture(gstreamer_pipeline(flip_method=0), cv2.CAP_GSTREAMER)
    open_window(WINDOW_NAME, 1280, 720,'TensorRT YOLOv3 Detector')
    vis = BBoxVisualization(cls_dict)
    if cap.isOpened():
        #window_handle = cv2.namedWindow("CSI Camera", cv2.WINDOW_AUTOSIZE)
        while True:
            ret_val, img = cap.read()
            img=cv2.flip(img,1) 
            loop_and_detect(img, 20, trt_yolov3, conf_th=0.3, vis=vis)
            if cv2.waitKey(1) & 0xFF == ord('q'):
               break
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()


