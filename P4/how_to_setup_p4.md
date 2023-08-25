# 如何启动P4

## 程序目录
/root/bf-sde-8.9.1/pkgsrc/p4-examples/programs/

## 每次开机需要加载驱动
./install/bin/bf_kdrv_mod_load $SDE_INSTALL/

## 配置环境变量
export SDE=/root/bf-sde-8.9.1
export SDE_INSTALL=/root/bf-sde-8.9.1/install
export PATH=$PATH:$SDE_INSTALL/bin

## 编译p4项目
cd ./bf-sde-8.9.1/pkgsrc/p4-build
./configure --prefix=$SDE_INSTALL --with-tofino P4_NAME=simple_switch P4_PATH=/root/bf-sde-8.9.1/pkgsrc/p4-examples/p4_16_programs/simple_switch/simple_switch.p4 P4_VERSION=p4-16 --enable-thrift
make
make install

## 产生配置文件
cd ./bf-sde-8.9.1/pkgsrc/p4-examples
./configure --prefix=$SDE_INSTALL
make
make install

## 配置流表
root@localhost:~/bf-sde-8.9.1# ./run_bfshell.sh -f lvjo40g.txt

## 运行
cd ./bf-sde-8.9.1
./run_switchd.sh -p basic_zsw



