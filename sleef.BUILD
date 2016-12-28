cc_library(
    name = "sleef-lib",
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
        "-xc++",
        "-std=c++14",
        "-ffp-contract=off",
        # TODO: This should depend on CPU architecture.
        "-DENABLE_SSE2",
    ],
    # TODO: More restrictive visibility setting.
    visibility = ["//visibility:public"],
)
