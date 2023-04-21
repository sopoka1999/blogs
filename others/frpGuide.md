# frp使用指南

 使用frp可以进行内网穿透，只需要一台云服务器，我们所有的设备都能被外网访问

参考博客： https://sspai.com/post/52523


## 1. 下载frp

链接：https://github.com/fatedier/frp/releases

服务端和客户端根据自己的系统，下载frp并解压

解压后会有

-   frps
-   frps.ini
-   frpc
-   frpc.ini

服务端保留frps和frps.ini

客户端保留frpc和frpc.ini



## 2. 配置服务端

``` vim frps.ini
vim frps.ini
```

```
[common]
bind_port = 7000
dashboard_port = 7500
token = 12345678
dashboard_user = admin
dashboard_pwd = admin
vhost_http_port = 10080
vhost_https_port = 10443
```

```
./frps -c frps.ini
```

输入ip:7500 就能查看frp的控制面板



## 服务端后台运行

``` 
nohup ./frps -c frps.ini &
```



## 3. 配置客户端

``` 
vim frpc.ini
```



```
[common]
server_addr = x.x.x.x
server_port = 7000
token = 12345678
[rdp]
type = tcp
local_ip = 127.0.0.1           
local_port = 3389
remote_port = 7001  
[smb]
type = tcp
local_ip = 127.0.0.1
local_port = 445
remote_port = 7002
```



```
./frpc -c frpc.ini
```





