#include <iostream>
#include <string>
#include "MyArray.h"

using namespace std;
int main()
{
	string filename("Text.txt");
	MyArray<int> arr;
	string choose;
	cout << "Read data from file or keyboard? (f/k)" << endl;
	cin >> choose;
	switch( choose[0] )
	{
		case 'f':arr.FileRead(filename); break;
		case 'k':arr.KBRead(); break;
		default:
			cout << "Wrong Iuput!" << endl;
			break;
	}

	cout << "Input [1] to read data from file(absolute path)\n"
		<< "Input [2] to read data from keyboard\n"
		<< "Input [3] to print max of data\n"
		<< "Input [4] to print min of data\n"
		<< "Input [5] to print Median of data\n"
		<< "Input [6] to print sum of data\n"
		<< "Input [7] to print average of data\n"
		<< "Input [8] to locate data\n"
		<< "Input [9] to locate data in one dimension\n"
		<< "Input [0] to print all\n"
		<< "Input [c] to print statistic\n"
		<< "Input [q] to exit" << endl;
	while( true )
	{
		cout << "In:>>";
		cin >> choose;
		switch( choose[0] )
		{
			case '1':cin >> filename; arr.FileRead(filename); break;
			case '2':arr.KBRead(); break;
			case '3':cout << "Max: " << arr.Max() << endl; break;
			case '4':cout << "Min: " << arr.Min() << endl; break;
			case '5':cout << "Median: " << arr.Median() << endl; break;
			case '6':cout << "Sum: " << arr.Sum() << endl; break;
			case '7':cout << "Average: " << arr.Average() << endl; break;
			case '8':
				int r, c;
				cout << "Inpur row:";
				cin >> r;
				cout << "Input column:";
				cin >> c;
				cout << arr.Locate(r, c); cout << endl; break;
			case '9':
				int num;
				cout << "Inpur num:";
				cin >> num;
				arr.OrderLocate(num); break;
			case 'c':
				cout << "Max: " << arr.Max() << endl;
				cout << "Min: " << arr.Min() << endl;
				cout << "Median: " << arr.Median() << endl;
				cout << "Sum: " << arr.Sum() << endl;
				cout << "Average: " << arr.Average() << endl;
				break;
			case '0':cout << arr; break;
		}
		if( choose[0] == 'q' )
		{
			break;
		}
	}
	return 0;
}