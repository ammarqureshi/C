#include <stdio.h>
#include <stdlib.h>
# define MASK 0
#include <string.h>


struct bitset{
unsigned char *vector;
int size;
int sizeInBytes;
};

void printSet(struct bitset *set){
printf("\n");
int i;
for(i=0;i<set->size;i++){

    int cmp = get_Item(set,i);
    if(cmp==1){
        //get position.
        char value = (char)i;
        printf(" %c " ,value);
    }

}

}

void bitset_union(struct bitset * dest, struct bitset * src1,struct bitset * src2){

	int ix;
for(ix=0;ix<dest->size;ix++){

int lk1 = lookup(src1,ix);
int lk2 = lookup(src2,ix);

if(lk1==1 | lk2==1){
    add(dest,ix);
}

	}

}


void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2){
int minSize;
//have bitset 1 and bitset 2
//what is common between the two bit arrays?
if((src1->size) > (src2->size)){
minSize = src2->size;
}

else{
    minSize = src1->size;
}

int ix;
//iterate through indixes.
for(ix=0;ix<minSize;ix++){

int lk1 = lookup(src1,ix);
int lk2 = lookup(src2,ix);
if(lk1==1 && lk2==1){
    add(dest,ix);
}

}




};


int bit_remove(struct bitset *set, int item){

int index = item/(sizeof(unsigned char)*8);
int position = item % (sizeof(unsigned char) * 8);


if(item>=0 && item<set->size){

set->vector[index] = set->vector[index] & (~(1<<position));

return 1;
}

else{

    return 0;
}



}
int get_Item(struct bitset *set,int item){

int index = item/(sizeof(unsigned char)*8);
int position = item % (sizeof(unsigned char) * 8);

if((set->vector[index] & 1<<position) == 1<<position){
return 1;
}
else{
    return 0;
}

}



int lookup(struct bitset *set,int item){

int index = item/(sizeof(unsigned char)*8);
int position = item % (sizeof(unsigned char) * 8);
//if within bounds.
if(item>=0 && item<set->size){

if((set->vector[index] & 1<<position) == 1<<position){

    return 1;
}
else{
    return 0;
}



}

else{
        //out of bounds.
    return -1;

}

}




int add(struct bitset *set, int item){

int index = item/(sizeof(unsigned char)*8);
int position = item % (sizeof(unsigned char) * 8);
if(item>=0 && item<set->size){

set->vector[index] = set->vector[index] | 1<<position;
return 1;

}

else{
    return 0;
}




}


struct bitset *new_set(int size){
struct bitset *set;

set = malloc(sizeof(struct bitset));
set->vector = calloc(size,sizeof(char));
int i;
for(i=0;i<size;i++){

    set->vector[i]=0;

}
set->size = size;

set->sizeInBytes = size/(sizeof(unsigned char) *8) + 1;


return set;

};


int main()
{

char *myInput[50];
int index=0;
const int STRING = 256;
char sent[STRING];
printf("\nEnter first set:\n");
fgets(sent,STRING,stdin);

size_t length = strlen(sent);
char * newBuffer = (char *)malloc(length);
memcpy(newBuffer,sent,length);

struct set *set1;
//create first set.
set1 = new_set(255);
int ie;
for(ie=0;ie<length-1;++ie){

    char val = newBuffer[ie];
    printf("\n val buff:%c \n",newBuffer[ie]);
    int pos = (int)val;
    add(set1,pos);
    printf(" charVal: %d \n",pos);


}


char sent2[STRING];
printf("\nEnter second set :\n");
fgets(sent2,STRING,stdin);

length = strlen(sent2);
char * newBuffer2 = (char *)malloc(length);
memcpy(newBuffer2,sent2,length);

struct set *set2;
//create set.
set2 = new_set(255);

for(ie=0;ie<length-1;++ie){

    char value2 = newBuffer2[ie];
    printf("\n val buff:%c \n",newBuffer2[ie]);
    int pos2 = (int)value2;
    add(set2,pos2);
    printf("  charVal: %d \n", pos2);


}

struct set *dest;
dest = new_set(255);
printf("\n intersection");
bitset_intersect(dest,set1,set2);
printSet(dest);

struct set *dest2;
dest2 = new_set(255);

printf("\n union ");
bitset_union(dest2,set1,set2);

//printSet(set1);
//printSet(set2);
printSet(dest2);



}



