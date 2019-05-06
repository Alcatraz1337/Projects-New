template <class T>
void ArrayList<T> :: deleteSpec(T x){
    int i = 0;
    for (i; i < curLen; i++){
        if(ArrayList[i] == x){
            for (int j = i; j < curLen - 1; j++)
                ArrayList[j] = ArrayList[j + 1];
            curLen--;
        }
    }
}