package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = ["server.cpp"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//server/service:user_service"
    ],
)