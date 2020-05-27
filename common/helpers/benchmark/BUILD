cc_binary(
    name = "bench_sign",
    srcs = ["bench_sign.c"],
    copts = [],
    deps = [
        "//common/helpers:sign",
    ],
)

cc_binary(
    name = "bench_pow",
    srcs = ["bench_pow.c"],
    copts = [],
    deps = [
        "//common/helpers:digest",
        "//common/helpers:pow",
        "//common/trinary:flex_trit",
        "//common/trinary:trit_tryte",
    ],
)
