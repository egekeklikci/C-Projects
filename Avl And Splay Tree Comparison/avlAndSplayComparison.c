// EGE KEKLIKCI 
// program to compare the performance of AVL and Splay trees 
// based on the two criteria: the total number of comparisons and the number of rotations 
// program can only be executed via terminal and take input file name as an argument


#include<stdio.h>
#include<stdlib.h>

typedef struct splayTreeNode{
    int data;
    struct splayTreeNode* right;
    struct splayTreeNode* left;
    struct splayTreeNode* parent;
}splayTree;
typedef splayTree * splayPointer;
int avlTotalCost = -1, splayTotalCost = 0;

typedef struct avlTreeNode{
    int data;
    unsigned int height;
    struct avlTreeNode *left;
    struct avlTreeNode *right;
}avlTree;
typedef avlTree* avlPointer;

// SPLAY FUNCTIONS
splayPointer splayRotateLeft(splayPointer node) {
    splayTotalCost+=1;
    splayPointer temp = node->parent;
    if(node->left != NULL){
        temp->right = node->left;
        temp->right->parent = temp;
    } else{
        temp->right = NULL;
    }
    node->left = temp;
    node->parent = temp->parent;
    temp->parent = node;
    return node;
}
splayPointer splayRotateRight(splayPointer node) {
    splayTotalCost+=1;
    splayPointer temp = node->parent;
    if(node->right != NULL){
        temp->left = node->right;
        temp->left->parent = temp;
    } else{
        temp->left = NULL;
    }
    node->right = temp;
    node->parent = temp->parent;
    temp->parent = node;
    return node;
}
splayPointer zigZigRight(splayPointer node){
    splayTotalCost+=2;
    splayPointer temp = node->parent;
    if(node->left!=NULL){
        temp->right = node->left;
        temp->right->parent = temp;
    }
    else{
        temp->right= NULL;
    }
    if(temp->left!=NULL){
        temp->parent->right=temp->left;
        temp->left->parent = temp->parent;
    }
    else{
        temp->parent->right = NULL;
    }
    node->left = temp;
    temp->left = temp->parent;
    if(temp->parent->parent!=NULL){
        if(temp->parent->parent->data > temp->parent->data){
            temp->parent->parent->left = node;
            node->parent = temp->parent->parent;
        }
        else if(temp->parent->parent->data < temp->parent->data){
            temp->parent->parent->right = node;
            node->parent = temp->parent->parent;
        }
    }
    else{
        node->parent=NULL;
    }
    temp->parent = node;
    temp->left->parent=temp;
    return node;
}
splayPointer zigZigLeft(splayPointer node){
    splayTotalCost+=2;
    splayPointer temp = node->parent;
    if(node->right!=NULL){
        temp->left = node->right;
        temp->left->parent = temp;
    }
    else{
        temp->left= NULL;
    }
    if(temp->right!=NULL){
        temp->parent->left=temp->right;
        temp->right->parent = temp->parent;
    }
    else{
        temp->parent->left = NULL;
    }
    node->right = temp;
    temp->right = temp->parent;
    if(temp->parent->parent!=NULL){
        if(temp->parent->parent->data < temp->parent->data){
            temp->parent->parent->right = node;
            node->parent = temp->parent->parent;
        }
        else if(temp->parent->parent->data > temp->parent->data){
            temp->parent->parent->left = node;
            node->parent = temp->parent->parent;
        }
    } else{
        node->parent=NULL;
    }
    temp->right->parent = temp;
    temp->parent = node;
    return node;
}
void insertSplayTree(splayPointer* tree, int value){
    // add a given value to splay tree according to binary search tree rules, this function does not splay, it just adds
    if ((*tree) == NULL){
        splayPointer newSplayNode = malloc(sizeof(splayTree));
        newSplayNode->data = value;
        *tree = newSplayNode;
        return;
    }
    if ((*tree)->data < value){
        splayTotalCost+=1;
        // go right
        if ((*tree)->right!=NULL) {
            insertSplayTree(&(*tree)->right, value);
        }
        else{
            splayPointer newSplayNode = malloc(sizeof(splayTree));
            newSplayNode->data = value;
            (*tree)->right = newSplayNode;
            newSplayNode->parent = *tree;
        }
    }
    else if ((*tree)->data > value){
        splayTotalCost+=1;
        // go left
        if ((*tree)->left != NULL) {
            insertSplayTree(&(*tree)->left, value);
        }
        else{
            splayPointer newSplayNode = malloc(sizeof(splayTree));
            newSplayNode->data = value;
            (*tree)->left = newSplayNode;
            newSplayNode->parent = *tree;
        }
    }
    else{
        splayTotalCost+=1;
    }

}
void printSplayTree(splayPointer givenAvlTree, int space) {
    // i used this for debugging
    if (givenAvlTree == NULL) return;
    printSplayTree(givenAvlTree->right, space + 3);
    printf("%*d\n", space, givenAvlTree->data);
    printSplayTree(givenAvlTree->left, space + 3);
}
splayPointer splay(splayPointer tree, int value){
    // this functions splays the given value

    // search the tree for the node
    if (tree->data < value){
        // go right
        tree = splay(tree->right, value);
    }
    else if (tree->data > value){
        // go left
        tree = splay(tree->left, value);
    }

    if(tree->parent != NULL && tree->parent->parent == NULL){
        // no grandparent
        if(tree->parent->data < tree->data){
            // child is in right side
            splayRotateLeft(tree);
            /*tree->left = tree->parent;
            tree->parent->right = NULL;
            tree->parent = NULL;*/
            return tree;
        }
        else if (tree->parent->data > tree->data){
            // child is in left side
            tree = splayRotateRight(tree);
            return tree;
        }
    }
    else if(tree->parent != NULL && tree->parent->parent != NULL){
        // if node has grandparent
        if(tree->parent->data > value){
            // left
            if(tree->parent->parent->data > tree->parent->data){
                // left left - zig zig
                tree = zigZigLeft(tree);
                return tree;
            }
            else if(tree->parent->parent->data < tree->parent->data){
                // right left - zig zag
                tree = splayRotateRight(tree);
                return splayRotateLeft(tree);
            }
        }
        else if(tree->parent->data < value){
            // right
            if(tree->parent->parent->data > tree->parent->data){
                // left right - zig zag
                tree = splayRotateLeft(tree);
                return splayRotateRight(tree);
            }
            else if(tree->parent->parent->data < tree->parent->data){
                // right right - zig zig
                tree = zigZigRight(tree);
                return tree;
            }
        }
    }
    return tree;
}
void printPreOrderSplayTree(splayPointer root) {
    if (root != NULL) {
        printf("%d ", root->data);
        printPreOrderSplayTree(root->left);
        printPreOrderSplayTree(root->right);
    }
}

