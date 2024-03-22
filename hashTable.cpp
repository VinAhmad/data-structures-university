#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 41

struct Node{
    int key;
    char input[100];
    Node *next;
};

struct hashBucket{
    Node *head;
    Node *tail;
    int nodeCount;
};

hashBucket hashTable[TABLE_SIZE];

Node *createNode(const char *input){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->input, input);
    newNode->key = hash_division(string_to_int(input));
    newNode->next = NULL;

    return newNode;
}

void push(Node *node){
    if(hashTable[node->key].head == NULL){
        hashTable[node->key].head = hashTable[node->key].tail = node;
        hashTable[node->key].nodeCount = 1;
    }
    else {
        hashTable[node->key].tail->next = node;
        hashTable[node->key].tail = node;
        hashTable[node->key].nodeCount++;
    }
    
}

void view(){
    for(int i = 0; i < TABLE_SIZE; i++){
        printf("HT[%d]: ", i);

        Node *temp = hashTable[i].head;
        while (temp)
        {
            printf("%s - ", temp->input);
            temp = temp->next;
        }
        printf("(null)\n");

    }
}

int string_to_int(const char *input){
    int len = strlen(input);
    int sum = 0;

    for (int i = 0; i < len; i++){
        sum += input[i];
    }

    return sum;
}

int hash_division(int input){
    return input % TABLE_SIZE;
}

int main(){

    // printf("budi: %d\n", hash_division(string_to_int("budi")));

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i].head = NULL;
        hashTable[i].tail = NULL;
    }

    push(createNode("Kepinn"));
    push(createNode("wibdawdbwad"));
    push(createNode("jksbfjkebisufb"));

    view();

    return 0;
}