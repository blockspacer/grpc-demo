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

### rules_proto更新延迟
由于新版本的grpc，把一些插件移动了位置，导致rules_proto依赖寻找报错，已有网友提交pr修复，目前未被合并，
故无法使用新版本的rules_proto对proto文件进行编译，详情：https://github.com/stackb/rules_proto/issues/108

### grpc官方支持
查阅bazel官方文档，从一个很不起眼的QA找到bazel给grpc官方提的issue，顺藤摸瓜找到grpc官方提供的proto编译插件

### envoy自签名证书，chrome不通过
访问：chrome://flags/#allow-insecure-localhost，把`Allow invalid certificates for resources loaded from localhost.`这
一项启用，就可以正常访问envoy

### webpack-dev-server绑定端口异常
docker容器中绑定的ip和端口，一开始无法在宿主机访问。原因是webpack配置写死了127.0.0.1，改为0.0.0.0解决。