// AVL FUNCTIONS
void printAvlTree(avlPointer givenAvlTree, int space) {
    // i used this for debugging
    if (givenAvlTree == NULL) return;
    printAvlTree(givenAvlTree->right, space + 3);
    printf("%*d\n", space, givenAvlTree->data);
    printAvlTree(givenAvlTree->left, space + 3);
}
avlPointer singleRotationToLeft(avlPointer node){
    avlTotalCost+=1;
    avlPointer center = node->right;
    node->right = center->left;
    center->left = node;
    if(node->right!=NULL && node->left!=NULL){
        if(node->right->height > node->left->height){
            node->height = 1 + node->right->height;
        }
        else{
            node->height = 1 + node->left->height;
        }
    }
    else if(node->right==NULL && node->left!=NULL){
        node->height = node->left->height + 1;
    }
    else if(node->right!=NULL && node->left==NULL){
        node->height = node->right->height + 1;
    }
    else{
        node->height = 1;
    }
    if(center->right!=NULL && center->left!=NULL){
        if(center->right->height > center->left->height){
            center->height = 1 + center->right->height;
        }
        else{
            center->height = 1 + center->left->height;
        }
    }
    else if(center->right==NULL && center->left!=NULL){
        center->height = center->left->height + 1;
    }
    else if(center->right!=NULL && center->left==NULL){
        center->height = center->right->height + 1;
    }
    else{
        center->height = 1;
    }
    return center;
}
avlPointer singleRotationToRight(avlPointer node){
    avlTotalCost+=1;
    avlPointer center = node->left;
    node->left = center->right;
    center->right = node;
    if(node->right!=NULL && node->left!=NULL){
        if(node->right->height > node->left->height){
            node->height = 1 + node->right->height;
        }
        else{
            node->height = 1 + node->left->height;
        }
    }
    else if(node->right==NULL && node->left!=NULL){
        node->height = node->left->height + 1;
    }
    else if(node->right!=NULL && node->left==NULL){
        node->height = node->right->height + 1;
    }
    else{
        node->height = 1;
    }
    if(center->right!=NULL && center->left!=NULL){
        if(center->right->height > center->left->height){
            center->height = 1 + center->right->height;
        }
        else{
            center->height = 1 + center->left->height;
        }
    }
    else if(center->right==NULL && center->left!=NULL){
        center->height = center->left->height + 1;
    }
    else if(center->right!=NULL && center->left==NULL){
        center->height = center->right->height + 1;
    }
    else{
        center->height = 1;
    }
    return center;
}
avlPointer avlInsert(avlPointer tree, avlPointer node, int value){
    if (tree == NULL){
        tree = node;
    }
    if (tree->data < node->data){
        avlTotalCost+=1;
        // go right
        if (tree->right!=NULL) {
            // go recursively right
            tree->right = avlInsert(tree->right, node, value);
        }
        else{
            // add node
            tree->right = node;
        }
    }
    else if (tree->data > node->data){
        avlTotalCost+=1;
        // go left
        if (tree->left != NULL) {
            // go recursively left
            tree->left = avlInsert(tree->left, node, value);
        }
        else{
            // add node
            tree->left = node;
        }
    }
    else{
        avlTotalCost+=1;
    }

    // this adjusts the height for the tree
    if(tree->right!=NULL && tree->left!=NULL){
        // find max
        if(tree->right->height > tree->left->height){
            tree->height = 1 + tree->right->height;
        }
        else{
            tree->height = 1 + tree->left->height;
        }
    }
    else if(tree->right==NULL && tree->left!=NULL){
        tree->height = tree->left->height + 1;
    }
    else if(tree->right!=NULL && tree->left==NULL){
        tree->height = tree->right->height + 1;
    }
    else{
        tree->height = 1;
    }
    int balanceFactor = 0;
    // find balance factor
    if(tree->right!=NULL && tree->left!=NULL){
        balanceFactor = tree->left->height - tree->right->height;
    }
    else if(tree->right==NULL && tree->left!=NULL){
        balanceFactor = tree->left->height-0;
    }
    else if(tree->right!=NULL && tree->left==NULL){
        balanceFactor = 0-tree->right->height;
    }
    // according to balance factor, balance the tree
    if(tree->left != NULL &&  balanceFactor>1 && value < tree->left->data){
        // left left
        return singleRotationToRight(tree);
    }
    else if(tree->left != NULL && balanceFactor>1 && value > tree->left->data){
        // left right
        tree->left = singleRotationToLeft(tree->left);
        return singleRotationToRight(tree);
    }
    else if(tree->right != NULL &&  balanceFactor<-1 && value > tree->right->data){
        // right right
        return singleRotationToLeft(tree);
    }
    else if(tree->right != NULL && balanceFactor<-1 && value < tree->right->data){
        // right left
        tree->right = singleRotationToRight(tree->right);
        return singleRotationToLeft(tree);
    }
    return tree;
}
void printPreOrderAvl(avlPointer root) {
    if (root != NULL) {
        printf("%d ", root->data);
        printPreOrderAvl(root->left);
        printPreOrderAvl(root->right);
    }
}

