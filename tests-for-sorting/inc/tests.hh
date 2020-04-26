#ifndef TESTS_HH
#define TESTS_HH

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include "quicksort.hh"
#include "introsort.hh"
#include "mergesort.hh"


using namespace std;

/*
	Function to reverse direction
	in sorted table
*/
template <typename T>
vector <vector <T>> reverse(vector <vector <T>> tab)
{
	vector <vector <T>> tmp_tab = tab;
	int k = 0;
	for(int i=0;i < int(tab.size());i++)
	{
		k = int(tab[i].size()) - 1;
		for(int j=0;j < int(tab[i].size());j++)
		{
			tmp_tab[i][j] = tab[i][k];
			k--;
		}
	}
	return tmp_tab;

}

/*
	Overload of showing 
	tables on the screen
*/
template <typename T>
ostream& operator<<(ostream& out,vector<vector<T>> tab)
{
	for(int i=0;i < int(tab.size());i++)
	{
		for(int j=0;j < int(tab[i].size());j++)
		{
			out << tab[i][j] << endl;
		}
		out << "-----------------------" << endl;
	}
	return out;
}

/*
	Fill in the given part of table
	with random numbers
*/
template <typename T>
void fill_in_random_tabs(vector <vector <T>> &tab,int fill)
{
	//"fill" tells which part of table must be sorted at start

	for(int i=0;i < int(tab.size());i++)
	{
		for(int j=fill;j < int(tab[i].size());j++)
		{
			tab[i][j] = rand() % 10000 + 10000;
		}
		for(int j=0;j < fill;j++)
		{
			tab[i][j] = rand() % 10000;

		}

		//sort this first part which should be sorted
		QuickSort(tab[i],0,fill);
	}


}

/*
	This function sort table 
	and count time of it
*/
template <typename T>
double count_time_of_sorting(vector <vector <T>> &tab,string sort_kind)
{
	//set start
	auto start = chrono::high_resolution_clock::now();

	//sorting in progress
	for(int i=0;i < int(tab.size());i++)
	{
		if(sort_kind == "quicksort") QuickSort(tab[i],0,int(tab[i].size()));
		else if(sort_kind == "introsort") HybridIntroSort(tab[i],0,int(tab[i].size()),(int)floor(2*log(int(tab[i].size()))/log(2)));
		else if(sort_kind == "merge_sort") MergeSort(tab[i],0,int(tab[i].size()));
	}

	//set end of sort
	auto finish = chrono::high_resolution_clock::now();

	//calculate the passed time
	chrono::duration<double> elapsed = finish - start;

	//return time of sort
	return elapsed.count();

}

/*
	Check if all table
	is sorted
*/

bool check_if_sorted(vector <vector <int>> &tab)
{
	int long unsigned counter = 0;
	int long unsigned all_elements = 0;
	for(int i=0;i < int(tab.size());i++)
	{
		for(int j=0;j < int(tab[i].size()) - 1;j++)
		{
			all_elements++;
			if(tab[i][j] <= tab[i][j+1])
			{
				counter++;
				//cout << tab[i][j];
				//cout << " - GOOD"<<endl;
			}
			else
			{
				;
				cout << tab[i][j-1] << " " <<tab[i][j] << " " << tab[i][j+1] << " " << tab[i][j+2];
				cout << " - BAD"<<endl;
				//exit(0);
			}
		}
		counter++;
		all_elements++;
	}

	if(counter == all_elements) return true;
	else return false;

	return false;

}


