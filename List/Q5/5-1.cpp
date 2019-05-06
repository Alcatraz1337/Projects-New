template <class T>
void mergeList(LinkList &La, LinkList &Lb, LinkList &Lc){
    pa=La->next;//初始化pa的初值指向表La的第一个结点
    pb=Lb->next;
    Lc=pc=La;//用La的头结点作为Lc的头结点，pc的初值指向Lc的头结点
    while(pa && pb){ //当两个表非空，依次取出两表中较小的结点插入到Lc表的最后
            if(pa->data<=pb->data){
                    pc->next=pa;pc=pa;pa=pa->next;
            }else{
                    pc->next=pb;pc=pb;pb=pb->next;
            }

    }
    pc->next=pa?pa:pb;//插入剩余结点
}