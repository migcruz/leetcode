# Linked Lists 📚

A **Linked List** is a linear data structure where each element (called a *node*) points to the next. Unlike arrays, linked lists do not require contiguous memory, making insertions and deletions more efficient in certain scenarios.

## 📌 Key Concepts

- **Node**: The building block of a linked list. Contains data and a pointer to the next node.
- **Head**: Points to the first node in the list.
- **Tail**: (In some implementations) Points to the last node.
- **Pointer (next)**: Each node stores the reference to the next node.

## 🔗 Types of Linked Lists

| Type               | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| **Singly Linked List** | Each node points to the next node. Traversal is one-directional.         |
| **Doubly Linked List** | Each node has two pointers: `next` and `prev`. Allows bidirectional traversal. |
| **Circular Linked List** | The last node points back to the head, forming a circle.               |

## ✏️ Basic Operations

### Insert
- **At beginning**: Insert a new node before the current head.
- **At end**: Traverse to the last node and add a new one.
- **At position**: Traverse to the desired location and insert.

### Delete
- **By value**: Find the node with a specific value and remove it.
- **At position**: Remove node at a specific index.

### Traverse
- Go through each node starting from `head` until `null` (or head again, in circular lists).

## 📈 Time Complexities

| Operation       | Singly/Doubly Linked List |
|----------------|---------------------------|
| Access         | O(n)                      |
| Search         | O(n)                      |
| Insertion (head) | O(1)                    |
| Deletion (head) | O(1)                    |
| Insertion (middle/end) | O(n)            |
| Deletion (middle/end) | O(n)             |

## ✅ When to Use Linked Lists

- When frequent insertions/deletions are needed and array resizing is costly.
- When memory fragmentation is a concern.

## ❌ When *Not* to Use

- When you need constant-time access to elements by index (use arrays instead).
- When memory overhead of pointers is an issue.
```
```
# 🐢🐇 Floyd's Cycle Detection Algorithm (Tortoise and Hare)

Floyd's Cycle Detection Algorithm, commonly known as the **Tortoise and Hare Algorithm**, is an efficient way to **detect cycles in a linked list** or any sequence where elements can be revisited through repeated traversal.

---

## 🚀 What Does It Do?

It answers the question:  
> **Is there a loop/cycle in the linked list?**

### ✅ Key Properties
- **Time Complexity**: O(n)
- **Space Complexity**: O(1) – No extra space is used!
- Detects **if** a cycle exists.
- Can be extended to **find the cycle's starting point**.

---

## 🧠 How It Works

Two pointers move through the list:
- 🐢 **Tortoise** moves one step at a time.
- 🐇 **Hare** moves two steps at a time.

### 🌀 If there's a cycle:
The fast pointer will eventually "lap" the slow pointer and they’ll meet inside the cycle.

### 🚫 If there's no cycle:
The fast pointer will reach the end (`null`) and exit.

---

## 🔄 Step-by-Step

1. Initialize two pointers at the head.
2. Move `slow` by 1 and `fast` by 2 until:
   - They meet (cycle exists), or
   - `fast` or `fast.next` becomes `None` (no cycle).
3. (Optional) To find the start of the loop:
   - Reset `slow` to head, keep `fast` where they met.
   - Move both one step at a time; the point they meet is the **start of the loop**.

---

## 🧪 Python Example

```python
class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

def has_cycle(head):
    slow = head
    fast = head

    while fast and fast.next:
        slow = slow.next          # Move one step
        fast = fast.next.next     # Move two steps
        if slow == fast:
            return True           # Cycle detected

    return False                  # No cycle

# Optional: Find start of the loop
def find_cycle_start(head):
    slow = head
    fast = head

    # First, detect if a cycle exists
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            break
    else:
        return None  # No cycle

    # Reset slow to head and move both one step
    slow = head
    while slow != fast:
        slow = slow.next
        fast = fast.next

    return slow  # Start of cycle
```