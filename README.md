# AVL Tree Dictionary

A self-balancing binary search tree implemented in C++, along with a dictionary
(key-value map) built on top of it. Keys are `int` and values are `double`.

An AVL tree keeps itself balanced after every insertion and removal, so the tree
never degenerates into a long chain even if keys are inserted in sorted order.
This keeps lookups fast.

## Features

- Insert, search, and remove, all in O(log n)
- Range queries that return every key-value pair between two keys
- In-order, pre-order, and post-order traversals
- Size, height, and emptiness checks
- Returning all keys, values, or entries as vectors
- Copy constructor and assignment operator (deep copy)

## Complexity

| Operation        | Time          |
|------------------|---------------|
| insert           | O(log n)      |
| search / get     | O(log n)      |
| remove           | O(log n)      |
| contains         | O(log n)      |
| get_range        | O(k + log n)  |
| keys / values    | O(n)          |

Here `n` is the number of nodes and `k` is the number of results in a range.

## Files

| File                | Purpose                                          |
|---------------------|--------------------------------------------------|
| `AVLNode.hpp/.cpp`  | A single tree node (key, value, links, height)   |
| `AVL.hpp/.cpp`      | The AVL tree itself                              |
| `Dictionary.hpp`    | Abstract dictionary interface                    |
| `AVLDictionary.hpp/.cpp` | Dictionary backed by the AVL tree           |
| `Pair.hpp`          | Simple key-value pair template                   |
| `main.cpp`          | Test driver that exercises every operation       |

## Building and Running

This project uses C++17. With the included Makefile:

```
make
./myProgram
```

Or compile directly:

```
g++ -std=c++17 main.cpp AVL.cpp AVLNode.cpp AVLDictionary.cpp -o myProgram
```

`make clean` removes the compiled program.

## Notes

- `AVLDictionary::get` returns `-1.0` when a key is not found, since the
  `Dictionary` interface returns a plain `double`. The underlying
  `AVL::search` uses `std::optional<double>` instead, which avoids this
  ambiguity.
- Node heights are cached on each node and updated as the tree changes, so
  balance checks stay O(1) instead of recomputing depth each time.

## Author

Bert Collins
