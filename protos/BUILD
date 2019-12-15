load("@rules_proto//proto:defs.bzl", "proto_library")

cc_library(
    name = "cc_lib_user_log_proto",
    deps = [":cc_proto_lib_user_log_proto"],
    visibility = ["//src:__pkg__"]
)

cc_proto_library(
    name = "cc_proto_lib_user_log_proto",
    deps = [":cc_user_log_proto"]
)

proto_library(
    name = "cc_user_log_proto",
    srcs = ["server.proto"]
)