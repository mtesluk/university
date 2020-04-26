

/*
	set the max element as 
	a first element of list
*/
template <typename T>
void MaxHeapify(vector<T> &tab, int heapSize, int index) 
{
	int left = (index + 1) * 2 - 1;
	int right = (index + 1) * 2;
	int largest = 0;

	//look for on the left branch bigger elem than root
	if (left<heapSize && tab[left]>tab[index])
		largest = left;
	else
		largest = index;

	//look for on the right branch bigger elem than root
	if (right<heapSize && tab[right]>tab[largest])
		largest = right;

	//swap this bigger element with actuall number
	if (largest != index)
	{
		swap(tab[index],tab[largest]);

		//and by recursice update all heap
		MaxHeapify(tab, heapSize, largest);
	}
}

/*
	sorting based on heap
*/
template <typename T>
void HeapSort(vector<T> &tab, int left, int right) {
	int size = right - left;
	int heapSize = size;

	//build heap
	for (int p=(heapSize-1)/2;p>=0;p--)
		MaxHeapify(tab, heapSize, p);

	//sorting
	for (int i=size-1;i>0;i--)
	{
		//delete max element at start of table
		//and put it to the end
		swap(tab[0],tab[i]);

		//except max number as last elem of list
		//and next set again max number but without 
		//this last biggets element
		heapSize--;
		MaxHeapify(tab, heapSize, 0);
	}
}



