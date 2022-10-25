######################################
# 
# References
#     https://www.javatpoint.com/python-command-line-arguments
#     https://docs.python.org/3/tutorial/stdlib.html#command-line-arguments
# 
# Command line arguments
#     Command line arguments is the input parameter that needs to be passed to the script when executing them.
# 
# Access command line arguments
#     Different modules can be used to parse command line arguments
#     sys
#     getopt
#     argparse
# 
# sys module
#     The sys module implements command-line arguments in a simple list structure named sys.argv.
#     Each list element represents a single argument. The first one sys.argv[0] is the name of Python script. 
#     The other list elements are sys.argv[1] to sys.argv[n] are the command line arguments 2 to n. 
#     
#     As a delimiter between arguments, space is used.
#     Argument values that contain space in it have to be quoted, accordingly.
# 
# getopt module
#     The getopt module extends the separation of the input string by parameter validation. 
#     Similar to C getopt() function, it allows both short and long options, including a value assignment.
#     Syntax:
#         getopt.getopt(args, options, [long_options])
# 
# argparse module
#     The argparse allows verification of fixed and optional arguments with a name checking as either UNIX or GNU style. 
#     It is the preferred way to parse command-line arguments. It provides a lot of option such as positional arguments, 
#     the default value for arguments, helps message, specifying the data type of argument etc.
# 
######################################

import sys
import getopt
import argparse


print(f"=== sys module ===")
print(f"type(sys.argv) {type(sys.argv)}")
print(f"Command line argumets are:")
for elem in sys.argv:
    print(f"{elem}", end=' ')
print()


print(f"=== getopt module ===")
argv = sys.argv[1:]
try:
    opts,args = getopt.getopt(argv, "hvi:o::", ['help', 'in-file=', 'out-file='])
    print(f"opts {opts}")
    print(f"args {args}")

    for opt, arg in opts:
        if '-h' == opt:
            print(f"sys.argv[0] -i <input-file> -o [output-file]")
            #sys.exit()
        elif opt in ('-i', 'in-file='):
            print(f"input file is {arg}")
        elif opt in ('-o', 'out-file='):
            print(f"output file is {arg}")

except getopt.GetoptError:
    print("Error while parsing options")
    sys.exit()


print(f"=== argparse module ===")
arg_parser= argparse.ArgumentParser(
    description = 'Learing to parse command line arguments',
    epilog = 'This is epilog'
)
arg_parser.add_argument('-v', '--verbose', action="store_true", help='print verbose log')
arg_parser.add_argument('-i', '--infile', type=str, required=True, help='input file')
arg_parser.add_argument('-o', '--outfile', type=str, default='output_log.log', help='output file')
args = arg_parser.parse_args()
print(f"args using argparse {args}")
if(args.verbose):
    if(args.infile):
        print(f"inout file: {args.infile}")
    if(args.outfile):
        print(f"output file: {args.outfile}")
else:
    if(args.infile):
        print(f"{args.infile}")
    if(args.outfile):
        print(f"{args.outfile}")   

#################
#   END OF FILE
#################
