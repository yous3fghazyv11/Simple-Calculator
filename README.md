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
you can use the calculator as a REPL
```
$ calc
> 3 + 3
6
```

the calculator accepts basic expressions with the operators: `+` `-` `*` `/` `(` `)` `^` `!`
```
> 3 ^ ( ( 8 - 2 * 3 )! )
6
```

you can use spaces however you see fit
```
> 3^((8-2*3)!)
6
```

also the calculator gives reasonable error messages for bad expressions
```
> # we removed the ')' at the end
> 3 ^ ( ( 8 - 2 * 3 )!
')' expected
> 2.2!
factorial of non-integer not allowed
```

as you can see we can also use comments.  

you can also define variables
```
> let my_var = 3 ^ ( ( 8 - 2 * 3 )!
6
> my_var!
720
> let my_var_fac = my_var!
720
> my_var_fac
720
```

once you define a variable, you can use it in your expressions as if it was a number.  

you can also assign to variables
```
> let x = 3
3
> x = 4
4
> x
4
> let y = let z = 5
5
> x = y = z = 1
1
> x
1
> y
1
> z
1
```

## configuration
if you find yourself using a lot of variables, like for example `pi` or `e`, you can define them
in `$HOME/.config/calc/calc.conf`, the syntax is the same for the REPL, and the calculator
will evaluate the expressions in that file before it starts the REPL.
### $HOME/.config/calc/calc.conf
```
# scientific constants
let pi = 22/7
let e = 2.71828
let var_i_use_a_lot = 44.87
```
and the next time the calculator loads it will evaluate these expressions so that you can use
them in your calculations without having to define them each time.

## <mark>TODO:</mark> add support for functions
the next step is going to be the ability to define functions:
```
> def f(x, y): x * y
> 12 + f(3, 4)
24
> def g(x): x^2
> 12 + f(3, g(2))
24
```
