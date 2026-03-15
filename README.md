# Stack Processor Emulator
**Algorithms and Data Structures – Project 2024/2025**

## Project Overview

The **Gedanum state** has decided to begin conquering space. As the first step, a number of probes will be sent to search for planets suitable for colonization.

These probes must be both **intelligent** and **energy-efficient**, which requires designing a new processor architecture to control them.

For this purpose, the **Experts Technology Interstellar Commission** designed a new processor:

> **Stack Translator Of Symbols – model AaD5**

Although the processor still requires further development before entering mass production, an **emulator** is needed so that software for the probes can already be developed.

Your task is to **implement an emulator of this processor**.

---

# Processor Architecture

The processor consists of three main components:

- **Program Memory** – stores the program
- **Instruction Pointer (IP)** – points to the instruction currently being executed
- **Stack** – stores data used during program execution

### Program Memory

A program is a **sequence of instructions**, where each instruction is represented by **a single character**.

Execution rules:

- The **first instruction has index `0`**
- After executing an instruction, the **instruction pointer increases by 1**
- The processor **terminates** when the instruction pointer goes beyond the last instruction in the program

---

# Stack Structure

The stack stores **lists of characters**.

Each stack element is a list containing **zero or more characters**, which may include:

- digits
- letters
- other symbols

### Numbers on the Stack

A list represents a **number** if:

- it contains **only digits**
- it contains **at most one `-` character**
- if present, `-` must appear **at the end of the list**

Numbers are stored **in reverse order**:

Example:

```
Number: -1234
Stored as: 4321-
```

The **least significant digit appears first** in the list.

---

# Processor Instructions

The processor operates using **single-character instructions**.

| Symbol | Instruction | Description |
|:---:|---|---|
| **'** | apostrophe | push an empty list on the stack |
| **,** | comma | pop a list from the stack |
| **:** | colon | duplicate the top list on the stack |
| **;** | semicolon | swap the top two lists on the stack |
| **@** | at | pop number **A** and push a copy of the list at position **A** on the stack |
| **.** | dot | read a character from input and append it to the beginning of the top list |
| **>** | greater than | print the first character of the top list and remove the list |
| **!** | exclamation mark | logical negation |
| **<** | less than | compare two numbers: push `1` if `B < A`, otherwise `0` |
| **=** | equal | compare two numbers: push `1` if `B = A`, otherwise `0` |
| **~** | tilde | push the current instruction pointer value onto the stack |
| **?** | question mark | conditional jump |
| **-** | minus | change the sign of the number |
| **^** | caret | absolute value |
| **$** | dollar | split the first character from the top list |
| **#** | hash | append list A to the list below it |
| **+** | plus | add two numbers |
| **&** | ampersand | print the entire stack |
| **]** | right bracket | convert ASCII code to character |
| **[** | left bracket | convert character to ASCII code |
| other | character | append the character to the top list |

---

# Input Format

The program reads input in two lines:

```
<program>
<input characters>
```

Where:

- **Line 1** – the processor program (sequence of instructions)
- **Line 2** – characters that will be provided as **standard input**

Restrictions:

- Neither the program nor the input contain whitespace characters.

---

# Output

The output should contain **exactly what the processor writes to standard output** during execution.

---

# Implementation Rules

The implementation must follow several restrictions:

- **STL containers are not allowed** (except for input/output handling)
- **Arrays cannot be used**, except for storing:
  - the program
  - the input data
- Loops (`for`, `while`, `do...while`) may be used **at most once**, and only for reading input
- The program logic should be implemented **using recursion**

---

# Examples

## Example 1

### Input

```
'123'-456&+&
```

### Output

```
1: 321
0: 654-
0: 333-
```

---

## Example 2

### Input

```
'...&$&
123
```

### Output

```
0: 321
1: 21
0: 3
```
