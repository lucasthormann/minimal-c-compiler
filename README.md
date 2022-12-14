#A compiler for "minimal" C
This compiler implementation was developed for CS 4318 @ TxState Uni
#Files Required to Build Parser:
*driver.c
*cgen.c - generates MIPS assembly
*cgen.h
*parser.y
*scanner.l
*symtab.c - generates the symbol tables
*symtab.h
*tree.c - generates the AST structure
*tree.h
*makefile
#Target Info
*MIPSs & the MARs simulator
*Compiled with GCC on Ubuntu
#Running mcc
Runs the parser against the input file
```
./mcc < inputFile.mC
```
Runs the parser against the input file and prints the AST
```
./mcc --ast < inputFile.mC
```
