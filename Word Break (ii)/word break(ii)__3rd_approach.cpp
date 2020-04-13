#include <iostream>
#include <memory>
#include <vector>

#define MAX_CHILDREN 26

using namespace std;

class Trie: public std::enable_shared_from_this<Trie> {
    public:
        vector<shared_ptr<Trie> > children;
        bool is_leaf;
        Trie(){
            is_leaf = false;
            for(int i=0; i<MAX_CHILDREN; i++)
                children.push_back(nullptr);
        }

        void insert(string s){
            shared_ptr<Trie> current_node = shared_from_this();
            for(int i=0; i<s.length(); i++){
                int index = s[i] - 'a';
                if(current_node->children[index] == nullptr){
                    current_node->children[index] = make_shared<Trie>();
                }
                current_node = current_node->children[index];

                if(i+1 == s.length())
                      current_node->is_leaf = true;
            }
        }

        bool has_character(char c){
            int index = c-'a';
            return this->children[index] != nullptr;
        }

        shared_ptr<Trie> get_node_from_char(char c){
            int index = c-'a';
            return this->children[index];
        }
};

class Solution{
    public:
        shared_ptr<Trie> dictionary;
        vector<int>dp;
        vector<vector<int> > adjacency_list;
        vector<string> sol;

        Solution(){
            dictionary = make_shared<Trie>();
        }
        vector<string> wordBreak(string s, vector<string>& wordDict) {
            for(string word : wordDict)
                dictionary->insert(word);

            dp.resize(s.length());
            adjacency_list.resize(s.length());
            fill(dp.begin(),dp.end(),-1);

            solve(0,s);
            vector<int>indices(1,0);
            dfs(0, indices, sol, s);
            return sol;
        }

         bool solve(int index, string &s){
                if(index == s.length())
                    return true;

                if(dp[index] != -1)
                    return dp[index];

                bool can = false;
                shared_ptr<Trie> current_node = dictionary;

                for(int i=index; i<s.length(); i++){
		   // if there is no such a word in the dict then early break 
		   if(!current_node->has_character(s[i]))
                        break;
                    current_node = current_node->get_node_from_char(s[i]);
                    if(current_node-> is_leaf){
                       bool found_solution = solve(i+1, s);
                       if(found_solution){
			    // add an edge from index -> i+1 if a solution exists after this split	 		
                            can = true;
                            adjacency_list[index].push_back(i+1);
                       }
                    }
                }
                return dp[index] = can;
        }

        void dfs(int index, vector<int> &indices, vector<string> &sol, string &s){
            if(index == s.length()){
                string str = "";
		// construct the solution if the vector has elemetns [3,5]
		// then this means we did 2 splits at each of these indices so add a space there
                int cur_index = 0, str_position = 0;
                while(cur_index < indices.size()){
                    if(str_position) str += ' ';
                    while(str_position < indices[cur_index]) str += s[str_position++];
                    cur_index++;
                }
                sol.push_back(str);
                return;
            }
            // apply all splits		
            for(int i:adjacency_list[index]){
                indices.push_back(i);
                dfs(i, indices, sol, s);
                indices.pop_back();
            }
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
