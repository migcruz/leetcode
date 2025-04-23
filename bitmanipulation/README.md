# 🧠 Bitwise Operators in C — Tips, Tricks, and Use Cases

Bitwise operators let you manipulate data at the binary level. They’re **fast**, **lightweight**, and incredibly useful for algorithms, embedded systems, and memory-efficient programming.

---

## 📌 Bitwise Operators in C

| Operator | Symbol | Description                          |
|----------|--------|--------------------------------------|
| AND      | `&`    | 1 if both bits are 1                 |
| OR       | `\|`   | 1 if either bit is 1                 |
| XOR      | `^`    | 1 if bits are different              |
| NOT      | `~`    | Inverts each bit                     |
| Left Shift  | `<<`   | Shifts bits left (×2 per shift)      |
| Right Shift | `>>`   | Shifts bits right (÷2 per shift)     |

---

## 💡 XOR Power Tricks

### 🔎 Find a Non-Duplicated Number (All Others Appear Twice)
```C
#include <stdio.h>

int findUnique(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    int nums[] = {2, 3, 5, 3, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("Unique number: %d\n", findUnique(nums, n));
    return 0;
}
```

### 🔎 Find a Missing Number from 1 to n+1
```C
#include <stdio.h>

int findMissing(int arr[], int n) {
    int xor_arr = 0, xor_full = 0;

    for (int i = 0; i < n; i++) {
        xor_arr ^= arr[i];
    }

    for (int i = 1; i <= n + 1; i++) {
        xor_full ^= i;
    }

    return xor_arr ^ xor_full;
}

int main() {
    int nums[] = {1, 2, 4, 5}; // Missing 3
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("Missing number: %d\n", findMissing(nums, n));
    return 0;
}
```
### 🔄 Swap Two Variables Without Temp
```C
#include <stdio.h>

int main() {
    int a = 5, b = 9;

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    printf("a = %d, b = %d\n", a, b); // a = 9, b = 5
    return 0;
}
```
### 🧪 XOR Fun Facts 
```
x ^ x = 0
``` 
and 
```
x ^ 0 = x
```
- So XOR is like binary subtraction and canceling out duplicates at the bit level.
- XOR is both associative and commutative

## 🧠 Bitwise Tips & Tricks in C

| Tip                   | Code Example              | Description                          |
|-----------------------|---------------------------|--------------------------------------|
| Check if even         | `if ((n & 1) == 0)`       | Returns true if number is even       |
| Toggle nth bit        | `x ^= (1 << n);`          | Flips the nth bit (0 ⇄ 1)            |
| Set nth bit           | `x I= (1 << n);`          | Forces the nth bit to 1              |
| Clear nth bit         | `x &= ~(1 << n);`         | Forces the nth bit to 0              |
| Check nth bit         | `if (x & (1 << n))`       | True if the nth bit is set (1)       |
| Multiply by 2^k       | `x << k`                  | Left shift multiplies by 2^k         |
| Divide by 2^k         | `x >> k`                  | Right shift divides by 2^k           |
| Count set bits (popcount) | Loop with `n &= (n - 1)` | Removes lowest set bit (see BK algo) |

