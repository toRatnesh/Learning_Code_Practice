##################
# 
# References
#     https://www.javatpoint.com/python-stack-and-queue
#   https://docs.python.org/3/tutorial/datastructures.html#using-lists-as-stacks
#   https://docs.python.org/3/tutorial/datastructures.html#using-lists-as-queues
# 
# 
#   A simple Python list can act as a queue and stack as well
#   It is common for stacks and queues to be implemented with an array or linked list
# 
# Stack 
#   A Stack is a data structure that follows the LIFO(Last In First Out) principle
#     
#   Operations:
#       push:   It adds an element to the top of the stack, increasing the stack size
#       pop:    It removes an element from the top of the stack decreasing the stack size 
#               If no element is present in the stack, then underflow occurs in the stack
#   
#   Characteristics:
#       Insertion order of the stack is preserved
#       Duplicacy is allowed
#       Useful for parsing the operations
#       
# Queue
#   A Queue follows the First-in-First-Out (FIFO) principle
#   It is opened from both the ends hence we can easily add elements to the back and can remove elements from the front
# 
#   Operations:
#       enqueue:    It adds an element to the end of the queue
#       dequeue:    It removes the element from the beginning of the queue
#                   If no element is present in the queue, Underflow occurs in the queue
#                   
#   Characteristics
#       Insertion order of the queue is preserved
#       Duplicacy is allowed
#       Useful for parsing CPU task operations
# 
##################


print("=== Stack ===")
astack= []
astack.append(1)
astack.append(2)
astack.append(3)
print(f"astack {astack}")
print(f"astack.pop() {astack.pop()}")
print(f"astack {astack}")
astack.append(4)
astack.append(5)
print(f"astack {astack}")
print(f"astack.pop() {astack.pop()}")
print(f"astack.pop() {astack.pop()}")
print(f"astack.pop() {astack.pop()}")
print(f"astack {astack}")
print(f"astack.pop() {astack.pop()}")
print(f"astack {astack}")


print("=== Queue ===")

from collections import deque
aqueue = deque([1, 2, 3])
print(f"aqueue {aqueue}")
aqueue.append(4)
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue {aqueue}")
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue {aqueue}")
aqueue.append(5)
print(f"aqueue {aqueue}")
aqueue.append(6)
aqueue.append(7)
print(f"aqueue {aqueue}")
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue.popleft() {aqueue.popleft()}")
print(f"aqueue {aqueue}")

##################
#   END OF FILE
##################


