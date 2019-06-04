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
        BinarySearchTreeNode *searchNode(BinarySearchTreeNode *root, int num);
        BinarySearchTreeNode *iterativeSearch(BinarySearchTreeNode *root, int num);
        BinarySearchTreeNode *minimum(BinarySearchTreeNode *root);
        BinarySearchTreeNode *maximum(BinarySearchTreeNode *root);
        BinarySearchTreeNode *successor(BinarySearchTreeNode *root);
        int getKey(BinarySearchTreeNode *node);
        BinarySearchTreeNode *getRightChild(BinarySearchTreeNode *node);
        BinarySearchTreeNode *getLeftChild(BinarySearchTreeNode *node);
        void insert(BinarySearchTreeNode *root, int z);
        void deleteByMerging(BinarySearchTreeNode *root);
        void deleteByCopying(BinarySearchTreeNode *root);

        void Inorder(BinarySearchTreeNode *root);
};

int BinarySearchTreeNode::getKey(BinarySearchTreeNode *node){
    return node->key;
}

BinarySearchTreeNode* BinarySearchTreeNode::getLeftChild(BinarySearchTreeNode *node){
    return node->lchild;
}

BinarySearchTreeNode* BinarySearchTreeNode::getRightChild(BinarySearchTreeNode *node){
    return node->rchild;
}

 void BinarySearchTreeNode::Inorder(BinarySearchTreeNode *root)        //递归中序遍历
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


BinarySearchTreeNode* BinarySearchTreeNode::searchNode(BinarySearchTreeNode *root, int num){
    if(root == NULL || num == root->key)
        return root;
    if(num < root->key)
        return root->searchNode(root->lchild, num);
    else
        return root->searchNode(root->rchild, num);
}

BinarySearchTreeNode* BinarySearchTreeNode::iterativeSearch(BinarySearchTreeNode *root, int num){
    while(root != NULL && num != root->key){
        if(num < root->key)
            root = root->lchild;
        else
            root = root->rchild;
    }
    return root;
}

BinarySearchTreeNode* BinarySearchTreeNode::minimum(BinarySearchTreeNode *root){
    while(root->lchild != NULL)
        root = root->lchild;
    return root;
}

BinarySearchTreeNode* BinarySearchTreeNode::maximum(BinarySearchTreeNode *root){
    while(root->rchild != NULL)
        root = root->rchild;
    return root;
}

BinarySearchTreeNode* BinarySearchTreeNode::successor(BinarySearchTreeNode *root){
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

void BinarySearchTreeNode::insert(BinarySearchTreeNode *root, int z){
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
        prev->rchild->addNode(prev->rchild, z, prev);
    else
        prev->lchild->addNode(prev->lchild, z, prev);
}

void BinarySearchTreeNode::deleteByMerging(BinarySearchTreeNode *root){
    BinarySearchTreeNode *temp = root;
    if(root != NULL){
        if(root->rchild == NULL && root->lchild == NULL)
            ;
        else if(root->rchild == NULL && root->lchild != NULL) // 没有右子树但是有左
            root = root->lchild;
        else if(root->lchild == NULL && root->rchild != NULL) // 没有左子树但是有右
            root = root->rchild;
        else{ //左右都非空
            temp = root->lchild;
            while(temp->rchild != NULL)
                temp = temp->rchild; // 找到中序遍历的最后一个节点
            temp->rchild = root->rchild;
            temp = root;
            root = root->lchild;
        }
        delete root;
    }
}

void BinarySearchTreeNode::deleteByCopying(BinarySearchTreeNode *root){
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
    cout << "\nthe minimum is: " << tree->getKey(tree->minimum(tree));
    cout << "\nthe maximum is: " << tree->getKey(tree->maximum(tree));
    cout << "\nthe successor of 122 is: " << tree->getKey(tree->successor(tree->searchNode(tree, 122)));
    tree->insert(tree, 228);
    cout << "\ninsert 228. Tree after: \n";
    tree->Inorder(tree);
    cout << "\ndelete 228. *by merging*: \n";
    tree->deleteByMerging(tree->searchNode(tree, 228));
    cout << "\nAfter:\n";
    tree->Inorder(tree);

    return 0;
}