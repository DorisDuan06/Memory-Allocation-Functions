# Memory-Allocation-Functions
This project implememted __malloc()__, __free()__, __realloc()__ and __memcheck()__ in C.

In __AVL.c__, it takes the address, size of the allocated, freed or reallocated memories, creating/deleting nodes in a AVL tree or changing the node information.

In __traverse.c__, it has a `traverse_xx()` function for each memory allocation function (`realloc537()` uses `traverse_free()`) to go through each node in the AVL tree and check if a memory request is valid.

In __537malloc.c__, it includes  `malloc537()`, `free537()`, `realloc537()` and `memcheck537()` four functions. When they are called, they will call their relative `traverse_xx()` functions to go through the AVL tree and check validations. As for `malloc537()`, in addition to actually allocating the memory by calling `malloc()`, it will record the address and size for the memory that is allocated in the heap. It will get the starting address from the return value from `malloc()` and the size from the size parameter. It will check the size parameter for zero length and report as WARNINGS; For `realloc537()`, if ptr is NULL, then it follows the specification of `malloc537()` above. If size is zero and ptr is not NULL, then it follows the specification of `free537()` above. Otherwise, in addition to changing the memory allocation by calling `realloc()`, it will first check to see if address = ptr, and removes that node, then adds a new one where address is the return value from `realloc()` and size is the memory size; `memcheck537()` checks to see the address range specified by address ptr and length size are fully within a range allocated by `malloc537()` and memory not yet freed by `free537()`. When an error is detected, then print out a detailed and informative error message and exit the program (with a -1 status).


## Different WARNINGS and ERRORS:

### malloc537()
#### WARNINGS:
1. Allocate memory of zero length.
#### ERRORS:
1. `malloc()` failure.
---
### free537()
#### ERRORS:
1. Free memory that has not be allocated with `malloc537()`.
2. Free memory that is not the first byte of the range of memory that was allocated.
3. Free memory that was previously freed (double free).
---
### realloc537()
#### WARNINGS:
1. Reallocate memory of zero length.
#### ERRORS:
(When need to free memory, same with `free537()`)
