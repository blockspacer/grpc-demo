package(default_visibility = ["//visibility:public"])

load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "server_proto_lib",
    srcs = ["server.proto"],
)

cc_proto_library(
    name = "server_cc_proto_lib",
    deps = [":server_proto_lib"],
)

cc_grpc_library(
    name = "server_grpc_lib",
    srcs = [":server_proto_lib"],
    grpc_only = True,
    deps = [":server_cc_proto_lib"]
)