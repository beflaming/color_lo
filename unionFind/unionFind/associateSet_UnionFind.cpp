// 805. Maximum Association Set: Given ListA = ["a","b","d","e","f"], ListB = ["b","c","e","g","g"], return ["d","e","f","g"].
// 806. Buy Fruits: Given codeList = [["apple", "apple"],["orange", "anything", "orange"]],shoppingCart = ["orange", "apple", "apple", "orange", "mango", "orange"], return 1. Ordered
// 808. Movie Rate: Given ratingArray = [10,20,30,40,50,60,70,80,90], contactRelationship = [[1, 4, 5], [0, 2, 3], [1, 7], [1, 6, 7], [0], [0], [3], [2, 3], []], S = 5, K = 3, return[6, 7, 4].


#include "stdafx.h"
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<functional>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution805 {
public:
	vector<string> maxAssociationSet(vector<string> &ListA, vector<string> &ListB) {
		unordered_map<string, string> parent;
		for (int i = 0; i < ListA.size();++i) {
			string p1, p2;
			if (!parent.count[ListA[i]]) {
				p1 = parent[ListA[i]] = ListA[i];
			}
			else {
				p1 = findParent(parent, ListA[i]);
			}

			if (!parent.count[ListB[i]]) {
				p2 = parent[ListB[i]] = ListB[i];
			}
			else {
				p2 = findParent(parent, ListB[i]);
			}
			if (p1 != p2) parent[p2] = p1;
		}

		unordered_map<string, vector<string>> table;
		for (auto p:parent) {
			table[findParent(parent, p.first)].push_back(p.second);
		}

		int maxSize = 0;
		string key;
		for (auto t:table) {
			if (t.second.size()>maxSize) {
				maxSize = t.second.size();
				key = t.first;
			}
		}
		return table[key];
	}

private:
	string findParent(unordered_map<string,string> &parent, string s) {
		while (parent[s] != s) {
			parent[s] = parent[parent[s]];
			s = parent[s];
		}
		return s;
	}
};

class Solution806 {
public:
	int buyFruits(vector<vector<string>> &codeList, vector<string> &shoppingCart) {
		vector<string> code;
		for (auto cd:codeList) {
			for (string t : cd) code.push_back(t);
		}

		if (code.size() > shoppingCart.size()) return 0;
		for (int i = 0; i < shoppingCart.size();++i) {
			int j;
			for (j = 0; j < code.size();++j) {
				if (shoppingCart[i + j] != code[j] && code[j] != "anything") break;
			}
			if (j == code.size()) return 1;
		}
		return 0;
	}
};

class Solution808 {
public:
	vector<int> topKMovies(vector<int> &rating, vector<vector<int>> &G, int S, int K) {
		int n=rating.size();
		vector<int> parent(n);
		for (int i = 0; i < n; ++i) parent[i] = i;
		//union
		for (int i = 0; i < n;++i) {
			for (int v:G[i]) {
				int p1 = findParent(parent,i);
				int p2 = findParent(parent,v);
				if (p1!=p2) {
					parent[p2] = p1;
				}
			}
		}

		int p = findParent(parent,S);
		//create a min heap; increasing;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
		for (int i = 0; i < n;++i) {
			if (i!=S && findParent(parent,i)==p) {
				pq.emplace(rating[i],i);
				if (pq.size() > K) pq.pop();
			}
		}

		vector<int> result;
		while (!pq.empty()) {
			result.push_back(pq.top().second);
			pq.pop();
		}
		return result;
	}

	int findParent(vector<int> &parent, int i) {
		while (parent[i] != i) {
			parent[i] = parent[parent[i]];
			i = parent[i];
		}
		return i;
	}
};
