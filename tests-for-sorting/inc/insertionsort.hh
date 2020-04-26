/*
	function to sort by insert,
	not very effective
*/
template <typename T>
void InsertionSort(vector<T> &tab, int size) {
	int save,j;

	//go through all elements in table
	for(int i=1;i<size;i++) 
	{
		//save each element in table
		save = tab[i];

		//if its smaller than last element
		//move elemenets
		for (j=i;j>=1 && tab[j-1]>save;j--)
			tab[j] = tab[j-1];

		//and insert this element in right place
		tab[j] = save;
	}
}