//sliding windows

#include "stdafx.h"
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<deque>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

class Solution{

	// medianSlidingWindow
    // reference FindMedianfromDataStream
	vector<double> medianSlidingWin(vector<int>& nums, int k) {
		vector<double> res;
		multiset<int> small, large;
		int len = nums.size();
		for (int i = 0; i < len;++i) {
			if (i>=k) {
				if (small.count(nums[i - k])) {
					small.erase(small.find(nums[i-k]));
				}else if(large.count(nums[i-k])) {
					large.erase(large.find(nums[i-k]));
				}
			}
			if (small.size() <= large.size()) {
				if (large.empty() || nums[i] <= *large.begin()) {
					small.insert(nums[i]);
				}else {
					small.insert(*large.begin());
					large.erase(large.begin());
					large.insert(nums[i]);
				}
			}else {
				if (nums[i] >= *small.rbegin()) {
					large.insert(nums[i]);
				}
				else {
					large.insert(*small.rbegin());
					small.erase(--small.end());
					small.insert(nums[i]);
				}
			}
			if (i>=(k-1)) {
				if (k % 2) res.push_back(*small.rbegin());
				else res.push_back((*small.rbegin()+*large.begin())/2);
			}
		}
		return res;
	}

	//slidingWindowMaxium
	vector<int> maxSlidWin(vector<int>&nums, int k) {
		vector<int> res;
		deque<int> q;
		int len = nums.size();
		for (int i = 0; i < len;++i) {
			if (!q.empty() && q.front() == i - k) q.pop_front();
			while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
			q.push_back(i);
			if (i >= (k - 1)) res.push_back(nums[q.front()]);
		}
		return res;
	}

	//window sum
	vector<int> winSum(vector<int>&nums, int k) {
		if (nums.empty()) return {};
		vector<int> res;
		int len = nums.size();
		int sum = 0;
		for (int i = 0; i < len && i < k; ++i) sum += nums[i];
		res.push_back(sum);
		for (int j = k; j < len; ++j) {
			sum = sum - nums[j - k] + nums[j];
			res.push_back(sum);
		}
		return res;
	}
};