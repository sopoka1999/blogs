# mysql使用指南

'root'@'%' 和 'root'@'localhost' 在 MySQL 中被视为两个不同的用户。它们具有相同的用户名（root），但它们的主机部分不同。


修改到最低的密码策略
```
SET GLOBAL validate_password.policy = LOW;
```

修改 MySQL 配置文件
在 MySQL 的配置文件中（通常是 my.cnf 或 my.ini），找到以下这一行：

在 `/etc/mysql/mysql.conf.d/mysqld.cnf` 将 `bind-address = 127.0.0.1`将其注释掉或者改为以下内容，以便监听所有 IP 地址：
`bind-address = 0.0.0.0`


修改root密码

```
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'new-password';
```