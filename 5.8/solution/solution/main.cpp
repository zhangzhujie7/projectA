#include <iostream>  
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
struct p
{
	string ss;
	int num;
};
class Solution
{
private:
	vector<p> result;
	vector<string> tmp;
	vector <string> ans;
	int status;
public:

	void getSuffix(string suf, set<string> &dict);
	void findSuffix(int num, set<string> &dict);
	vector<p> getResult();
	vector<string> getAns();
};


int main()
{
	ifstream fs("res/dictionary.txt", ios::in);
	string buffer;
	set<string> wordList;
	char c;
	Solution sl;
	if (fs.is_open())
	{
		while (!fs.eof())
		{
			getline(fs, buffer);
			wordList.insert(buffer);
		}
	}
	while (true)
	{
		cout << endl;
		cout << "Please input the number of letters of suffix :";
		int num = 0;
		cin >> num;
		sl.findSuffix(num, wordList);
		vector<p> ss=sl.getResult();
		for (int i = 0; i < 10; i++)
		{
			cout << ss[i].ss << " " << ss[i].num << endl;
		}
		cout << "Please input suffix :";
		string suf;
		cin >> suf;
		sl.getSuffix(suf, wordList);
		vector<string> aa = sl.getAns();
		cout << "Num:" << aa.size() << endl;
		for (int i = aa.size()-1; i >=0; i--)
		{
			cout << aa[i] << endl;
		}


	}
	system("pause");


	return 0;
}

vector<p> Solution::getResult()
{
	return result;
}
vector<string> Solution::getAns()
{
	return ans;
}

void Solution::getSuffix(string suf, set<string> &dict)
{
	set<string>  replica;
	set<string>::iterator it;
	string xxx;
	replica = dict;
	int num = suf.length();
	for (it = replica.begin(); it != replica.end(); it++)
	{
	
		if (it->length() < num) continue;
		xxx = it->substr(it->length() - num, num);
		if (xxx == suf)
		{
			ans.push_back(*it);
		}
	}

}

void Solution::findSuffix(int num, set<string> &dict)
{
	result.clear();
	set<string>  replica;
	map<string, int> count;
	set<string>::iterator it;
	string tmp;
	replica = dict;
	int max = -1;
	for (it = replica.begin(); it != replica.end(); it++)
	{
		if (it->length() < num) continue;
		tmp = it->substr(it->length() - num, num);
		if (count.count(tmp)==0)
		{
			count.insert(make_pair(tmp, 1));
		}
		else
		{
			count[tmp]++;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		max = 0;
		for (auto it = count.begin(); it != count.end(); it++)
		{
			if (it->second > max)
			{
				max = it->second;
				tmp = it->first;
			}
		}
		p pp;
		pp.num = max;
		pp.ss = tmp;
		result.push_back(pp);
		count.erase(tmp);
	}
}

