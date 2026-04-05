# Data Structures in C

Low-level implementations of classic data structures in C, with emphasis on memory management, pointer manipulation, ordered storage, and algorithmic efficiency.

This repository explores how core data structures work under the hood through manual implementations, without relying on high-level abstractions.

---

## Overview

This project contains implementations of:

- Sorted singly linked lists
- Doubly linked lists with sentinel node
- Binary Search Trees (BST)
- AVL Trees

The repository also includes practical routines for:

- Ordered insertion
- Traversal
- Search
- Removal
- Frequency counting
- Performance comparison between tree structures

---

## Highlights

### Linked Lists
The list implementations focus on dynamic allocation, pointer updates, and ordered insertion logic.

### Trees
The tree implementations go beyond basic insertion and traversal by also including:

- Word frequency counting from text input
- Alphabetical organization of terms
- Comparison between **Binary Search Tree** and **AVL Tree**
- Execution time and comparison counting for both approaches

This makes the project not only a data structure exercise, but also a practical study of structural trade-offs between unbalanced and self-balancing trees.

---

## Design Principles

- **Manual memory management**
- **Pointer-first implementation**
- **Algorithmic clarity**
- **Ordered data maintenance**
- **Comparison of structural trade-offs**

---

## Time Complexity

### Linked Lists

| Operation | Complexity |
|----------|-----------|
| Insertion (sorted) | O(n) |
| Search | O(n) |
| Removal | O(n) |
| Traversal | O(n) |

### Binary Search Tree (BST)

| Operation | Average | Worst Case |
|----------|--------|-----------|
| Insertion | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

### AVL Tree

| Operation | Complexity |
|----------|-----------|
| Insertion | O(log n) |
| Search | O(log n) |
| Traversal | O(n) |

> AVL trees maintain balance through rotations, ensuring more stable performance than a standard BST in adverse insertion orders.

---

## Why This Repository

This project is useful for strengthening foundations in:

- Data structures
- Low-level programming
- Memory management in C
- Recursive and iterative algorithms
- Performance trade-offs between different structures

It is also a strong base for technical interview preparation and deeper Computer Science study.

---

## Tech Stack

- C
- Dynamic memory allocation
- Pointer manipulation
- File I/O
- Recursive algorithms

---

## Future Extensions

- Removal in BST and AVL
- Red-Black Trees
- Heaps and priority queues
- Hash tables
- Benchmarks with larger datasets
- Generic implementations using `void*`

---

## Author

Lucas Winter
