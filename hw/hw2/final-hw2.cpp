#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdio.h>

//#define DEBUG false

using namespace std;

typedef long long int lli;

class Data {
public:
	int 		date;
	string 		currency;
	string 		exchange;
	float 		low;
	float 		high;
	lli 		cap;

	Data () { }

	Data (int d, string& currency_name, string& exchange_name, float l, float h, lli& c) {
		date 		= d;
		currency 	= currency_name;
		exchange 	= exchange_name;
		low 		= l;
		high 		= h;
		cap 		= c;
	}

	void print() {
		cerr << date << "\t" << currency << "\t" << exchange << "\t" 
			 << low << "\t" << high << "\t" << cap << "\n";
	}
};

typedef vector<Data*>::iterator iter;

struct BSPair {
	// start index and end index for binary search
	iter idx_start;
	iter idx_end;
	BSPair () { }
	BSPair (iter s, iter e) {
		idx_start = s;
		idx_end   = e;
	}
	void print(iter beg) {
		cerr << "[ " << distance(beg, idx_start) << " " << distance(beg, idx_end) << " )\n";
	}
};

inline void data_head(vector<Data*>& ptr, int size) {
	int nData = ptr.size();
	if (nData < size)
		size = nData;

	for (int i = 0; i < size; ++i) {
		cerr << i << ".\t";
		ptr[i]->print();
	}
}

inline bool compare_by_date (Data* d1, Data* d2) { 
	// d1->date goes before d2->date if:
	// d1 : 20130316
	// d2 : 20130907
	// d1 < d2
	return (d1->date < d2->date);
}

inline bool compare_by_currency (Data* d1, Data* d2) {
	// d1->currency goes before d2->currency if:
	// currency_1 : Sprouts	KuCoin
	// currency_2 : DigiByte
	return (d1->currency < d2->currency);
}

inline bool compare_by_exchange (Data* d1, Data* d2) {
	return (d1->exchange < d2->exchange);
}

inline bool compare_by_high (Data* d1, Data* d2) {
	return (d1->high < d2->high);
}

inline bool compare_by_low (Data* d1, Data* d2) {
	return (d1->low < d2->low);
}

inline bool compare_date_low (Data* d1, int value) { 
	// d1->date goes before value if:
	// d1 : 20130316
	// value : 20130907
	return (d1->date < value);
}

inline bool compare_currency_low (Data* d1, const string& value) {
	// d1->currency goes before d2->currency if:
	// currency_1 : Sprouts	KuCoin
	// value : DigiByte
	return (d1->currency < value);
}

inline bool compare_exchange_low (Data* d1, const string& value) {
	return (d1->exchange < value);
}

inline bool compare_date_up (int value, Data* d1) { 
	// d1->date goes before d2->date if:
	// d1 : 20130316
	// d2 : 20130907
	// d1 < d2
	return (value < d1->date);
}

inline bool compare_currency_up (const string& value, Data* d1) {
	// d1->currency goes before d2->currency if:
	// currency_1 : Sprouts	KuCoin
	// currency_2 : DigiByte
	return (value < d1->currency);
}

inline bool compare_exchange_up (const string& value, Data* d1) {
	return (value < d1->exchange);
}

inline void sort_by_date (vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by date
	// note: last should be inclusive
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_date);
}

inline void sort_by_currency(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by currency name
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_currency);
}

inline void sort_by_exchange(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by exchange name
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_exchange);
}

// Binary-search.
// Ref: https://www.geeksforgeeks.org/binary-search/
// A iterative binary search function. It returns
// location of x in given array arr[l..r] if present,

// note: [l, r)
inline BSPair binary_search_date(vector<Data*>& ptr_dataset, iter l, iter r, const int target_date) {
	iter lower, upper;
	lower = lower_bound(l, r, target_date, compare_date_low);
    upper = upper_bound(l, r, target_date, compare_date_up);

    return BSPair(lower, upper);
}

inline BSPair binary_search_currency(vector<Data*>& ptr_dataset, iter l, iter r, string& target_currency) {
	iter lower, upper;
	lower = lower_bound(l, r, target_currency, compare_currency_low);
    upper = upper_bound(l, r, target_currency, compare_currency_up);

    return BSPair(lower, upper);
}

inline BSPair binary_search_exchange(vector<Data*>& ptr_dataset, iter l, iter r, string& target_exchange) {
	iter lower, upper;
	lower = lower_bound(l, r, target_exchange, compare_exchange_low);
    upper = upper_bound(l, r, target_exchange, compare_exchange_up);

    return BSPair(lower, upper);
}

inline lli calc_total_cap(vector<Data*>& ptr_dataset, iter idx_start, iter idx_end) {
	// we assumed that ptr_dataset is already sorted from
	// exchange->date
	// and [idx_start, idx_end)
	lli ret = (*idx_start)->cap;
	for (iter i = idx_start + 1; i != idx_end; ++i) {
		ret += (*i)->cap;
	}
	return ret;
}

