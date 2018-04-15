#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

typedef long long int lli;

struct BSPair {
	// start index and end index for binary search
	int idx_start;
	int idx_end;
	BSPair () { }
	BSPair (int s, int e) {
		idx_start = s;
		idx_end   = e;
	}
	void print() {
		cerr << "[ " << idx_start << " " << idx_end << " ]\n";
	}
};

class Data {
public:
	int 		date;
	string 		currency;
	string 		exchange;
	//char* 		currency;
	//char* 		exchange;
	float 		low;
	float 		high;
	lli 		cap;

	Data () { }

	Data (int d, string& currency_name, string& exchange_name, float l, float h, lli& c) {
	//Data (int d, char* currency_name, char* exchange_name, float l, float h, lli c) {
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

/*
inline void data_head(vector<Data*>& ptr, int size=num_head) {
	int nData = ptr.size();
	if (nData < size)
		size = nData;

	for (int i = 0; i < size; ++i) {
		cerr << i << ".\t";
		ptr[i]->print();
	}
}*/

inline bool compare_by_date (Data* d1, Data* d2) { 
	// d1->date goes before d2->date if:
	// d1 : 20130316
	// d2 : 20130907
	// d1 < d2
	if (d1->date < d2->date) {
		return true;
	} else {
		return false;
	}
}

inline bool compare_by_currency (Data* d1, Data* d2) {
	// d1->currency goes before d2->currency if:
	// currency_1 : Sprouts	KuCoin
	// currency_2 : DigiByte
	if (d1->currency < d2->currency) {
		return true;
	} else {
		return false;
	}
}

inline bool compare_by_exchange (Data* d1, Data* d2) {
	if (d1->exchange < d2->exchange) {
		return true;
	} else {
		return false;
	}
}

inline bool compare_by_high (Data* d1, Data* d2) {
	if (d1->high < d2->high) {
		return true;
	} else {
		return false;
	}
}

inline bool compare_by_low (Data* d1, Data* d2) {
	if (d1->low < d2->low) {
		return true;
	} else {
		return false;
	}
}

inline void sort_by_date (vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by date
	// note: last should be inclusive

	//time(&start_time);
	//cerr << "Start sorting by date.\n";
	// last is inclusive, so the range to sort is 
	// [begin() + first, begin() + last + 1)
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_date);
	
	//time(&end_time);
	//seconds = difftime(end_time, start_time);
	//cerr << "Time spent on sort_by_date: " << seconds << "\n";
	//cerr << "End sorting by date.\n";
}

inline void sort_by_currency(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by currency name

	//time(&start_time);
	//cerr << "Start sorting by currency.\n";
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_currency);

	//time(&end_time);
	//seconds = difftime(end_time, start_time);
	//cerr << "Time spent on sort_by_currency: " << seconds << "\n";
	//cerr << "End sorting by currency.\n";

}

inline void sort_by_exchange(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by exchange name

	//time(&start_time);
	//cerr << "Start sorting by exchange.\n";
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_exchange);
	
	//time(&end_time);
	//seconds = difftime(end_time, start_time);
	
	//cerr << "Time spent on sort_by_exchange: " << seconds << "\n";
	//cerr << "End sorting by exchange.\n";
	
}

// Binary-search.
// Ref: https://www.geeksforgeeks.org/binary-search/
// A iterative binary search function. It returns
// location of x in given array arr[l..r] if present,
// otherwise -1
//int binarySearch(int arr[], int l, int r, int x)
//int binary_search_date(vector<Data*>& ptr_dataset, int l, int r, int target_date) {


//inline BSPair binary_search_date(vector<Data*>& ptr_dataset, target_date) {
//	auto lower = std::lower_bound(data.begin(), data.end(), target_date, compare_by_date);
//    auto upper = std::upper_bound(data.begin(), data.end(), target_date, compare_by_date);


//}


