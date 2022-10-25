######################################
# 
# References
#     https://www.javatpoint.com/python-date
# 
# Date and Time
#     the datetime module work with real dates and times
#     the date is not a data type 
#     we can work with the date objects by importing the module named with datetime, time, and calendar
# 
#     datetime classes are classified in the six main classes
#         date        It is a naive ideal date. It consists of the year, month, and day as attributes.
#         time        It is a perfect time, assuming every day has precisely 24*60*60 seconds. 
#                     It has hour, minute, second, microsecond, and tzinfo as attributes.
#         datetime    It is a grouping of date and time, along with the attributes year, month, day, hour, minute, second, microsecond, and tzinfo.
#         timedelta   It represents the difference between two dates, time or datetime instances to microsecond resolution.
#         tzinfo      It provides time zone information objects.
#         timezone    It is included in the new version of Python. It is the class that implements the tzinfo abstract base class.
# 
# Time module
#     Tick
#         In Python, the time instants are counted since 12 AM, 1st January 1970. 
#         The function time() of the module time returns the total number of ticks spent since 12 AM, 1st January 1970. 
#         A tick can be seen as the smallest unit to measure the time.
# 
#     Current time
#         localtime() function returns a time tuple
# 
#     Time tuple
#         It is tuple of 9 numbers
#         Year		4 digit (for example 2018)
#         Month		1 to 12
#         Day			1 to 31
#         Hour		0 to 23
#         Minute		0 to 59
#         Second		0 to 60
#         Day of weak	0 to 6
#         Day of year	1 to 366
#         Daylight savings	-1, 0, 1 , or -1
# 
#     Formatted time
#         asctime() returns the formatted time for the time tuple being passed
# 
#     Sleep time
#         sleep() method is used to stop the execution of the script for a given amount of time, 
#         that is provided as the number of seconds provided as the float
# 
# Datetime Module
#     The datetime module enables us to create the custom date objects, perform various operations on dates like the comparison, etc.
# 
#     Creating date objects
#         Create the date objects bypassing the desired date in the datetime constructor for which the date objects are to be created
# 
# Calendar module
#     Calendar module contains various methods to work with the calendars
# 
#     prcal() method 
#         It is used to print the calendar of the entire year
# 
######################################

import time;

print("=== time module ===")
# Tick
print(f"time.time() : {time.time()}")

print("=== localtime ===")
print(f"time.localtime(time.time()) : {time.localtime(time.time())}")  

print("=== formatted time ===")
print(f"time.asctime(time.localtime(time.time())) : {time.asctime(time.localtime(time.time()))}")  

print("=== sleep ===")
for i in range(0, 5):
    print(f"sleeping for 1 seconds")
    time.sleep(1)


print("=== datetime module ===")
import datetime
from datetime import datetime as dt
print(f"datetime.datetime.now() : {datetime.datetime.now()}") 

print("=== creating datetime ===")
print(f"datetime.datetime(2020,4,4, 13, 15, 28) : {datetime.datetime(2020,4,4, 13, 15, 28)}")    

print("=== date comparison ===")
if dt(dt.now().year,dt.now().month,dt.now().day,9) < dt(dt.now().year,dt.now().month,dt.now().day,18):
    print("Inside office ....")    
else:    
    print("Out of office")   


print("=== calendar module ===")
import calendar
print("=== calendar of a particular month ===")
march2022 = calendar.month(2022,3)
print(f"{march2022}")

print("=== calendar of whole year ===")
cal2023 = calendar.prcal(2023)
print(f"{cal2023}")

#################
#   END OF FILE
#################

