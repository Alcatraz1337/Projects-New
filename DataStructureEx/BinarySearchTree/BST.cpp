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
        BinarySearchTreeNode *&searchNode(BinarySearchTreeNode *root, int num);
        BinarySearchTreeNode *iterativeSearch(BinarySearchTreeNode *root, int num);
        BinarySearchTreeNode *minimum(BinarySearchTreeNode *root);
        BinarySearchTreeNode *maximum(BinarySearchTreeNode *root);
        BinarySearchTreeNode *successor(BinarySearchTreeNode *root);
        int getKey(BinarySearchTreeNode *node);
        BinarySearchTreeNode *getRightChild(BinarySearchTreeNode *node);
        BinarySearchTreeNode *getLeftChild(BinarySearchTreeNode *node);
        void insert(BinarySearchTreeNode *root, int z);
        void deleteByMerging(BinarySearchTreeNode *&root);
        //void deleteByCopying(BinarySearchTreeNode *root);

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


BinarySearchTreeNode*& BinarySearchTreeNode::searchNode(BinarySearchTreeNode *root, int num){
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

void BinarySearchTreeNode::deleteByMerging(BinarySearchTreeNode *&root){
    BinarySearchTreeNode *temp = root;
    if(root != NULL){
        if(root->rchild == NULL && root->lchild == NULL){ //左右都空
            if(root->parent->rchild == root)
                root->parent->rchild = NULL;
            else
                root->parent->lchild = NULL;              
        }
        else if(root->lchild && root->rchild){ //左右都非空
            temp = root->lchild;
            while(temp->rchild != NULL)
                temp = temp->rchild; // 找到中序遍历的最后一个节点
            temp->rchild = root->rchild;
            if(root->parent != NULL){ //父节点不空
                if(root->parent->rchild == root)
                    root->parent->rchild = temp->parent;
                else
                    root->parent->lchild = temp->parent;
            }
            else{
                root = root->lchild;
                return;
            }
        }
        else{ // 左右有一个是空
            if(root->lchild)
                temp = root->lchild;
            else
                temp = root->rchild; //找到要拼接的节点
            if(root->parent != NULL){
                if(root->parent->lchild == root) // 如果该删除节点是其父节点的左孩子 则将该节点的孩子拼到父节点左孩子之下
                    root->parent->lchild = temp;
                else
                    root->parent->rchild = temp;
            }
            else
                temp->parent = NULL;
        }
        root->key = NULL;
        root->lchild = NULL;
        root->rchild = NULL;
        root->parent = NULL;
    }
}

int main(){
    BinarySearchTreeNode *tree = NULL;
    int q[12] = {105, 110, 99, 122, 250, 200, 400, 330, 450, 300, 500, 122};
    for(int i = 0; i < 12; i++)
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
    cout << "\ndelete . *by merging*:\n";
    //BinarySearchTreeNode *pointer = tree->searchNode(tree, 99);
    tree->deleteByMerging(tree->searchNode(tree, 250));
    tree->Inorder(tree);

    return 0;
}