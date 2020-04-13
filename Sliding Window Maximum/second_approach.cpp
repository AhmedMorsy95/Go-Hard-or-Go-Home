#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <set>
#define MAX_CHILDREN 26

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int,greater<int> > st;
        vector<int>answer;

        /// insert first k-1 elements
        for(int i=0; i<k-1; i++)
            st.insert(nums[i]);

        for(int i=k-1; i<(int)nums.size(); i++){
            /// we will shift the window to the right so
            /// 1.insert new element from the right
            st.insert(nums[i]);

            /// 2.remove old element from the left
            if(i >= k)
                st.erase(st.find(nums[i-k]));

            answer.push_back(*st.begin());
        }

        return answer;
    }
};

