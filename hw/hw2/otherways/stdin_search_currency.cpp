#include <iostream>
#include <iomanip>

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>

time_t start_time;
time_t end_time;
double seconds;
int    num_head = 30;

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
	float 		low;
	float 		high;
	lli 		cap;

	Data () { }

	Data (int d, string currency_name, string exchange_name, float l, float h, lli c) {
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

void data_head(vector<Data*> ptr, int size=num_head) {
	int nData = ptr.size();
	if (nData < size)
		size = nData;

	for (int i = 0; i < size; ++i) {
		cerr << i << ".\t";
		ptr[i]->print();
	}
}

bool compare_by_date (Data* d1, Data* d2) { 
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

bool compare_by_currency (Data* d1, Data* d2) {
	// d1->currency goes before d2->currency if:
	// currency_1 : Sprouts	KuCoin
	// currency_2 : DigiByte
	if (d1->currency < d2->currency) {
		return true;
	} else {
		return false;
	}
}

bool compare_by_exchange (Data* d1, Data* d2) {
	if (d1->exchange < d2->exchange) {
		return true;
	} else {
		return false;
	}
}

bool compare_by_high (Data* d1, Data* d2) {
	if (d1->high < d2->high) {
		return true;
	} else {
		return false;
	}
}

bool compare_by_low (Data* d1, Data* d2) {
	if (d1->low < d2->low) {
		return true;
	} else {
		return false;
	}
}

void sort_by_date(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by date
	// note: last should be inclusive

	time(&start_time);
	cerr << "Start sorting by date.\n";
	// last is inclusive, so the range to sort is 
	// [begin() + first, begin() + last + 1)
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_date);
	
	time(&end_time);
	seconds = difftime(end_time, start_time);
	cerr << "Time spent on sort_by_date: " << seconds << "\n";
	cerr << "End sorting by date.\n";
}

void sort_by_currency(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by currency name

	time(&start_time);
	cerr << "Start sorting by currency.\n";
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_currency);

	time(&end_time);
	seconds = difftime(end_time, start_time);
	cerr << "Time spent on sort_by_currency: " << seconds << "\n";
	cerr << "End sorting by currency.\n";

}

void sort_by_exchange(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by exchange name

	time(&start_time);
	cerr << "Start sorting by exchange.\n";
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_exchange);
	
	time(&end_time);
	seconds = difftime(end_time, start_time);
	
	cerr << "Time spent on sort_by_exchange: " << seconds << "\n";
	cerr << "End sorting by exchange.\n";
	
}

