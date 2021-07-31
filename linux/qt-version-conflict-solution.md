# Qt版本冲突问题(已解决)

操作系统：macOS Catalina 10.15.7

【报错：**You might be loading two sets of Qt binaries into the same process**】
原因是使用`brew`安装过一遍，`conda`又安装过一遍，两个包重叠使用，使得版本冲突
大致的详细报错如下
```bash
You might be loading **two sets of Qt binaries** into the same process. Check that all plugins are compiled against the right Qt binaries. Export DYLD_PRINT_LIBRARIES=1 and check that only one set of binaries are being loaded.
qt.qpa.plugin: Could not load the Qt platform plugin "cocoa" in "**/anaconda3/envs/face/lib/python3.7/site-packages/cv2/qt/plugins**" even though it was found.
This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.
Available platform plugins are: cocoa, minimal, offscreen, webgl.
```

【解决方法】
我们优先写在conda安装的Qt
```bash
conda uninstall pyqt
conda uninstall qt
```
如果无法卸载，并报一大堆错，请参考[[conda uninstall xxx报错]]

如果有时使用OpenCV的时候还是报这个问题，可以考虑通过降低opencv-python版本解决
```bash
python install opencv-python==4.1.0.25
```

我还更换了opencv环境
```bash
pip uninstall opencv-python
pip install opencv-contrib-python-headless
```