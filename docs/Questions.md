# grpcDemo
## 踩坑记录

### grpc_extra_deps
最新一期release把grpc中一些外部扩展库的依赖从原包的grpc_deps中抽离了出来，其中包括`protobuf`相关的依赖，所以依赖引入需要通过这种方式：
```
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/f99dfed5a79f2cb56c2f1893a64776b11d80e622.tar.gz",
    ],
    strip_prefix = "grpc-f99dfed5a79f2cb56c2f1893a64776b11d80e622",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

# issue#20511
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()
```

### rules_proto
bazel官方提供的rules_proto库不支持grpc协议的proto编译，导致service结构无法解析输出，需要使用第三方的rules_proto库支持：
https://github.com/stackb/rules_proto

### 第三方插件rules_proto问题
由于新版本的grpc，把一些插件移动了位置，导致rules_proto依赖寻找报错，已有网友提交pr修复，目前未被合并，
故无法使用新版本的rules_proto对proto文件进行编译，详情：https://github.com/stackb/rules_proto/issues/108

### envoy自签名证书，chrome不通过
访问：chrome://flags/#allow-insecure-localhost，把`Allow invalid certificates for resources loaded from localhost.`这
一项启用，就可以正常访问envoy

### webpack-dev-server绑定端口异常
docker容器中绑定的ip和端口，一开始无法在宿主机访问。原因是webpack配置写死了127.0.0.1，改为0.0.0.0解决。
关于127.0.0.1和0.0.0.0的区别：https://juejin.im/post/5d258b6ae51d454f73356dcf

### GRPC拿到的客户端ip是Envoy容器IP
在Envoy配置中设置`use_remote_address`字段即可透传真实客户端IP。

### docker-compose下启动顺序不可控导致服务器初始化时db不可用
解决方案很多：
1. https://www.cnblogs.com/wang_yb/p/9400291.html
2. https://www.jianshu.com/p/9446f210e327

最终还是通过修改服务器逻辑解决：初始化时如果连接失败，则在下一次发起db请求时，重新尝试连接。