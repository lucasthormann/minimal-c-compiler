#ifndef TREE_H
#define TREE_H

#define MAXCHILDREN 100
#include "strtab.h"

typedef struct treenode tree;

enum nodeKinds {
  PROGRAM,
  DECLLIST,
  DECL,
  VARDECL,
  TYPESPEC,
  FUNDECL,
  FORMALDECLLIST,
  FORMALDECL,
  FUNBODY,
  LOCALDECLLIST,
  STATEMENTLIST,
  STATEMENT,
  COMPOUNDSTMT,
  ASSIGNSTMT,
  CONDSTMT,
  LOOPSTMT,
  RETURNSTMT,
  EXPRESSION,
  RELOP,
  ADDEXPR,
  ADDOP,
  TERM,
  MULOP,
  FACTOR,
  FUNCCALLEXPR,
  ARGLIST,
  INTEGER,
  IDENTIFIER,
  VAR,
  ARRAYDECL,
  CHAR,
  FUNCTYPENAME,
  VOID
};

/* tree node - you may want to add more fields */
struct treenode {
      int nodeKind;
      int numChildren;
      int val;
      int scope; // Used for var/id. Index of the scope. This works b/c only global and local.
      int type;
      int sym_type; // Only used by var to distinguish SCALAR vs ARRAY
      int mathVal;
      int match;
      char *nodeName;
      tree *parent;
      tree *children[MAXCHILDREN];
};

extern tree *ast; /* pointer to AST root */

/* builds sub tree with zeor children  */
tree *maketree(int kind);

/* builds sub tree with leaf node */
tree *maketreeWithVal(int kind, int val);

tree *maketreeWithID(int kind, char *name);

void addChild(tree *parent, tree *child);

void mathVal(tree *node);

void checkMatch(tree *currTree);

void printAst(tree *root, int nestLevel);
char *getID(tree *tree);


/* Adds all children of sublist to list */
void flattenList(tree *list, tree *subList);

/* tree manipulation macros */
/* if you are writing your compiler in C, you would want to have a large collection of these */

#define nextAvailChild(node) node->children[node->numChildren]
#define getChild(node, index) node->children[index]

#endif
