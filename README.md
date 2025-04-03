These are my solutions for my leetcode grind

# Sorting Algorithms

| Algorithm        | Best Case  | Average Case | Worst Case  | Space Complexity |
|-----------------|-----------|-------------|-------------|------------------|
| Bubble Sort     | <span style="color:green">O(n)</span>      | <span style="color:red">O(n²)</span>       | <span style="color:red">O(n²)</span>       | <span style="color:blue">O(1)</span>             |
| Selection Sort  | <span style="color:red">O(n²)</span>     | <span style="color:red">O(n²)</span>       | <span style="color:red">O(n²)</span>       | <span style="color:blue">O(1)</span>             |
| Insertion Sort  | <span style="color:green">O(n)</span>      | <span style="color:red">O(n²)</span>       | <span style="color:red">O(n²)</span>       | <span style="color:blue">O(1)</span>             |
| Merge Sort      | <span style="color:orange">O(n log n)</span> | <span style="color:orange">O(n log n)</span>  | <span style="color:orange">O(n log n)</span>  | <span style="color:purple">O(n)</span>             |
| Quick Sort      | <span style="color:orange">O(n log n)</span> | <span style="color:orange">O(n log n)</span>  | <span style="color:red">O(n²)</span>       | <span style="color:purple">O(log n)</span>         |
| Heap Sort       | <span style="color:orange">O(n log n)</span> | <span style="color:orange">O(n log n)</span>  | <span style="color:orange">O(n log n)</span>  | <span style="color:blue">O(1)</span>             |
| Counting Sort   | <span style="color:green">O(n + k)</span>  | <span style="color:green">O(n + k)</span>    | <span style="color:green">O(n + k)</span>    | <span style="color:purple">O(k)</span>             |
| Radix Sort      | <span style="color:green">O(nk)</span>     | <span style="color:green">O(nk)</span>       | <span style="color:green">O(nk)</span>       | <span style="color:purple">O(n + k)</span>         |
# Searching Algorithms

| Algorithm        | Best Case | Average Case | Worst Case  | Space Complexity |
|-----------------|----------|--------------|-------------|------------------|
| Linear Search   | <span style="color:green">O(1)</span>     | <span style="color:red">O(n)</span>         | <span style="color:red">O(n)</span>        | <span style="color:blue">O(1)</span>             |
| Binary Search   | <span style="color:green">O(1)</span>     | <span style="color:green">O(log n)</span>     | <span style="color:green">O(log n)</span>    | <span style="color:blue">O(1)</span>             |
| Jump Search     | <span style="color:orange">O(√n)</span>    | <span style="color:orange">O(√n)</span>        | <span style="color:orange">O(√n)</span>       | <span style="color:blue">O(1)</span>             |
| Interpolation Search | <span style="color:green">O(1)</span> | <span style="color:green">O(log log n)</span> | <span style="color:red">O(n)</span>        | <span style="color:blue">O(1)</span>             |
| Exponential Search | <span style="color:green">O(1)</span>  | <span style="color:green">O(log n)</span>     | <span style="color:green">O(log n)</span>    | <span style="color:blue">O(1)</span>             |


### Notes
- **Binary Search requires sorted input!**
- **Quick Sort can degrade to O(n²) in the worst case.**
- **Jump & Interpolation Search work best when elements are uniformly distributed.**
- **Counting & Radix Sort are faster for restricted number ranges.**

# Linear Data Structures

| Data Structure  | Access | Search | Insert | Delete | Space Complexity |
|----------------|--------|--------|--------|--------|------------------|
| Array         | <span style="color:green">O(1)</span>   | <span style="color:orange">O(n)</span>   | <span style="color:orange">O(n)</span>   | <span style="color:orange">O(n)</span>   | <span style="color:blue">O(n)</span>             |
| Linked List   | <span style="color:orange">O(n)</span>   | <span style="color:orange">O(n)</span>   | <span style="color:green">O(1)</span>   | <span style="color:green">O(1)</span>   | <span style="color:blue">O(n)</span>             |
| Stack         | <span style="color:orange">O(n)</span>   | <span style="color:orange">O(n)</span>   | <span style="color:green">O(1)</span>   | <span style="color:green">O(1)</span>   | <span style="color:blue">O(n)</span>             |
| Queue         | <span style="color:orange">O(n)</span>   | <span style="color:orange">O(n)</span>   | <span style="color:green">O(1)</span>   | <span style="color:green">O(1)</span>   | <span style="color:blue">O(n)</span>             |
| Hash Table    | <span style="color:green">O(1)</span>   | <span style="color:green">O(1)</span>   | <span style="color:green">O(1)</span>   | <span style="color:green">O(1)</span>   | <span style="color:blue">O(n)</span>             |

# Non-Linear Data Structures

| Data Structure    | Search  | Insert  | Delete  | Space Complexity |
|------------------|---------|---------|---------|------------------|
| Binary Search Tree | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:blue">O(n)</span>             |
| AVL Tree         | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:blue">O(n)</span>             |
| Red-Black Tree  | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:blue">O(n)</span>             |
| Min Heap    | <span style="color:green">O(1)</span> <span style="color:orange">O(n)</span>    | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:blue">O(n)</span> |
| Max Heap    | <span style="color:green">O(1)</span> <span style="color:orange">O(n)</span>    | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:blue">O(n)</span> |
| Min-Max Heap | <span style="color:green">O(1)</span> <span style="color:orange">O(n)</span>    | <span style="color:green">O(log n)</span> | <span style="color:green">O(log n)</span> | <span style="color:blue">O(n)</span> |
| Graph (Adj. List) | <span style="color:orange">O(V + E)</span> | <span style="color:green">O(1)</span>    | <span style="color:green">O(1)</span>    | <span style="color:purple">O(V + E)</span>         |
| Graph (Adj. Matrix) | <span style="color:green">O(1)</span> | <span style="color:green">O(1)</span>    | <span style="color:green">O(1)</span>    | <span style="color:purple">O(V²)</span>             |
| Trie            | <span style="color:green">O(m)</span>    | <span style="color:green">O(m)</span>    | <span style="color:green">O(m)</span>    | <span style="color:purple">O(n * m)</span>          |

### Color Code Meaning
- 🟢 **Green** → **Fast (Efficient) Complexity**
- 🟠 **Orange** → **Moderate Complexity**
- 🔴 **Red** → **Slow (Inefficient) Complexity**
- 🔵 **Blue** → **Constant Space Complexity**
- 🟣 **Purple** → **Logarithmic or Linear Space Complexity**
  
### Notes
- **Arrays** offer O(1) access but are expensive for insertions/deletions.
- **Linked Lists** are better for frequent insertions/deletions.
- **Stacks & Queues** are specialized structures following LIFO and FIFO principles.
- **BSTs & Balanced Trees (AVL, Red-Black)** are useful for fast **sorted** data operations.
- **Graphs** can be represented as adjacency lists (space-efficient) or adjacency matrices (quick access).
- **Tries** are optimized for fast **prefix-based searches**.
