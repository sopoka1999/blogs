

# dpdk学习笔记

环境：**ubuntu20.04-x86_64**

网卡驱动：MLNX_OFED_LINUX-5.4-3.1.0.0

DPDK版本：dpdk-22.03

假设项目名称为dcqcn

项目目录：/home/lyj/dpdk-22.03/examples/dcqcn





# 安装dpdk

一、下载dpdk22.03,先对dpdk进行编译安装

\1.   我使用的dpdk的版本是dpdk22.03

2.首先先安装依赖

sudo apt-get install python-pyelftools python3-pyelftools -y

3.cd dpdk-22.03

4.对dpdk进行编译 meson build

5.cd build

6.使用ninja命令进行安装

7.sudo ninja install

## 安装驱动

**MLNX_OFED_LINUX-5.4-3.1.0.0-ubuntu20.04-x86_64.tgz**

在系统目录下进行解压并执行sudo ./mlnxofedinstall --dpdk



sudo /etc/init.d/openibd restart



查询驱动版本：

ofed_info -s 



在这个项目目录中，build目录是编译出的二进制文件

config是项目配置文件，所有主机必须同步。

​	1. flow_info_test.txt是流文件，flow_id, source_ip, des_ip,  virtual_port_source, virtual_port_des, flow_size, flow_start_time

​	2. ip_addr_info.txt是主机地址文件，第一行是主机0的ip，第二行是主机1的ip， 以此类推



main.c是项目源程序

sudo LD_LIBRARY_PATH=/usr/local/lib/x86_64-linux-gnu ./dcqcnsend -l 0,1

每次开机需要设置巨页, 以下命令没有输出代表设置成功
```shell
$ cd /home/chenzihao/dpdk-22.03/usertools
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
cd /home/chenzihao/dpdk-22.03/examples/MRQ/build
sudo ./MRQ -l 0 -- --host_id 0
sudo ./MRQ -l 0 -- --host_id 1
sudo ./MRQ -l 0 -- --host_id 2
```