# ns3-lec-project
##一、以Hello-simulator.cc为示例，并在新的要求下完成任务用命令行读入的自己的学号和姓名参数以及输出频率，周期性输出姓名和学号，不能使用硬编码
###a.运行结果截图
![webo](http://ww3.sinaimg.cn/mw690/e75b2095gw1f57mgn08efj20kg05ttbx.jpg)
###b.结果分析
  在printhello函数里面定义了两个形参，word和ID，分被传递姓名和学号。两个调用cmd.AddValue将姓名和学号的传递给name变量和ID变量，同时将姓名和学号的值打印在命令行中。
##二、利用unix实用工具wc(word count)统计输出的总次数
###a.运行结果截图
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f57mh64qo2j20k80220su.jpg)
###b.结果分析
  利用命令| grep 20134431筛选出打印在命令行的结果，再利用1>my.txt将运行的结果保存在事先建立好的my.txt文件中。通过命令wc -l my.txt读取指定文件my.txt中的命令行数，输出的值5即为统计的输出的总次数。
##三、利用unix实用工具grep筛选特定信息
###a.运行结果截图
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f57mh605xij20kc01it8q.jpg)
###b.结果分析
  利用命令| grep "+4",可以筛选出第4秒执行的语句，从图中显示的结果可以看出第4秒执行的结果为：name:  zhangwei   ID: 20134431
##四、程序截图 
![weibo](http://ww2.sinaimg.cn/mw690/e75b2095gw1f57mh5s9sgj20fa0bm3zc.jpg)

