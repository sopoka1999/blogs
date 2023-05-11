# nginx 指导

## 1. ubuntu 20.04安装nginx

```
sudo apt install nginx
sudo systemctl start nginx
sudo systemctl enable nginx
sudo systemctl status nginx
sudo systemctl restart nginx
```

## 2. 修改nginx配置文件
vim /etc/nginx/nginx.conf

sudo systemctl reload nginx

注意：一定要加上user root ，不然很可能没有访问权限
nginx的错误日志位于：/var/log/nginx/error.log


```
user root;
worker_processes auto;
http {
    include       mime.types;
    default_type  application/octet-stream;
    server {
        listen 80;
        server_name a.qxme.com;
        return 301 https://$host$request_uri;
    }
    server {
        listen 443 ssl;
        server_name a.qxme.com;

        ssl_certificate /etc/nginx/ssl/a.qxme.com_bundle.pem;
        ssl_certificate_key /etc/nginx/ssl/a.qxme.com.key;
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers 'TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384';

        # 前端项目配置
        location / {
            root /root/chatGPT/chatgpt;
            index index.html index.htm;
            try_files $uri $uri/ /index.html;
        }

        # 后端项目配置
        location /api {
            proxy_pass http://127.0.0.1:7001;
            default_type octet-stream;
            proxy_buffering off;
            chunked_transfer_encoding on;
            tcp_nopush on;
            tcp_nodelay on;
            keepalive_timeout 65;
            proxy_set_header Host $host;
            proxy_set_header REMOTE-HOST $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }
   }

   server {
        listen 80;
        server_name qxme.com www.qxme.com;
        return 301 https://$host$request_uri;
    }
    server {
        listen 443 ssl;
        server_name  qxme.com www.qxme.com;

        ssl_certificate /etc/nginx/ssl/qxme.com_bundle.pem;
        ssl_certificate_key /etc/nginx/ssl/qxme.com.key;
        ssl_protocols TLSv1.2 TLSv1.3;

        ssl_ciphers 'TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384';

        # 前端项目配置
        location / {
            root /root/qxmeHomePage;
            index index.html index.htm;
            try_files $uri $uri/ /index.html;
        }
    }
}
events {
    worker_connections 1024;
}
```