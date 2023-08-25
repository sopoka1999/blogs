# 搭建ChatGPT网站

ubuntu 20.04网络不是很稳定，有时候出现如下报错：

![image-20230320172328465](/Users/chenzihao/Library/Application Support/typora-user-images/image-20230320172328465.png)

解决方法：关闭ipv6和修改dns

通过以下步骤关闭 Ubuntu 中的 IPv6：

1.  打开终端（Terminal）。你可以按下“Ctrl+Alt+T”快捷键来打开终端。
2.  编辑 `/etc/sysctl.conf` 文件，输入以下命令并按回车键：

```
复制代码sudo nano /etc/sysctl.conf
```

1.  在文件末尾添加以下内容：

```
复制代码# Disable IPv6
net.ipv6.conf.all.disable_ipv6 = 1
net.ipv6.conf.default.disable_ipv6 = 1
net.ipv6.conf.lo.disable_ipv6 = 1
```

1.  按下“Ctrl+O”保存更改，然后按下“Ctrl+X”退出编辑器。
2.  输入以下命令以使更改生效：

```
复制代码sudo sysctl -p
```

完成以上步骤后，IPv6 将被禁用。
