#include <iostream>
#include <numeric> 
#include <vector>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

//#define DEBUG 1

typedef long long int llint;

struct Range {
	int left;
	int right;

	Range () {}
	Range (int l, int r) {
		left = l;
		right = r;
	}

	void print() {
		printf("[ %d %d ]\n", left, right);
	}
};

class Data {
public:
	int date ;
	string currency ;
	string exchange ;
	float low ;
	float high ;
	llint cap ;

	Data () { }
	Data (int i_d, string& i_cur, string& i_ex, float i_low, float i_high, llint i_cap) {
		date = i_d;
		currency = i_cur;
		exchange = i_ex;
		low = i_low;
		high = i_high;
		cap = i_cap;
	}

	void print() {
		cout << date << "\t" << currency << "\t" << exchange << "\t" << low << "\t" << high << "\t" << cap << "\n";
	}
};

void print_data(vector<Data*> ptr, int num) {
	for (int i = 0; i < num; ++i ) {
		printf("%d. ", i);
		ptr[i]->print();
	}
}

bool sortByexchange(const Data* lhs, const Data* rhs) { return lhs->exchange < rhs->exchange ; }
bool sortBycurrency(const Data* lhs, const Data* rhs) { return lhs->currency < rhs->currency ; }
bool sortBydate(const Data* lhs, const Data* rhs) { return lhs->date < rhs->date ; }
bool myfunction (const Data &element, const int value) { return element.date < value ; }

Range binary_date(vector < Data* > &ptr_d, int left, int right, int date) {
	if (left == -1 || right == -1)
		return Range(-1, -1);

    while (left <= right)
    {
        int m = left + (right-left)/2;
 
        if (ptr_d[m]->date == date) {
        	int lower = m, upper = m;
        	int num_data = ptr_d.size() - 1;
        	while (lower > left && ptr_d[lower - 1]->date == date)
        		--lower;

        	while (upper < right && ptr_d[upper + 1]->date == date)
        		++upper;

            return Range(lower, upper);
        }
 
        if (ptr_d[m]->date < date) {
            left = m + 1;
        } else {
            right = m - 1;
        }
    }
 
 	// not found
    return Range(-1, -1);
}

Range binary_currency (vector < Data* >& ptr_d, int left, int right, string& currency) {
	if (left == -1 || right == -1)
		return Range(-1, -1);

    while (left <= right)
    {
        int m = left + (right-left)/2;
 
        if (ptr_d[m]->currency == currency) {
        	int lower = m, upper = m;
        	int num_data = ptr_d.size() - 1;
        	while (lower > left && ptr_d[lower - 1]->currency == currency)
        		--lower;

        	while (upper < right && ptr_d[upper + 1]->currency == currency)
        		++upper;

            return Range(lower, upper);
        }
 
        if (ptr_d[m]->currency < currency)
            left = m + 1;
 
        else
            right = m - 1;
    }
 
 	// not found
    return Range(-1, -1);
}

Range binary_exchange (vector < Data* >& ptr_d, int left, int right, string& t_exchange) {
	if (left == -1 || right == -1)
		return Range(-1, -1);

    while (left <= right)
    {
        int m = left + (right-left)/2;
 
        if (ptr_d[m]->exchange == t_exchange) {
        	int lower = m, upper = m;
        	int num_data = ptr_d.size() - 1;
        	while (lower > left && ptr_d[lower - 1]->exchange == t_exchange)
        		--lower;

        	while (upper < right && ptr_d[upper + 1]->exchange == t_exchange)
        		++upper;

            return Range(lower, upper);
        }
 
        if (ptr_d[m]->exchange < t_exchange)
            left = m + 1;
 
        else
            right = m - 1;
    }
 
 	// not found
    return Range(-1, -1);
}


int left_date ( vector < Data* > &ptr_d, int date , int left, int right ) {
	if ( left > right ) {
		return left ;
	}
	int mid = left + ( ( right - left ) / 2 ) ;
	if (ptr_d[mid]->date >= date) {
		return left_date (ptr_d, date, left, mid - 1);
	} else {
       	return left_date (ptr_d, date, mid + 1, right);
   	}
}

int right_date ( vector < Data* > &ptr_d, int date , int left, int right ) {
	if ( left > right ) {
		return right ;
	}
	int mid = left + (( right - left ) / 2 ) ;
	if (ptr_d[mid]->date > date) {
		return right_date (ptr_d, date, left, mid - 1);
	} else {
       	return right_date (ptr_d, date, mid + 1, right);
   	}
}

