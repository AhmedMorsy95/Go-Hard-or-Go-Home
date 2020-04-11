#include <iostream>
#include <memory>
#include <vector>

#define MAX_CHILDREN 26

using namespace std;

class Solution{
    public:
    unordered_set<string>dictionary;
    unordered_map<int,vector<string> > dp;

    vector<string> wordBreak(string s, vector<string>& wordDict) {
            for(string s:wordDict)
                dictionary.insert(s);
            return solve(0,s);
    }

    vector<string> solve(int index, string &s){
        if(index == s.length())
            return vector<string>{""};

        if(dp.count(index))
                return dp[index];

        dp[index] = vector<string>();
        string current = "";
        for(int i=index; i<s.length(); i++){
            current += s[i];
            if(dictionary.count(current)){ /// found a split
                vector<string> nxt = solve(i+1, s);
                for(string s : nxt){
                    dp[index].push_back(index ? " " + current + s : current + s);
                }
            }
        }
        return dp[index];
    }
};

int main()
{
    shared_ptr<Solution> x = make_shared<Solution>();
    vector<string>v{"cat", "cats", "and", "sand", "dog"};
    vector<string> sol = x->wordBreak("catsanddog",v);
    for(auto i : sol) cout<<i<<endl;
    return 0;
}

