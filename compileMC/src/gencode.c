#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gencode.h"
#include "tree.h"   // definition for nodes of the AST
#include "strtab.h" // the symbol table for needed information about nodes

const char *register_names[32] = { "$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3",
                                   "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",  
                                   "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
                                   "$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra" }; 
// a flag to see if we have a header yet
int has_header = 0;
// a counter for jump labels to be made unique
int labelcounter=0;
// reset register counter (done after calling a func or at beginning of func)
int registercounter=7;
//An example of how / why for label counters
/*
Suppose we have:
FORNODE
FORNODE->children[0] = stmtnode (init)
FORNODE->children[1] = condnode (condition)
FORNODE->children[2] = compoundstmt (body)
FORNODE->children[3] = stmtnode (post)

void emitforstmt(tree *ast,FILE *outfile) {
  // Get a unique label number for the labels of this FORSTMT
  const int forlabel = nextlabel();

  // emit the for statement:
  fprintf(outfile,"FORSTMT_INIT%d: # Preparing to do for loop\n",
                  forlabel);
  gencode(ast->children[0],outfile);
  fprintf(outfile,"FORSTMT_COND%d: # For statement condition\n",
                  forlabel);
  // how you evaluate conditions will probably vary
  const int result = gencode(ast->children[1],outfile);
  // here I am assuming this register will equal zero if the condition is false
  fprintf(outfile,"beq %s, $zero, FORSTMT_END%d # Exit the for statement\n",
                  registernames[result], forlabel);
  // otherwise we do the body of the for loop
  fprintf(outfile,"FORSTMT_BODY%d: # Begin the for statement\'s body\n",
                  forlabel);
  // emit the body of the loop
  gencode(ast->children[2],outfile);
  // do the post expression
  fprintf(outfile,"FORSTMT_POST%d: # For statement post statement\n",
                  forlabel);
  // We need to return to the for loop's condition
  fprintf(outfile,"j FORSTMT_COND%d # Return to for condition\n",
                  forlabel);
  // Now we print the label for the for statement exit
  fprintf(outfile,"FORSTMT_END%d: # End of for loop\n",
                  forlabel);
}
int gencode(tree *ast,FILE *outfile) {
  switch(ast->nodeKind) {
  case FORSTMT:
    emitforstmt(ast,outfile); return 0;
  }
  // if we don't return a value in the switch statement then it wasn't handled
  // returning -1 should cause a seg-fault if used to index registernames[]
  return -1;
}
*/

/*
 * The following page is a good reference for MIPS
https://ecs-network.serv.pacific.edu/ecpe-170/tutorials/mips-instruction-set
*/
int gencode(tree *ast/*,FILE *outfile*/) {
  if (!has_header) {
    make_header();
    has_header = 1;
  }
  // variables can't be defined inside a switch
  // move more complicated things to their own function to keep this cleaner
  // (e.g., function definition needs to setup/teardown stack, ...)
  int lhs,rhs,dst;
  tree *tree_baby = ast->children[0];
  for (int i = 0; i < tree_baby->numChildren; i++) { 
	  switch(tree_baby->children[i]->nodeKind) {
	// output(6);
	    case INTEGER:
	      dst = get_register();
	      //fprintf(outfile,"li %s, %d\n", registernames[dst], ast->value);
	      printf("li %s, %d\n", register_names[dst], ast->val);
	      return dst;
	/*
	 *     FUNCCALLNODE
	 *     ARGLIST
	 *     EXPRESSION , ....
	 */
	    case EXPRESSION:
	      break;
	    case ARGLIST:
	      break;
	    case VARDECL:
	      //2 cases: either a global or local declaration
	      //if (ast->scope == 0) //if true then it should be added to a list to be printed as part of make_footer()
	      //printf("%s: .word 4\n", tree_baby->children[i]->children[1]->nodeName);
              
	      break;
	    case FUNDECL:
	      setup_frame();
	      resetregisters();
	      //for all statements in funcdefnode emitcode();
	      teardown_frame_and_restore();
	      set_return_value();
	      //if (ast->children[1]->nodeName != NULL && strcmp(ast->children[1]->nodeName,"main")==0)
		syscall_for_clean_exit();
	      //else {
		//fprintf(outfile,"jr $ra\n");
	      //}
	      break;
	    case FUNCCALLEXPR:
	      if (strcmp(ast->children[0]->nodeName, "output")) {
		rhs = gencode(ast->children[0]->children[0]);
		printf("li $v0, 1\n");
		printf("mov $a0, %s\n",register_names[rhs]);
		printf("syscall\n");
	      }
	      else {
		// save registers, prepare to move context
		// resolve arguments, put them where appropriate
		// jump and link to function label
		// immediately after jump and link all $t_ registers are garbage.
		// return value will be (somewhere)
		reset_registers();
		// anything needed will have to be restored from the stack
	      }
	      // return 0, break, (?)
	      return 0;
	      break;
	    default: break;
	  }
  }
  return -1; // (?)
}