int left_currency ( vector < Data* > &ptr_d, string currency , int left, int right ) {
	if ( left > right ) {
		return left ;
	}
	int mid = left + (( right - left ) / 2 ) ;
	if (ptr_d[mid]->currency >= currency) {
		return left_currency (ptr_d, currency, left, mid - 1);
	} else {
       	return left_currency (ptr_d, currency, mid + 1, right);
   	}
}

int right_currency ( vector < Data* > &ptr_d, string currency , int left, int right ) {
	if ( left > right ) {
		return right ;
	}
	int mid = left + (( right - left ) / 2 ) ;
	if (ptr_d[mid]->currency > currency) {
		return right_currency (ptr_d, currency, left, mid - 1);
	} else {
       	return right_currency (ptr_d, currency, mid + 1, right);
   	}
}

int left_exchange ( vector < Data* > &ptr_d, string exchange , int left, int right ) {
	if ( left > right ) {	
		return left ;
	}
	int mid = left + (( right - left ) / 2 ) ;
	if (ptr_d[mid]->exchange >= exchange) {
		return left_exchange (ptr_d, exchange, left, mid - 1);
	} else {
       	return left_exchange (ptr_d, exchange, mid + 1, right);
   	}
}

int right_exchange ( vector < Data* > &ptr_d, string exchange , int left, int right ) {
	if ( left > right ) {
		return right ;
	}
	int mid = left + (( right - left ) / 2 ) ;
	if (ptr_d[mid]->exchange > exchange) {
		return right_exchange (ptr_d, exchange, left, mid - 1);
	} else {
       	return right_exchange (ptr_d, exchange, mid + 1, right);
   	}
}

void query_search ( vector < Data* > &ptr_d, int date, string& currency, string& exchange , int left, int right ) {
	/*int left_1, left_2, left_3, right_1, right_2, right_3 ;

	
	left_1 = left_date ( ptr_d, date, left, right ) ;
	right_1 = right_date ( ptr_d, date, left, right ) ;
	left_2 = left_currency ( ptr_d, currency, left_1, right_1 ) ;
	right_2 = right_currency ( ptr_d, currency, left_1, right_1 ) ;
	left_3 = left_exchange ( ptr_d, exchange, left_2, right_2 ) ;
	right_3 = right_exchange ( ptr_d, exchange, left_2, right_2 ) ;*/
	Range retRange;
	retRange = binary_date(ptr_d, left, right, date);
	retRange = binary_currency(ptr_d, retRange.left, retRange.right, currency);
	retRange = binary_exchange(ptr_d, retRange.left, retRange.right, exchange);
	left = retRange.left, right = retRange.right;
	
	//fprintf(fp_w, "%.4f\t%.4f\t%lli\n", ptr_d[left_3]->low, ptr_d[left_3]->high, ptr_d[left_3]->cap);
	cout << fixed << setprecision(4);
	//if ( left_3 > right_3 ) {
	if ( left == -1 || right == -1) {
		//cout << left_1 << " " << right_1 << '\n' ;
		//cout << left_2 << " " << right_2 << '\n' ;
		//cout << left_3 << " " << right_3 << '\n' ;
		cout << "none\n";
	} else {
		//cout << ptr_d[left_3]->low << " " << ptr_d[left_3]->high << " " << ptr_d[left_3]->cap << "\n" ;
		cout << ptr_d[left]->low << " " << ptr_d[left]->high << " " << ptr_d[left]->cap << "\n" ;
	}//cout << ptr_d[left_3]->low << '\t' << ptr_d[left_3]->high << '\t' << ptr_d[left_3]->cap << '\n' ;
	/*cout << left_1 << " " << right_1 << '\n' ;
	cout << left_2 << " " << right_2 << '\n' ;
	cout << left_3 << " " << right_3 << '\n' ;*/
}

