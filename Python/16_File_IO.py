#####################################
# 
# References
#     https://www.javatpoint.com/python-files-io
# 
# File Handling
#     The file may be in the text or binary format, and each line of a file is ended with the special character.
#     File operation
#         Open a file
#         Read or write - Performing operation
#         Close the file
# 
# Opening a file
#     open() function that accepts two arguments, file name and access mode
#     returns a file object
#     Syntax:
#         file_object = open(<file-name>, <access-mode>, <buffering>)
#         
#     For text mode:      r, r+, w, w+, a, a+
#     For binary mode:    rb, rb+, wb, wb+, ab, ab+
#     NOTE: x - it creates a new file with the specified name. It causes an error a file exists with the same name.
# 
# Closing a file
#     using close() method
#     Any unwritten information gets destroyed once the close() method is called on a file object
#     Syntax
#         fileobject.close()   
# 
# Writing to File
#     write() Writes any string to an open file. Python strings can have binary data and not just text.
#     The write() method does not add a newline character ('\n') to the end of the string.
#     Syntax
#         fileObject.write(string)
# 
#     string: content to be written into the opened file
# 
# Reading from File
#     read()  Reads a string from an open file. Python strings can have binary data, apart from text data.
#     Syntax
#         fileObject.read([count])
# 
#     count: number of bytes to be read from the opened file. (optional argument)
#     if count is missing, then it tries to read as much as possible, maybe until the end of file.
# 
# Read file through for loop
#     use for loop to read one line at a time
#     
# Read Lines of the file
#     readline()  to read the file line by line
#     readlines() It returns the list of the lines till the end of file(EOF) is reached
#     
# File Positions
#     tell()  Tells you the current position within the file
#             In other words, the next read or write will occur at that many bytes from the beginning of the file.
# 
#     seek()  Changes the current file position
# 
#         Syntax
#         seek(offset[, from])
#         offset: indicates the number of bytes to be moved
#         from: specifies the reference position from where the bytes are to be moved
#                 0	beginning of the file
#                 1	current position
#                 2	end of the file
# 
# Renaming the file
#     os module provides us the rename() method to rename the specified file to a new name
#     Syntax:
#         rename(current-name, new-name)
# 
# Removing the file
#     os module provides the remove() method which is used to remove the specified file
#     Syntax:
#         remove(file-name)
# 
# Writing Python output to the files
#     check_call() method of module subprocess is used to execute a Python script and write the output of that script to a file
#     
# The with statement
#     with statement is useful in the case of manipulating the files
#     It is used in the scenario where a pair of statements is to be executed with a block of code in between
#     
#     with open(<file name>, <access mode>) as <file-pointer>:    
#         #statement suite
#     
#     if the break, return, or exception occurs in the nested block of code then it automatically closes the file, we don't need to write the close() function. IT DOESN'T LET THE FILE TO CORRUPT.
# 
# FILE Methods
#   close()	Close the file
#   flush()	Flush the internal buffer, like stdio's fflush. This may be a no-op on some file-like objects
#   fileno()	Returns the integer file descriptor that is used by the underlying implementation to request I/O operations from the operating system
#   isatty()	Returns True if the file is connected to a tty(-like) device, else False
#   next()		Returns the next line from the file each time it is being called
#   read([size])	Reads at most size bytes from the file (less if the read hits EOF before obtaining size bytes)
#   readline([size])	Reads one entire line from the file. A trailing newline character is kept in the string
#   readlines([sizehint])	Reads until EOF using readline() and return a list containing the lines. 
#   	If the optional sizehint argument is present, instead of reading up to EOF, whole lines totalling approximately sizehint bytes (possibly after rounding up to an internal buffer size) are read.
#   seek(offset[, whence])	Sets the file's current position
#   tell()	Sets the file's current position
#   truncate([size])	Truncates the file's size. If the optional size argument is present, the file is truncated to (at most) that size
#   write(str)	Writes a string to the file. There is no return value
#   writelines(sequence)	Writes a sequence of strings to the file. The sequence can be any iterable object producing strings, typically a list of strings
#   
#       
#####################################

import os


print("=== Reading from file ===")

print("=== Reading using read() method ===")
rfile = open("16_01_read_this_file.txt", "r")
if rfile:
    content = rfile.read()
else:
    print("Error while opening file for reading")
print(content)
rfile.close()

print("=== Reading using for loop ===")
rfile = open("16_01_read_this_file.txt", "r")
for content in rfile:
    print(content)
rfile.close()

print("=== Reading using readline() method ===")
rfile = open("16_01_read_this_file.txt", "r")
for content in rfile:
    print(content)
rfile.close()

print("=== Reading using readlines() method ===")
rfile = open("16_01_read_this_file.txt", "r")
content = rfile.readlines()
print(content)
rfile.close()

print("=== File Positions ===")
rfile = open("16_01_read_this_file.txt", "a")
print(f"rfile.tell() {rfile.tell()}")
print(f"rfile.seek(13, 0) {rfile.seek(13, 0)}")
print(f"rfile.tell() {rfile.tell()}")
rfile.close()


print("=== Renaming and Removing ===")

print("=== renaming change_this_name.txt to this_is_new_name.txt  ===")
wfile = open("change_this_name.txt", "w")
wfile.close()
os.rename("change_this_name.txt", "this_is_new_name.txt")

print("=== removing this_is_new_name.txt  ===")
os.remove("this_is_new_name.txt")


print("=== using with-open ===")
with open("16_02_outputfile.txt", "w") as wfile:
    wfile.write("Learning Python code to read-wrote from a file using with-open. with open offers safety that it auto closes the file and does not corrupt it. So in this example this file is not closed")


##################
#   END OF FILE
##################

