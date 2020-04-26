#ifndef INTROSORT_HH
#define INTROSORT_HH

#include "heapsort.hh"
#include "partition.hh"
#include "insertionsort.hh"

/*
	sorting function which is based on 
	quicksort and heapsort
*/
template <typename T>
void IntroSort(vector<T> &tab, int left, int right, int M)
{
	//take M as max deapth of recursive
	//this is not good example to quchsort
	//so heapsort helps here
	if (M<=0)
  	{
    	HeapSort(tab,left,right);
    	return;
  	}

  	//partition like in quicksort
  	//return indexes
	Jumpers tmp = partition(tab,left,right);
    int i = tmp.i;
    int j = tmp.j;

    //and normal recursion as quicksort
  	if(left < j) IntroSort(tab,left,j,M-1);
    if(right > i) IntroSort(tab,i,right,M-1);
	

}

/*
	use introsort but with supplementary
	sorting like insertsort which is good to small 
	tables 
*/
template <typename T>
void HybridIntroSort(vector<T> &tab, int left, int right, int M)
{
	IntroSort(tab,left,right,M);
	InsertionSort(tab,right - left);
}


#endif