#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    Node *left;
    Node *right;
};

Node *root = NULL;

Node *createNode(int key){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node *push(Node *curr, int key){
    if(!curr){
        return createNode(key);
    }
    else if( key == curr->key){
        printf("Duplicate Key!!\n");
        return curr;
    }
    else if(key < curr->key){
        curr->left = push(curr->left, key);
    }
    else if(key > curr->key){
        curr->right = push(curr->right, key);
    }
    
    return curr;
}

Node *getPredecessor(Node *node){
    Node *temp = node->left;
    while (temp->right){
        temp = temp->right;
    }
    return temp;
}

Node *pop(Node *curr, int key){
    if(!root){
        printf("BST is Empty!!\n");
    }
    else if(!curr){
        printf("Key %d not found!\n");
    }
    else if (key < curr->key){
        curr->left = pop(curr->left, key);
    }
    else if(key > curr->key){
        curr->right = pop(curr->right, key);
    }
    else if(key == curr->key){
        if(!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        }
        else if(!curr->left){
            Node *replacement = curr->right;
            free(curr);
            curr = replacement;
        }
        else if (!curr->right){
            Node *replacement = curr->left;
            free(curr);
            curr = replacement;
        }
        else {
            Node *replacement = getPredecessor(curr);
            curr->key = replacement->key;
            curr->left = pop(curr->left, replacement->key);
        }
    }
    
    return curr;
}

void preOrder(Node *curr){
    if(curr){
        printf("%d - ", curr->key);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void inOrder(Node *curr){
    if(curr){
        inOrder(curr->left);
        printf("%d - ", curr->key);
        inOrder(curr->right);
    }
}

void postOrder(Node *curr){
    if(curr){
        postOrder(curr->left);
        postOrder(curr->right);
        printf("%d - ", curr->key);
    }
}

int main(){

    root = push(root, 10);
    root = push(root, 5);
    root = push(root, 12);
    root = push(root, 27);
    root = push(root, 8);
    root = push(root, 6);
    root = push(root, 2);
    root = push(root, 30);

    printf("In Order: ");
    inOrder(root);

    root = pop(root, 9);
    root = pop(root, 8);

    printf("Setelah di pop: ");
    inOrder(root);

    return 0;
}