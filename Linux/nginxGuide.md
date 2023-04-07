# nginx 指导

## 1. ubuntu 20.04安装nginx

```
sudo apt install nginx
sudo systemctl start nginx
sudo systemctl enable nginx
sudo systemctl status nginx
```

## 2. 修改nginx配置文件
vim /etc/nginx/nginx.conf
sudo systemctl reload nginx

```
user root;
worker_processes auto;

events {
    worker_connections 1024;
}

http {
    include       mime.types;
    default_type  application/octet-stream;

    server {
        listen 80;
        server_name chat.qxme.com;
        return 301 https://$host$request_uri;
    }

    server {
        listen 443 ssl;
        server_name chat.qxme.com;

        root /root/chatGPT/chatgpt;
        index index.html;

        ssl_certificate /etc/nginx/ssl/chat.qxme.com_bundle.crt;
        ssl_certificate_key /etc/nginx/ssl/chat.qxme.com.key;
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers 'TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384';

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

        location / {
            try_files $uri $uri/ /index.html;
        }

        location ~* \.(jpg|jpeg|gif|png|ico|css|js|pdf|txt|css)$ {
            expires 30d;
            add_header Cache-Control "public";
        }
    }
}
```