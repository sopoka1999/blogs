

# dpdk学习笔记



假设项目名称为dcqcn

项目目录：/home/lyj/dpdk-22.03/examples/dcqcn



在这个项目目录中，build目录是编译出的二进制文件

config是项目配置文件，所有主机必须同步。

​	1. flow_info_test.txt是流文件，flow_id, source_ip, des_ip,  virtual_port_source, virtual_port_des, flow_size, flow_start_time

​	2. ip_addr_info.txt是主机地址文件，第一行是主机0的ip，第二行是主机1的ip， 以此类推



main.c是项目源程序



每次开机需要设置巨页, 以下命令没有输出代表设置成功
```shell
$ cd /home/lyj/dpdk-22.03/usertools
$ sudo ./dpdk-hugepages.py -p 1G --setup 20G
```




## 编译
```shell
$ cd /home/lyj/dpdk-22.03/examples/dcqcn
$ make
```

## 运行
-l参数代表启动的核心，main函数占用一个0核，为主线程

```shell
$ cd /home/lyj/dpdk-22.03/examples/dcqcn/build
$ sudo ./dcqcnsend -l 0,1
```