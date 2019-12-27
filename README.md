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
## 需求功能点
1. 用户注册
2. 用户登录
3. 持久登录态
4. 登录态tab、ip互斥

## 功能设计
### 登录态设计
1. 安全
   - 防伪造：混合加密，部分数据服务端存储
   - 防窃取：传输链路使用https，服务器针对传输数据做充分XSS、SQL安全检查
2. 性能
   - token算法只在生成时执行，其余时候只做比对
   - 使用混合hash算法计算
3. 互斥
   - 登录态信息包含渠道、IP等信息

### 登录态字段构成：
字段名|备注
---|---
uid|用户id，此处简单处理，为db自增ID
loginTime|登录时间，默认过期时间为30分钟
ip|登录ip，发生变更则登录态失效
channel|登录渠道，不同渠道登录态不共享
token|登录态凭证，使用混合算法加密

### DB设计
用户信息表

字段名|类型|是否主键|备注
---|---|---|---
id|INT(11)|Y|AUTO_INCREMENT
user|VARCHAR(100)|N
password|VARCHAR(255)|N

登录态表

字段名|类型|是否主键|备注
---|---|---|---
uid|INT(11)|Y|不做外键
loginTime|VARCHAR(20)|N
ip|VARCHAR(20)|N
channel|VARCHAR(10)|N
token|VARCHAR(100)|N

## 功能实现
### 目录结构
├── README.md
├── WORKSPACE
├── client -- 客户端代码
├── docker -- 执行环境封装
├── docker-compose.yml -- docker-compose配置文件
├── docs -- 文档存储
├── envoy.yaml -- Enovy代理配置
├── protos -- proto文件存储
├── scripts -- 运行时执行脚本存放
└── server -- 服务端代码

# 踩坑记录
https://github.com/Calvin-cn/grpc-demo/blob/master/docs/Questions.md