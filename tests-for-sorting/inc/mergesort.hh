



/*
	make sort by partition table to single 
	pieces and while rebuilding it sorts table
*/	
template <typename T>
void MergeSort(vector<T> &tab , T left, T right)
{
	//limit for end when the table is separated
	if (left >= right) return;

	//determine mid of table
	int pivot = (left + right)/2;

	//make recursion until all elements are separated
	MergeSort(tab, left, pivot);
 	MergeSort(tab, pivot + 1, right);

 	//new container for helping main container
 	vector<T> tmp(right - left + 1);

 	//supplementary variable, woring on two subtables
 	//and k responsible for additional container
    int i = left, j = pivot + 1, k = 0;

    //algorithm for separating
    while (i < pivot+1 && j < right+1)
    {
    	//add smaller number to new table 
        if (tab[i] <= tab[j])
        {
            tmp[k] = tab[i];
            i++;
        }
        else
        {
            tmp[k] = tab[j];
            j++;
        }
        k++;
    }

    //add next numebrs to the same sorted table
    if (i >= pivot+1)
    {
        while (j < right+1)
        {
            tmp[k] = tab[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i < pivot+1)
        {
            tmp[k] = tab[i];
            i++;
            k++;
        }
    }

    //fill in our originall table by this sorted table
    k = 0;
    for (i = left; i < right+1; i++)
    {
        tab[i] = tmp[k];
        k++;
    }
}
