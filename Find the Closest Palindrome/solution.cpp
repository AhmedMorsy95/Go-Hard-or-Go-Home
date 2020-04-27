#define pb push_back
#define ll long long
#define F first
#define S second

class Solution {
public:

    // returns difference between 2 strings
    long long get_difference(string a,string b){
        ll x = 0, y = 0;
        for(char c : a){
            x *= 10;
            x += c - '0';
        }
        for(char c : b){
            y *= 10;
            y += c - '0';
        }
        return abs(y-x);
    }

    /*
        Sorts the pair according to this criteria
        1. min value comes first
        2. in case of tie, pick string of smaller length
        3. in case of tie, pick string of smaller value
    */

    bool static compare_string(pair<ll,string> a, pair<ll,string> b){
        if(a.F != b.F)
            return a.F < b.F;
        if(a.S.length() == b.S.length())
            return a.S < b.S;
        return a.S.length() < b.S.length();
    }

vector<int>choices[10];
ll mn = 1e18;
string best = "Garabage";

/*
    Generates the first half of the palindrome then finds the difference between this palindrome and the original number
*/

void solve(ll prefix, string &s, int  idx){
    int mid_point = ((int)s.length() + 1) / 2;
    if(idx == mid_point){
        ll suffix = 0;
        bool odd = (int)s.length() & 1;
        ll x = prefix;

        /// add suffix to complete the palindrome
        while(x){
            int last_digit = x%10;
            x /= 10;
            if(odd)
                odd = !odd;

            else{
                suffix *= 10;
                suffix += last_digit;
                prefix *= 10;
            }
        }
        prefix += suffix;
        ll cost = get_difference(s, to_string(prefix));

        /// find best palindrome
        if(cost < mn && cost){
           mn = cost;
           best = to_string(prefix);
        }
        else if(cost == mn && to_string(prefix) < best)
            best = to_string(prefix);
    }

    /// try all choices
    for(int i : choices[idx])
        solve(prefix*10 + i, s, idx+1);

}
    string nearestPalindromic(string s) {
    /// special case
    if(s == "1") return "0";

    /*
        for each position in the string we will have 3 choices
        1. keep the number as it is
        2. increment the value of the number
        3. decrement the value

        This makes 3 possible values for each position which makes Complexity 3^N, N = 9 here so it's fine.
    */

    vector<pair<ll, string> >solutions;
    for(int i=0;i<((int)s.length()+1)/2; i++){
        choices[i].pb(s[i]-'0');
        if(!(s[i] == '1' && i == 0) && s[i]!='0')
            choices[i].pb(s[i]-'0'-1);
        if(s[i] != '9')
            choices[i].pb(s[i]-'0'+1);
    }

    /// generate nearest palindrome of length n
    solve(0,s,0);
    solutions.pb(make_pair(mn, best));

    /// generate largest palindorme with length n-1 if exists
    if(s.length() != 1){
        string x = "";
        for(int i=1;i<s.length();i++)
            x += "9";
        solutions.pb(make_pair(get_difference(x,s), x));
    }

    /// generate smallest palindorme with length n+1
    string x = "1";
    for(int i=1;i<s.length();i++)
        x += "0";
    x += "1";
    solutions.pb(make_pair(get_difference(x,s), x));

    /// sort all solutions and get the min difference
    sort(solutions.begin(),solutions.end(), compare_string);
    return solutions[0].S;
    }
};

