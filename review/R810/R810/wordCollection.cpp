#include "stdafx.h"
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<queue>
using namespace std;

/*word ladder
transformation sequence, all words have the same length,only lowercase alphabetic characters.
start-->end, in the dictionary.  one letter changed one time.
*/
class Solution120 {
public:
	int lengthChange(string &start, string &end, unordered_set<string> &dict) {
		unordered_map<string, int> mp;
		mp[start] = 1;
		queue<string> q;
		q.push(start);

		while (!q.empty()) {
			string word = q.front(); q.pop();
			for (int i = 0; i < word.size();++i) {
				string newWord = word;
				for (char ch = 'a'; ch <= 'z';++ch) {
					newWord[i] = ch;
					if (dict.count(newWord) && newWord == end) return mp[word] + 1;
					if (dict.count(newWord) && !mp.count(newWord)) {
						q.push(newWord);
						mp[newWord] = mp[word] + 1;
					}
				}
			}
		}
		return 0;
	}
};

class Solution121 {
public:
	vector<vector<string>> findLadders(string start, string end, vector<string> &wordList) {
		vector<vector<string>> res;
		unordered_set<string> dict(wordList.begin(), wordList.end());
		vector<string> p{ start };
		queue<vector<string>> paths;
		paths.push(p);

		int level = 1, minLevel = INT_MAX;
		unordered_set<string> words;
		while (!paths.empty()) {
			auto t = paths.front(); paths.pop();
			if (t.size()>level) {
				for (string w : words) dict.erase(w);
				words.clear();
				level = t.size();
				if (level > minLevel) break;
			}
			string last = t.back();
			for (int i = 0; i < last.size();++i) {
				string newLast = last;
				for (char ch = 'a'; ch <= 'z';++ch) {
					newLast[i] = ch;
					if (!dict.count(newLast)) continue;
					words.insert(newLast);
					vector<string> nextPath = t;
					nextPath.push_back(newLast);
					if (newLast==end) {
						res.push_back(nextPath);
						minLevel = level;
					}
					else {
						paths.push(nextPath);
					}
				}
			}
		}
		return res;
	}
};