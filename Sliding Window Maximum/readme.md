# **Sliding Window Maximum**

In this problem we are given an array and an integer K.

For each window of length K it's required to find the max element.

Example:
```
Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
```

## First Approach
--------------

For each K elements let's loop and find the max element.
```
    for i in range 0 : n-k
        for j in range i : i + k
            calculate the max and save it
```

O(N*K) but what's worth mentioning is that we are not using additional space.

## Second Approach
-----------------

Let's try to analyze how our window changes:

first k elements are [1,3,-1] , then when the window slides, leftmost element will be removed and we add a new element at the end.

Can we simulate this ?

So the problem reduces to the following:

We want a data structure which

1. supports adding new elements fast
2. supports removing existing elements fast
3. can query max element fast

We can use Balanced Binary search trees for this where each query can be executed in O(logn)

Can we use a heap ?

**Complexity** O(nlogk) time and O(K) additional space

## Third Approach
-----------------

**Can we do better ?**

Let's add a new piece of information with each number, its **index** in the array.

example:

let [1,3,-1] become [(1,0), (3,1) , (-1,2)] where the first element is the number and the second is its index.

Now let's use a [deque](https://www.geeksforgeeks.org/deque-set-1-introduction-applications/) or a double ended queue which will maintain the maximum number at the front and let's see how.

### Inserting a new number

Assuming the max element at the front of the deque, we don't want to ruin that.

Let's insert the new element at the end of the deque.
But **before this** let's remove from the back all the elements smaller than it.

let's simulate the first 3 insertions
1. [(1,0)]
2. 1 is smaller than 3 so removes it [(3,1)]
3. 3 is bigger, so just insert it at the back, [(3,1), (-1,2)]

### Finding the max

If we keep on inserting, then after a couple of iteration we will get a wrong answer.

**Why**

For the first max number, we get it right which is 3.


Let's continue one more iteration

We insert -3 so the deque becomes [(3,1), (-1,2), (-3,2)] and the front is 3 but isn't it out of the current window ?

Simple! let's pop all invalid numbers from the front of the deque before asking for the max.

We can figure out the invalid numbers from the index so assume window ends at position i then any number at index smaller than i-k must be popped.

Note that we don't pop here unless an invalid number is at the front, which means the deque can have more than K elements.

**Complexity** O(N) time and space

Note that each element is inserted once and poped once.

