## 1. ssh连接过程

今天我在本机用ssh连接虚拟机，输入ip地址，用户名和密码后，提示需要验证指纹，系统提示了下面的信息：

```
The authenticity of host '172.16.30.128 (172.16.30.128)' can't be established.
ED25519 key fingerprint is SHA256:egmND2sQBiCsUj2nw8vGRr+iMYxnDiOzh4E2WFawWgk.
This key is not known by any other names
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '172.16.30.128' (ED25519) to the list of known hosts.、
```

ED25519为公钥名称，SHA256:egmND2sQBiCsUj2nw8vGRr+iMYxnDiOzh4E2WFawWgk为公钥指纹。

按理说，ssh知道了ip地址，用户名和密码，应该是有了足够的信息来连接远程主机，不需要公钥指纹。在询问了chatgpt之后发现，这是一种防止中间人攻击（Man-in-the-Middle Attack）的措施，以确保连接的安全性和准确性。如果直接通过IP地址和用户名和密码登录远程主机，则存在中间人攻击的风险。攻击者可以劫持通信，窃取带有远程主机密码的数据包。

本地主机在进行SSH连接时，会先向远程主机发送请求，请求远程主机发送公钥。远程主机收到请求后，会将自己的公钥发送给本地主机。本地主机在接收到远程主机发送的公钥后，会使用该公钥对带密码的数据包进行加密，然后将这个数据发送给远程主机。远程主机验证密码后就成功登录了。因此ssh用户需要比较公钥匙指纹和远程主机的公钥指纹是否匹配。**如果不匹配，很可能就是被中间人劫持了通信。**

公钥指纹的作用是提供一个更容易验证公钥的方式。如果让用户去比较公钥，很容易出错。



![b5624f5a37527cf95a15610abdf83f4c](../images/b5624f5a37527cf95a15610abdf83f4c.png)



ubuntu存放公钥的位置：/etc/ssh/

mac存放公钥的位置：~/.ssh/

查看公钥指纹：

``` 
ssh-keygen -l -f /path/to/public/key
```



我们一般使用 PuTTY 等 SSH 客户端来远程管理 Linux 服务器。但是，一般的密码方式登录，容易有密码被暴力破解的问题。所以，一般我们会将 SSH 的端口设置为默认的 22 以外的端口，或者禁用 root 账户登录。其实，有一个更好的办法来保证安全，而且让你可以放心地用 root 账户从远程登录——那就是通过密钥方式登录。

密钥形式登录的原理是：利用密钥生成器制作一对密钥——一只公钥和一只私钥。将公钥添加到服务器的某个账户上，然后在客户端利用私钥即可完成认证并登录。这样一来，没有私钥，任何人都无法通过 SSH 暴力破解你的密码来远程登录到系统。此外，如果将公钥复制到其他账户甚至主机，利用私钥也可以登录。



## 2. 配置私钥登录服务器

下面来讲解如何在 Linux 服务器上制作密钥对，将公钥添加给账户，设置 SSH，最后通过客户端登录。

### 2.1 制作密钥对
首先在服务器上制作密钥对。首先用密码登录到你打算使用密钥登录的账户，然后执行以下命令：

```
[root@host ~]$ ssh-keygen  <== 建立密钥对
Generating public/private rsa key pair.
Enter file in which to save the key (/root/.ssh/id_rsa): <== 按 Enter
Created directory '/root/.ssh'.
Enter passphrase (empty for no passphrase): <== 输入密钥锁码，或直接按 Enter 留空
Enter same passphrase again: <== 再输入一遍密钥锁码
Your identification has been saved in /root/.ssh/id_rsa. <== 私钥
Your public key has been saved in /root/.ssh/id_rsa.pub. <== 公钥
The key fingerprint is:
0f:d3:e7:1a:1c:bd:5c:03:f1:19:f1:22:df:9b:cc:08 root@host
```

密钥锁码在使用私钥时必须输入，这样就可以保护私钥不被盗用。当然，也可以留空，实现无密码登录。

现在，在 root 用户的家目录中生成了一个 .ssh 的隐藏目录，内含两个密钥文件。id_rsa 为私钥，id_rsa.pub 为公钥。



### 2.2 在服务器上安装公钥

键入以下命令，在服务器上安装公钥：

```
[root@host ~]cd .ssh
[root@host .ssh] cat id_rsa.pub >> authorized_keys
```


如此便完成了公钥的安装。为了确保连接成功，请保证以下文件权限正确：

```
[root@host .ssh]$ chmod 600 authorized_keys
[root@host .ssh]$ chmod 700 ~/.ssh
```



###  2.3 设置 SSH，打开密钥登录功能

编辑` /etc/ssh/sshd_config` 文件，进行如下设置：

```
RSAAuthentication yes
PubkeyAuthentication yes
```


另外，请留意 root 用户能否通过 SSH 登录：

```
PermitRootLogin yes
```


当你完成全部设置，并以密钥方式登录成功后，再禁用密码登录：

```
PasswordAuthentication no
```

最后，重启 SSH 服务：

```
[root@host .ssh]$ service sshd restart
```

