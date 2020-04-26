#ifndef QUICKSORT_HH
#define QUICKSORT_HH

#include "partition.hh"

/*
	function for sorting
	while its making table devided
	it sorts it
*/
template <typename T>
void QuickSort(vector<T> &tab , int left, int right)
{
	//determine indexes where table is devided
	Jumpers tmp = partition(tab,left,right);
	int i = tmp.i;
	int j = tmp.j;


	//make operation on devided tables
	if(left < j) QuickSort(tab, left, j);
	if(right > i) QuickSort(tab, i, right);
   
}

#endif