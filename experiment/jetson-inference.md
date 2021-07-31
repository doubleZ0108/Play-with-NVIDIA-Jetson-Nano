# Nano跑通jetson-inference

> 📦Github Repo
>  [GitHub - dusty-nv/jetson-inference: Hello AI World guide to deploying deep-learning inference networks and deep vision primitives with TensorRT and NVIDIA Jetson.](https://github.com/dusty-nv/jetson-inference)

## 填坑
- [x] 推荐把整个git仓库都迁移到gitee再进行clone
	- [x] clone的时候记得加上`—recursive`命令，或是后续再执行`git submodule update --init`
	- [x] ⚠️还要把`.gitmodules`中的repo源也换到gitee，主要是`pytorch-segmentation`有170M
- [x] 最终主要参考的是这位大佬的实践：[笔记（八）Jetson Nano 跑通 jetson-inference_SWorld-CSDN博客](https://blog.csdn.net/baidu_26678247/article/details/109025873)
	- [x] 在官方下载网络和pytorch的绿色界面可以都直接`skip`
- [x] 暂时只跑通了Classify
	- [ ] Detection还是会有问题
	- [ ] 主要是报`custom xxx`的问题暂未解决

## Resources
- 国内源：
	- [关于NV Jetson 产品运行jetson-inference出现问题的终极解决办法](https://mp.weixin.qq.com/s?__biz=MjM5NTE3Nzk4MQ==&mid=2651234503&idx=1&sn=1e513c3af55382b640dbf3d582af4608&chksm=bd0e74558a79fd43dd2a6f7b1034ebd9b47b7ac191e2d87a93b0e92558fd356b6ce4c1cb7065&scene=21#wechat_redirect)    
	- [Jetson-inference国内下载终极解法](https://blog.csdn.net/qq_34045801/article/details/106697986)
	- 跑通bp：[笔记（八）Jetson Nano 跑通 jetson-inference_SWorld-CSDN博客](https://blog.csdn.net/baidu_26678247/article/details/109025873)
	- [AI学习库的安装jetson-inference（国内详细教程） - Yimiu - 博客园](https://www.cnblogs.com/vcan123/p/13269218.html)