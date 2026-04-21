
| Mutex Manager Class | Supported Mutex Types | Mutexes Managed |
| -------- | -------- | -------- |
| std::lock_guard | All | 1 |
| std::scoped_lock | All | 0 or more |
| std::unique_lock | All | 1 |
| std::shared_lock | std::shared_mutex std::shared_timed_mutex | 1 |

