template <class T>
LinkNode<T> * LinkList<T> :: reverseList(){
    LinkNode<T> *prevPtr, *curPtr, *tempPtr;
    prevPtr = head;
    curPtr = prevPtr->next;

    while (curPtr->next != null)
        {
            tempPtr = curPtr->next;
            curPtr->next = prevPtr;
            prevPtr = curPtr;
            curPtr = tempPtr;
        } //遍历指表尾
    head->next = null; //倒序之后头部变成队尾。
    *head = curPtr; // 更改现在的表头
    return head;
}