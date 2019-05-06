template <class T>
void ArrayList<T> :: deleteInter(T min, T max){
    for (int i = 0; i < curLen; i++){
        if((ArrayList[i] > min && ArrayList[i] < max){
            for (int j = i; j < curLen - 1; j++)
                ArrayList[j] = ArrayList[j + 1];
        }
        curLen--;
    }
}