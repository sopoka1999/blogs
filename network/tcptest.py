from scapy.all import *


#指定网卡
conf.iface = 'en0'

#创建IP头部，指定源IP和目标IP
ip = IP(src="192.168.10.147", dst="43.143.103.114")

#创建UDP头部，指定源端口和目标端口
udp = UDP(sport=8012, dport=8099)

# 假设你有一个结构体，包含一个整数和一个字符串
my_struct = (32, 8,'Hello'.encode())

# 将结构体转换为二进制数据 32位整数
data = struct.pack('ii5s', *my_struct)
binary = ' '.join(format(byte, '08b') for byte in data)
print(binary)