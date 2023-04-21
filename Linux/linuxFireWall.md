# linux 防火墙配置

Firewalld 和UFW 都是基于 iptables 的前端工具，可以用于管理Linux系统的防火墙规则。它们提供了简单易用的用户界面和命令行工具，使得配置防火墙变得更加容易。个人服务器通过修改iptables来配置自己的防火墙就已经足够了，因此我们关闭所有的防火墙工具，然后添加一些规则。



## 1. 首先清除所有的防火墙配置

### 1.1. 删除iptables所有表项

sudo iptables -F

### 1.2. 关闭Firewalld

要关闭Firewalld并使其在系统重启后仍然保持关闭状态，请按以下步骤操作：

1.  停止Firewalld服务：`sudo systemctl stop firewalld`
2.  禁止Firewalld服务开机自启动：`sudo systemctl disable firewalld`
3.  确认Firewalld服务已经停止：`sudo systemctl status firewalld`

这些命令将停止正在运行的Firewalld服务，禁止它在下一次系统启动时自动启动，并确认它已被停止。如果你需要重新启用防火墙，可以使用`sudo systemctl start firewalld`来启动Firewalld服务，并使用`sudo systemctl enable firewalld`让它在系统重启后自动启动。



### 1.3. 关闭UFW

要关闭UFW并使其在系统重启后仍然保持关闭状态，请按以下步骤操作：

1.  停止UFW服务：`sudo ufw disable`
2.  确认UFW已经停用：`sudo ufw status`

这些命令将禁用正在运行的UFW服务，并确认它已被禁用。如果你需要重新启用防火墙，可以使用`sudo ufw enable`来启用它。



## 2. 配置iptables

打开tcp端口80：

``` shell
iptables -I INPUT 5 -p tcp --dport 80 -j ACCEPT
```

查看iptables规则：

```shell
iptables -L
```

