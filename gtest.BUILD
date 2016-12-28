cc_library(
    name = "main",
    srcs = glob(
        [
            "googletest/src/*.cc",
            "googletest/src/*.h",
            "googletest/include/**/*.h",
        ],
        exclude = ["googletest/src/gtest-all.cc"],
    ),
    hdrs = glob([
        "googletest/include/**/*.h",
        "googletest/src/*.h",
    ]),
    copts = [
        "-Iexternal/gtest/googletest",
        "-Iexternal/gtest/googletest/include",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
