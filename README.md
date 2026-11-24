# Arbitrary Precision Calculator (APC)

A command-line calculator in C that performs `+`, `-`, `x` and `/` on integers of **any length**, beyond the range of `int` or `long long`.

## How it works

Each number is stored as a **doubly linked list with one digit per node**. The sign is stored separately.

```
123  ->  head -> [1] <-> [2] <-> [3] <- tail
```

- **Addition:** digit-by-digit from the tail using `prev`, with a carry.
- **Subtraction:** borrow method. The larger magnitude is always subtracted from the smaller one (found with `compare_list`), and the sign follows the larger operand.
- **Multiplication:** school method. Each digit of operand 2 multiplies operand 1, the partial product is shifted, and the partials are added.
- **Division:** long division using repeated subtraction (integer quotient).
- Signs and zero results (`-0` is never printed) and division by zero are handled.

## Build and run

```
gcc *.c -o a.out
./a.out <operand1> <operator> <operand2>
```

Operators: `+`  `-`  `x`  `/`  (use `x` for multiplication, since `*` is expanded by the shell)

## Examples

```
$ ./a.out 99999999999999999999 + 1
100000000000000000000

$ ./a.out 99999999999 x 99999999999
9999999999800000000001

$ ./a.out -100 / 7
-14

$ ./a.out 45 - 123
-78
```

## Files

| File | Purpose |
|------|---------|
| `apc.h` | Node structure and function prototypes |
| `apc.c` | List operations, validation, and the four arithmetic functions |
| `main.c` | Argument handling and sign logic |

## Concepts used

Doubly linked list, dynamic memory (`malloc`/`free`, checked with valgrind), pointer-to-pointer parameters, command-line arguments.
