#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include "strtab.h"


/* Provided is a hash function that you may call to get an integer back. */
param *working_list_head = NULL;
param *working_list_end = NULL;
table_node *current_scope = NULL; // A global variable that should point to the symbol table node in the scope tree as discussed in lecture 13 and 14.

// ST_init initializes // to default values
void ST_init(){
    int i;
    working_list_head = NULL;
    working_list_end = NULL;
    current_scope = NULL;
}

//hash calulates the hash for the index key for inserting.
unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

// ST_insert inserts id, scope, data_type, and symbol_type into the current_scope's StrTable using a hash.
// returns the index upon a sucessful insert.
int ST_insert(char *id, char *scope, int data_type, int symbol_type,  int sz) {
  int index = hash((unsigned char *)strcat(id, scope));
  int key = index%MAXIDS;
  if (current_scope->strTable[key]->id == NULL){
    //the hash table has an empty entry at this key
    setSymEntry(key, id, scope, data_type, symbol_type, sz);
    return -1;
  }else if(strcmp(current_scope->strTable[key]->id, id) == 0){ //the hash table has the same entry at this key already
    return key;
  }else{ //the symEntry isn't NULL or the entry at the symEntry is not the id we want to insert
    //we don't know if the key exists already or if there is no entry
    //might need to create a new lookup that only takes the current scope in mind
    //st_lookup now checks for the global scope, we can't use that function here,
    //we should create another helper to check only the current_scope to find if it has an entry.
    int symbol = entryLookUp(id);
    if(symbol == -1){ //if the symbol doesn't exists
      //find a place to put the symbol
      key = linear_probe(key, id);
      //if the key is not -1 then we have an empty spot to check,
      //if the key is -1 then we just return.
      setSymEntry(key, id, scope, data_type, symbol_type, sz);
      return key;
    }else{ //the symbol does exist
      //Should we probe? Not sure what we do in the event a value is updated.
      key = symbol;
      return key;
    }
  }
  //we somehow got through all the conditionals and we don't know what the fuck is going on.
  return key;
}

/*
 * Looks up str_table for an id to see if an entry already exists.
 * If the entry does exist we return the index else we return -1.
 * Only use this function if we already know there was a conflict in the hash table.
*/
int entryLookUp(char *id){
  for(int i = 0; i < MAXIDS; i++){
    if(strcmp(id, current_scope->strTable[i]->id) == 0){
      return i;
    }
  }
  return -1;
}

/*
 * If we have an empty spot and the variable does not exist in the table then we 
 * use linear probe to find an empty spot.
 * if the variable/function exists then we return -1
 * else return the key to insert into.
*/
int linear_probe(int key, char *id){
  //we're looking for a id that is empty
  //with linear probe we know the id does not exist in the symbolTable of the current scope.
  for(int i = key+1; i <= MAXIDS; i++){
    char *currId = current_scope->strTable[i]->id;
    int key = i;
    if(strcmp(currId, id)){
      //we found an empty spot.
      return key;
    }
  }
  return -1;
}

void setSymEntry(int key, char *id, char *scope, int data_type, int symbol_type, int sz){
  if(current_scope->strTable[key] != NULL){
    current_scope->strTable[key]->id = id;
    current_scope->strTable[key]->scope = scope;
    current_scope->strTable[key]->data_type = data_type;
    current_scope->strTable[key]->symbol_type = symbol_type;
    current_scope->strTable[key]->size = sz;
  }
}


//ST_lookup returns an index given an id and scope
//returns symEntry if the symbol exists in the current scope.
symEntry* ST_lookup(char *id, char *scope){
  int index = hash((unsigned char*)id)%MAXIDS;    
	int i = index;
  table_node *global_scope = NULL;
  if(current_scope->parent != NULL){
    //check if we're in a child scope or the global scope
    //set global scope if we're not in the child scope
    global_scope = current_scope->parent;
  }
  if(global_scope != NULL){
    //we check both global and child scope
    for(int j = 0; j < MAXIDS; j++){
      char *check_id = current_scope->strTable[j]->id;
      if(strcmp(id, check_id) == 0){
        return current_scope->strTable[j];
      }
    }
    for(int j = 0; j < MAXIDS; j++){
      char *check_id = global_scope->strTable[j]->id;
      if(strcmp(id, check_id) == 0){
        return current_scope->strTable[j];
      }
    }
  }else{
    //global scope is NULL we're already in the global scope.
    for(int j = 0; j < MAXIDS; j++){
      char *check_id = current_scope->strTable[j]->id;
      if(strcmp(id, check_id) == 0){
        return current_scope->strTable[j];
      }
    }
  }
  return NULL;
}

