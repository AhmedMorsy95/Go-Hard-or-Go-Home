#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

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
        unordered_map<int,vector<string> > dp;
        Solution(){
            dictionary = make_shared<Trie>();
        }
        vector<string> wordBreak(string s, vector<string>& wordDict) {
            for(string word : wordDict)
                dictionary->insert(word);
            return get_strings(0,s);
        }

        vector<string> get_strings(int index, string &s){
            if(index == s.length())
                return vector<string>{""};

            if(dp.count(index))
                return dp[index];

            dp[index] = vector<string>();
            shared_ptr<Trie> current_node = dictionary;

            string cur = "";
            if(index) cur += ' ';
            vector<string> solutions;

            for(int i=index; i<s.length(); i++){
                if(!current_node->has_character(s[i]))
                    break;

                cur += s[i];
                current_node = current_node->get_node_from_char(s[i]);

                if(current_node-> is_leaf){
                    vector<string> right_part = get_strings(i+1, s);
                    for(string s:right_part)
                        solutions.push_back(cur + s);
                }
            }
            return dp[index] = solutions;
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
