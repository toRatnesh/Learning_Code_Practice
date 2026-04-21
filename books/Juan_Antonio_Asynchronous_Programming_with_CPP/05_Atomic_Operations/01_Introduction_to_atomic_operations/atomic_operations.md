
Atomic operations can be used in the following cases:

- If multiple threads share a mutable state
- If synchronized access to shared state is fine-grained
- To improve performance

Atomic operations must be provided by the CPU.

Locks can be used in the following cases:

- If the protected data is not fine-grained
- If performance is not an issue
- To avoid the need to acquire low-level knowledge



