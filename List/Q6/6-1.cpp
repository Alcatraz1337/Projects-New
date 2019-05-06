template<class T>
void mergeList(LinkNode<T> *ha, LinkNode<T> *hb){
    LinkNode<T> *L1p = ha;
    LinkNode<T> *L2p = hb;
    LinkNode<T> *L1 = ha->next;
    LinkNode<T> *L2 = hb->next;

  
    while(L1 && L2){
        if(L1p->data > L2p->data){
            L2p->next = L1p;
            L2p = L2;
            L2 = L2->next;
        }  
        else if(L1p->data <= L2p->data && L2p->data < L2->data){
            L1p->next = L2p;
            L2p->next = L1;
            L1p = L1;
            L1 = L1->next;
            L2p = L2;
            L2 = L2->next;
        }
        else{
            L1 = L1->next;
            L1p = L1p->next;
        }
    }
    
    if(L1 == null)
        L1 = L2p;
    else
        L2 = L1p;
}
