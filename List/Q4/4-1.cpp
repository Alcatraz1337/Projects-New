template <class T>
T LinkList<T> :: findMax(LinkNode<T> *p){
    LinkNode<T> *temp = p;
    if(p -> next != null){
        
        int curVal = temp -> data;
        int returnVal = findMax(temp->next);
        return (returnVal > curVal) ? returnVal : curVal;
    }
    else
    {
        return temp -> data;
    }
}