/*
Number  | Name      | Description
0       | $zero     | The value 0
2-3     | $v0 - $v1 | (values) from expression evaluation and function results
4-7     | $a0 - $a3 | (arguments) First four parameters for subroutine
8-15    | $t0 - $t7 | Temporary variables
16-23   | $s0 - $s7 | Saved values representing final computed results
24-25   | $t8 - $t9 | Temporary variables2
31      | $ra       |Return address
*/
// get the next available register
// this naiively just cycles through $t0 -> $t9 -> $t0
int nextreg() {
  // jump the gap from $t7 to $t8
  if (++registercounter == 16) registercounter = 24;
  // wrap from $t9 to $t0
  else if (registercounter == 26) registercounter = 8;
  return registercounter;
}

void setup_frame() {
	printf("          sw      $fp, 0($sp)      #previous fp\n");
	printf("          sw      $ra, -4($sp)     #previous ra\n");
	printf("          addu    $fp, $zero, $sp  #current fp\n");
      //printf("          addiu   $sp, $sp, X	   #function stack (main)"\n);
      //^^X is the # of instructions * 4
	/*Calling a Subroutine (done by caller func):
	 * 1. Push any registers $t0-t9 that contain vals that must be saved.
	 * 2. Put argument vals into $a0-$a3.
	 * 3. Call the subroutine with jal.
	 * Subroutine Prolog (done by subroutine):
	 * 4. Push $ra.
	 * 5. Push caller's Frame Pointer $fp.
	 * 6. Push any registers $s0-$s7 that the subroutine might alter.
	 * 7. Init. $fp = $sp - space_for_vars (space_for_vars = 4 * # of local vars)
	 *    NB: Subtracting from the $sp grows the stack and vars are always 4 Bytes
	 * 8. Init. $sp = $fp
	 */

	return;
}
void reset_registers() {
	registercounter = 7;
	return;
}
void set_return_value() {
	return;
}
void syscall_for_clean_exit() {
  //I think calling make_footer() at the end of this function
  //is the way.
  printf("          li      $v0,10\n          syscall                  # Code for syscall: exit\n");
	//make_footer();
	return;
}
void teardown_frame_and_restore() {
	/*
	 * 1. Put wanted vals in $v0 and $v1 as necessary.
	 * 2. $sp = $fp + space_for_vars.
	 * 3. Pop into $s0-$s7 any vals for them that were previously saved
	 * in the frame. (Refer to note 6 in setup_frame().)
	 * 4. Pop caller's frame pointer into $fp.
	 * 5. Pop $ra.
	 * 6. Return to caller function using: jr $ra.
	 * Not sure if this last step should be inlcuded as a last step in 
	 * this function but the caller function needs to pop registers $t0-$t9
	 * that the caller previously pushed. This step can be hardcoded back in the
	 * switch statement following this call.
	 */
	return;
}
int get_register(){
	return 7;
}
void make_header() { //this will be called once in the beginning.
  printf("          .text\n          .globl main\n\nmain:\n");
  return;
}
void make_footer() { //this will be called once at the end.
  //this will add the list of global variables declared in the prog
  //with their respective starting values.
  //printf("          .data\nvar:\t.word %d",var value); 
  return;
}
