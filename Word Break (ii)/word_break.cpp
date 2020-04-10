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
        Solution(){
            dictionary = make_shared<Trie>();
        }
        bool wordBreak(string s, vector<string>& wordDict) {
            for(string word : wordDict)
                dictionary->insert(word);

            dp.resize(s.length());
            fill(dp.begin(),dp.end(),-1);
            return solve(0,s);
        }

        bool solve(int index, string &s){
            if(index == s.length())
                return true;

            if(dp[index] != -1)
                return dp[index];

            bool can = 0;
            shared_ptr<Trie> current_node = dictionary;
            for(int i=index; i<s.length() && !can; i++){
                if(!current_node->has_character(s[i]))
                    break;
                current_node = current_node->get_node_from_char(s[i]);
                if(current_node-> is_leaf)
                    can |= solve(i+1, s);
            }
            return dp[index] = can;
        }
};

int main()
{
    shared_ptr<Solution> x = make_shared<Solution>();
    vector<string>v{"ahm","e","d"};
    cout<<x->wordBreak("ahmed",v);
    return 0;
}
