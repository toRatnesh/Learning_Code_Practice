
Why do we need mutual exclusion?

Mutual exclusion is a fundamental concept in concurrent programming that ensures that multiple threads or processes do not simultaneously access a shared resource such as a shared variable, a critical section of code, or a file or network connection. Mutual exclusion is crucial for preventing race conditions such as the one we have seen in the previous section.

C++ Standard Library mutual exclusion implementation

| Mutex Type | Access | Recursive | Timeout |
| ------ | ------- | ------- | ------ |
| std::mutex | EXCLUSIVE | NO | NO |
| std::recursive_mutex | EXCLUSIVE | YES | NO |
| std::shared_mutex | 1 - EXCLUSIVE, N - SHARED | NO | NO |
| std::timed_mutex | EXCLUSIVE | NO | YES |
| std::recursive_timed_mutex | EXCLUSIVE | YES | YES |
| std::shared_timed_mutex | 1 - EXCLUSIVE, N - SHARED | NO | YES |

