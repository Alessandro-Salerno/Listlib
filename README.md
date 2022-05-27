# Listlib
Listlib is a simple, unsafe, slow and easy to use library that implements a heap-allocated vector of any type.
It currently doesn't work on Linux for some reason, but it works on macOS and Windows.

## Compiling the library
```
git clone https://github.com/Alessandro-Salerno/Listlib
make listlib
```

## How to use
```c
// Include Liblist
#include "Listlib/include/listlib.h"

// Include standard library
#include <stdio.h>


int main() {
    list_t l = LIST(int, 15);

    // Push items onto the list
    LIST_PUSH(l, 10);
    LIST_PUSH(l, 20);
    LIST_PUSH(l, 30);

    // Should print 20
    int x = LIST_GET(l, 1, int);
    printf("%d", x);

    // Delete the list once you're done
    LIST_DELETE(l);
}
```

## Compiling programs that use the library
To use the library, you have to link the static archive file with your code.
To do so, just add `Listlib/bin/listlib.a` to your command.