void add_param(int data_type, int symbol_type){
  if(working_list_head == NULL && working_list_end == NULL){
    param *newscope = param_buddy();
    newscope->data_type = data_type;
    newscope->symbol_type = symbol_type;
    working_list_head = newscope;
    working_list_end = newscope;
    working_list_head->next = working_list_end;
   } else {
    param *newscope = param_buddy();
    param *oldscope = working_list_end;
    newscope->data_type = data_type;
    newscope->symbol_type = symbol_type;
    oldscope->next = newscope;
    working_list_end = newscope;
   }
}

//Might need another helper for this.
void connect_params(char* name, char *scope){
  symEntry* token = ST_lookup(name, scope);
  if(token != NULL){
    token->params = working_list_head;
  }
  working_list_head = NULL;
  working_list_end = NULL;
}

//helper function for mem allocation and init for PARAMS
param* param_buddy() {
    param *newscope = (param*)malloc(sizeof(struct param));
    newscope -> data_type = -1;
    newscope -> symbol_type = -1;
    newscope -> next = NULL;
    
    return newscope;
}

void new_scope(){
  //if first and last child is null then we malloc and set first and last child to that node
  if(current_scope == NULL){
    table_node* newscope = scope_buddy();
    current_scope = newscope;
    return;
  }
  if(current_scope->first_child == NULL && current_scope->last_child == NULL){
    table_node *newscope = scope_buddy();
    newscope->parent = current_scope;
    current_scope->first_child = newscope;
    current_scope->last_child= newscope;
    current_scope->first_child->next = current_scope->last_child;
    current_scope->last_child->next = NULL;
    current_scope->numChildren++;
    current_scope = newscope;
  }else if(current_scope->first_child == current_scope->last_child){
    table_node* newscope = scope_buddy();
    newscope->parent = current_scope;
    current_scope->last_child = newscope;
    current_scope->numChildren++;
    current_scope = newscope;
  }else{
    /*the current scope already has 1 or more children we allocate for a newscope and set the current 
    last next pointer to the new scope and then set newscope to be the last child*/
    table_node* newscope = scope_buddy();
    newscope->parent = current_scope;
    current_scope->last_child->next = newscope;
    current_scope->last_child = newscope;
    current_scope->numChildren++;
    current_scope = newscope;
  }
}
//helper function for mem allocation and init
table_node* scope_buddy() {
    table_node *newscope = (table_node*)malloc(sizeof(struct table_node));
    for (int i = 0; i < MAXIDS; i++) {
      newscope->strTable[i] = (symEntry*)malloc(sizeof(struct symEntry));
      newscope->strTable[i]->id = NULL;		
      newscope->strTable[i]->scope = NULL;		
      newscope->strTable[i]->data_type = -1;		
      newscope->strTable[i]->symbol_type = -1;		
      newscope->strTable[i]->size = 0;		
      newscope->strTable[i]->params = NULL;		
    }
    newscope -> parent = NULL;
    newscope -> first_child = NULL;
    newscope -> last_child = NULL;
    newscope -> next = NULL;
    newscope -> numChildren = 0;
    
    return newscope;
}

//Upscope moves up a level
void up_scope(){
  if(current_scope != NULL){
    table_node *parent = current_scope->parent;
    if(parent != NULL){
      current_scope = parent;
    }
  }else{
    printf("Can't do that babe.\n");
  }
}

//output_entry prints out a symbol in the symbal table given an index
//use ST_lookup before calling this function to ensure you have an existing value to check
void output_entry(int i){
    char *id_str = NULL; //[i].id;
    char *scope_str = NULL;//[i].scope;
    char *d_type;
    char *s_type;
    /*
    switch ([i].data_type)
	{
	  case INT_TYPE: d_type = "INT_TYPE"; break;
	  case CHAR_TYPE: d_type = "CHAR_TYPE"; break;
	  case VOID_TYPE: d_type = "VOID_TYPE"; break;
	  default: d_type = "UNSUPPORTED_TYPE"; break;
	}
    switch (//[i].symbol_type)
	{
	  case SCALAR: s_type = "SCALAR"; break;
	  case ARRAY: s_type = "ARRAY"; break;
	  case FUNCTION: s_type = "FUNCTION"; break;
	  default: s_type = "UNSUPPORTED_TYPE"; break;
	}	

  if (strcmp(s_type, "UNSUPPORTED_TYPE")){
     printf("%d: %s \n", i, d_type);
     printf("%s:%s %s\n", scope_str, id_str, s_type);
  }
  */
}

