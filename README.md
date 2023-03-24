



[ACM模版](https://github.com/csu-czh/blogs/blob/main/ACM/ACMTemplate.md)

[个人书签](https://github.com/csu-czh/blogs/blob/main/others/PersonalBookmark.md)



计划：
1. 搭建自己的密码管理服务器 
2. 搭建自己的邮箱聚合服务器 
3. 搭建自己的文件下载服务器（或者nas）
4. 搭建私人vpn
5. express





千万删掉index.html中的  <meta http-equiv="Content-Security-Policy" content="upgrade-insecure-requests">

不然静态资源的访问都会走https



shell 脚本开头必须加这个，在命令行上调用不会出错，但是一些系统程序，例如服务调用时，会出错

\#!/bin/sh



只有那种阻塞的进程才能作为服务调用
