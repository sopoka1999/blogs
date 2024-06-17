sudo tcpdump -i ens4f0 tcp port 8091 

sudo tcpdump -i ens4f0 udp



指定主机：host [ip]

指定端口：port

```
from scapy.all import *


#指定网卡
conf.iface = 'en0'

#创建IP头部，指定源IP和目标IP
ip = IP(src="192.168.10.147", dst="43.143.103.114")

#创建UDP头部，指定源端口和目标端口
udp = UDP(sport=8012, dport=8099)

# 假设你有一个结构体，包含一个整数和一个字符串
my_struct = (123, 123,'Hello')

# 将结构体转换为二进制数据
data = struct.pack('i5s', *my_struct)
print(data)
#组合成一个完整的IP/UDP包
<!-- packet = ip/udp/data -->

#发送包
<!-- send(packet) -->
```





TCP（Transmission Control Protocol）头部是变长，具体大小和数据偏移有关

TCP 头部的基本结构包括以下字段：

1.  **源端口和目的端口**（各占用 16 位）
2.  **序列号**（32 位）
3.  **确认号**（32 位）
4.  **数据偏移（或头部长度）**（4 位）
5.  **保留位**（6 位）
6.  **标志位**（6 位，如 SYN, ACK, FIN 等）
7.  **窗口大小**（16 位）
8.  **校验和**（16 位）
9.  **紧急指针**（16 位）