inline BSPair binary_search_date(vector<Data*>& ptr_dataset, int l, int r, int target_date) {
	// if l = r = -1
	// then it's because we can't find the target from the previous binary search
	// so we return BSPair(-1, -1) again
	if (l == -1 || r == -1)
		return BSPair(-1, -1);

	while (l <= r) {
		int m = l + (r-l)/2;

		// Check if x is present at mid
		if (ptr_dataset[m]->date == target_date) {
			int idx_start = m, idx_end = m;
			int nData = ptr_dataset.size();
			// linear search for the start index of the range
			
			//while (idx_start != 0 && ptr_dataset[idx_start - 1]->date == target_date) {
			while (idx_start > l && ptr_dataset[idx_start - 1]->date == target_date) {
				--idx_start;
			}

			while (idx_end < r && ptr_dataset[idx_end + 1]->date == target_date) {
				++idx_end;
			}

			// linear search for the start index of the range
			return BSPair(idx_start, idx_end);
		}

		// If x greater, ignore left half
		if (ptr_dataset[m]->date < target_date)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	// if we reach here, then element was
	// not present
	return BSPair(-1, -1);
}

inline BSPair binary_search_currency(vector<Data*>& ptr_dataset, int l, int r, string& target_currency) {
	// if l = r = -1
	// then it's because we can't find the target from the previous binary search
	// so we return BSPair(-1, -1) again
	if (l == -1 || r == -1)
		return BSPair(-1, -1);

	while (l <= r) {
		int m = l + (r-l)/2;

		// Check if x is present at mid
		if (ptr_dataset[m]->currency == target_currency) {
			int idx_start = m, idx_end = m;
			int nData = ptr_dataset.size();

			// linear search for the start index of the range
			while (idx_start != 0 && ptr_dataset[idx_start - 1]->currency == target_currency) {
				--idx_start;
			}

			while (idx_end != nData - 1 && ptr_dataset[idx_end + 1]->currency == target_currency) {
				++idx_end;
			}

			// linear search for the start index of the range
			return BSPair(idx_start, idx_end);
		}

		// If x greater, ignore left half
		if (ptr_dataset[m]->currency < target_currency)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	// if we reach here, then element was not present
	return BSPair(-1, -1);
}

inline BSPair binary_search_exchange(vector<Data*>& ptr_dataset, int l, int r, string& target_exchange) {
	// if l = r = -1
	// then it's because we can't find the target from the previous binary search
	// so we return BSPair(-1, -1) again
	if (l == -1 || r == -1)
		return BSPair(-1, -1);

	while (l <= r) {
		int m = l + (r-l)/2;

		// Check if x is present at mid
		if (ptr_dataset[m]->exchange == target_exchange) {
			int idx_start = m, idx_end = m;
			int nData = ptr_dataset.size();

			// linear search for the start index of the range
			while (idx_start != 0 && ptr_dataset[idx_start - 1]->exchange == target_exchange) {
				--idx_start;
			}

			while (idx_end != nData - 1 && ptr_dataset[idx_end + 1]->exchange == target_exchange) {
				++idx_end;
			}

			// linear search for the start index of the range
			return BSPair(idx_start, idx_end);
		}

		// If x greater, ignore left half
		if (ptr_dataset[m]->exchange < target_exchange)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	// if we reach here, then element was
	// not present
	return BSPair(-1, -1);
}

inline lli calc_total_cap(vector<Data*>& ptr_dataset, int idx_start, int idx_end) {
	// we assumed that ptr_dataset is already sorted from
	// exchange->date
	// and idx_start, idx_end is inclusive
	lli ret = ptr_dataset[idx_start]->cap + ptr_dataset[idx_end]->cap;
	for (int i = idx_start + 1; i <= idx_end - 1; ++i) {
		ret += ptr_dataset[i]->cap;
	}
	return ret;
}

int main(int argc, char const *argv[]) {
	/*
	if (argc < 2) {
		cerr << "usage: ./program transactionData.txt";
		return 1;
	}*/
	const char* dataFile = argv[1];
	// read data
	FILE* pFile = fopen (dataFile, "r");
	//ifstream ifs;

	//ifs.open(dataFile, fstream::in);
	//if (!fs.is_open()) {
	//	cerr << "Error opening file from " << dataFile << ".\n";
	//	return 1;
	//}

	// vector of dataset
	//vector<Data> d(25620477);
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

	//cerr << "Start reading input from " << dataFile << ".\n";
	//time(&start_time);

	//while (ifs >> tmp_date >> tmp_currency >> tmp_exchange >> tmp_low >> tmp_high >> tmp_cap) {
	while (EOF != fscanf (pFile, "%d%s%s%f%f%lli", &tmp_date, buf_currency, buf_exchange, &tmp_low, &tmp_high, &tmp_cap)) {
		
		string tmp_currency(buf_currency);
		string tmp_exchange(buf_exchange);
		

		//Data* tmp_data = new Data(tmp_date, tmp_currency, tmp_exchange, tmp_low, tmp_high, tmp_cap);
		//dataset.push_back(tmp_data);
		//tmp_data.print();
		dataset.push_back(Data(tmp_date, tmp_currency, tmp_exchange, tmp_low, tmp_high, tmp_cap));
		//ptr_data = &(dataset.back());
		//dataset[i] = *tmp_data;
		//dataset[i].print();
		//ptr_dataset.push_back(ptr_data);
		//dataset.push_back(Data(tmp_date, string(buf_currency), tmp_exchange, tmp_low, tmp_high, tmp_cap));
	}
	
	// generate a pointer to our vector which stores the true data
	//data_head(ptr_dataset);
	//cin >> tmp_date;

	int nData = dataset.size();


	
	vector<Data*> ptr_dataset(nData);
	for (int i = 0; i < nData; ++i) {
		ptr_dataset[i] = &(dataset[i]);
	}
	
	//int nData = ptr_dataset.size();

	//cerr << "Stable sort from exchange -> currency -> date.\n";
	sort_by_exchange(ptr_dataset, 0, nData - 1);
	vector<Data*> ptr_dataset_ecd(ptr_dataset); // for 'query', 'price'
	//vector<Data*> ptr_dataset_cap(ptr_dataset);

	sort_by_currency(ptr_dataset_ecd, 0, nData - 1);
	sort_by_date(ptr_dataset_ecd, 0, nData - 1);

	//cerr << "Stable sort from exchange -> date.\n";
	//sort_by_exchange(ptr_dataset, 0, nData - 1);
	//sort_by_date(ptr_dataset_cap, 0, nData - 1);
	sort_by_date(ptr_dataset, 0, nData - 1);
	//vector<Data*> ptr_dataset_cap(ptr_dataset); // for 'cap'

	//string query;
	//string q_price;     // max or min
	int q_date;
	//string q_currency;
	//string q_exchange;
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
			//cerr << query << "\t" << q_date << "\t" << q_currency << "\t" << q_exchange << "\n";

			// binary search, with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. exchange, [BSPair of 2]
			// 4. peek the result from 3. None if [-1, -1]
			search_range = binary_search_date(ptr_dataset_ecd, 0, nData - 1, q_date);
			search_range = binary_search_currency(ptr_dataset_ecd, search_range.idx_start,
												  			search_range.idx_end, q_currency);
			search_range = binary_search_exchange(ptr_dataset_ecd, search_range.idx_start,
															search_range.idx_end, q_exchange);
			
			if (search_range.idx_start == -1) {
				//fprintf(stdout, "none\n");
				//printf("none\n");
				//cout << "none\n";
				cout.write(none_out, 5);
			} else {
				target_data = ptr_dataset_ecd[search_range.idx_start];
				fprintf(stdout, "%.4f %.4f %lli\n", target_data->low, target_data->high, target_data->cap);
				//printf("%.4f %.4f %lli\n", target_data->low, target_data->high, target_data->cap);
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
			search_range = binary_search_date(ptr_dataset_ecd, 0, nData - 1, q_date);
			search_range = binary_search_currency(ptr_dataset_ecd, search_range.idx_start,
												  			search_range.idx_end, q_currency);
			

			if (search_range.idx_start == -1 || search_range.idx_start == -1 ) {
				//fprintf(stdout, "none\n");
				//printf("none\n");
				cout.write(none_out, 5);
			} else {
				if (q_price == "max") {
					//target_data = *max_element(ptr_dataset_ecd.begin() + search_range.idx_start,
					//							ptr_dataset_ecd.begin() + search_range.idx_end + 1, compare_by_high);
					//cout << target_data->high << "\n";
					printf("%.4f\n", (*max_element(ptr_dataset_ecd.begin() + search_range.idx_start,
												ptr_dataset_ecd.begin() + search_range.idx_end + 1, compare_by_high))->high);
					//fprintf(stdout, "%.4f\n", target_data->high);
				} else { // q_price == "min"
					//target_data = *min_element(ptr_dataset_ecd.begin() + search_range.idx_start,
					//							ptr_dataset_ecd.begin() + search_range.idx_end + 1, compare_by_low);
					//cout << target_data->low << "\n";
					printf("%.4f\n", (*min_element(ptr_dataset_ecd.begin() + search_range.idx_start,
												ptr_dataset_ecd.begin() + search_range.idx_end + 1, compare_by_low))->low);
					//fprintf(stdout, "%.4f\n", target_data->low);
				}
			}
		} else if (query == "cap") { // cap
			//linestream >> q_date >> q_exchange;
			fscanf(stdin, "%d %s", &q_date, buf_exchange);
			string q_exchange(buf_exchange);
			// binary search with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. exchange, [BSPair of 2]
			// 4. peek the result from 3. None if [-1, -1]

			// ### change ptr_dataset_cap to ptr_dataset


			//search_range = binary_search_date(ptr_dataset_cap, 0, nData - 1, q_date);
			//search_range = binary_search_exchange(ptr_dataset_cap, search_range.idx_start,
			//									  			search_range.idx_end, q_exchange);

			search_range = binary_search_date(ptr_dataset, 0, nData - 1, q_date);
			search_range = binary_search_exchange(ptr_dataset, search_range.idx_start,
												  			search_range.idx_end, q_exchange);

			if (search_range.idx_start == -1 || search_range.idx_end == -1 ) {
				//printf("none\n");
				cout.write(none_out, 5);
			} else {
				//cap_result = calc_total_cap(ptr_dataset_cap, search_range.idx_start,
				//													search_range.idx_end);
				//printf("%lli\n", calc_total_cap(ptr_dataset_cap, search_range.idx_start,
				//													search_range.idx_end));
				//cout.write((char*)&cap_result, sizeof(lli));
				fprintf(stdout, "%lli\n", calc_total_cap(ptr_dataset, search_range.idx_start,
																	search_range.idx_end));
			}
		} else { //query == "end"
			break;
		}
	}
	return 0;
}