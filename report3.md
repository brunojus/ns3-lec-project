##ns3-lec3-project3
###一、系统日志信息截图（能看到计算机用户名）
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f5ftunfcf9j20k604274z.jpg)
![weibo](http://ww1.sinaimg.cn/mw690/e75b2095gw1f5ftuom030j20nw0ketnc.jpg)

    利用NS_LOG_ALL输出所有的信息
###二、Tracing的两种信道文件（每种信道各有两种）
![weibo](http://ww3.sinaimg.cn/mw690/e75b2095gw1f5ftupw4lkj20e505it9g.jpg)

    利用ASCII tracing输出了两个.tr文件，分别是p2p信道和csma信道；利用PCAP Tracing输出了四个.pcap文件。
###三、PyViz截图
![weibo](http://ww1.sinaimg.cn/mw690/e75b2095gw1f5ftur4mklj20z70dwn6r.jpg)

    利用命令sudo ./waf --run ns3-lec2-project2-1 --vis可得到如上的仿真结果。从仿真结果可以看到，红点不停地在在做匀速直线运动。
    红色的点代表了wifi结点，灰色的点表示p2p结点。
###四、Wireshark查看文件截图
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f5ftus5cj1j20l80hlwmv.jpg)

    利用wireshark工具打开ns3-lec2-project3-1-0-0.pcap文件，可以得到如上图所示的结果。
###五、安装步骤文档
####a.PyViz安装
   在命令行键入如下语句：

    sudo apt-get install python-dev python-pygraphviz python-kiwi python-pygoocanvas python-gnome2 python-rsvg
####b.Wireshark安装
   在命令行键入如下语句：

    sudo apt-get install wireshark
   更改权限：

    #sudo groupadd wireshark
    #sudo chgrp wireshark /usr/bin/dumpcap 
    #sudo chmod 4755 /usr/bin/dumpcap 
    #sudo gpasswd -a zhangwei wireshark 
####c.Gnuplot安装
   在命令行键入如下语句：

    sudo apt-get install gnuplot
