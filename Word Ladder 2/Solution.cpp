#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    public:

        unordered_map<string, vector<string> > adjacenty_list;
        unordered_set<string> visited;
        vector<vector<string> > sol;
        unordered_map<string, int> sp;
        unordered_set<string> exists;

        vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
            std::vector<string>::iterator it = std::find(wordList.begin(), wordList.end(), beginWord);
            if(it == wordList.end())
                wordList.push_back(beginWord);

            for(auto i : wordList)
                    exists.insert(i);

            /// build the graph
            for(string s : wordList){
                string k = s;
                for(int i=0;i<s.length();i++){
                    for(char c='a'; c<='z'; c++){
                        if(c == s[i]) continue;
                        string k = s;
                        k[i] = c;
                        if(exists.count(k))
                            adjacenty_list[s].push_back(k);
                    }
                }
            }

            /// find shortest path for all nodes to the endWord
            bfs(endWord, beginWord);

            /// find all path having same length as shortest path
            vector<string>path;
            solve(sp[beginWord],beginWord,endWord,path);

            return sol;
        }

        bool neighbours(string a, string b){
            /// 2 strings are considered neighbours iff differ in 1 char
            int diff = 0;
            for(int i=0;i<a.length() && diff < 2;i++)
                diff += (a[i] != b[i]);

            return diff == 1;
        }

        void bfs(string src, string dest){
            queue<string>q;
            q.push(src);
            sp[src] = 0;

            while(q.size()){
                string cur = q.front();
                q.pop();

                for(auto i : adjacenty_list[cur]){
                    if(!sp.count(i)){
                        q.push(i);
                        sp[i] = sp[cur] + 1;
                    }
                }
            }
        }

        void solve(int depth,string cur, string &finish, vector<string> &path){
            if(cur == finish){
                path.push_back(cur);
                sol.push_back(path);
                path.pop_back();
                return;
            }

            path.push_back(cur);
            visited.insert(cur);

            /* only continue the path if
                    1. node is not already in the path
                    2. shortest path to the dest = depth
            */
            for(auto i : adjacenty_list[cur])
                if(!visited.count(i) && sp[i] == depth-1)
                    solve(depth-1,i,finish,path);

            visited.erase(cur);
            path.pop_back();
        }
};
int main(){
    Solution x = Solution();
    vector<string> s = {"hot","dot","dog","lot","log","cog"};
    x.findLadders("hit", "cog", s);

    for(auto i : x.sol){
        for(auto k : i) cout<<k<<' ';cout<<endl;
    }
    return 0;
}
