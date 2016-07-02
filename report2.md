# ns3-lec2-project2
##一、拓扑结构图
###a.网络拓扑1
![weibo](http://ww1.sinaimg.cn/mw690/e75b2095gw1f58ndlfwmwj20f9076wfs.jpg)

        如图所示，建立了三种信道的网络（wifi、p2p、csma），wifi网络中有5个节点，csma网络中有4个节点，两个网络通过p2p信道连接起来。
###b.网络拓扑2
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f58ned179fj20gj06u0u1.jpg)

        如图所示，建立了两种信道的网络（csma1、csma2），csma1网络中有4个节点，csma2网络中有5个节点，两个网络通过p2信道连接起来。
##二、client与server通信结果截图（能看到计算机用户名）
###a.网络拓扑1通信
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f58necfr7kj20kh0aeah9.jpg)

        将wifi网络中的n8,n5,n6,n7分别作为clinet1、2、3、4,将csma网络中的n4作为server。
###b.网络拓扑2通信
![weibo](http://ww3.sinaimg.cn/mw690/e75b2095gw1f58nedysndj20kk0c1tgs.jpg)


        将LAN2网络中的n8,n5,n6,n7分别作为client1、2、3、4，将LAN1网络中的n4作为server。
##三、STA移动模型部分代码截图
![weibo](http://ww1.sinaimg.cn/mw1024/e5334a89gw1f5fu97zt5yj20hs04z76b.jpg)

        移动模型代码如图所示。
