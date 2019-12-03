# IOTA common library 

# Build via Bazel 

```shell
bazel build -- //... -//mobile/...
```

# Build via CMake

```shell
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=. -DTRINARY_TEST=ON ..
make -j8 && make test
```
