#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include"prime.h"
#include"prime.c"
HASH_TABLE_INITIAL_BASE_SIZE = 53;
    
static hash_table_item* hash_table_deleted_item = {NULL,NULL};


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



hash_table* hash_table_different_sized(const int variable_size){
    hash_table* new_ = xmalloc(sizeof(hash_table));
    new_->variable_size = variable_size;
    new_->size = next_prime(new_->variable_size); ////this value defines how many items can it store
    new_->count = 0;//how full it is 
    new_->items = xcalloc((size_t)new_->size,sizeof(hash_table*));;
    return new_;
}

//Creating new hash table instance and initializing it with certain properties.
hash_table* hash_table_new(){
    hash_table_different_sized(HASH_TABLE_INITIAL_BASE_SIZE);
    
    
}

//functions for deleting so that we free the memory an do not cause memory leaks
static void hash_table_delete_item(hash_table_item* element){
    free(element->key);
    free(element->value);
    free(element);

}

void hash_table_delete(hash_table* new_){
    for(int start = 0;start<new_->size;start++){
        hash_table_item* item = new_->items[start];
        if(item!=NULL){
            hash_table_delete_item(item);
        }
    }
    free(new_->items);
    free(new_);

}

static int hash_table_hash(const char *string_, const int prime_number, const int modulus_value){
    long hash = 0;
    const int len_string = len(string_);
    for(int i =0;i<len_string;i++){
        hash+= (long) pow(prime_number,len_string-(i+1))*string_[i];
        hash = hash %modulus_value;

    }
    return hash;
}

static int hash_table_get_hash(const char* string_,const int modulus_value , const int no_of_attempts){
    const int hash_a = hash_table_hash(string_,151,modulus_value);
    const int hash_b = hash_table_hash(string_,191,modulus_value);
    return (hash_a+(no_of_attempts*(hash_b+1)))%modulus_value;
}

//for inserting value in the hash_table
void hash_table_insert(hash_table *ht,const char * key,const char* value){
    hash_table_item* item = hash_table_newItem(key,value);
    int index = hash_table_hash(item->key,0,ht->size);
    hash_table_item* current_item = ht->items[index];
    int i = 1;
    while(current_item!=NULL && current_item!=&hash_table_deleted_item){
        if(current_item!=&hash_table_deleted_item){
            if (strcmp(current_item->key, key) == 0) {
                ht_del_item(current_item);
                ht->items[index] = item;
                return;
            }
        }
        index = hash_table_get_hash(item->key,i,ht->size);
        current_item = ht->items[index];
        i++;
    }
    ht->items[index]= item;
    ht->count++;


}

//for searching a particular value in the hash table
//searching a value by its key
char hash_table_search(hash_table *ht, const char* key){
    int index = hash_table_get_hash(key,0,ht->size);
    hash_table_item* item = ht->items[index];
    int i = 1;
    while(item!=NULL){
        if(item!=&hash_table_deleted_item){

        if(strcmp(item->key,key)){
            return item->value;
        }}
        index = hash_table_get_hash(ht,i,ht->size);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void hash_table_delete_element(hash_table* ht, const char* key){
    int index = hash_table_get_hash(key,0,ht->size);
    hash_table_item* item = ht->items[index];
    int i = 1;
    while(item!=NULL){
        if(item!=&hash_table_deleted_item){
            if(strcmp(item->key,key)==0){
                hash_table_delete_item(item);
                ht->items[index] = &hash_table_deleted_item;
            }
        }
        index = hash_table_hash(ht,i,ht->size);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

