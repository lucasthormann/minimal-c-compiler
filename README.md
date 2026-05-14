# ***A Compiler For Minimalists*** 
This compiler implementation was developed for CS 4318 @ Texas State University in the year 2022. This software takes what is colloquially referred to as a Minimal C source code file as input and compiles it into the MIPS assembly language.

# Dependencies:
* GCC 16.1 or newer
* Ubuntu 22.04 LTS or later
* GNU Make
* flex (The Fast Lexical Analyzer Generator) 2.6 or newer
* GNU Bison

# Target Info:
*  The generated MIPS assembly code is intended to be assembled into binary and ran in a simulated hardware environment using the MIPS Assembler and Runtime Simulator (https://computerscience.missouristate.edu/mars-mips-simulator.htm)

# Running The Code:
```
make clean && make
./obj/mcc ./test/*test file*.mC
```

* If you'd like to analyze the abstract syntax tree or the symbol table used to generate the MIPS assembly code simply add the --ast or --sym flags as seen below.

```
./obj/mcc --ast ./test/testVals.mC
```
or 
```
./obj/mcc --sym ./test/testVals.mC
```
