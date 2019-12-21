# package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = ["server.cpp"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:server_grpc_lib",
        "mysql_conn"
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
        "lib/libmysqlclient.20.dylib",
        "lib/libmysqlclient.dylib"
    ],
    deps = [],
)