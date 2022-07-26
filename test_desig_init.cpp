// Copyright (c) 2022 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

struct HasDefault
{
    int val{0};
};

struct A {
    struct Options {
        HasDefault defval;
        unsigned cache_size;
        signed delta;
        bool in_memory = false;
    };
    A(const Options&) {} // unsafe (may have fields uninitialized)
    A(unsigned cache_size, signed delta, bool in_memory = false) {}  // safe, all non-default args are initialized
};


// Test should warn that A::Options::cache_size is uninitialized.
int main() {
    (void)A{
        A::Options{
            .delta = -1,
        },
    };
}
