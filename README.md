# ***A Compiler For Monkeys*** 🐒
This compiler implementation was developed for CS 4318 @ Texas State University in the year 2022. This software takes monkeyC code and compiles it into assembly.

# Dependencies:
* GCC
* Ubuntu 22.04 LTS or later
* Lex
* Yacc

# Target Info:
*  MIPS Assembler and Runtime Simulator (https://computerscience.missouristate.edu/mars-mips-simulator.htm)

# Running The Code:
```
make clean && make
./obj/mcc ./test/*test file*.mC
```

* If you'd like to analyze the abstract syntax tree or the symbol table of the generated assembly simply add the --ast or --sym flags as seen below.

```
./obj/mcc --ast ./test/testVals.mC
```
or 
```
./obj/mcc --sym ./test/testVals.mC
```