void price_search ( vector < Data* > &ptr_d, string min_max, int date , string& currency, int left, int right ) {
	/*
	int left_1, left_2, left_3, right_1, right_2, right_3 ;
	left_1 = left_date ( ptr_d, date, left, right ) ;
	right_1 = right_date ( ptr_d, date, left, right ) ;
	left_2 = left_currency ( ptr_d, currency, left_1, right_1 ) ;
	right_2 = right_currency ( ptr_d, currency, left_1, right_1 ) ;*/
	Range retRange;
	retRange = binary_date(ptr_d, 0, ptr_d.size() - 1, date);
	retRange = binary_currency(ptr_d, retRange.left, retRange.right, currency);
	
	//if ( left_2 > right_2)
	//	return Range(-1, -1);
	//else
	//	return Range(left_2, right_2);
	left = retRange.left, right = retRange.right;
	cout << fixed << setprecision(4);
	if ( left == -1 || right == -1 ) {
		cout << "none\n" ;
	} else {
		if ( min_max == "min" ) {
			
			vector < float > lows ;
			//for ( int i = left_2 ; i < right_2 + 1 ; i++ ) {
			for ( int i = left ; i <= right; i++ ) {
				lows.push_back( ptr_d[i]->low ) ;
			}
			float _min = *(min_element(lows.begin(), lows.end()));
			
			//float _min = *(min_element(ptr_d.begin() + left_2, ptr_d.begin() + right_2 + 1))
			cout << _min << "\n" ;
		} else if ( min_max == "max" ) {
			vector < float > highs ;
			//for ( int i = left_2 ; i < right_2 + 1 ; i++ ) {
			for ( int i = left ; i <= right; i++ ) {
				highs.push_back( ptr_d[i]->high ) ;
			}
			float _max = *(max_element(highs.begin(), highs.end()));
			cout << _max << "\n" ;
		} else {
			cout << "none\n" ;
		}
	}
}

Range cap_search ( vector < Data* > &ptr_d, int date , string& exchange, int left, int right ) {
	//Range ret;
	
	int left_1, left_2, right_1, right_2 ;
	left_1 = left_date ( ptr_d, date, left, right ) ;
	right_1 = right_date ( ptr_d, date, left, right ) ;
	left_2 = left_exchange ( ptr_d, exchange, left_1, right_1 ) ;
	right_2 = right_exchange ( ptr_d, exchange, left_1, right_1 ) ;
	
	//Range retRange;
	//retRange = binary_date(ptr_d, 0, ptr_d.size() - 1, date);
	//retRange = binary_exchange(ptr_d, retRange.left, retRange.right, exchange);

	if ( left_2 > right_2 ) {
		//cout << "none\n" ;
		return Range(-1, -1);
	} else {
		return Range(left_2, right_2);
		//llint cap_sum = 0;
		//for ( int i = left_2 ; i < right_2 + 1 ; ++i ) {
		//	cap_sum += ptr_d[i]->cap;
		//}
		//cout << cap_sum << "\n" ;
		//printf("%lli\n", cap_sum);
	}
}


