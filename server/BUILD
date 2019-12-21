# package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = ["server.cpp"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:server_grpc_lib",
        "mysql_conn",
        "md5"
    ],
)

cc_library(
    name = "mysql_conn",
    srcs = ["Conn.cpp"],
    hdrs = ["Conn.h"],
    deps = ["mysql"],
)

cc_library(
    name = "mysql",
    hdrs = glob(["include/**/*.h"]),
    deps = ["mysql-lib"]
)

cc_library(
    name = "mysql-lib",
    srcs = [
        "lib/libmysqlclient.so.20",
        "lib/libmysqlclient.so"
    ],
    deps = [],
)

cc_library(
    name = "md5",
    srcs = ["Md5.cpp"],
    hdrs = ["Md5.h"],
)