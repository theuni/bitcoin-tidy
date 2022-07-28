clang-tidy plugin for Bitcoin Core

These are checks that are believed to be stable and are intended to be used
by c-i.

### Dependencies:
llvm 14+ headers and clang-tidy 14+ are required, but libs are not.

To install them, build llvm with clang-tools-extra enabled, and:
`make install-llvm-headers install-clang-tidy-headers install-clang-headers`

### Building the plugin:
- cmake -S . -B build
- cmake --build build

### Using the plugin:

Example bitcoin-init-list usage:

``clang-tidy --load=`pwd`/libbitcoin-tidy.so -checks='-*,bitcoin-init-list' ../test_desig_init.cpp -- -std=c++17``

```
1 warning generated.
/home/cory/dev/bitcoin-tidy/build/../test_desig_init.cpp:25:19: warning: Designated initializer with uninitialized member of type: unsigned int [bitcoin-init-list]
        A::Options{
                  ^
```

### Caveats:

The clang/clang-tidy libs are not ABI safe, so the clang-tidy runtime version
must be the same as the headers used to build the plugin.
