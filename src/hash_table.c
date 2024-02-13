#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

//creating a function hash_table_newItem and this function returns a pointer to hash_table_item
static hash_table_item* hash_table_newItem(const char* key_, const char* value_){
    hash_table_item* element = malloc(sizeof(hash_table_item));
    //storing the copy of our key and value using strdup (string duplicate)
    //This helps because its a pointer and any changes made to these values will be reflected in the same memory itself 
    //if the original strings are modified or deallocated elsewhere in the program.

    element->key = strdup(key_);
    element->value = strdup(value_);
    return element;

}