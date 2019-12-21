# 运行指引
## 依赖环境
1. docker&docker-compose

## 设置本地运行服务不检查HTTPS证书（Chrome）
> 由于是自签名证书，所以浏览器会不信任，需要开启本地服务绕过证书检查的步骤
1. 访问`chrome://flags/#allow-insecure-localhost`
2. 设置`Allow invalid certificates for resources loaded from localhost.`项为`Enabled`

## 运行
```
$ cd /path/of/project && docker-compose up
```

## 访问
浏览器输入路径：`https://127.0.0.1:8081`