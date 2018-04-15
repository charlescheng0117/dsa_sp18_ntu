#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>


#include <unistd.h>

unsigned int microseconds = 2000;

time_t start_time;
time_t end_time;
double seconds;
int    num_head = 30;

using namespace std;

typedef long long int lli;

struct Date {
	int year;
	int month;
	int date;
	Date () { }
	Date (int y, int m, int d) {
		year  = y;
		month = m;
		date  = d;
	}
};

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
	//Date  		date;
	int 		date;
	string 		currency;
	string 		exchange;
	float 		low;
	float 		high;
	lli 		cap;

	Data () { }

	//Data (Date d, string currency_name, string exchange_name, float l, float h, lli c) {
	Data (int d, string currency_name, string exchange_name, float l, float h, lli c) {
		date 		= d;
		currency 	= currency_name;
		exchange 		= exchange_name;
		low 		= l;
		high 		= h;
		cap 		= c;
	}

	void print() {
		//printf("%d %d %d\t%s\t%s\t%f\t%f\t%lld\n", date.year, date.month, date.date, currency.c_str(), exchange.c_str(), low, high, cap);
		printf("%d\t%s\t%s\t%f\t%f\t%lld\n", date, currency.c_str(), exchange.c_str(), low, high, cap);
	}
};


Date convert_date(int date) {
	int y = date / 10000;
	date = date % 10000;
	int m = date / 100;
	int d = date % 100;
	Date ret = Date(y, m, d);
	return ret;
}

void data_head(vector<Data*> ptr, int size=num_head) {
	int nData = ptr.size();
	if (nData < size)
		size = nData;

	for (int i = 0; i < size; ++i) {
		cerr << i << ".\t";
		ptr[i]->print();
	}
}


