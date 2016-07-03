#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"


                                                        
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ns3-pro4");		//定义记录组件

int main (int argc, char *argv[])
{
  
   bool verbose = true;		
   uint32_t nWifi1 = 6;                          //wifi1节点数量
   uint32_t nWifi2 = 6;				//wifi2节点数量
   bool tracing = false;

   //LogComponentEnable("ns3-pro4",LOG_LEVEL_ALL); 


  CommandLine cmd;
  cmd.AddValue ("nWifi1", "Number of wifi STA devices", nWifi1);
  cmd.AddValue ("nWifi2", "Number of wifi STA devices", nWifi2);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);

  cmd.Parse (argc,argv);

  // Check for valid number of csma or wifi nodes
  // 250 should be enough, otherwise IP addresses 
  // soon become an issue		//判断是否超过了250个，超过报错 , 原因？
  if (nWifi1 > 250||nWifi2 > 250)
    {
      std::cout << "Too many wifi nodes, no more than 250 each." << std::endl;
      return 1;
    }

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	//启动记录组件
    }

//创建2个wifi网络的 wifista无线终端(6个)，AP接入点(1个)
//创建wifista1无线终端，AP接入点
  NodeContainer wifiStaNodes1;
  wifiStaNodes1.Create (nWifi1);
//创建wifista2无线终端，AP接入点
  NodeContainer wifiStaNodes2;
  wifiStaNodes2.Create (nWifi2);
//wifiAPNodes1,wifiAPNodes2接入点
  NodeContainer wifiApNode1;
  wifiApNode1.Create(1);
  NodeContainer wifiApNode2;
  wifiApNode2.Create(1);

  //创建无线设备于无线节点之间的互联通道，并将通道对象与物理层对象关联
  //确保所有物理层对象使用相同的底层信道，即无线信道
  //AP节点使用
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
   phy.SetChannel (channel.Create ());
   channel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
   //nwifi1使用
  YansWifiChannelHelper channel1= YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy1 = YansWifiPhyHelper::Default ();
  phy1.SetChannel (channel1.Create ());
  channel1.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  //nwifi2使用
  YansWifiChannelHelper channel2= YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy2 = YansWifiPhyHelper::Default ();
  phy2.SetChannel (channel2.Create ());
  channel2.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  
  
  //配置速率控制算法，AARF算法
  //AP节点使用
  WifiHelper wifi = WifiHelper::Default ();
  wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();//没有QoS保障的Mac层机制
  //nwifi1节点使用
  WifiHelper wifi1 = WifiHelper::Default ();
  wifi1.SetRemoteStationManager ("ns3::AarfWifiManager");
  NqosWifiMacHelper mac1 = NqosWifiMacHelper::Default ();
  //nwifi2节点使用
  WifiHelper wifi2 = WifiHelper::Default ();
  wifi2.SetRemoteStationManager ("ns3::AarfWifiManager");
  NqosWifiMacHelper mac2 = NqosWifiMacHelper::Default ();
  
  //配置mac类型为sta模式，不发送探测请求
  //AP节点使用
  Ssid ssid = Ssid ("ns-3-ssid");
  mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));
  //nwifi1节点使用
  Ssid ssid1 = Ssid ("ns-3-ssid");
  mac1.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid1),
               "ActiveProbing", BooleanValue (false));
  //nwifi2节点使用
  Ssid ssid2 = Ssid ("ns-3-ssid");
  mac2.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid2),
               "ActiveProbing", BooleanValue (false));

  //创建无线设备，将mac层和phy层安装到设备上
  //安装AP节点
  //NetDeviceContainer APDevices1;
  //APDevices1 = wifi.Install (phy, mac, wifiAPNodes1);
  NetDeviceContainer staDevices;  
  staDevices = wifi.Install (phy, mac, wifiApNode2);
  //安装nwifi1节点
  NetDeviceContainer staDevices1;  
  staDevices1 = wifi1.Install (phy1, mac1, wifiStaNodes1);
  //安装nwifi2节点
  NetDeviceContainer staDevices2; 
  staDevices2 = wifi2.Install (phy2, mac2, wifiStaNodes2);
  
  //配置AP节点的mac层为AP模式，创建AP设备
  //将wifiAPNodes1节点作为wifiAPNodes1和wifiAPNodes2组成的无线网络的AP节点
  mac.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid));
  NetDeviceContainer apDevices;
  apDevices = wifi.Install (phy, mac, wifiApNode1);
  //配置AP1节点的mac1层为AP1模式，创建AP1设备
  mac1.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid1));
  NetDeviceContainer apDevices1;
  apDevices1 = wifi1.Install (phy1, mac1, wifiApNode1);

  //配置AP2节点的mac2层为AP2模式，创建AP2设备
  mac2.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid2));
  NetDeviceContainer apDevices2;
  apDevices2 = wifi2.Install (phy2, mac2, wifiApNode2);

  //配置移动模型，起始位置,wifi网络的分布
  MobilityHelper mobility; 
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> (); 
  //第一个wifi网络的sta节点位置
  positionAlloc->Add (Vector (10.0, 10.0, 0.0)); 
  positionAlloc->Add (Vector (5.0, 18.66, 0.0)); 
  positionAlloc->Add (Vector (10.0, 27.32, 0.0)); 
  positionAlloc->Add (Vector (20.0, 27.32, 0.0)); 
  positionAlloc->Add (Vector (25.0, 18.66, 0.0)); 
  positionAlloc->Add (Vector (20.0, 10.0, 0.0));
  //第2个wifi网络的sta节点位置
  positionAlloc->Add (Vector (60.0, 10.0, 0.0)); 
  positionAlloc->Add (Vector (55.0, 18.66, 0.0)); 
  positionAlloc->Add (Vector (60.0, 27.32, 0.0)); 
  positionAlloc->Add (Vector (70.0, 27.32, 0.0)); 
  positionAlloc->Add (Vector (75.0, 18.66, 0.0)); 
  positionAlloc->Add (Vector (70.0, 10.0, 0.0));
  //两个Ap节点的位置
  positionAlloc->Add (Vector (15.0, 18.66, 0.0)); 
  positionAlloc->Add (Vector (65.0, 18.66, 0.0));
  mobility.SetPositionAllocator (positionAlloc);      

  //配置STA移动方式，RandomWalk2dMobilityModel，随机游走模型
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 100, 0, 100)));
  mobility.Install (wifiStaNodes1);

  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 100, 0, 100)));
  mobility.Install (wifiStaNodes2);


