<div align="center">

# 📚 C++ Stack Data Structure — Complete Demo

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-informational?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)

> A fully visual, color-coded terminal demo covering everything about the **Stack** data structure in C++ — from fundamentals to real-world applications.

</div>

---

## 📋 Table of Contents

- [About](#-about)
- [Demo Sections](#-demo-sections)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Requirements](#-requirements)
- [How to Run](#-how-to-run)
- [Concepts Covered](#-concepts-covered)
- [License](#-license)

---

## 🧠 About

This project is a hands-on learning demo for the **Stack** data structure in C++.  
Every section runs in your terminal with **colored output**, **ASCII tables**, **memory diagrams**, and **step-by-step traces** — no theory walls, just visual learning.

---

## 🎯 Demo Sections

| # | Section | What you learn |
|---|---------|---------------|
| 1 | **STL `std::stack`** | All core operations in a colored table |
| 2 | **Array-based Stack** | Internal array memory layout with TOP pointer |
| 3 | **Linked List Stack** | Heap node visualization with pointer addresses |
| 4 | **Stack Sorting** | Recursive sort with step-by-step trace |
| 5 | **Bracket Matching** | Real-world use case with ✅/❌ results |
| 6 | **LIFO Concept** | Push order vs pop order comparison |
| 7 | **Reverse a String** | Character stack trace with palindrome check |
| 8 | **Undo/Redo System** | Two-stack simulation of editor undo/redo |
| 9 | **Infix → Postfix** | Shunting-yard algorithm with full trace table |
| 10 | **Overflow & Underflow** | Error handling + safe push/pop patterns |

---

## 📁 Project Structure

```
cpp_stack/
├── src/
│   └── stack_demo.cpp    # All 10 demo sections
├── bin/
│   └── stack_demo        # Compiled binary (auto-created, git-ignored)
├── Makefile              # Build system
├── run.sh                # One-shot compile & run script
├── .gitignore            # Ignores bin/ and editor files
└── README.md             # This file
```

---

## ⚡ Getting Started

### Clone the repo

```bash
git clone https://github.com/YOUR_USERNAME/cpp_stack.git
cd cpp_stack
```

### Install g++ (Fedora / RHEL)

```bash
sudo dnf install gcc-c++
```

### Install g++ (Ubuntu / Debian)

```bash
sudo apt install g++
```

### Install g++ (macOS)

```bash
xcode-select --install
```

---

## 🚀 How to Run

### Option 1 — One-shot script (easiest)

```bash
./run.sh
```

### Option 2 — Using Make

```bash
make        # compile
make run    # compile + run
make clean  # remove binary
```

### Option 3 — Manual

```bash
mkdir -p bin
g++ -Wall -std=c++17 -o bin/stack_demo src/stack_demo.cpp
./bin/stack_demo
```

---

## 📖 Concepts Covered

### Data Structures
- `std::stack` (STL)
- Array-based Stack
- Linked List Stack (heap nodes with pointers)

### Algorithms
- Stack sorting — `O(n²)` recursive insertion
- Infix → Postfix conversion — Shunting-yard algorithm
- Palindrome detection via stack reversal

### Error Handling
- Stack Overflow detection
- Stack Underflow detection
- Safe push/pop patterns

### Real-world Applications
- **Undo/Redo** — Two-stack editor simulation
- **Bracket Matching** — Syntax validator
- **Expression Evaluation** — Postfix conversion
- **String Reversal** — LIFO character processing

---

## 📊 Time & Space Complexity

| Operation | Array Stack | Linked Stack |
|-----------|:-----------:|:------------:|
| Push      | O(1)        | O(1)         |
| Pop       | O(1)        | O(1)         |
| Top/Peek  | O(1)        | O(1)         |
| Search    | O(n)        | O(n)         |
| Space     | O(n)        | O(n)         |

---

## 📜 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).  
Feel free to use, modify, and share for learning purposes.

---

<div align="center">
Made with ❤️ for learning C++ Data Structures
</div>
