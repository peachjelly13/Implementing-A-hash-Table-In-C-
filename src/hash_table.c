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

//Creating new hash table instance and initializing it with certain properties.
hash_table* hash_table_new(){
    hash_table* new = malloc(sizeof(hash_table));
    new->size = 53; //this value defines how many items can it store
    new->count = 0; //how full it is
    new->item = calloc((size_t)new->size,sizeof(hash_table*));
    return new;
    
}

//functions for deleting so that we free the memory an do not cause memory leaks
static void hash_table_delete_item(hash_table_item* element){
    free(element->key);
    free(element->value);
    free(element);



}