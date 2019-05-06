template<class T>
double LinkList<T> :: avgVal(LinkNode<T> *p, double sum, int i){ //一开始从传入i = 0开始为正常操作，否则出错
    if(p->next != null){
        sum += p->data;
        return avgVal(p->next, sum, ++i);
    }
    else
    {
        double avg = (sum + p->data) / (i + 1);
        return avg;
    }
}