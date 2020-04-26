#ifndef PARTITION_HH
#define PARTITION_HH

using namespace std;

struct Jumpers{
    int i;
    int j;
};

/*
    function is for partition tables to 
    twice smaller and ordered tables  
*/
template <typename T>
Jumpers partition(vector<T> &tabs , int left, int right)
{

    //i start from the left side of table
    //j start from the right spot of table
    //pivot is middle number
    int i = left;
    int j = right;
    T pivot = tabs[(i+j)/2];

    do
    {
        //if number is smaller than pivot,
        //everythink is ok and increment i
        while(tabs[i] < pivot) i++;

        //if number is bigger than pivot , 
        //everythink is ok and decrement j
        while(tabs[j] > pivot) j--;
       
        //if nombers didnt move from last step
        //it means you need to swap this numbers 
        //to the other side
        if(i <= j)
        {
            swap(tabs[i],tabs[j]);
           
            i++;
            j--;
        }
    } while(i <= j);

    //return pack of indexes
    Jumpers tmp;
    tmp.i = i;
    tmp.j = j;
    return tmp;
}

#endif