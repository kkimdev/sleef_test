cc_library(
    name = "sleef",
    srcs = glob([
        "purec/*.h",
        "simd/*.h",
    ]) + [
        "purec/sleefdp.c",
        "purec/sleefsp.c",
        "simd/sleefsimddp.c",
        "simd/sleefsimdsp.c",
    ],
    hdrs = [
        "purec/sleef.h",
        "simd/sleefsimd.h",
    ],
    copts = [
        "-std=gnu11",
        "-DENABLE_SSE2",
        "-ffp-contract=off",
        "-Iexternal/sleef/purec",
        "-Iexternal/sleef/simd",
    ],
    visibility = ["//visibility:public"],
)
