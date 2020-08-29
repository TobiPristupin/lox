# lox

C++ port of the Interpreter for the lox programming language created by Bob Nystrom in the book Crafting Interpreters.

### Goal
The goal of the project was to write the interpreter using modern C++ idioms and features such as smart pointers, RAII, std::optional, etc.
I tried to write the code in such a way that if someone else were to read it they wouldn't feel that it was a port of a Java program.

### Differences from the original

* Added support for 'break' and 'continue'.
* Added support for postfix and prefix `++` and `--`. They work the same way they do in C/C++.
* Added support for lambda expressions following Python's syntax. Use them like this `var add = lambda a, b : a + b;`. One limitation of lambda's is that they can only contain one expression as their body (not a statement!) so you can't print from a lambda because print is a statement in Lox.
* Replaced 'else if' with 'elif'.
* `print` supports "\n" and "\t", and an empty `print` statement will automatically print a newline.
* Added a native function called `str` that takes in one argument and returns its string representation.
* Created a `ScopedEnvironment` type following RAII principles that will pop itself from the environment chain during cleanup .
* There is no AST Printer class as I found it easier to use Clion's debugger to inspect the AST.
* The book uses Java's `Object` class to represent Lox types (variables, functions, classes, etc). I decided to create a `LoxObject` class that wraps around all of the Lox types and provides more type safety than the book's approach.
* The visitor pattern does not use templates because it was impossible to implement in C++ without compromising other areas of the code. Instead visitor methods for expressions return `LoxObject` and visitor methods for statements return `void`. This is fine because the visitor's return values are really only used by the interpreter, and the resolver can just return dummy values as they will never be used.

I drew some inspiration from other C++ ports such as https://gitlab.com/aggsol/lox-simple and https://github.com/ThorNielsen/loxint .
