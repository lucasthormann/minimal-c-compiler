#ifndef STRTAB_H
#define STRTAB_H
#define MAXIDS 1000

#include <stddef.h>


enum dataType {INT_TYPE, CHAR_TYPE, VOID_TYPE};
enum symbolType {SCALAR, ARRAY, FUNCTION};

typedef struct param{
    int data_type;
    int symbol_type;
    struct param* next;
} param;

extern param *working_list_head;
extern param *working_list_end;

typedef struct symEntry{
    char* id;
    char* scope;
    int   data_type;
    int   symbol_type;
    int   size; //Num elements if array, num params if function
    param*  params;
} symEntry;


/* You should use a linear linklist to keep track of all parameters passed to a function. The working_list_head should point to the beginning of the linklist and working_list_end should point to the end. Whenever a parameter is passed to a function, that node should also be added in this list. */
extern param *working_list_head;
extern param *working_list_end;

typedef struct table_node{
    symEntry* strTable[MAXIDS];
    int numChildren;
    struct table_node* parent;
    struct table_node* first_child; // First subscope
    struct table_node* last_child;  // Most recently added subscope
    struct table_node* next; // Next subscope that shares the same parent
} table_node; // Describes each node in the symbol table tree and is used to implement a tree for the nested scope as discussed in lecture 13 and 14.

extern table_node *current_scope; // A global variable that should point to the symbol table node in the scope tree as discussed in lecture 13 and 14.

//Initializes our variables to be null
void ST_init();

/* Inserts a symbol into the current symbol table tree. Please note that this function is used to instead into the tree of symbol tables and NOT the AST. Start at the returned hash and probe until we find an empty slot or the id.  */
int ST_insert(char *id, char *scope, int data_type, int symbol_type, int sz);

void setSymEntry(int key, char *id, char *scope, int data_type, int symbol_type, int sz);

int linear_probe(int key, char *id);

int entryLookUp(char *id);

/* The function for looking up if a symbol exists in the current_scope. Always start looking for the symbol from the node that is being pointed to by the current_scope variable*/
symEntry* ST_lookup(char *id, char *scope);

/* Creates a param* whenever formalDecl in the parser.y file declares a formal parameter. Please note that we are maining a separate linklist to keep track of all the formal declarations because until the function body is processed, we will not know the number of parameters in advance. Link list provides a way for the formalDecl to declare as many parameters as needed.*/
void add_param(int data_type, int symbol_type);

param *param_buddy();

/*connect_params is called after the funBody is processed in parser.y. At this point, the parser has already seen all the formal parameter declaration and has built the entire list of parameters to the function. This list is pointed to by the working_list_head pointer. current_scope->parent->strTable[index]->params should point to the header of that parameter list. */
void connect_params(char* name, char *scope);

// Creates a new scope within the current scope and sets that as the current scope.
void new_scope();

table_node* scope_buddy();

// Moves towards the root of the sym table tree.
void up_scope();

#endif
