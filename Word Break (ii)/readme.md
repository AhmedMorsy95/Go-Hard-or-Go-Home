# **Word Break ii**

In this problem we are given a dictionary of words and a string just like this (example from leetcode)

`"catsanddo", ["cat", "cats", "and", "sand", "dog"]`

and we are required to return all possible all possible splits for the string such that each word in the split exists in the dictionary.

`["cats and dog","cat sand dog"]`

Let's first simplify the problem by **solving word break 1**.

In word break 1 it's required to return only a boolean indicating whether we can split the string or not.

## First Approach:
------------------
What comes first to any mind is the brute force solution.
We can use recursion and whenever we find a valid split we do it and check if the rest of string can be splitted.

One question is though, how to determine if a split is valid ?

### Here are some ideas:
1. Just loop on an array and compare (slow).
2. Add the elements to a set and check if it's there (faster).
3. Use a tree data structure like [Trie](https://en.wikipedia.org/wiki/Trie) aka prefix tree (the best) which given a string s of length n finds if it exists in O(n).

## Second Approach
-------------------
Let's make our recursion faster using [memoization](https://en.wikipedia.org/wiki/Memoization) so that we don't visit a node in the recursion tree more than once.

### Complexity Analysis
--------------------
**Space Complexity** : `Σ length(Si)` which are the dictionary strings inserted to the Trie + `O(N)` for the memoization array which is the length of the string to be splitted.

**Time Complexity** : One can see that it's `O(N^2)` 

However if we look at this piece of code

```
                bool can = 0;
                shared_ptr<Trie> current_node = dictionary;
                
                for(int i=index; i<s.length() && !can; i++){
                    // Check if the trie has the ith character in the string
                    if(!current_node->has_character(s[i]))
                        break;
                    
                    current_node = current_node->get_node_from_char(s[i]);
                    
                    if(current_node-> is_leaf)
                        can |= solve(i+1, s);
                }
```

There is a break statement which executes when we reach a deadend in the Trie.

Let's denote the length of the longest string in the Trie as w.

Therefore complexity becomes `O(n * min(n,w))` which can be quite good if w is small.

There is also a minor optimization up there can you find it ?


## Now that we have solved Word Break 1 let's return to our original problem

## First Approach
---------------
Let's create a recursive function which tries to split whenever it's valid and also remembers how it splitted.

example:
    
    Let's use the sample input above
    
    1.  Current string = "catsanddog", split = ""
        Then we find a valid split "cat" so we split.
    
    2.  Current string = "sanddog" split = "cat"
        Then we find a valid split "sand" so we split.

    3.  Current string = "dog", split = "cat sand"
        Finally we find the last split.

    4.  Current string = "", split = "cat sand dog"
        The string is now empty, we found a match!

## Second Approach
--------------------

Let's try to make the 1st approach faster by adding memoization.

Once we visit an index and we find a valid split, let's save them.

The complexity here for time and space depends on the number of valid splits, since all splits will be found and saved.


## Third Approach
-----------------

We can add a minor optimization to the solution above by only visiting states in which it's guranteed to find a solution by using Word Break 1.

So before splitting we can call our old solve function, to check that there is a solution after doing this split.

This means that we only save and iterate through splits which will give one of the solutions.

All other valid splits will be discarded.

example:
    let s = "abbc" and dictionary = ["a", "b", "bb", "bc"]
    
    Second approach
    
    1. Current string = "abbc", split = ""
    
    2. Current Stirng = "bbc", split = "a bb"
       Let's split using bb

    3. Current Stirng = "c", split = "c"
       No valid solution exists! 

    The third approach would not visit this state.   

## Fourth Approach
------------------
Let's modify Word Break 1 in such a way which helps us build a **Graph**.

This problem can be mapped to printing all valid paths from a source to a destination.

### Model
    1. source = string begin

    2. destination = string end

    3. edges represent a valid split after which it's guranteed to find a solution

The question is now how to build it ?

If you still remember -and bear with me this is the final approach- Word Break 1 solution we can add a simple modification to build the graph.

```
                for(int i=index; i<s.length(); i++){
                    if(!current_node->has_character(s[i]))
                        break;
                    current_node = current_node->get_node_from_char(s[i]);
                    if(current_node-> is_leaf){
                       bool found_solution = solve(i+1, s);
                       if(found_solution){
                            can = true;
                            /// This is the one
                            adjacency_matrix[index].push_back(i+1);
                       }
                    }
                }

```
 
We create an edge from index to i+1 denoting that we can split substring
[index,i] and it's guranteed to find a solution starting from i+1.

**Space Complexity** : Same as word break 1 in addition to O(N + M) where N denotes nodes and M denotes edges for our adjacency matrix

**Time Complexity** : Same as word break as for the new part, it's O(Paths) where each path represents a solution 