template<class T>
DLList<T> DLList<T> :: transform(DLList &L){
    DLList newDLList = InitDLList();
    DLLNode *p, *q, *pa, *qb;
    q = p = L->next;
    pa = pb = newDLList;

    while(p != L){
        if(p != L){
            q = p->next;
            p->prev = pa;
            pa->next = p;
            p->next = pb;
            pb->prev = p;

            pa = pa->next;
            p = q;
        }
        if(p != L){
            q = p->next;
            p->next = pb;
            pb -> prev = p;
            p->prev = pa;
            pa->next = p;

            pb = pb->prev;
            p = q;
        }
    }
    return newDLList;
}