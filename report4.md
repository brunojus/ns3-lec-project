## ns3-lec4-project4
###一、仿真拓扑
![weibo](http://ww4.sinaimg.cn/mw690/e75b2095gw1f5gun0lm3mj20ke0edqcr.jpg)
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f5gv9rgiy3j20hz02d0tu.jpg)

    1.搭建拓扑：搭建了两个wifi网络，每个wifi网络各有6个sta，1个ap;同时用两个wifi网络中的ap节点搭建第三个wifi网络，
      从而实现两个wifi网络通信，而不通过p2p链路通信；
    2.参数配置：配置wifi网络1中的ap为第三个wifi网络的ap节点，并将其作为服务器；设置packetsize为512byte，
      包间隔为100ms；通过六边形边长为10，分别计算每个节点的坐标；
    3.运行仿真：截图如上图所示，一个服务器分别和6个客户端进行通信。其中客户端6位于wifi网络2，客户端1~5位于wifi网络1。
###二、PyViz截图（能看到计算机用户名）
![weibo](http://ww3.sinaimg.cn/mw690/e75b2095gw1f5gun169gdj20yp0eak2q.jpg)
![weibo](http://ww4.sinaimg.cn/mw690/e75b2095gw1f5gun22y9oj20i20ebjtd.jpg)

    PyViz截图如图所示，图二为运行中的拓扑图。
###三、Tracing的两种信道文件（每种信道各有两种）
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f5gun2iq76j20eg06q0t7.jpg)
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f5gv9qi6ruj20k404amyn.jpg)

    如上图所示为生成的Tacing文件。
