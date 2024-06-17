# 如何启动P4

p4 源码学习
https://github.com/csu-czh/p4c

## 配置环境变量
```
export SDE=/root/bf-sde-8.9.1
export SDE_INSTALL=/root/bf-sde-8.9.1/install
export PATH=$PATH:$SDE_INSTALL/bin
```

## 每次开机需要加载驱动
```
bash /root/bf-sde-8.9.1/install/bin/bf_kdrv_mod_load $SDE_INSTALL/
```

如果下面的语句，代表已经加载了驱动：
```
insmod: ERROR: could not insert module /root/bf-sde-8.9.1/install//lib/modules/bf_kdrv.ko: File exists
```

## 程序目录
/root/bf-sde-8.9.1/pkgsrc/p4-examples/programs/

## 编译p4项目

```
cd /root/bf-sde-8.9.1/pkgsrc/p4-build
./configure --prefix=$SDE_INSTALL --with-tofino P4_NAME=recirculate P4_PATH=/root/bf-sde-8.9.1/pkgsrc/p4-examples/programs/recirculate/recirculate.p4 P4_VERSION=p4-14 --enable-thrift
make
make install
```

## 产生配置文件
每个p4项目必须产生一次配置文件
```
cd /root/bf-sde-8.9.1/pkgsrc/p4-examples
./configure --prefix=$SDE_INSTALL
make
make install
```


## 运行
```
cd /root/bf-sde-8.9.1
./run_switchd.sh -p recirculate
```

## 配置表项
```
cd /root/bf-sde-8.9.1
./run_bfshell.sh -f /root/bf-sde-8.9.1/pkgsrc/p4-examples/programs/recirculate/setport.txt
```



# 注意
1. p4的每个action里面的语句必须并行执行，如果需要按照顺序执行，那么就需要拆分为多个action
ingress和egress 的寄存器不能共享

2. ptfTest.py 为端口开启回环！
  ```
  ./run_p4_tests.sh -t /root/bf-sde-8.9.1/pkgsrc/p4-examples/programs/recirculate/ptf/ -p recirculate
  ```

3. 修改相应的两个出端口
#define EGRESS1 1
#define EGRESS2 2

4. 启动交换机

5. 主机发送一个同步包到交换机
  ``` 
  python3 send_syn.py
  ```

6. 发送udp的流量，开始做实验

