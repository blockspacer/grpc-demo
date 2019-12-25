# WORKSPACE FILE
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

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()