// Binary-search.
// Ref: https://www.geeksforgeeks.org/binary-search/
// A iterative binary search function. It returns
// location of x in given array arr[l..r] if present,
// otherwise -1
//int binarySearch(int arr[], int l, int r, int x)
//int binary_search_date(vector<Data*>& ptr_dataset, int l, int r, int target_date) {
BSPair binary_search_date(vector<Data*>& ptr_dataset, int l, int r, int target_date) {
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

BSPair binary_search_currency(vector<Data*>& ptr_dataset, int l, int r, string target_currency) {
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

BSPair binary_search_exchange(vector<Data*>& ptr_dataset, int l, int r, string target_exchange) {
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

lli calc_total_cap(vector<Data*>& ptr_dataset, int idx_start, int idx_end) {
	// we assumed that ptr_dataset is already sorted from
	// exchange->date
	// and idx_start, idx_end is inclusive
	lli ret = 0;
	for (int i = idx_start; i <= idx_end; ++i) {
		ret += ptr_dataset[i]->cap;
	}
	return ret;
}

void write_to_file(vector<Data*>& ptr_dataset, string& out_file_name) {
	Data* tmp;
	ofstream os;
	os.open(out_file_name, fstream::out);
	if (!os.is_open()) {
		cerr << "Error opening file: " << out_file_name << ".\n";
	}

	for (int i = 0; i < ptr_dataset.size(); ++i) {
		tmp = ptr_dataset[i];
		os << tmp->date << "\t" << tmp->currency << "\t" << tmp->exchange << "\t"
		   << tmp->low  << "\t" << tmp->high     << "\t" << tmp->cap 	  << "\n";
	}

	os.close();
	if (os.is_open()) {
		cerr << "Error closing file: " << out_file_name << ".\n";
	}
}


int main(int argc, char const *argv[]) {
	if (argc < 2) {
		cerr << "usage: ./program transactionData.txt";
		return 1;
	}

	const char* dataFile = argv[1];

	// read data
	ifstream fs;
	fs.open(dataFile, fstream::in);
	if (!fs.is_open()) {
		cerr << "Error opening file from " << dataFile << ".\n";
		return 1;
	}

	// vector of dataset
	vector<Data> dataset;

	Data   tmp_data;
	
	int    tmp_date;
	string tmp_currency;
	string tmp_exchange;
	float  tmp_low;
	float  tmp_high;
	lli    tmp_cap;


	cerr << "Start reading input from " << dataFile << ".\n";
	time(&start_time);

	string line;
	while (getline(fs, line)) {
		stringstream linestream(line);
		linestream >> tmp_date >> tmp_currency >> tmp_exchange >> tmp_low >> tmp_high >> tmp_cap;
		tmp_data = Data(tmp_date, tmp_currency, tmp_exchange, tmp_low, tmp_high, tmp_cap);
		dataset.push_back(tmp_data);
	}

	cerr << "End reading input from " << dataFile << ".\n";
	cerr << "Size: " << dataset.size() << " Range: [ 0 " << dataset.size() - 1 << " ]\n";
	time(&end_time);
	seconds = difftime(end_time, start_time);
	cerr << "Time spent on reading " << dataFile << " : " << seconds << "\n";

	// generate a pointer to our vector which stores the true data
	vector<Data*> ptr_dataset;
	for (int i = 0; i < dataset.size(); ++i) {
		ptr_dataset.push_back(&(dataset[i]));
	}
	int nData = ptr_dataset.size();

	cerr << "Stable sort from exchange -> currency -> date.\n";
	sort_by_exchange(ptr_dataset, 0, nData - 1);
	sort_by_currency(ptr_dataset, 0, nData - 1);
	sort_by_date(ptr_dataset, 0, nData - 1);
	vector<Data*> ptr_dataset_ecd(ptr_dataset); // for 'query', 'price'


	cerr << "Stable sort from exchange -> date.\n";
	sort_by_exchange(ptr_dataset, 0, nData - 1);
	sort_by_date(ptr_dataset, 0, nData - 1);
	vector<Data*> ptr_dataset_cap(ptr_dataset); // for 'cap'


	string query;
	string q_price;     // max or min
	int q_date;
	string q_currency;
	string q_exchange;

	BSPair search_range;
	Data* target_data;


	cout << fixed << setprecision(4);
	while (getline(cin, line)) {
		stringstream linestream(line);
		linestream >> query;
		if (query == "query") {
			linestream >> q_date >> q_currency >> q_exchange;
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
				cout << "none\n";
			} else {
				target_data = ptr_dataset_ecd[search_range.idx_start];
				cout << target_data->low << " " << target_data->high << " " << target_data->cap << "\n";
			}
		}

		if (query == "price") {
			linestream >> q_price >> q_date >> q_currency;
			//cerr << query << "\t" << q_price << "\t" << q_date << "\t" << q_currency << "\n";

			// binary search with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. find the `max' by high
			//          or `min' by low    based on the result from 3. None if [-1, -1]
			search_range = binary_search_date(ptr_dataset_ecd, 0, nData - 1, q_date);
			search_range = binary_search_currency(ptr_dataset_ecd, search_range.idx_start,
												  			search_range.idx_end, q_currency);
			

			if (search_range.idx_start == -1 || search_range.idx_start == -1 ) {
				cout << "none\n";
			} else {
				if (q_price == "max") {
					target_data = *max_element(ptr_dataset_ecd.begin() + search_range.idx_start,
												ptr_dataset_ecd.begin() + search_range.idx_end + 1, compare_by_high);
					cout << target_data->high << "\n";
				}
			
				if (q_price == "min") {
					target_data = *min_element(ptr_dataset_ecd.begin() + search_range.idx_start,
												ptr_dataset_ecd.begin() + search_range.idx_end + 1, compare_by_low);
					cout << target_data->low << "\n";
				}
			}
		}

		if (query == "cap") {
			linestream >> q_date >> q_exchange;
			//cerr << query << "\t" << q_date << "\t" << q_exchange << "\n";


			// binary search with the following step
			// 1. date, [0, nData-1]
			// 2. currency, [BSPair of 1]
			// 3. exchange, [BSPair of 2]
			// 4. peek the result from 3. None if [-1, -1]
			search_range = binary_search_date(ptr_dataset_cap, 0, nData - 1, q_date);
			search_range = binary_search_exchange(ptr_dataset_cap, search_range.idx_start,
												  			search_range.idx_end, q_exchange);

			if (search_range.idx_start == -1 || search_range.idx_start == -1 ) {
				cout << "none\n";
			} else {
				lli cap_result = calc_total_cap(ptr_dataset_cap, search_range.idx_start,
																	search_range.idx_end);
				cout << cap_result << "\n";
			}
		}

		if (query == "end")
			break;
	}

	fs.close();
	if (fs.is_open()) {
		cout << "file " << dataFile << " close failed.\n";
		return 1;
	}
	
	return 0;
}