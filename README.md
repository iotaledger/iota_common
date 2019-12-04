# IOTA common library  

This is a collection of libraries containing models, utils, and cryptography primitives used in IOTA. It's able to use in a Bazel or CMake project.  

# Using in a Bazel project  

First you need to add `org_iota_common` to your Bazel project in the `WORKSPACE` file like this:

```
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "org_iota_common",
    commit = "6ef2af84950f56c8489623e9672c4ac882bb3961",
    remote = "https://github.com/iotaledger/iota_common.git",
)

git_repository(
    name = "rules_iota",
    commit = "e08b0038f376d6c82b80f5283bb0a86648bb58dc",
    remote = "https://github.com/iotaledger/rules_iota.git",
)

load("@rules_iota//:defs.bzl", "iota_deps")
iota_deps()
```

Then add it to dependencies in the `BUILD` file:  

```
cc_binary(
    name = "my_app",
    srcs = ["my_app.c"],
    deps = [
        "@org_iota_common//common:errors",
        "@org_iota_common//common/model:transaction"],
)
```

# Build and test via Bazel  

```shell
bazel build -- //... -//mobile/...
bazel test -- //... -//mobile/...
```

# Build and test via CMake  

```shell
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=. -DTRINARY_TEST=ON ..
make -j8 && make test
```
