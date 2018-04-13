1.Ubuntu运行
annotation.tar是Ubuntu运行的
参考https://github.com/wkentaro/labelme安装一下labelme
# Ubuntu 14.04 / Ubuntu 16.04
# Python2
# sudo apt-get install python-qt4 pyqt4-dev-tools  # PyQt4
sudo apt-get install python-pyqt5 pyqt5-dev-tools  # PyQt5
sudo pip install labelme
# Python3
sudo apt-get install python3-pyqt5 pyqt5-dev-tools  # PyQt5
sudo pip3 install labelme
安装好后，用labelme进行标注，已经在前几张图中定义好了标签了。你标注的时候在跟我讨论下
标注好后，运行./auto.sh
在此目录下产生label_pic文件夹
2.Windows下matlab运行
data_annotation是matlab脚本
将label_pic拷到data_annotation下，运行annotation.m
产生out_pic文件夹下的语义分割文件