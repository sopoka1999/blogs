sudo tcpdump -i ens4f0 tcp port 8091 

sudo tcpdump -i ens4f0 udp

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