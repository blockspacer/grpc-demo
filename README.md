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

# 实现
## 功能
1. 用户注册
2. 用户登录
3. 登录态tab、ip互斥

## 部分细节
1. client到envoy走了HTTPS，envoy使用的自签名证书。
2. 客户端、代理、服务端使用docker部署，docker-compose进行容器管理。
3. 所有代码走的运行时编译，非提前编译好的可执行文件。

# 不足之处
## 安全性
1. XSS过滤
2. SQL注入防范
   - mysql-connector-c++可以使用prepared statement来执行SQL语句
3. 密码存储
   - 当前只使用了md5加盐，为提高安全性，应考虑混合加密的方式
4. envoy和server之间链路没有做加密，在单机部署的情况下是安全的，但对多机集群的情况，还是需要做链路加密。
    
## 封装程度
1. `server.cpp`文件略显臃肿，操作数据库部分可以封装得复用程度更高一些。

## 性能
1. 服务器只使用一个`mysql`连接实例
2. 登录态存储在mysql，对于单点登录的设计来说，存在性能问题，业界方案一般存储在redis等kv高性能持久层。

# 踩坑记录
https://github.com/Calvin-cn/grpc-demo/blob/master/docs/Questions.md