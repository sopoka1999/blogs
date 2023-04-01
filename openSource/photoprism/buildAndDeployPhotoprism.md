# 二次开发和部署Photoprism
## 1. 介绍
想弄一个照片管理系统，网上查看了很多关于类似资料，最后选择了Photoprism。大部分人都是选择直接采用docker-compose部署，但是我想定制自己的Photoprism，于是不得不学习编译和部署方法了。

官方文档：https://docs.photoprism.app/

github 地址：https://github.com/photoprism/photoprism
## 2.依赖
1. docker
2. docker-compose
3. git
4. make
   
## 2. 创建工程
先fork官方的项目，便于自己部署和更新，为了避免一些报错，运行：
``` bash
git config --global core.autocrlf false
```

然后进入自己的工作目录，下载源码：
``` bash
cd workspace
git clone git@github.com:photoprism/photoprism.git
cd photoprism
```

## 3. 安装镜像并启动
这里默认采用`docker-compose.yml`作为配置文件，记得修改数据库密码
```
make docker-build
docker compose up
```

## 4. 安装镜像依赖并编译项目
1. 进入容器 `make terminal`
2. 安装依赖 `make dep`
3. 编译前端和后端
``` bash
make build-js
make build-go
```
4. 启动项目
```
./photoprism start
```

## 5.部署
在需要配置的电脑上执行相同的操作。需要更新就执行`git pull` 并重新编译。只有源码修改的情况下需要编译，其他情况下启动容器，并执行`./photoprism start` 即可。