# ***A Compiler For Minimalists*** 
This compiler implementation was written in the year 2022 to serve as a capstone project of the computer science focused bachelor's degree program offered by Texas State University. I wrote this digital translator while enrolled in the university's Compiler Construction (CS 4318) course. This tool takes what is colloquially referred to as a Minimal C source code file as an argument via the command line and produces MIPS assembly code as output. 

## Development Environment:
* Acer Aspire E5-575 (x86_64)
* Red Hat Enterprise Linux 8.6
* GNOME Terminal
* Vi IMproved 8.2

# Dependencies:
* GCC 16.1 or newer
* GNU Make 4.3 or newer
* flex (The Fast Lexical Analyzer Generator) 2.6 or newer
* GNU Bison 3.8.2 or newer

# Target Info:
* The generated MIPS assembly code is intended to be converted into machine code and ran in a simulated hardware environment using the MIPS Assembler and Runtime Simulator (https://computerscience.missouristate.edu/mars-mips-simulator.htm)

# Building (i.e. preprocessing, compiling, assembling, and linking) & Running The Code:
```
make clean && make
./obj/mcc ./test/*test file*.mC > output.asm
```

* If you'd like to analyze the abstract syntax tree or the symbol table used to generate the MIPS assembly code simply add the --ast or --sym flags as seen below.

```
./obj/mcc --ast ./test/testVals.mC
```
or 
```
./obj/mcc --sym ./test/testVals.mC
```
