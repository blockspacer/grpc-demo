package(default_visibility = ["//visibility:public"])

cc_library(
    name = "user_entitiy",
    srcs = ["UserEntity.cpp"],
    hdrs = ["UserEntity.h"],
    deps = [
        "//server/mysql:mysql_conn",
        "//server/encryption:bcrypt",
        "//server/encryption:md5",
    ],
)
