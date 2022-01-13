#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>

#include "LoggerClass.hpp"

using namespace std;

struct Data
{
	string name;
	string email;
	string department;
	string position;
	string project;
	string task;
	string date;
	int logged_hours;

};

//class Singleton {
//	Singleton() {
//		// Thread-unsafe code
//	}
//	static Singleton* getInstance() {
//		static Singleton instance;
//		return &instance;
//	}
//};






vector<Data> getReport(vector<Data>& strings) {
	
	Logging::LoggerSingleton::Instance().WriteLine("Start method getReport          ", false);

	for (int i = 0; i < strings.size(); i++) {

		for (int j = 0; j < strings.size(); ++j)
		{
			if (strings[i].name == strings[j].name && strings[i].date == strings[j].date && i != j) {
				strings[i].logged_hours += strings[j].logged_hours;
				strings.erase(strings.begin() + j);
				j--;
			}
		}
	}

	Logging::LoggerSingleton::Instance().WriteLine("Method getReport completed      ", false);

	return strings;
}

vector<Data> stringToStruct(vector<string> strings) {

	Logging::LoggerSingleton::Instance().WriteLine("Start method stringToStruct     ", false);

	vector<Data> info;

	for (size_t i = 0; i < strings.size(); i++)
	{
		vector<string> b;

		string delim(";");
		size_t prev = 0;
		size_t next;
		size_t delta = delim.length();

		for (size_t j = 0; j < 8; j++)
		{
			next = strings[i].find(delim, prev);
			string tmp = strings[i].substr(prev, next - prev);
			b.push_back(tmp);
			prev = next + delta;
		}

		info.push_back({ b[0],b[1] ,b[2] ,b[3] ,b[4] ,b[5] ,b[6].erase(b[6].size() - 3),stoi(b[7]) });
	}

	Logging::LoggerSingleton::Instance().WriteLine("Method stringToStruct completed ", false);

	return info;
}

string getMmonth(int a) {
	switch (a)
	{
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	default:
		break;
	}
}

string date(string a) {

	string year = a.substr(0, 4);
	string month = a.substr(5, 8);

	return getMmonth(stoi(month)) + " " + year;
}

vector<string> readFile() {

	vector<string> strings;

	string a;

	Logging::LoggerSingleton::Instance().WriteLine("Start method getReport          ", false);


	ifstream file("db.csv");
	if (file)
	{
		double start_time = clock();

		while (getline(file, a)) {
			strings.push_back(a);
		}
		double end_time = clock();

		double search_time = end_time - start_time;

		cout << "File reading took " << search_time / 1000 << " sec" << endl;

		Logging::LoggerSingleton::Instance().WriteLine("Reading completed               ", false);

		file.close();

		Logging::LoggerSingleton::Instance().WriteLine("Closing the file after reading  ", false);

		strings.erase(strings.begin());

	}
	else {
		Logging::LoggerSingleton::Instance().WriteLine("File open error                 ", false);

		cout << "File open error" << endl;
	}
	return strings;
}

void writeReport(vector<Data>& report) {

	ofstream file;

	Logging::LoggerSingleton::Instance().WriteLine("Opening file for recording      ", false);

	file.open("report.csv");

	for (size_t i = 0; i < report.size(); i++)
	{
		file << report[i].name << ";" << date(report[i].date) << ";" << report[i].logged_hours << endl;
	}

	Logging::LoggerSingleton::Instance().WriteLine("Closing the file after recording", false);

	file.close();


}

int main()
{
	vector<Data> info;

	vector<string> strings;

	strings = readFile();

	if (!strings.empty())
	{
		info = stringToStruct(strings);

		getReport(info);

		writeReport(info);

		Logging::LoggerSingleton::Instance().WriteLine("Program successfully completed  ", false);

	}
	else
	{
		Logging::LoggerSingleton::Instance().WriteLine("Program terminated with an error", false);

	}

	Logging::LoggerSingleton::Instance().WriteLine("//////////////////////////////////////////////////////////",true);


	cout << "Program execution time " << clock() / 1000 << " sec";

	return 0;
}

