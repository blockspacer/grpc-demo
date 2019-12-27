# 前端请求封装
> 使用protobuf最难受的就是请求对象的配置，所以这里对grpc请求做了通用化封装。

## 使用指引
proto中所有接口的定义应遵循：`xxRequest`/`xxResponse`的命名规范  
例如login接口，在proto中，应该封装成：
```
// request
message LoginRequest {
  string user = 1;
  string password = 2;
  string channel = 3;
}

// response
message LoginResponse {
  uint32 ret_code = 1;
  uint32 uid = 2;
  string token = 3;
}
```
相应的，在前端的调用只需要执行如下代码：
```javascript
const login = (user, password, channel) => {
  return Request.send('Login', {
    user,
    password,
    channel
  });
}
```

## 封装实现代码
https://github.com/Calvin-cn/grpc-demo/blob/master/client/src/libs/request.js