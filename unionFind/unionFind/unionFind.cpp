// unionFind.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<vector>
#include<iostream>
using namespace std;

class UnionFindSet{
public:
	UnionFindSet(int n) {
		ranks_ = vector<int>(n+1,0);
		parents_ = vector<int>(n+1,0);
		for (int i = 0; i < parents_.size(); ++i) parents_[i] = i;
	}
	//Merge sets that contains u and v
	//Return true if merged, false if u and v are already in one set. 
	bool Union(int u, int v) {
		int pu = Find(u);
		int pv = Find(v);
		if (pu == pv) return false;

		//Merge low rank tree into high rank tree
		if (ranks_[pv]<ranks_[pu]) {
			parents_[pv] = pu;
		}
		else if (ranks_[pu]<ranks_[pv]) {
			parents_[pu] = pv;
		}
		else {
			parents_[pv] = pu;
			ranks_[pu] += 1;
		}
		return true;
	}

	int Find(int u) {
		if (u != parents_[u]) {
			parents_[u] = Find(parents_[u]);
		}
		return parents_[u];
	}

private:
	vector<int> ranks_;
	vector<int> parents_;
};

int main()
{
    return 0;
}

