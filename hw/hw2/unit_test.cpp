#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#define BUFF_SIZE 100

typedef long long int lli;

class Data {
public:
	int 		date;
	//string 		currency;
	//string 		exchange;
	char 		currency[BUFF_SIZE];
	char 		exchange[BUFF_SIZE];
	float 		low;
	float 		high;
	lli 		cap;

	Data () { }

	//Data (int d, string& currency_name, string& exchange_name, float l, float h, lli& c) {
	Data (int d, char* currency_name, char* exchange_name, float l, float h, lli c) {
		date 		= d;
		strncpy(currency, currency_name, BUFF_SIZE);
		strncpy(exchange, exchange_name, BUFF_SIZE);
		low 		= l;
		high 		= h;
		cap 		= c;
	}

	void print() {
		cerr << date << "\t" << currency << "\t" << exchange << "\t" 
			 << low << "\t" << high << "\t" << cap << "\n";
	}
};

void compare(Data& d1, Data& d2) {
	d1.print();
	d2.print();
}

int main(int argc, char const *argv[]) {
	//bool val;

	string s1 = "CMU";
	string s2 = "UCBerkeley";
	string s3 = "UC Berkeley";
	if (s1 > s2)
		cout << s2 << " is before " << s1 << "\n";
	else
		cout << s1 << " is before " << s2 << "\n";

	if (s2 > s3)
		cout << s3 << " is before " << s2 << "\n";
	else
		cout << s2 << " is before " << s3 << "\n";


	if (s2 == "UCBerkeley")
		cout << "Go Bears!" << "\n";

	const char* c_str = "UCBerkeley";
	const char* c_str_2 = "UC Berkeley";

	const char* c_ptr = new char[20];
	c_ptr = c_str;

	cout << c_ptr << "\n";

	cout << strcmp(c_ptr, c_str) << "\n";

	if (strcmp(c_ptr, c_str_2) < 0) {
		cout << "c_ptr < c_str_2!\n";
	}

	char buffer[100];
	fprintf ( stdout, "The  %s is %.4f\n", "CMU", 1.0);

	string str_tmp(c_str);


	//cout.write(buffer)
	vector<Data> v;

	char none[] = "none\n";




	Data d1 = Data(809, "dogecoin", "exchange", 0.01, 1.02, 333);
	Data d2 = Data(809, "bitcoin", "bitexchange", 0.01, 1.02, 333);

	compare(d1, d2);

	char* b = "a   oge";
	cerr << strcmp(d2.currency, b) << "\n";


	vector<int> h(10);
	//for (int i = 0; i < 10; ++i)
	//	h.push_back(1);

	int n = h.end() - h.begin();
	cout << "n is " << n << "\n";

	return 0;
}