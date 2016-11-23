#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define COMPARE(parent,child)   ((parent)>=(child))
#define RightChild(x) (2*x)+ 2
#define LeftChild(x)  (2*X) + 1




struct node{
int isLeaf;
int freq;
char value;
struct node *right;
struct node *left;
};

struct minHeap{
int size;
int capacity;
struct node **arrayofNodes;
};


struct node* create_newNode(int freq,char value){

struct node *thisNode = (struct node*)malloc(sizeof(struct node));
thisNode->freq = freq;
thisNode->value = value;

thisNode->left = NULL;
thisNode->right = NULL;
return thisNode;
};


struct minHeap * new_minHeap(int capacity){
    //allocate space for array of nodes.
struct minHeap * thisMinHeap = (struct minHeap*)malloc(sizeof(struct minHeap));

thisMinHeap->size=0;
thisMinHeap->capacity = capacity;
//alocate space for capaxity x nodes
thisMinHeap->arrayofNodes = (struct arrayofNodes**)malloc(thisMinHeap->capacity*sizeof(struct Node*));

return thisMinHeap;
};





void insertNodetoHeap(struct minHeap* thisHeap, struct node * thisNode){

//allocate space

++thisHeap->size;
int child = (thisHeap->size) -1;
int parent = (child-1)/2;

while(child && thisNode->freq < thisHeap->arrayofNodes[parent]->freq)
{
    //swap parent and child.
    thisHeap->arrayofNodes[child] = thisHeap->arrayofNodes[parent];
    child = parent;
    parent = (child-1)/2;
}

thisHeap->arrayofNodes[child] = thisNode;



}




void minHeapify(struct minHeap *thisHeap,int index){

int leftIx = 2*index  + 1;
int rightIx = 2*index + 2;
int smallest = index;

if(leftIx<thisHeap->size &&
   thisHeap->arrayofNodes[leftIx]->freq < thisHeap->arrayofNodes[index]->freq){

  smallest=leftIx;
}


if(rightIx< thisHeap->size &&
    thisHeap->arrayofNodes[rightIx]->freq < thisHeap->arrayofNodes[smallest]->freq){
    smallest= rightIx;
}

if(smallest != index){
    swapNodes(&thisHeap->arrayofNodes[smallest], &thisHeap->arrayofNodes[index]);
    minHeapify(thisHeap, smallest);

}


};


void swapNodes(struct node** node1, struct node** node2){

struct node* temp = *node1;

*node1 = *node2;
*node2 = temp;
}



struct node* getMin(struct minHeap* thisHeap){


//constant time to get min element as it is a min heap and will always root of the tree.
//delete root and replace with last elem from the heap and apply minheapfiy recursively until heap property is restored.
struct node* tempNode = thisHeap->arrayofNodes[0];
thisHeap->arrayofNodes[0] = thisHeap->arrayofNodes[(--thisHeap->size)];
//realloc()
minHeapify(thisHeap,0);
return tempNode;
};



void buildMinHeap(struct minHeap* thisHeap){

//int heapSize = thisHeap->size - 2;
//int i;
//for(i=(heapSize/2);i>=0;i--){
//    minHeapify(thisHeap, i);
//}

int size = thisHeap->size -1;
int i;
for(i = (size-1)/2; i>=0;--i){
    minHeapify(thisHeap,i);
}

}



struct minHeap* constructHeap(int* freqs, int size){

struct minHeap* thisHeap = new_minHeap(size);

//populate array with freqs
int i;
for(i=0;i<size;++i){

    struct node* thisNode = create_newNode(freqs[i],(char)i);
    thisNode->isLeaf=1;     //all of intials are leafs.
    thisHeap->arrayofNodes[i] = thisNode;       //add to heap.

}
thisHeap->size = size;

    buildMinHeap(thisHeap);

return thisHeap;
};

int isSizeOne(struct minHeap* thisHeap){
if(thisHeap->size == 1){return 1;}
else{return 0;}

}

struct node* constructHuffmanTree(int* freqs, int size){
    int totalFreq;
    struct node* leftNd;
    struct node* rightNd;
    struct node* compoundNd;

    //heap constructed.
    struct minHeap* thisHeap = constructHeap(freqs,size);


    while(!isSizeOne(thisHeap)){
        leftNd = getMin(thisHeap);
        rightNd = getMin(thisHeap);
        totalFreq = leftNd->freq + rightNd->freq;

        compoundNd = create_newNode(totalFreq,'#');
        compoundNd->left = leftNd;
        compoundNd->right = rightNd;
        compoundNd->isLeaf=0;
        insertNodetoHeap(thisHeap,compoundNd);


    }

//when size of heap is one we return the root.

return getMin(thisHeap);


};



void decodeHuffmanTree(struct node* root, int arrayCode[], int arrayIx){

//traverse until all leafs not found.


if(root->right!=NULL){
    arrayCode[arrayIx] =1;
    decodeHuffmanTree(root->right,arrayCode,arrayIx+ 1);
}

if(root->left!=NULL){

    arrayCode[arrayIx] =0;
    decodeHuffmanTree(root->left,arrayCode,arrayIx+ 1);
}

if(root->isLeaf==1){
    printf("%c: ",root->value);
    printCode(arrayCode,arrayIx);
    printf("\n");
}


}


void printCode(int code[], int len){

int i;
for(i=0;i<len;i++){

    printf("%d",code[i]);

}

}



void HuffmanCode(int freqs[], int size){

struct node * root = constructHuffmanTree(freqs,size);
int array[400];
int ix =0;
decodeHuffmanTree(root,array,ix);

}




int main(int argc, char ** argv)
{
  FILE *pToFile = fopen("msg.txt","r");
  char singleChar;
  int *freqs;
  freqs = (int *)calloc(256,sizeof(int));

    while((singleChar = fgetc(pToFile)) !=EOF){

        freqs[(unsigned)singleChar]++;
    }

    int i;
    for(i=0;i<256;i++){

    if(freqs[i]==0){
    freqs[i]=1;
    }

    }

HuffmanCode(freqs,256);

// for(i=0;i<256;i++){
//
//             if(freqs[i]>0)
//        {
//        printf("\n ASCII:%d char:%c\t %d",i,i,freqs[i]);
//
//       }
//
// }
printf("\n \n");
//HuffmanCode(freqs,256);

  printf("\n END OFPROGRAM");

  fclose(pToFile);
  return 0;
}
