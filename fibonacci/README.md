# Java vs. Rust Fibonacci Benchmark

This document summarizes a simple benchmark comparing the performance of Java and Rust for a CPU-intensive task: calculating the 45th Fibonacci number recursively.

## Results

The following table shows the execution time for each implementation.

| Language | Optimizations | Real Time (seconds) |
| :--- | :--- | :--- |
| Java | JIT (Just-In-Time) | ~1.6 s |
| Rust | None | ~6.7 s |
| Rust | `-O` (AOT) | ~3.3 s |

## Why Optimized Rust Runs Faster

The Rust compiler (`rustc`) does not optimize for speed by default. Its primary goal in a standard build is to compile quickly and provide a good debugging experience.

When the `-O` (optimization) flag is used, you instruct the compiler to spend more time analyzing the code to generate a much faster executable. This is typically done for release builds. The compiler, using its **LLVM** backend, applies numerous optimization techniques, such as:

*   **Function Inlining:** In the recursive `fib` function, the overhead of making repeated function calls is significant. Inlining replaces the function call with the function's body, reducing this overhead.
*   **Dead Code Elimination:** The compiler removes any code that is never executed or whose results are not used.
*   **Instruction Reordering:** It rearranges the low-level machine code instructions to make more efficient use of the CPU's processing capabilities.

In this benchmark, Java's Just-In-Time (JIT) compiler automatically optimizes the code during execution, which is why it performs well out-of-the-box. The optimized Rust code is still slower in this specific micro-benchmark, but for many other workloads, Rust's ahead-of-time (AOT) optimizations can lead to superior performance.

## How to Reproduce

### Java

```bash
# Compile
javac Fibonacci.java

# Run and Time
time java Fibonacci
```

### Rust

```bash
# Compile (Unoptimized)
rustc main.rs

# Run and Time
time ./main

# Compile (Optimized)
rustc -O main.rs

# Run and Time
time ./main
```

## Source Code

<details>
<summary>Fibonacci.java</summary>

```java
class Fibonacci {
    public static int fib(int n) {
        if (n <= 1) {
            return n;
        }
        return fib(n - 1) + fib(n - 2);
    }

    public static void main(String[] args) {
        System.out.println(fib(45));
    }
}
```
</details>

<details>
<summary>main.rs</summary>

```rust
fn fib(n: i32) -> i32 {
    if n <= 1 {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

fn main() {
    println!("{}", fib(45));
}
```
</details>
