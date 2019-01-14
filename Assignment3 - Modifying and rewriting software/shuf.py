#!/usr/bin/python

# Zhubo Deng
# 605186231

import random, sys
from optparse import OptionParser
from argparse import ArgumentParser

def openFile(filename): 
    file = open(filename, "r")
    line = file.readlines()
    file.close()

    
def shuffle(filename, number): 
    file = open(filename, "r")
    line = file.readlines()
    file.close()
    for i in range(number):
        sys.stdout.write(random.choice(line))

def main():
    version_msg = "%shuf.py 1.0"
    usage_msg = """%shuf.py [option] ... [file] or shuf -i LO-HI [option] \n
        Write a random permutation of the lines input. \n
        shuf: --input-range (-i), 
              --head-count (-n), 
              --repeat (-r), and 
              --help. 
        As with GNU shuf, if --repeat (-r) is used without --head-count (-n), 
        your program should run forever. Your program should also support zero
        non-option arguments or a single non-option argument "-" 
        (either of which means read from standard input),
        Read standard file input."""

    parser = ArgumentParser(usage=usage_msg, add_help=False)    

    parser.add_argument("-e", "--echo", nargs ="*", dest="word_list",
                        help="Treat each ARG as an input line")
    parser.add_argument("-i", "--input-range", action="store", nargs ="*", 
                        dest="range",
                        help="treat each number LO through HI as an input line")
    parser.add_argument("-n", "--head-count", action="store", nargs="*", 
                        dest="numlines", help="Output at most COUNT lines")
    parser.add_argument("-r", "--repeat", action="store", nargs="*",
                        dest="repeater", help="Output lines can be repeated")
    parser.add_argument("-", dest="stdinput", action="store_true", 
                        help="Call standard input.")
    # parser.add_argument("--help", action="help", help=argparse.SUPPRESS)
    
    args = parser.parse_args(sys.argv[1:])
    
    # set default
    echo = False
    num = False
    repeat = False
    i_range = False
    # print(echo, num, repeat)
    
    if (args.word_list is not None): echo = True
    if (args.numlines is not None): num = True
    if (args.repeater is not None): repeat = True
    if (args.range is not None): i_range = True
    
    # eg: ./randline.py -r -n 6 null.txt
    if(num and repeat):
        numlines = int(args.numlines[0])
        if(len(args.numlines) > 1):
            filename = str(args.numlines[1])
            shuffle(filename, numlines)
        elif(len(args.repeater) > 0):
            filename = str(args.repeater[0])
            shuffle(filename, numlines)  
        elif(len(args.repeater) == 0):
            stdinput(numlines)
 
    # eg: ./randline.py -n 6 null.txt
    elif (num):
        filename = str(args.numlines[1])
        numlines = int(args.numlines[0])
        if(len(args.numlines) > 1): 
            # filename, numlines
            shuffle(filename, numlines)
        else: 
            stdinput(numlines)

    # eg: ./randline.py -r null.txt
    elif(repeat):
        if(len(args.repeater) > 0):
            # open file with name and "reading"
            file = open(args.repeater[0], 'r')    
            line = file.readlines()
            file.close()
            while True:
                # ALWAYS TRUE! THIS is an infinite LOOP!
                sys.stdout.write(random.choice(line))

    # eg: ./randline.py -i 12-14 null.txt
    elif(i_range): 
        filename = str(args.range[1])
        num_range_list = (str(args.range[0])).split('-')   # [LO, HI]
        num_range = int(num_range_list[1]) - int(num_range_list[0]) + 1
        shuffle(filename, num_range)

    # eg: ./randline.py - (which is the only argument)
    elif(args.stdinput):
        word_list = list()
        text = input()
        word_list.append(str(text))
        while(len(text) >= 0):
            text = input()
            word_list.append(str(text))            
    
    
if __name__ == "__main__":
    main()



'''
dengzhubodeMacBook-Pro:Desktop dengzhubo$ ./shuf.py -r -n 6 null.txt
line3
line4
line4
line4
line2
line5
dengzhubodeMacBook-Pro:Desktop dengzhubo$ 
dengzhubodeMacBook-Pro:Desktop dengzhubo$ ./shuf.py -n 6 null.txt
line5
line5
line3
line5
line4
line3
dengzhubodeMacBook-Pro:Desktop dengzhubo$ 
dengzhubodeMacBook-Pro:Desktop dengzhubo$ ./shuf.py -r null.txt
line7
line2
line8
line3
line4
.
.
.
(infinite loop)
dengzhubodeMacBook-Pro:Desktop dengzhubo$ 
dengzhubodeMacBook-Pro:Desktop dengzhubo$ ./shuf.py -i 12-14 null.txt
line7
line2
line4
dengzhubodeMacBook-Pro:Desktop dengzhubo$ 
'''