//配置AP移动方式，ConstantPositionMobilityModel，固定位置模型
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiApNode1);
  mobility.Install (wifiApNode2);

  //已经创建了节点，设备，信道和移动模型，接下来配置协议栈
  InternetStackHelper stack;
  stack.Install (wifiApNode1);
  stack.Install (wifiApNode2);
  stack.Install (wifiStaNodes1);
  stack.Install (wifiStaNodes2);


  //分配IP地址
  Ipv4AddressHelper address;
 //wifi信道
  address.SetBase ("10.1.1.0", "255.255.255.0");
  address.Assign (staDevices);
  address.Assign (apDevices);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  address.Assign (staDevices1);
  Ipv4InterfaceContainer interfaces=address.Assign (apDevices1);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  address.Assign (staDevices2);
  address.Assign (apDevices2);

  //放置echo服务端程序在第二个wifi网络的Ap节点，端口为9
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (wifiApNode1.Get(0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  //回显客户端放在最后的STA节点，指向CSMA网络的服务器，上面的节点地址，端口为9

  UdpEchoClientHelper echoClient (interfaces.GetAddress(0),9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (512));

  //安装其他节点应用程序
  
  ApplicationContainer clientApps1 = 
  echoClient.Install (wifiStaNodes1.Get (nWifi1 - 2));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));

  ApplicationContainer clientApps2 = 
  echoClient.Install (wifiStaNodes1.Get (nWifi1 - 3));
  clientApps2.Start (Seconds (2.1));
  clientApps2.Stop (Seconds (10.0));

  ApplicationContainer clientApps3 = 
  echoClient.Install (wifiStaNodes1.Get (nWifi1 - 4));
  clientApps3.Start (Seconds (2.2));
  clientApps3.Stop (Seconds (10.0));

  ApplicationContainer clientApps4 = 
  echoClient.Install (wifiStaNodes1.Get (nWifi1 - 5));
  clientApps4.Start (Seconds (2.3));
  clientApps4.Stop (Seconds (10.0));

  ApplicationContainer clientApps5 = 
  echoClient.Install (wifiStaNodes1.Get (nWifi1 - 6));
  clientApps5.Start (Seconds (2.4));
  clientApps5.Stop (Seconds (1.0));

  ApplicationContainer clientApps6 = 
  echoClient.Install (wifiStaNodes1.Get(nWifi1 - 1));
  clientApps6.Start (Seconds (2.5));
  clientApps6.Stop (Seconds (10.0));
  
  ApplicationContainer clientApps7 = 
  echoClient.Install (wifiStaNodes2.Get(nWifi1 - 1));
  clientApps6.Start (Seconds (3));
  clientApps6.Stop (Seconds (10.0));
 
  
  
  
 
  //启动互联网络路由
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  if (tracing == true)
    {
      AsciiTraceHelper ascii; 
      phy1.EnableAsciiAll (ascii.CreateFileStream("ns3-le4-project4-1p2p.tr"));
      phy.EnablePcap ("ns3-lec4-project4", staDevices.Get (0));
      phy1.EnablePcap("ns3-lec4-project4",staDevices1.Get(0));
      phy2.EnablePcap("ns3-lec4-project4",staDevices2.Get(0)); 
    }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
