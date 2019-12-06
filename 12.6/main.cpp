#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include "HuffmanTree.h"

using namespace std;

int main(void)
{
	map<char, int> ch_count;
	string sent;
	getline(cin, sent);
	for( const auto &c : sent )
	{
		++ch_count[c];
	}
	for( const auto &c : ch_count )
	{
		cout << c.first << " occurs " << c.second << " times" << endl;
	}
	vector<pair<char, int>> so;
	string NeCode;
	auto it = back_inserter(so);
	for( const auto &c : ch_count )
	{
		*it = c;
	}
	sort(so.begin(), so.end(), [](pair<char, int> &a, pair<char, int> &b) { return a.second < b.second; });
	HuffmanTree huf(so);
	cout << huf << endl;
	return 0;
}
