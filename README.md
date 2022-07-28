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

Example bitcoin-init-list usage (paths snipped):

``$ clang-tidy --load=build/libbitcoin-tidy.so -checks='-*,bitcoin-init-list' test_desig_init.cpp -- -std=c++17``

```
2 warnings generated.
test_desig_init.cpp:31:19: warning: Designated initializer for struct A::Options contains nested object of type struct HasNoDefault with unitialized member of type int [bitcoin-init-list]
        A::Options{
                  ^
test_desig_init.cpp:31:19: warning: Designated initializer for struct A::Options has uninitialized member of type unsigned int [bitcoin-init-list]
```

### Caveats:

The clang/clang-tidy libs are not ABI safe, so the clang-tidy runtime version
must be the same as the headers used to build the plugin.
