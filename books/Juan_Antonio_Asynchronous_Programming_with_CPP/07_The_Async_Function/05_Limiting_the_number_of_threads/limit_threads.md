# Limiting the number of threads

use counting semaphore with initial value set to max number of allowed hardware threads

acquire semaphore and then if resource is available execute the task