int main(int argc, char const *argv[]){

	FILE *fp_r = fopen( argv[1] , "r");

	vector < Data > my_data ;

	if (fp_r == NULL)
	    return -1;

	Data tmp ;
	int tmp_date;
	string tmp_currency;
	string tmp_exchange;
	char char_currency[100] ;
	char char_exchange[100] ;
	float tmp_low;
	float tmp_high;
	llint tmp_cap;

	while ( !feof(fp_r) ) {
		
		//fscanf(fp_r, "%d %s %s %f %f %llint", &(tmp.date), char_currency, char_exchange, &(tmp.low), &(tmp.high), &(tmp.cap) );
		fscanf(fp_r, "%d%s%s%f%f%lli", &tmp_date, char_currency, char_exchange, &tmp_low, &tmp_high, &tmp_cap );
		//tmp.currency = string(char_currency) ;
		//tmp.exchange = string(char_exchange) ;
		string tmp_currency(char_currency);
		string tmp_exchange(char_exchange);

		my_data.push_back ( Data(tmp_date, tmp_currency, tmp_exchange, tmp_low, tmp_high, tmp_cap) ) ;
	}

	vector < Data* > ptr_d ;
	ptr_d.reserve(my_data.size());
	for (int i = 0; i < my_data.size(); i++) {
    	ptr_d.push_back( &(my_data[i]) );
	}


	stable_sort(ptr_d.begin(), ptr_d.end(), sortByexchange);

	vector < Data* > ptr_d2(ptr_d);

	stable_sort(ptr_d.begin(), ptr_d.end(), sortBycurrency);
	stable_sort(ptr_d.begin(), ptr_d.end(), sortBydate);

	stable_sort(ptr_d2.begin(), ptr_d2.end(), sortBydate);
	/*for ( int i = 84000 ; i < 87999; i++ ) {
		cout << ptr_d2[i]->date << '\t' << ptr_d2[i]->currency << '\t' << ptr_d2[i]->low << '\n';
	}*/

	int i_date ;
	//string i_key ;
	char buf_i_key[100];
	string i_currency ;
	string i_exchange ;
	char buf_i_exchange[100];
	string key ;
	string min_max ;
	
	Range retRange;
	int left, right;
	cout << fixed << setprecision(4);

	#ifdef DEBUG
	int test_left, test_right, test_date;
	Range test_range;
	print_data(ptr_d, 20);
	#endif

	//while ( cin >> i_key ) {
	while (EOF != fscanf(stdin, "%s", buf_i_key)) {
		string i_key(buf_i_key);
		//cout << i_key << '\n' ;
 		if ( i_key == "query" ) {
			cin >> i_date >> i_currency >> i_exchange ;
			//query_search (ptr_d, i_date, i_currency, i_exchange, 0, ptr_d.size()-1 ) ;

			//print_data(ptr_d, 20);
			retRange = binary_date(ptr_d, 0, ptr_d.size() - 1, i_date);
			#ifdef DEBUG
			printf("insert l, r, date:\n");
			while (cin >> test_left >> test_right >> test_date) {
				test_range = binary_date(ptr_d, test_left, test_right, test_date);
				test_range.print();
				printf("insert l, r, date:\n");
			}
			#endif
			retRange = binary_currency(ptr_d, retRange.left, retRange.right, i_currency);
			retRange = binary_exchange(ptr_d, retRange.left, retRange.right, i_exchange);
			left = retRange.left, right = retRange.right;
			
			if ( left == -1 || right == -1) {
				//cout << left_1 << " " << right_1 << '\n' ;
				//cout << left_2 << " " << right_2 << '\n' ;
				//cout << left_3 << " " << right_3 << '\n' ;
				cout << "none\n";
			} else {
			//cout << ptr_d[left_3]->low << " " << ptr_d[left_3]->high << " " << ptr_d[left_3]->cap << "\n" ;
				//cout << ptr_d[left]->low << " " << ptr_d[left]->high << " " << ptr_d[left]->cap << "\n" ;
				printf("%.4f %.4f %lli\n", ptr_d[left]->low, ptr_d[left]->high, ptr_d[left]->cap);
			}
		} else if ( i_key == "price" ) {
			cin >> min_max >> i_date >> i_currency ;
			//price_search (ptr_d, min_max, i_date, i_currency, 0, ptr_d.size()-1 ) ;
			retRange = binary_date(ptr_d, 0, ptr_d.size() - 1, i_date);
			retRange = binary_currency(ptr_d, retRange.left, retRange.right, i_currency);
			
			//if ( left_2 > right_2)
			//	return Range(-1, -1);
			//else
			//	return Range(left_2, right_2);
			left = retRange.left, right = retRange.right;
			if ( left == -1 || right == -1 ) {
				cout << "none\n" ;
			} else {
				if ( min_max == "min" ) {
					
					float _min = 10000000000.0;
					for ( int i = left ; i <= right; i++ ) {
						if (ptr_d[i]->low < _min)
							_min = ptr_d[i]->low;
					}
					
					//float _min = *(min_element(ptr_d.begin() + left_2, ptr_d.begin() + right_2 + 1))
					//cout << _min << "\n" ;
					printf("%.4f\n", _min);

				} else {//( min_max == "max" ) {
					//for ( int i = left_2 ; i < right_2 + 1 ; i++ ) {
					float _max = -10000000000.0;
					for ( int i = left ; i <= right; i++ ) {
						if (ptr_d[i]->high > _max)
							_max = ptr_d[i]->high;
					}
					//cout << _max << "\n" ;
					printf("%.4f\n", _max);
				} 
			}

		} else if ( i_key == "cap" ) {
			//cin >> i_date >> i_exchange ;
			fscanf(stdin, "%d %s", &i_date, buf_i_exchange);
			string i_exchange(buf_i_exchange);
			//cout << "hey" << i_date << " " << i_exchange << "\n";
			//ans = cap_search (ptr_d2, i_date, i_exchange, 0, ptr_d2.size()-1 ) ;

			retRange = binary_date(ptr_d2, 0, ptr_d2.size() - 1, i_date);
			retRange = binary_exchange(ptr_d2, retRange.left, retRange.right, i_exchange);

			left = retRange.left, right = retRange.right;
			if (left == -1 || right == -1)
				printf("none\n");
			else {
				//int right = ans.right;
				llint cap_sum = 0;
				for ( int i = left ; i <= right; ++i ) {
						cap_sum += ptr_d2[i]->cap;
				}
				//cout << cap_sum << "\n" ;
				printf("%lli\n", cap_sum);
			}

		} else {// ( i_key == "end") 
			break;
		}
	}
	fclose(fp_r) ;

	return 0 ;

}