/*
	Compare every kind 
	of sorting
*/
void test(int amount_of_tables, int amount_of_elements_in_table)
{
	//create 100 conrainers with "counts" elements
	vector <vector <int>> tabs(amount_of_tables, vector<int> (amount_of_elements_in_table));
	vector <vector <int>> tabs1(amount_of_tables, vector<int> (amount_of_elements_in_table));
	vector <vector <int>> tabs2(amount_of_tables, vector<int> (amount_of_elements_in_table));

	int fill = 0;
	cout << "Test for " << amount_of_tables << " tables contains " << amount_of_elements_in_table << " elements:" << endl;

	/*
		ALL NUMEBRS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//sort
	double time_rand_quicksort=count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with all random numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with all random numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_rand_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with all random numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with all random numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_rand_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with all random numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with all random numbers with 'Introsort'. Result: NOT SORTED..." << endl;

	
	/*
		25% OF NUMBERS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------

	//determine 25% of all elements
	fill = int(0.25*amount_of_elements_in_table);

	//25% sorted
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//start counting and sorting
	double time_25_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with 25%% sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 25%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_25_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with 25%% sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with 25%% sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_25_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with 25%% sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with 25%% sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;


	/*
		50% OF NUMBERS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------
	//determine 50% of all elements
	fill = int(0.5*amount_of_elements_in_table);

	//50% sorted
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//start counting and sorting
	double time_50_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with 50%% sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 50%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_50_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with 50%% sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with 50%% sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_50_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with 50%% sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with 50%% sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;

	



	/*
		75% OF NUMBERS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------
	//determine 75% of all elements
	fill = int(0.75*amount_of_elements_in_table);

	//75% sorted
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//start counting and sorting
	double time_75_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with 75%% sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 75%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_75_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with 75%% sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with 75%% sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_75_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with 75%% sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with 75%% sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;




	/*
		95% OF NUMBERS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------

	//determine 95% of all elements
	fill = int(0.95*amount_of_elements_in_table);

	//95% sorted
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//start counting and sorting
	double time_95_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with 95%% sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 95%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_95_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with 95%% sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with 95%% sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_95_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with 95%% sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with 95%% sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;



	/*
		99% OF NUMBERS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------

	//determine 99% of all elements
	fill = int(0.99*amount_of_elements_in_table);

	//99% sorted
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//start counting and sorting
	double time_99_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with 99%% sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 99%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_99_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with 99%% sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with 99%% sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_99_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with 99%% sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with 99%% sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;


	/*
		99,7% OF NUMBERS ARE RANDOM
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------

	//determine 99,7% of all elements
	fill = int(0.997*amount_of_elements_in_table);

	//99,7% sorted
	fill_in_random_tabs(tabs,fill);
	tabs1 = tabs;
	tabs2 = tabs;

	//start counting and sorting
	double time_99_7_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with 99.7%% sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 99.7%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------

	//sort
	double time_99_7_mergesort=count_time_of_sorting(tabs1,"merge_sort");

	if(check_if_sorted(tabs1)) cout << "Start with 99.7%% sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with 99.7%% sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//sort
	double time_99_7_introsort=count_time_of_sorting(tabs2,"introsort");

	if(check_if_sorted(tabs2)) cout << "Start with 99.7%% sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with 99.7%% sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;





	/*
		SORTED IN SECOND DIRECTIONS
	*/
	//-------------------------------------------------
	//QUICKSORT
	//-------------------------------------------------

	//tab is sorted by last operation
	//so change the direction
	tabs = reverse(tabs);

	//start counting and sorting
	double time_reverse_quicksort = count_time_of_sorting(tabs,"quicksort");

	if(check_if_sorted(tabs)) cout << "Start with reverse sorted numbers with 'Quicksort'. Result: SORTED..." << endl;
	else cout << "Start with 75%% sorted numbers with 'Quicksort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//MERGE SORT
	//-------------------------------------------------
	
	//tab is sorted by last operation
	//so change the direction
	tabs = reverse(tabs);

	//sort
	double time_reverse_mergesort = count_time_of_sorting(tabs,"merge_sort");

	if(check_if_sorted(tabs)) cout << "Start with reverse sorted numbers with 'Mergesort'. Result: SORTED..." << endl;
	else cout << "Start with reverse sorted numbers with 'Mergesort'. Result: NOT SORTED..." << endl;

	//-------------------------------------------------
	//INTOSORT
	//-------------------------------------------------

	//tab is sorted by last operation
	//so change the direction
	tabs = reverse(tabs);

	//sort
	double time_reverse_introsort=count_time_of_sorting(tabs,"introsort");

	if(check_if_sorted(tabs)) cout << "Start with reverse sorted numbers with 'Introsort'. Result: SORTED..." << endl;
	else cout << "Start with reverse sorted numbers with 'Introsort'. Result: NOT SORTED..." << endl;




	//-------------------------------------------------
	//-------------------------------------------------
	//show all results
	cout << endl << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Category\\Sort" <<"                        "<< "Quicksort"<< "   "<< "Mergesort" <<"   "<< "Introsort" << endl; 
	cout << "ALL RANDOM: " <<"                          "<< fixed << setprecision(4) << time_rand_quicksort <<"       "<<fixed << setprecision(4)<< time_rand_mergesort << "       "<<fixed << setprecision(4)<< time_rand_introsort<< endl;
	cout << "25 sorted: " <<"                           "<< fixed << setprecision(4) << time_25_quicksort <<"       "<< fixed << setprecision(4)<< time_25_mergesort << "       "<<fixed << setprecision(4)<< time_25_introsort<< endl;
	cout << "50 sorted: " <<"                           "<< fixed << setprecision(4) << time_50_quicksort <<"       "<< fixed << setprecision(4)<< time_50_mergesort << "       "<<fixed << setprecision(4)<< time_50_introsort<< endl;
	cout << "75 sorted: " <<"                           "<< fixed << setprecision(4) << time_75_quicksort <<"       "<< fixed << setprecision(4)<< time_75_mergesort << "       "<<fixed << setprecision(4)<< time_75_introsort<< endl;
	cout << "95 sorted: " <<"                           "<< fixed << setprecision(4) << time_95_quicksort <<"       "<< fixed << setprecision(4)<< time_95_mergesort << "       "<<fixed << setprecision(4)<< time_95_introsort<< endl;
	cout << "99 sorted: " <<"                           "<< fixed << setprecision(4) << time_99_quicksort <<"       "<< fixed << setprecision(4)<< time_99_mergesort << "       "<<fixed << setprecision(4)<< time_99_introsort<< endl;
	cout << "99,7 sorted: " <<"                         "<< fixed << setprecision(4) << time_99_7_quicksort <<"       "<< fixed << setprecision(4)<< time_99_7_mergesort << "       "<<fixed << setprecision(4)<< time_99_7_introsort<< endl;
	cout << "All sorted, but in reverse direction: " << fixed << setprecision(4) << time_reverse_quicksort <<"       "<< fixed << setprecision(4)<< time_reverse_mergesort << "       "<<fixed << setprecision(4)<< time_reverse_introsort<< endl;
	cout << "--------------------------------------------------------------------------------" << endl;


}


#endif