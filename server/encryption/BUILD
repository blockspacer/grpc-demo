package(default_visibility = ["//visibility:public"])

cc_library(
    name = "md5",
    srcs = ["Md5.cpp"],
    hdrs = ["Md5.h"],
)

cc_library(
    name = "bcrypt",
    srcs = ["bcrypt/bcrypt.c"],
    hdrs = ["bcrypt/bcrypt.h"],
    deps = ["crypt_blowfish"]
)

cc_library(
    name = "crypt_blowfish",
    srcs = glob(["bcrypt/crypt_blowfish/*.c"]),
    hdrs = glob(["bcrypt/crypt_blowfish/*.h"])
)