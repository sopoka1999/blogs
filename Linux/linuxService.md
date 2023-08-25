# linux 服务管理


## 1. systemctl

systemctl是一个Linux系统服务管理工具，它用于启动、停止、重启、重新加载和查询系统服务的状态。它是systemd系统和服务管理器的主要命令之一，可以管理各种类型的系统服务，包括系统守护进程、网络服务、套接字激活服务等等。通过systemctl，系统管理员可以方便地管理和监控系统服务的运行状态。

### 1.1. 配置服务

编写 systemd 服务单元文件需要以下步骤：

1. 确定服务的名称、描述和要运行的命令
2. 创建服务单元文件，并将其保存在 `/etc/systemd/system/` 目录下
3. 定义服务单元文件中的 `[Unit]` 部分，包括服务的名称、描述和依赖项
4. 定义服务单元文件中的 `[Service]` 部分，包括要运行的命令、用户和组、工作目录等信息
5. 定义服务单元文件中的 `[Install]` 部分，指定服务启动方式


下面是一个简单的示例 `systemd` 服务单元文件，可以作为参考：


```ini
[Unit]
Description=chatgpt

[Service]
Type=simple
User=chenzihao
WorkingDirectory=/home/chenzihao/workspace/chatGPT/chatgptService
ExecStart=pnpm prod
Restart=always

[Install]
WantedBy=multi-user.target
```

⚠️：ExecStart指定命令可以是shell，但是shell头部必须包含 `#!/bin/sh`

⚠️：只有那种阻塞的进程才能作为服务调用，如果一瞬间就运行完毕，那就不能让它作为服务，例如tomcat的`startup.sh`，我们替换为： `ExecStart=./catalina.sh run`

⚠️：在控制台中运行脚本时需要加入 "./" 的原因是，"." 表示当前目录，在没有指定路径的情况下，系统默认只在环境变量 \$PATH 中定义的路径中查找可执行文件。而当前目录通常不在 \$PATH 中，因此需要使用 "./" 显式地告诉系统在当前目录中查找要执行的脚本文件。而运行Unix可执行文件，则先找当前目录，然后找 \$PATH 

⚠️：WorkingDirectory只能指定工作路径，但是当前工具必须采用绝对路径



在这个示例文件中，`[Unit]` 部分定义了服务的名称、描述和依赖项。`[Service]` 部分定义了要运行的命令、用户和组、工作目录以及重启策略。`[Install]` 部分指定了服务启动方式。



完成以上步骤之后，使用 `systemctl` 命令加载并启动服务：

```shell
sudo systemctl daemon-reload
sudo systemctl start chatgpt
```

如果您希望该服务每次系统启动时自动启动，可以运行以下命令：

```shell
sudo systemctl enable chatgpt
```

如果您希望查看该服务的状态，可以运行以下命令：

```shell
sudo systemctl status chatgpt
```

查看服务日志：

```shell
journalctl -u 服务名
fn+方向键可以快速翻阅日志
```



## 1.2. 个人的一些配置文件：

Rust-desk:

```shell
[Unit]
Description=rustdesk

[Service]
Type=simple
WorkingDirectory=/home/chenzihao/workspace/rustdesk-server
ExecStart=/bin/bash -c './hbbs | ./hbbr'
ExecStop=/bin/bash -c 'fuser -k 21119/tcp | fuser -k 21117/tcp'
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target
```



Tomcat:

```shell
[Unit]
Description=tomcat

[Service]
Type=simple
ExecStart=/home/chenzihao/workspace/apache-tomcat-8.5.73/bin/catalina.sh run
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target
```



Frps:

```shell
[Unit]
Description=frps

[Service]
Type=simple
ExecStart=/home/chenzihao/workspace/frp/frp_0.48.0_linux_amd64/frps -c /home/chenzihao/workspace/frp/frp_0.48.0_linux_amd64/frps.ini
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target
```



