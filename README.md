# Simple calculator
Simple yet powerful and easy to use CLI calculator written in C++
## installation
to install the calculator on Linux you can use the following commands
``` bash
$ git clone https://github.com/yous3fghazyv11/Simple-Calculator
$ cd Simple-Calculator/
$ sudo make install clean # creates 'calc' binary
$ calc # to run the program
```
if you would like to try the program without creating the binary `/usr/bin/calc` you can use:
``` bash
$ git clone https://github.com/yous3fghazyv11/Simple-Calculator
$ cd Simple-Calculator/
$ sudo make run clean # compiles and runs the program
```
## usage
you can use the calculator as a REPL or you can provide an input file as an argument
```
$ calc
> 3 + 3
6
```
or, if you have a file called e.g. test.txt with `3 + 3` as its contents, you can use:
```
$ calc test.txt
reading from file: test.txt
Expression: 3 + 3
output: 6
```
