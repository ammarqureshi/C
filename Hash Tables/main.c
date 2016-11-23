#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    char *str;
    struct node *next;
} list;

typedef struct hash_table {
    int size;       /* the size of the table */
    list **table; /* the table elements */
} hash_table;


hash_table *create_hash_table(int size)
{
    hash_table *new_table;

    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    new_table = malloc(sizeof(hash_table));



    /* Attempt to allocate memory for the table itself */
    new_table->table = malloc(sizeof(list) * size);

int i;
    /* Initialize the elements of the table */
    for(i=0; i<size; i++) new_table->table[i] = NULL;

    /* Set the table's size */
    new_table->size = size;

    return new_table;
}

unsigned int hash(hash_table *hashtable, char *str)
{
    unsigned int hashval;



unsigned hash = 0;  int i;
  for ( i = 0; str[i] != '\0'; i++ ) {
    hash = hash * 37 + str[i];
  }


//    /* we then return the hash value mod the hashtable size so that it will
//     * fit into the necessary range
//     */

  return hash % hashtable->size;

  //  return hashval % hashtable->size;
}




int *lookup_string(hash_table *hashtable, char *str)
{
    list *list;
    unsigned int hashval = hash(hashtable, str);

    /* Go to the correct list based on the hash value and see if str is
     * in the list.  If it is, return return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL.
     */
     if(hashtable->table[hashval] == NULL) return NULL;
    for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, list->str) == 0) return 1;
    }
    return 0;
}


void add_string(hash_table *hashtable, char *item)
{
    list *new_list;
    list *current_list;
    unsigned int hashVal = hash(hashtable, item);
   // current_list = malloc(sizeof(list));
    /* Attempt to allocate memory for list */
    new_list = malloc(sizeof(list));

    int res= lookup_string(hashtable, item);
    //if res is 1 dont add
    if (res == 0){

    new_list->str = item;
    new_list->next =hashtable->table[hashVal];
   hashtable->table[hashVal]= new_list;
    }


}


// remove string from the hash table, no effect if not in table
void remove_str(hash_table *hashtable, char *item){

list *list,*q,*prevlist;
unsigned int hashVal = hash(hashtable, item);

int res= lookup_string(hashtable, item);
//no node
if(res==0){return;}

//one node
else if(strcmp(item,hashtable->table[hashVal]->str)==0){

    if(hashtable->table[hashVal]->next!=NULL){
        //list = hashtable->table[hashVal]->next;
        hashtable->table[hashVal]= hashtable->table[hashVal]->next;
        //free(list);
    }
    //else if not linked,only element.
    else{
        hashtable->table[hashVal]=NULL;

    }



}


else{
    int found=0;
    prevlist = hashtable->table[hashVal];
    //list = prevlist->next;
    while(found==0){
    list = prevlist->next;
    if(strcmp(item,list->str)==0){

    prevlist->next = list->next;

//        q = list->next;     //NODE TO DELETE.
//        list->next = q->next;
        free(list);
        found =1;
        return;
    }
    prevlist = list;
    list = list->next;
}
}


}




void free_table(hash_table *hashtable)
{
    int i;
    list *list, *temp;


    /* Free the memory for every item in the table, including the
     * strings themselves.
     */
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
    }

//     Free the table itself
    free(hashtable->table);
    free(hashtable);

}


// print out each entry in the hash table and the values
// stored at that entry
void print(hash_table * hashtable){

 int i;
list *list, *temp;

 for(i=0; i<hashtable->size; i++) {
    list = hashtable->table[i];
    printf("\n");
    printf("%d\t",i);



        while(list!=NULL){
        temp = list;
        list = list->next;
        printf("%s \t",temp->str);

        }


    }


printf("\n");
}



int main(int argc,const char*argv[]){

printf("argc:%d \n",argc);
int i;
//+ glub + moonlight +  I +  "a fish" +  am - moonlight =
hash_table *my_hash_table;

my_hash_table = create_hash_table(9);

printf("size is: %d",my_hash_table->size);


for(i=1;i<argc;i++){

   // printf("argv[%d]:%s \n",i,argv[i]);

    if(strcmp(argv[i],"+")==0){

        add_string(my_hash_table,argv[++i]);

    }

    if(strcmp(argv[i],"-")==0){
    //print(my_hash_table);

    remove_str(my_hash_table,argv[++i]);

    }

    if(strcmp(argv[i],"=")==0){

    print(my_hash_table);


    }
}

return 0;
}
