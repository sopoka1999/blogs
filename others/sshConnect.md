# ssh连接过程

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



