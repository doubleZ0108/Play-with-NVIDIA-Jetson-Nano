# Nano跑通Yolov3

- 调用摄像头识别：[Jetson nano之pytorch 深度学习_whujk的博客-CSDN博客](https://blog.csdn.net/whujk/article/details/106469860)
- Yolov3系列最佳实践：[GitHub - doubleZ0108/IDEA-Lab-Summer-Camp: ZJU IDEA Lab Summer Camp](https://github.com/doubleZ0108/IDEA-Lab-Summer-Camp)

```bash
# 图片
./darknet detect cfg/yolov3.cfg yolov3.weights data/test.jpg

# 摄像头
./darknet detector demo cfg/coco.data cfg/yolov3.cfg yolov3.weights "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=1280, height=720, format=NV12, framerate=30/1 ! nvvidconv flip-method=2 ! video/x-raw, width=1280, height=720, format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink"

# 视频(暂时未成功)
./darknet detecte cfg/yolov3.cfg yolov3.weights -thresh 0.35 -dont_show data/test.mp4 -i 0 -out_filename results.avi

```

![](https://doublez-site-bed.oss-cn-shanghai.aliyuncs.com/img/20210112173502.png)

![](https://doublez-site-bed.oss-cn-shanghai.aliyuncs.com/img/20210112173515.png)