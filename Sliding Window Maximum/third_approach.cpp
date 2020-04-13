#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#define MAX_CHILDREN 26

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<pair<int,int> > q;
        vector<int>answer;
        /// We will maitain the deque so that it's sorted from the back to the front

        /// insert first k-1 elements
        for(int i=0; i<k-1; i++){
            /// before adding the element to the back, remove all element less or equal to it
            while(q.size() > 0 && q.back().first <= nums[i])
                q.pop_back();

            q.push_back(make_pair(i,nums[i]));
        }
        for(int i=k-1; i<(int)nums.size(); i++){
            /// we will shift the window to the right so
            /// 1.insert new element from the right
            while(q.size() > 0 && q.back().first <= nums[i])
                q.pop_back();

            q.push_back(make_pair(i,nums[i]));

            ///while the front of the deque is out of the current range remove it
            while(q.front().second <= i-k)
                q.pop_front();

            answer.push_back(q.front().first);
        }

        return answer;
    }
};

int main()
{

    return 0;
}
