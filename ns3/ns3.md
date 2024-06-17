# ns3笔记
## 1. 安装ns3
ns3 版本为3.39

配置ns3：
```C++
$ ./ns3 configure --enable-examples --enable-tests
```

编译ns3:
```C++
$ ./ns3 build
```

检查ns3程序是否正确安装（可选）
```C++
$ ./test.py
```

运行ns3示例程序：
```C++
$ ./ns3 run first
```

运行自己的ns3程序：
1. 在ns-allinone-3.39/ns-3.39/scratch 下新建my_program.cc
2. 编译加运行  ./ns3 run my_program2 

清理ns3编译文件

```
./ns3 clean 
```



## 2. ns3 创建新的模块

https://www.nsnam.org/docs/manual/html/new-modules.html

1. 运行脚本创建新模块
    ./utils/create-module.py new-module
2. 配置
    ./ns3 configure --enable-examples --enable-tests
3. 编译
    ./ns3 build
4.  运行
    ./test.py
    
## 3. ns3 启动包跟踪：
```C++
AsciiTraceHelper ascii;
p2p.EnableAsciiAll (ascii.CreateFileStream ("my-routing.tr"));
p2p.EnablePcapAll ("my-routing");
```

得到两组文件：
1. pcap是经过网卡的数据包, 可以通过tcpdump查看
my-routing-0-1.pcap
my-routing-1-1.pcap
my-routing-2-1.pcap
my-routing-3-1.pcap
2. 全局信息事件
my-routing.tr



## 4. 修改静态路由规则
```C++
if(idev->GetNode()->GetId() == 3){
    //czh
    Ptr<Ipv4> ipv4 = idev->GetNode()->GetObject<Ipv4>();
    int32_t interface = ipv4->GetInterfaceForDevice(idev);
    Ipv4Address inIp= ipv4->GetAddress(interface, 0).GetLocal();
    if(inIp != Ipv4Address("10.1.3.2")){    
        // std::cout<<"RouteInput: "<<inIp<<std::endl;
        rtentry->SetGateway(Ipv4Address("10.1.3.1"));
        rtentry->SetOutputDevice(idev->GetNode()->GetDevice(3));
        // std::cout<<"GetGateway : "<<rtentry->GetGateway()<<std::endl;
    }
}
```



### 5. 各个组件在网络的位置

netdevice 和 queue 位于数据链路层，负责缓存管理和流量调度

socket位于传输层，tcp的socket负责拥塞控制和建立端到端的连接，udp的socket只负责发送数据，需要在应用层自己实现拥塞控制。

ipv4Router 位于网络层，负责选择网络路径