int main(int argc, char const *argv[]) {
	
	if (argc < 2) {
		cerr << "usage: ./program dataset";
		return 1;
	}
	const char* dataFile = argv[1];
	// read data
	FILE* pFile = fopen (dataFile, "r");

	vector<Data> dataset;

	Data   tmp_data;
	Data*  ptr_data;

	int    tmp_date;
	string tmp_currency;
	string tmp_exchange;
	char   buf_currency[100];
	char   buf_exchange[100];
	float  tmp_low;
	float  tmp_high;
	lli    tmp_cap;


	while (EOF != fscanf (pFile, "%d%s%s%f%f%lli", &tmp_date, buf_currency, buf_exchange, &tmp_low, &tmp_high, &tmp_cap)) {
		
		string tmp_currency(buf_currency);
		string tmp_exchange(buf_exchange);
		
		dataset.push_back(Data(tmp_date, tmp_currency, tmp_exchange, tmp_low, tmp_high, tmp_cap));
	}
	
	int nData = dataset.size();


	
	vector<Data*> ptr_dataset(nData);
	for (int i = 0; i < nData; ++i) {
		ptr_dataset[i] = &(dataset[i]);
	}
	
	sort_by_exchange(ptr_dataset, 0, nData - 1);
	vector<Data*> ptr_dataset_ecd(ptr_dataset); // for 'query', 'price'

	sort_by_currency(ptr_dataset_ecd, 0, nData - 1);
	sort_by_date(ptr_dataset_ecd, 0, nData - 1);


	sort_by_date(ptr_dataset, 0, nData - 1);   // for 'cap'

	int q_date;
	lli cap_result;

	char   buf_query[100];
	char   buf_price[100];

	BSPair search_range;
	Data* target_data;

	char buffer_out[100];
	char none_out[] = "none\n";

	while (EOF != fscanf(stdin, "%s", buf_query)) {
		string query(buf_query);
		if (query == "query") {

			fscanf(stdin, "%d %s %s", &q_date, buf_currency, buf_exchange);
			string q_currency(buf_currency);
			string q_exchange(buf_exchange);

			// binary search, with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. exchange, [BSPair of 2]
			// 4. peek the result from 3. None if [-1, -1]
			iter end_pt = ptr_dataset_ecd.end();
			search_range = binary_search_date(ptr_dataset_ecd, ptr_dataset_ecd.begin(), end_pt, q_date);

			search_range = binary_search_currency(ptr_dataset_ecd, search_range.idx_start,
												  			search_range.idx_end, q_currency);

			search_range = binary_search_exchange(ptr_dataset_ecd, search_range.idx_start,
															search_range.idx_end, q_exchange);

			if ( search_range.idx_start == end_pt || (*search_range.idx_start)->exchange != q_exchange) {
				cout.write(none_out, 5);
			} else {
				target_data = *(search_range.idx_start);
				#ifdef DEBUG
				search_range.print(ptr_dataset_ecd.begin());
				target_data->print();
				#endif
				fprintf(stdout, "%.4f %.4f %lli\n", target_data->low, target_data->high, target_data->cap);
			}
		} else if (query == "price") {
			fscanf(stdin, "%s %d %s", buf_price, &q_date, buf_currency);
			string q_price(buf_price);
			string q_currency(buf_currency);
			// binary search with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. find the `max' by high
			//          or `min' by low    based on the result from 3. None if [-1, -1]
			iter end_pt = ptr_dataset_ecd.end();
			search_range = binary_search_date(ptr_dataset_ecd, ptr_dataset_ecd.begin(), ptr_dataset_ecd.end(), q_date);
			search_range = binary_search_currency(ptr_dataset_ecd, search_range.idx_start,
												  			search_range.idx_end, q_currency);
			

			if (search_range.idx_start == end_pt || (*search_range.idx_start)->currency != q_currency) {
				cout.write(none_out, 5);
			} else {
				if (q_price == "max") {
					printf("%.4f\n", (*max_element(search_range.idx_start,
												search_range.idx_end, compare_by_high))->high);
				} else { // q_price == "min"
					printf("%.4f\n", (*min_element(search_range.idx_start,
												search_range.idx_end, compare_by_low))->low);
				}
			}
		} else if (query == "cap") { // cap
			fscanf(stdin, "%d %s", &q_date, buf_exchange);
			string q_exchange(buf_exchange);
			// binary search with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. exchange, [BSPair of 2]
			// 4. peek the result from 3. None if [-1, -1]

			iter end_pt = ptr_dataset.end();
			search_range = binary_search_date(ptr_dataset, ptr_dataset.begin(), end_pt, q_date);

			search_range = binary_search_exchange(ptr_dataset, search_range.idx_start,
												  			search_range.idx_end, q_exchange);
			

			if ( search_range.idx_start == end_pt || (*search_range.idx_start)->date != q_date || (*search_range.idx_start)->exchange != q_exchange
				) {
				cout.write(none_out, 5);
			} else {

				fprintf(stdout, "%lli\n", calc_total_cap(ptr_dataset, search_range.idx_start,
																	search_range.idx_end));
			}
		} else { //query == "end"
			break;
		}
	}
	return 0;
}
