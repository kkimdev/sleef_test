cc_binary(
    name = "example",
    srcs = ["example.cpp"],
    copts = [
        "-std=c++14",
        "-I./",
        "-Iexternal/sleef/purec",
        "-Iexternal/sleef/simd",
    ],
    deps = ["@sleef//:sleef"],
)
