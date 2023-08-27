# 1. ns3笔记
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

卸载ns3
./ns3 clean


ns3 启动包跟踪：
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





请为我解释：
Node: 0, Time: +10s, Local time: +10s, Ipv4GlobalRouting table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         10.1.1.2        0.0.0.0         UG    -      -      -   1
这是一个IPv4全局路由表的记录。

这个表记录了如何将数据包从一个网络发送到另一个网络。它包含了以下几个字段：

Destination: 这是目标网络的IP地址。在这个例子中，目标是 0.0.0.0，这通常表示默认路由，即如果没有其他具体的路由匹配，数据包就会沿这条路由发送。

Gateway: 这是路由器的IP地址，数据包将通过这个路由器发送到目标网络。在这个例子中，网关的IP地址是 10.1.1.2。

Genmask: 这是子网掩码，用于确定目标IP地址的网络部分和主机部分。在这个例子中，子网掩码是 0.0.0.0，这通常与默认路由一起使用。

Flags: 这表示路由的一些属性。在这个例子中，UG 表示这是一个使用网关的上行路由（U表示up，G表示gateway）。

Metric: 这是路由的度量值，用于选择最佳路由。在这个例子中，度量值被省略了。

Ref: 这是路由条目的引用计数，表示有多少个路径正在使用这个路由。在这个例子中，引用计数被省略了。

Use: 这表示该路由已经使用了多少次。在这个例子中，使用次数被省略了。

Iface: 这是数据包将要出去的网络接口。在这个例子中，网络接口是 1。

这个路由表的条目表示所有未匹配其他路由的数据包将通过IP为 10.1.1.2 的网关和网络接口 1 进行发送。