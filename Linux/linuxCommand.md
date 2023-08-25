# linux 命令



| 命令                                         | 功能               |
| ------------------------------------------- | ------------------ |
| grep -e mysql -e 999                        | 搜索两个关键字       |
| ctrl+c                                      | kill               |
| ctrl+z                                      | stop               |
| lsof -i:端口号                               | 查询端口占有的进程    |
| kill -9 PID                                 | 杀死进程            |
| tar -xvf file.tar                           | 解压               |
| tar -cvf file.tar path/to/directory_or_file | 压缩               |
|                                             |                    |


查看网关地址
ip route | grep default

新建一个hushlogin文件，屏蔽掉登录提示
touch ~/.hushlogin 

修改ubuntu主机名称
运行下面的命令，然后替换主机名称
sudo vim /etc/hostname
sudo vim /etc/hosts