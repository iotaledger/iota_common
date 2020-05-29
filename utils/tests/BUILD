cc_test(
    name = "test_bundle_miner",
    timeout = "long",
    srcs = ["test_bundle_miner.c"],
    deps =
        [
            "//common/crypto/iss:normalize",
            "//common/trinary:trit_tryte",
            "//common/trinary:trits",
            "//common/trinary:tryte",
            "//utils:bundle_miner",
            "@unity",
        ],
)

cc_test(
    name = "test_merkle",
    timeout = "long",
    srcs = ["test_merkle.c"],
    deps =
        [
            "//common/trinary:trit_tryte",
            "//utils:merkle",
            "@unity",
        ],
)

cc_test(
    name = "test_input_validators",
    timeout = "short",
    srcs = ["test_input_validators.c"],
    deps =
        [
            "//utils:input_validators",
            "@unity",
        ],
)

cc_test(
    name = "test_handles_lock",
    timeout = "short",
    srcs = ["test_handles_lock.c"],
    deps =
        [
            "//utils/handles:lock",
            "//utils/handles:thread",
            "@unity",
        ],
)

cc_test(
    name = "test_logger",
    timeout = "short",
    srcs = ["test_logger.c"],
    deps =
        [
            "//utils:logger_helper",
            "@unity",
        ],
)
