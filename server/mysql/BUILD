package(default_visibility = ["//visibility:public"])

config_setting(
    name = "macos",
    values = {"define": "os=macos"},
)

config_setting(
    name = "linux",
    values = {"define": "os=linux"},
)

cc_library(
    name = "mysql_conn",
    srcs = ["Conn.cpp"],
    hdrs = ["Conn.h"],
    deps = ["mysql"],
)

cc_library(
    name = "mysql",
    hdrs = select({
        "//server/mysql:macos": glob(["macos/include/**/*.h"]),
        "//server/mysql:linux": glob(["linux/include/**/*.h"]),
        "//conditions:default": glob(["macos/include/**/*.h"]),
    }),
    includes = select({
        "//server/mysql:macos": ["macos/"],
        "//server/mysql:linux": ["linux/"],
        "//conditions:default": ["macos/"],
    }),
    deps = ["mysql-lib"]
)

cc_library(
    name = "mysql-lib",
    srcs = select({
        "//server/mysql:macos": [
            "macos/lib/libmysqlclient.dylib",
            "macos/lib/libmysqlclient.20.dylib",
        ],
        "//server/mysql:linux": [
            "linux/lib/libmysqlclient.so",
            "linux/lib/libmysqlclient.so.20",
            "linux/lib/libmysqlclient.so.20.3.15",
        ],
        "//conditions:default": [
            "macos/lib/libmysqlclient.dylib",
            "macos/lib/libmysqlclient.20.dylib",
        ]
    }),
    deps = [],
)
