template <class T>
int LinkList<T> :: nodeCount(LinkNode<T> *p){
    LinkNode<T> *temp = p;
    if(temp -> next != null){
        int returnCount = nodeCount(temp->next);
        return returnCount++;
    }
    else{
        return 1;
    }
}