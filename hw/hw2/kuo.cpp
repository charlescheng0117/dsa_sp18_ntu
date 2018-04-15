# include <iostream>
# include <vector> 
# include <fstream>
# include <string>
# include <iomanip>
# include <stdio.h>
# include <algorithm>
using namespace std;

#define KEY_NOT_FOUND -1

class Data {
	public:
		int date;
		string currency;
		string exchange;
		float low;
		float high;
		long long int daily_caps;
		
	Data () { }
	
	Data (int d, string& c, string& e, float l, float h, long long int dc) {
		date = d;
		currency = c;
		exchange = e;
		low = l;
		high = h;
		daily_caps = dc;
	}
};
/*
void insertion_sort_date (vector<Data*> );
void insertion_sort_currency (vector<Data*> );
void insertion_sort_exchange (vector<Data*> );
*/

bool compare_date( Data* , Data* );
bool compare_cur( Data* , Data* );
bool compare_ex( Data* , Data* );

int binarySearchDate (vector<Data*>& , int , int , int );
int binarySearchCurrency (vector<Data*>& , string& , int , int );
int binarySearchExchange (vector<Data*>& , string& , int , int );
int midpoint(int ,int);

int main (int argc, char** argv){


//Read data
	//ifstream in_public_data( str_filename, ios::in);
	FILE* fp = fopen (argv[1], "r");
//variable declaration
	string scheme;
	int date;
	string currency;
	string exchange;
	char  buffer_currency[100];
	char  buffer_exchange[100];
	float low;
	float high;
	long long int daily_caps;
//class and vector declaration
	Data temp;
	vector <Data> vec;
	vector <Data*> vecPtr;
//read data into vector	
	while (fscanf(fp, "%d%s%s%f%f%lli", &date, buffer_currency, buffer_exchange, &low, &high, &daily_caps) != EOF) {
		currency = string(buffer_currency);
		exchange = string(buffer_exchange);
		temp = Data(date, currency, exchange, low, high, daily_caps);
		vec.push_back(temp);
	}
	for (int i = 0; i < vec.size(); i++ )
		vecPtr.push_back( &(vec[i]) );
/*		
	cout << "Before sorting...\n";
	for(int i = 0; i < 100; i++)
	{
		cout << vecPtr[i]->date << " " << vecPtr[i]->currency << " " << vecPtr[i]->exchange << " " 
		<< vecPtr[i]->low << " " << vecPtr[i]->high << " " << vecPtr[i]->daily_caps << "\n";
	}	
*/		
//sort(insertion sort)
	stable_sort( vecPtr.begin(), vecPtr.end(), compare_ex );
	stable_sort( vecPtr.begin(), vecPtr.end(), compare_cur );
	stable_sort( vecPtr.begin(), vecPtr.end(), compare_date );
	
	/*
	insertion_sort_exchange ( vecPtr );
	insertion_sort_currency ( vecPtr );
	insertion_sort_date ( vecPtr );
	

	cout << "After sorting...\n";
	for(int i = 0; i < 100; i++)
	{
		cout << vecPtr[i]->date << " " << vecPtr[i]->currency << " " << vecPtr[i]->exchange << " " 
		<< vecPtr[i]->low << " " << vecPtr[i]->high << " " << vecPtr[i]->daily_caps << "\n";
	}
	*/	
//search	
//	cout << "Please input scheme, date, currency, exchange : \n";
	cout << fixed << setprecision(4);
	int end_data = vecPtr.size() - 1;
	while( cin >> scheme )
	{
		if( scheme == "end" )
			break;
		else
		//else if( scheme == "query" )
		{
			cin >> date >> currency >> exchange;
			
			int index_date = binarySearchDate( vecPtr, date, 0, vecPtr.size() - 1 );
//	cout << "index_date : " << index_date << "\n";
			if ( index_date == -1 )
			{
				cout << "none\n";
				continue;
			}
			else
			{
				int lower_bound_date = index_date;
				int higher_bound_date = index_date;
				if( lower_bound_date != 0 )
				{
					while( lower_bound_date > 0 && vecPtr[lower_bound_date]->date == vecPtr[lower_bound_date - 1]->date )
					{
						lower_bound_date--;
					}					
				
				}

				if( higher_bound_date != end_data )
				{
					while( higher_bound_date < end_data && vecPtr[higher_bound_date]->date == vecPtr[higher_bound_date + 1]->date )
					{
						higher_bound_date++;
					}	
				}
//	cout << "lower_bound_date : " << lower_bound_date<<"\n";
//	cout << "higher_bound_date : " << higher_bound_date<<"\n";
			 
				int index_cur = binarySearchCurrency( vecPtr, currency, lower_bound_date, higher_bound_date);
//	cout << "index_currency : " << index_cur <<"\n";
				if ( index_cur == -1 )
				{
					cout << "none\n";
					continue;
				}
				else
				{
					int lower_bound_cur = index_cur;
					int higher_bound_cur = index_cur;
					if( lower_bound_cur != lower_bound_date )
					{
						while( vecPtr[lower_bound_cur]->currency == vecPtr[lower_bound_cur - 1]->currency )
						{
							lower_bound_cur--;
							if( lower_bound_cur == lower_bound_date )
							break;
						}
					}	
					if( higher_bound_cur != higher_bound_date )
					{
						while( vecPtr[higher_bound_cur]->currency == vecPtr[higher_bound_cur + 1]->currency )
						{
							higher_bound_cur++;							
							if( higher_bound_cur == higher_bound_date )
							break;
						}

					}
//	cout << "lower_bound_cur : " << lower_bound_cur<<"\n";
//	cout << "higher_bound_cur : " << higher_bound_cur<<"\n";
			
					int index_ex = binarySearchExchange( vecPtr, exchange, lower_bound_cur, higher_bound_cur );
					if ( index_ex == -1 )
					{
						cout << "none\n";
						continue;
					}
//	cout << "index_ex : " << index_ex << "\n";
					cout << vecPtr[index_ex]->low << " " << vecPtr[index_ex]->high << " " << vecPtr[index_ex]->daily_caps << "\n";
				}
			}	
				
		}
		
		
			
	}	
	return 0;
}