bool compare_by_Date (Date& d1, Date& d2) { 
	// d1 before d2
	// eg
	// d1 : 20130316
	// d2 : 20130907
	// d1 < d2
	if (d1.year < d2.year) {
		return true;
	} else if (d1.year == d2.year) { 
		if (d1.month < d2.month) {
			return true;
		} else if (d1.month == d2.month) {
			if (d1.date < d2.date) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
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

//void sort_by_date(vector<Data*>& ptr_dataset) {
void sort_by_date(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by date
	// note: last should be inclusive

	time(&start_time);
	cerr << "Start sorting by date.\n";
	// last is inclusive, so the range to sort is 
	// [begin() + first, begin() + last + 1)
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_date);
	cerr << "End sorting by date.\n";
	time(&end_time);
	seconds = difftime(end_time, start_time);
	//cerr << "Time spent on sort_by_date: " << seconds << "\n";
}

void sort_by_currency(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by currency name

	time(&start_time);
	cerr << "Start sorting by currency.\n";
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_currency);
	cerr << "End sorting by currency.\n";
	time(&end_time);
	seconds = difftime(end_time, start_time);
	// cerr << "Time spent on sort_by_currency: " << seconds << "\n";
}

void sort_by_exchange(vector<Data*>& ptr_dataset, int first, int last) {
	// stable_sort the dataset by exchange name

	time(&start_time);
	cerr << "Start sorting by exchange.\n";
	stable_sort(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_exchange);
	cerr << "End sorting by exchange.\n";
	time(&end_time);
	seconds = difftime(end_time, start_time);
	//cerr << "Time spent on sort_by_exchange: " << seconds << "\n";
}

// Binary-search.
// Ref: https://www.geeksforgeeks.org/binary-search/
// A iterative binary search function. It returns
// location of x in given array arr[l..r] if present,
// otherwise -1
//int binarySearch(int arr[], int l, int r, int x)
//int binary_search_date(vector<Data*>& ptr_dataset, int l, int r, int target_date) {
BSPair binary_search_date(vector<Data*>& ptr_dataset, int l, int r, int target_date) {
	//BSPair ret;
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

void test_sorts(vector<Data*>& ptr_dataset, string& command, int l, int r) {
	int nData = ptr_dataset.size();

	cerr << "Original order of data\n";
	data_head(ptr_dataset, 20);

	if (command == "-ecd") {
		cerr << "Stable sort from exchange -> currency -> date.\n";
		sort_by_exchange(ptr_dataset, 0, nData - 1);
		sort_by_currency(ptr_dataset, 0, nData - 1);
		sort_by_date(ptr_dataset, 0, nData - 1);
	}

	if (command == "-ed") {
		cerr << "Stable sort from exchange -> date.\n";
		sort_by_exchange(ptr_dataset, 0, nData - 1);
		sort_by_date(ptr_dataset, 0, nData - 1);
	}

	if (command == "-d") {
		cerr << "Stable sort by date, result: \n";
		sort_by_date(ptr_dataset, l, r);
		data_head(ptr_dataset, 20);
	}

	if (command == "-c") {
		cerr << "Stable sort by currency, result: \n";
		sort_by_currency(ptr_dataset, l, r);
		data_head(ptr_dataset, 20);
	}

	if (command == "-e") {
		cerr << "Stable sort by exchange, result: \n";
		sort_by_exchange(ptr_dataset, l, r);
		data_head(ptr_dataset, 20);
	}

	// just set command to abitrary string
	command = "next";
	
}

void test_binary_search_by_date(vector<Data*>& ptr_dataset) {
	// test binary search in ptr_dataset
	// sort_by_date(ptr_dataset, 0, ptr_dataset.size() - 1);
	data_head(ptr_dataset, 20);

	cerr << "Insert date to be searched, or -1 to exit: ";
	int target_date;
	int l, r;
	//int l = 0, r = ptr_dataset.size() - 1;

	while (cin >> target_date) {
		if (target_date == -1)
			break;
		cerr << "In range [first, last]: ";
		cin >> l >> r;
		//int idx = binary_search_date(ptr_dataset, l, r, target_date);
		BSPair idx = binary_search_date(ptr_dataset, l, r, target_date);
		idx.print();
		cerr << "Insert date to be searched, or -1 to exit: ";
	}
	return;
}

void test_binary_search_by_currency(vector<Data*>& ptr_dataset) {
	// test binary search in ptr_dataset
	// sort_by_currency(ptr_dataset, 0, ptr_dataset.size() - 1);
	data_head(ptr_dataset);

	cerr << "Insert currency to be searched, or q to exit: ";
	string target_currency;
	int l, r;
	//int l = 0, r = ptr_dataset.size() - 1;

	while (cin >> target_currency) {
		if (target_currency == "q")
			break;
		cerr << "In range [first, last]: ";
		cin >> l >> r;
		BSPair idx = binary_search_currency(ptr_dataset, l, r, target_currency);
		idx.print();
		cerr << "Insert currency to be searched, or q to exit: ";
	}
	return;
}

void test_binary_search_by_exchange(vector<Data*>& ptr_dataset) {
	// test binary search in ptr_dataset
	// sort_by_exchange(ptr_dataset, 0, ptr_dataset.size() - 1);
	data_head(ptr_dataset);

	cerr << "Insert exchange to be searched, or q to exit: ";
	string target_exchange;
	int l, r;
	//int l = 0, r = ptr_dataset.size() - 1;

	while (cin >> target_exchange) {
		if (target_exchange == "q")
			break;
		cerr << "In range [first, last]: ";
		cin >> l >> r;
		BSPair idx = binary_search_exchange(ptr_dataset, l, r, target_exchange);
		idx.print();
		cerr << "Insert exchange to be searched, or q to exit: ";
	}
	return;
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
	
	const char* dataFile = argv[1];

	// read data
	ifstream fs;
	fs.open(dataFile, fstream::in);
	if (!fs.is_open()) {
		cerr << "Error opening file from " << dataFile << ".\n";
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
		//cerr << "1. line: " << line << "\n";
		stringstream linestream(line);


		// tab delimited and space delimited
		//linestream >> raw_date;
	    //linestream.ignore(3, '\t'); // discard '\t'
		//getline(linestream, tmp_currency, '\t');
		//getline(linestream, tmp_exchange, '\t');
		//linestream >> tmp_low >> tmp_high >> tmp_cap;

		linestream >> tmp_date >> tmp_currency >> tmp_exchange >> tmp_low >> tmp_high >> tmp_cap;

		tmp_data = Data(tmp_date, tmp_currency, tmp_exchange, tmp_low, tmp_high, tmp_cap);
		//tmp_data.print();

		dataset.push_back(tmp_data);
	}

	cerr << "End reading input from " << dataFile << ".\n";
	cerr << "Size: " << dataset.size() << " Range: [ 0 " << dataset.size() - 1 << " ]\n";
	time(&end_time);
	seconds = difftime(end_time, start_time);
	cerr << "Time spent on reading " << dataFile << " : " << seconds << "\n";

	vector<Data*> ptr_dataset;
	for (int i = 0; i < dataset.size(); ++i) {
		ptr_dataset.push_back(&(dataset[i]));
	}

	cerr << "Stable sort from exchange -> currency -> date.\n";

	sort_by_exchange(ptr_dataset, 0, nData - 1);
	sort_by_currency(ptr_dataset, 0, nData - 1);
	sort_by_date(ptr_dataset, 0, nData - 1);
	
	vector<Data*> ptr_dataset_ecd(ptr_dataset); // for 'query', 'price'

	cerr << "Stable sort from exchange -> currency -> date.\n";
	sort_by_exchange(ptr_dataset, 0, nData - 1);
	sort_by_date(ptr_dataset, 0, nData - 1);

	vector<Data*> ptr_dataset_ed(ptr_dataset); // for 'cap'

	// TODO use linestram to getline
	// then based on 'query', 'price', 'cap', 'end', we
	// perform different operation
	
	// get command flag from CLI
	// if (argc > 2) {
	//     const char* in_command_flag = argv[2];
	//     string command_flag(in_command_flag);
	cerr << "Please provide your command flag: \n";
	cerr << "-s: sorting\n";
	cerr << "-d: binary search by date\n";
	cerr << "-c: binary search by currency\n";
	cerr << "-e: binary search by exchange\n";
	cerr << "-max: get max price within entry [start, end]\n";
	cerr << "-min: get min price within entry [start, end]\n";
	cerr << "-cap: get trading volume within [date_start, date_end] of exchange\n";
	cerr << "-w: write output\n";
	cerr << "-p: peek entry\n";
	cerr << "-q: quit\n";
	string command_flag;
	int l, r;
	while (cin >> command_flag) {

		if (command_flag == "-s") {
			cerr << "Sort by:\n";

			cerr << "-d: 	sort by date\n";
			cerr << "-c: 	sort by currency\n";
			cerr << "-e: 	sort by exchange\n";
			cerr << "-ecd: 	sort by ex->cur->date\n";
			cerr << "-ed: 	sort by ex->date\n";

			cin >> command_flag;
			cerr << "In range [first, last]: ";
			cin >> l >> r;
			//cerr << l << " " << r << "\n";
			test_sorts(ptr_dataset, command_flag, l, r);
		}

		if (command_flag == "-d")
			// test binary search by date in ptr_dataset
			test_binary_search_by_date(ptr_dataset);

		if (command_flag == "-c")
			// test binary search by currency in ptr_dataset
			test_binary_search_by_currency(ptr_dataset);
		
		if (command_flag == "-e")
			// test binary search by exchange in ptr_dataset
			test_binary_search_by_exchange(ptr_dataset);

		if (command_flag == "-w") {
			if (argc != 4) {
				cerr << "usage: ./program input-file.txt -w [out-file-name].txt\n";
				return 1;
			}

			const char* out_file_name = argv[3];
			string out_file_str(out_file_name);

			// want to output sorted by date
			sort_by_date(ptr_dataset, 0, ptr_dataset.size());
			write_to_file(ptr_dataset, out_file_str);
		}

		if (command_flag == "-p") {
			int entry;
			cerr << "Enter the entry to peek: ";
			cin >> entry;
			ptr_dataset[entry]->print();
		}

		if (command_flag == "-max") {
			Data* target_data;

			int first, last;
			cerr << "Enter the range [first, last] to find max price: ";
			cin >> first >> last;
			
			target_data = *max_element(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_high);
			target_data->print();
		}

		if (command_flag == "-min") {
			Data* target_data;

			int first, last;
			cerr << "Enter the range [first, last] to find min price: ";
			cin >> first >> last;

			target_data = *min_element(ptr_dataset.begin() + first, ptr_dataset.begin() + last + 1, compare_by_low);
			target_data->print();
		}

		if (command_flag == "-cap") {
			// TODO: have to binary search within period [start, end]
			// Then add all the trading volumes.
			int first, last;
			cerr << "Enter the range [first, last] to find cap: ";
			cin >> first >> last;
			lli total_cap = calc_total_cap(ptr_dataset, first, last);
			cerr << "total_cap = " << total_cap << "\n";
		}

		if (command_flag == "-q")
			break;

		cerr << "Input your command flag: -s -d -c -e -max -min -cap -w -p -q\n";
	}

	fs.close();
	if (fs.is_open())
		cerr << "file " << dataFile << " close failed.\n";

	return 0;
}