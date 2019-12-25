package(default_visibility = ["//visibility:public"])

cc_library(
    name = "user_service",
    srcs = ["UserService.cpp"],
    hdrs = ["UserService.h"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//protos:server_grpc_lib",
        "//server/entity:user_entitiy",
        "//server/utility:utility"
    ],
)