#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strtab.h"


/* Provided is a hash function that you may call to get an integer back. */

// ST_init initializes strTable to default values
void ST_init()
{
    int i;
    for (i = 0; i < MAXIDS; i++)
    {
      strTable[i].id = "";
      strTable[i].scope = "";
      strTable[i].data_type = -1;
      strTable[i].symbol_type = -1;
    }
}

//hash calulates the hash for the index key for inserting.
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// ST_insert inserts id, scope, data_type, and symbol_type into StrTable using a hash.
// returns the index upon a sucessful insert.
int ST_insert(char *id, char *scope, int data_type, int symbol_type)
{
    int index = hash(id)%MAXIDS;    
    int i = index;  
    if (strcmp(strTable[i].id, "") == 0 || strcmp(strTable[i].id, id) == 1) {
      strTable[i].id = id;	  
      strTable[i].scope = scope;	  
      strTable[i].data_type = data_type;	  
      strTable[i].symbol_type = symbol_type;	  
      return i;
    } else {
      while (strcmp(strTable[i].id, "")) {
        i = (i + 1) % MAXIDS; //makes it circular
        if (i == index) { //we've made a complete iteration
          printf("\nstrTable is FULL OH NOOOOOOOOOO\n");
          return -1;
        }
      }
      strTable[i].id = id;	  
      strTable[i].scope = scope;	  
      strTable[i].data_type = data_type;	  
      strTable[i].symbol_type = symbol_type;	  
    }

    return i;
}

//ST_lookup returns an index given an id and scope
//returns the index if the value exists else it returns -1
int ST_lookup(char *id, char *scope) 
{
  int index = hash(id)%MAXIDS;    
	int i = index;
    while (strcmp(strTable[i].id, ""))
	{
	  if (strcmp(strTable[i].id, id))
		return i;
	  i = (i + 1) % MAXIDS; //makes it circular
	  if (i == index)
      {
    	  printf("\nstrTable is FULL OH NOOOOOOOOOO\n");
		  return -1;
	  }
	}
 	 
	return i;
}

//output_entry prints out a symbol in the symbal table given an index
//use ST_lookup before calling this function to ensure you have an existing value to check
void output_entry(int i){
    char *id_str = strTable[i].id;
    char *scope_str = strTable[i].scope;
    char *d_type;
    char *s_type;
    switch (strTable[i].data_type)
	{
	  case INT_TYPE: d_type = "INT_TYPE"; break;
	  case CHAR_TYPE: d_type = "CHAR_TYPE"; break;
	  case VOID_TYPE: d_type = "VOID_TYPE"; break;
	  default: d_type = "UNSUPPORTED_TYPE"; break;
	}
    switch (strTable[i].symbol_type)
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
}

