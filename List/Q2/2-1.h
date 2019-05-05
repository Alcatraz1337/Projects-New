template <class T>
void ArrayList<T> :: delete minElement(){
    T min;
    int position;
    min = ArrayList[0];

    for (int i = 0; i < curLen; i++){
        if(min < ArrayList[i]){
            min = ArrayList[i];
            position = i;
        }
    } // find the minimum element and record the position

    ArrayList[position] = ArrayList[curLen];
}