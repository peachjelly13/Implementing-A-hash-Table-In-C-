//This represents one item in my hash table there is an item and there is a value related to that item
typedef struct{
    char* key;
    char* value;
}hash_table_item;

//An array of items will be stored it is stored as pointers to hash_table_item , we store 
//multiple items in the hash table like this
//array of pointers to hash_table_items
//we also keep a track of the size of the hash table and how many items have been added

typedef struct{
    int size;
    int count;
    hash_table_item** items; //represents an array of pointers
}hash_table;

//this is what all our hash function can implement and it will implement the following API

void hash_table_insert(hash_table* ht, const char* key, const char* value);
void hash_table_delete_element(hash_table* ht,const char* key);
char hash_table_search(hash_table* ht, const char* key);