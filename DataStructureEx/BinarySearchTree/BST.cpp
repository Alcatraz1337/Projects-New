#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class BinarySearchTreeNode{
    private:
        int key;
        BinarySearchTreeNode *rchild;
        BinarySearchTreeNode *lchild;
        BinarySearchTreeNode *parent = NULL;

    public:
        BinarySearchTreeNode *addNode(BinarySearchTreeNode *&root ,int num, BinarySearchTreeNode *prevNode);
        BinarySearchTreeNode *searchNode(BinarySearchTreeNode *&root, int num);
        BinarySearchTreeNode *iterativeSearch(BinarySearchTreeNode *&root, int num);
        BinarySearchTreeNode *minimum(BinarySearchTreeNode *&root);
        BinarySearchTreeNode *maximum(BinarySearchTreeNode *&root);
        BinarySearchTreeNode *successor(BinarySearchTreeNode *&root);
        void insert(BinarySearchTreeNode *&root, int z);
        void deleteByMerging(BinarySearchTreeNode *&root);
        void deleteByCopying(BinarySearchTreeNode *&root);

        void Inorder(BinarySearchTreeNode *&root);
};

 void BinarySearchTreeNode::Inorder(BinarySearchTreeNode *&root)        //递归前序遍历
{
   if(root!=NULL)
   {
       root->Inorder(root->lchild);
       cout << root->key << "\t|";
       root->Inorder(root->rchild);
   }
}

BinarySearchTreeNode* BinarySearchTreeNode :: addNode(BinarySearchTreeNode *&root, int num, BinarySearchTreeNode *prevNode){

    if(root == NULL){
        root = (BinarySearchTreeNode *) malloc(sizeof(BinarySearchTreeNode) * 1);
        root->key = num;
        root->lchild = root->rchild = NULL;
        root->parent = prevNode;
    }
    else if(num == root->key)
        return root;
    else if(num < root->key)
        root->addNode(root->lchild, num, root);
    else 
        root->addNode(root->rchild, num, root);

    return root;
}


BinarySearchTreeNode* BinarySearchTreeNode::searchNode(BinarySearchTreeNode *&root, int num){
    if(root == NULL || num == root->key)
        return root;
    if(num < root->key)
        return root->searchNode(root->lchild, num);
    else
        return root->searchNode(root->rchild, num);
}

BinarySearchTreeNode* BinarySearchTreeNode::iterativeSearch(BinarySearchTreeNode *&root, int num){
    while(root != NULL && num != root->key){
        if(num < root->key)
            root = root->lchild;
        else
            root = root->rchild;
    }
    return root;
}

BinarySearchTreeNode* BinarySearchTreeNode::minimum(BinarySearchTreeNode *&root){
    while(root->lchild != NULL)
        root = root->lchild;
    return root;
}

BinarySearchTreeNode* BinarySearchTreeNode::maximum(BinarySearchTreeNode *&root){
    while(root->rchild != NULL)
        root = root->rchild;
    return root;
}

BinarySearchTreeNode* BinarySearchTreeNode::successor(BinarySearchTreeNode *&root){
    if(root->rchild != NULL)
        return root->minimum(root->rchild);
    else{
        BinarySearchTreeNode *node = root->parent;
        while(node != NULL && root == node->rchild){
            root = node;
            node = node->parent;
        }
        return node;
    }
}

void BinarySearchTreeNode::insert(BinarySearchTreeNode *&root, int z){
    BinarySearchTreeNode *node = root;
    BinarySearchTreeNode *prev = NULL;
    while(node != NULL){
        prev = node;
        if(node->key < z)
            node = node->rchild;
        else
            node = node->lchild;
    }
    if(root == NULL)
        root->addNode(root, z, root->parent);
    else if(prev->key < z)
        prev->rchild->addNode(prev->rchild, z, prev->rchild->parent);
    else
        prev->lchild->addNode(prev->lchild, z, prev->lchild->parent);
}

void BinarySearchTreeNode::deleteByMerging(BinarySearchTreeNode *&root){
    BinarySearchTreeNode *temp = root;
    if(root != NULL){
        if(!root->rchild)
            root = root->lchild;
        else if(root->lchild == NULL)
            root = root->rchild;
        else{
            temp = root->lchild;
            while(temp->rchild != NULL)
                temp = temp->rchild;
            temp->rchild = root->rchild;
            temp = root;
            root = root->lchild;
        }
        delete temp;
    }
}

void BinarySearchTreeNode::deleteByCopying(BinarySearchTreeNode *&root){
    BinarySearchTreeNode *temp = root;
    BinarySearchTreeNode *prev;
    if(root->rchild == NULL)
        root = root->lchild;
    else if(root->lchild == NULL)
        root = root->rchild;
    else{
        temp = root->lchild;
        prev = root;
        while(temp->rchild != NULL){
            prev = temp;
            temp = temp->rchild;
        }
        root->key = temp->key;
        if(prev == root)
            prev->lchild = temp->lchild;
        else
            prev->rchild = temp->lchild;
    }
    delete temp;
}

int main(){
    BinarySearchTreeNode *tree = NULL;
    int q[11] = {105, 110, 99, 122, 250, 200, 300, 330, 400, 450, 500};
    for(int i = 0; i < 11; i++)
        tree->addNode(tree, q[i], nullptr);
    tree->Inorder(tree);
    cout << "\nfind number 122, *using normal search* ad: " << tree->searchNode(tree, 122);
    cout << "\nfind number 122, *using iteractive search* ad: " << tree->iterativeSearch(tree, 122);
    return 0;
}