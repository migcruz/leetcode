# Binary Search Tree (BST)

## **Definition**
A **Binary Search Tree (BST)** is a type of **binary tree** where each node follows the rule:

- The **left child** has a value **less than** the parent.
- The **right child** has a value **greater than** the parent.
- This ordering applies recursively throughout the tree.


## **BST Properties**
1. **Left Child < Parent < Right Child**  
   - Ensures efficient searching and retrieval of values.

2. **Efficiency in Operations**  
   - Searching, insertion, and deletion have a **time complexity of O(log n)** in a balanced BST.
   - Worst-case (unbalanced BST) may degrade to **O(n)**.

3. **Uniqueness of Values**  
   - Typically, BSTs **do not allow duplicate values**.
   - Some variations (like **multisets**) may permit duplicates.


## **Example BST**
```
        6
       / \
      2   8
     / \  / \
    0   4 7  9
       / \
      3   5
```

- The **left subtree** of `8` contains smaller values (`1, 3, 4, 6, 7`).
- The **right subtree** of `8` contains larger values (`10, 13, 14`).

---

## **Common BST Operations**
| Operation | Time Complexity (Balanced BST) |
|-----------|-------------------------------|
| **Search** | O(log n) |
| **Insert** | O(log n) |
| **Delete** | O(log n) |
| **Traversal (Inorder, Preorder, Postorder)** | O(n) |

---

## **Use Cases of BST**
- **Efficient Searching** → Used in databases and indexing systems.
- **Sorting** → Inorder traversal gives sorted elements.
- **Symbol Tables** → Used in compilers and dictionaries for key-value mappings.

---  
# DFS vs. BFS: Depth-First Search vs. Breadth-First Search

## Introduction
- **Depth-First Search (DFS)** explores as deep as possible along one branch before backtracking.
- **Breadth-First Search (BFS)** explores each level of the tree or graph before moving deeper.

## **Tree Example**
Consider the following **binary tree**:
```
       1
      / \
     2   3
    / \
   4   5
```

### **DFS Traversals**
1. **Preorder (Root → Left → Right)**  
   - **Output:** `1 → 2 → 4 → 5 → 3`  

2. **Inorder (Left → Root → Right)**  
   - **Output:** `4 → 2 → 5 → 1 → 3`  

3. **Postorder (Left → Right → Root)**  
   - **Output:** `4 → 5 → 2 → 3 → 1`

### **BFS Traversal**
- **Level Order Traversal**  
  - **Output:** `1 → 2 → 3 → 4 → 5`

---

## **Key Differences Between DFS and BFS**

| Feature        | DFS (Depth-First Search) | BFS (Breadth-First Search) |
|---------------|--------------------------|--------------------------|
| **Traversal Approach** | Goes deep into one branch first | Explores level by level |
| **Data Structure Used** | **Stack (recursion or explicit)** | **Queue** |
| **Memory Usage** | Less memory (`O(h)`, where `h` is height) | More memory (`O(n)` for full tree) |
| **Best For** | Tree traversals, pathfinding (limited space) | Finding shortest paths (unweighted graphs) |
| **Time Complexity** | `O(n)` | `O(n)` |

## **When to Use DFS vs. BFS?**
- **Use DFS when**:
  - You need to **search deeply** into a tree/graph (e.g., solving puzzles, exploring paths).
  - Space usage needs to be **minimized** (lower memory than BFS).
  - You are traversing **deep recursive structures**.

- **Use BFS when**:
  - You need to **find the shortest path** (e.g., unweighted graphs).
  - The problem involves **level-order processing** (e.g., connecting nodes at the same depth).
  - You want a **breadth-wise exploration**.