bool compare_date( Data* i, Data* j ){
	return i->date < j->date;
}
bool compare_cur( Data* s1, Data* s2){
	return s1->currency < s2->currency;
}
bool compare_ex( Data* s1, Data* s2){
	return s1->exchange < s2->exchange;
}

void insertion_sort_date (vector<Data*> ptr)
{
	Data insert;
	for (int next = 1; next < ptr.size(); next++)
	{
		insert = *ptr[next];
		int moveItem = next;
		
		while ( ( moveItem > 0 ) && ( ptr[ moveItem - 1 ]->date > insert.date ) )
		{
			*ptr[ moveItem ] = *ptr[ moveItem - 1 ];
			moveItem--;
		}
		
		*ptr[ moveItem ] = insert;
	}
}

void insertion_sort_currency (vector<Data*> ptr)
{
	Data insert;
	for( int next = 1; next < ptr.size(); next++)
	{
		insert = *ptr[next];
		int moveItem = next;
		
		while ( ( moveItem > 0) && ( ptr[ moveItem - 1 ] -> currency > insert.currency) )
		{
			*ptr[ moveItem ] = *ptr[ moveItem - 1];
			moveItem--;
		}
		
		*ptr[ moveItem ] = insert;
	}
}

void insertion_sort_exchange ( vector<Data*> ptr)
{
	Data insert;
	for( int next = 1; next < ptr.size(); next++)
	{
		insert = *ptr[next];
		int moveItem = next;
		
		while ( ( moveItem > 0) && ( ptr[ moveItem - 1 ] -> exchange > insert.exchange ) )
		{
			*ptr[ moveItem ] = *ptr[ moveItem - 1];
			moveItem--;
		}
		
		*ptr[ moveItem ] = insert;
	}
}

int binarySearchDate(vector<Data*>& ptr, int key, int left, int right)
{
	//int KEY_NOT_FOUND = -1;
	while (left <= right)
	{
		int mid = midpoint(left, right);
		if( ptr[ mid ] -> date == key )
			return mid;
		if( ptr[ mid ] -> date < key )
			left = mid + 1;
		else
			right = mid - 1;
	}
	return KEY_NOT_FOUND;
}

int binarySearchCurrency(vector<Data*>& ptr, string& key, int left, int right)
{
	//int KEY_NOT_FOUND = -1;
	while (left <= right)
	{
		int mid = midpoint(left, right);
		if( ptr[ mid ] -> currency == key )
			return mid;
		if( ptr[ mid ] -> currency < key )
			left = mid + 1;
		else
			right = mid - 1;
	}
	return KEY_NOT_FOUND;
}

int binarySearchExchange(vector<Data*>& ptr, string& key, int left, int right)
{
	//int KEY_NOT_FOUND = -1;
	while (left <= right)
	{
		int mid = midpoint(left, right);
		if( ptr[ mid ] -> exchange == key )
			return mid;
		if( ptr[ mid ] -> exchange < key )
			left = mid + 1;
		else
			right = mid - 1;
	}
	return KEY_NOT_FOUND;
}

int midpoint(int l, int r)
{
	return l + ( ( r - l ) / 2);
}
