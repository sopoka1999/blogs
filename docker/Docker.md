Docker

安装

https://www.runoob.com/docker/macos-docker-install.html





1.  运行以下命令将镜像保存到一个 tar 文件中：

    ```
    docker save -o /path/to/save/image.tar image-name
    ```

    其中，`/path/to/save/image.tar` 是您要保存镜像的文件路径和名称，而 `image-name` 则是您要保存的 Docker 镜像的名称或 ID。

2.  该命令会将镜像打包为 tar 文件，并将其保存到指定的路径中。

如果您想要还原保存的 Docker 镜像，请使用 `docker load` 命令加载并还原该镜像。例如：

```
docker load -i /path/to/save/image.tar
```

docker ps 查看所有的镜像
docker exec -it my_container bash 进入镜像命令行