int main(int argc, const char* argv[]){
    if (argc == 1) {
        printf("Please use the terminal.");
    }
    if (argc >= 2) {
//         open input file
    splayPointer splayRoot = NULL;
    avlPointer x, avlRoot = NULL;
//         argv[1]
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error, Can't open file\n");
        return -1;
    }
    char ch;
    int value = 0, base = 1;
    do{
        ch = fgetc(inputFile);
        if (48 <= ch && ch <= 57) {
            value = value*base + (int)(ch - '0');
            base *= 10;
        }else if(ch == EOF){
            if(value!=0){
                // create splayRoot node for avl then insert
                x = malloc(sizeof(avlTree));
                x->data = value;
                x->height = 1;
                avlRoot = avlInsert(avlRoot, x, x->data);

                // insert to splay like bst
                insertSplayTree(&splayRoot, value);
                // splay the value
                splayRoot = splay(splayRoot, value);
                value = 0;
                base = 1;
            }
        }
        else{
            // create splayRoot node for avl then insert
            x = malloc(sizeof(avlTree));
            x->data = value;
            x->height = 1;
            avlRoot = avlInsert(avlRoot, x, x->data);

            // insert to splay like bst
            insertSplayTree(&splayRoot, value);
            // splay the value
            splayRoot = splay(splayRoot, value);
            value = 0;
            base = 1;
        }
    }
    while (ch != EOF);
    puts("AVL Tree is:");
    printPreOrderAvl(avlRoot);
    printf("\nTotal cost for AVL: %d", avlTotalCost);
    puts("\nSplay Tree is:");
    printPreOrderSplayTree(splayRoot);
    printf("\nTotal cost for splay: %d", splayTotalCost);
    // close file
    return 0;
    }
}