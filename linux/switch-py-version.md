# 切换python版本
#创乐 Invix/Linux#

前提条件：
1. linux已经安装好多个版本的python 如2.7 & 3.6
2. linux为Debian系

1. 查看是否有关于Python的候选项 `update-alternatives --display python`，输出 `update-alternatives: 错误: 无 python 的候选项`
2. 建立python的组，并添加Python2和Python3的可选项
```bash
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 2 # 添加Python2可选项，优先级为2
$ sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.6 1 #添加Python3可选项，优先级为1
```
3. 更改自动模式为手动模式
```bash
$ sudo update-alternatives --config python
有 2 个候选项可用于替换 python (提供 /usr/bin/python)。

  选择       路径              优先级  状态
------------------------------------------------------------
* 0            /usr/bin/python2.7   2         自动模式
  1            /usr/bin/python2.7   2         手动模式
  2            /usr/bin/python3.6   1         手动模式
要维持当前值[*]请按回车键，或者键入选择的编号：
```
此时输入`2`即可切换到python3.6
4. 验证：`python --version`


> [Linux下切换Python版本的几种方法 - Feyn - 博客园](https://www.cnblogs.com/feynxd/p/11367806.html)