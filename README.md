# Trie
## Aim 
Created memory efficient Trie datastructure with O(n) complexity of search ,insert and delete operations of string .<br>
## Class Pxtree Member 
1) int count(string s) :- Return the count associated with the string s. If the string is not in the tree, return 0.<br>
2) void add(string s)  :- Add the string s to the tree if it is not already represented the tree, and assign a count of 1. If it is already in the tree increment the count by 1.<br>
3) void remove(string ):- Reduce the count of the string s by 1, if s is represented in the tree. For simplicity, leaves with count 0 are kept in the <br>
<tb><tb>tree (they are dealt with separately in the compact function). If s is not in the tree at all or already has count 0, do nothing.<br>
4) string print() :-  print the tree in the way described in the assignment page.The root node is not printed. If the tree is empty (i.e. only has the root), return an empty<br>
string.<br>
5) string autoComplete(string s) :-return the string with the highest count that ends in the subtree rooted at s, including s itself. If there are strings with equal <br>
maximum counts, return anyone.If there are no such strings, return s itself.This is meant to be difficult.<br>
6) void compact() :- This "compacts" the tree by removing any leaves with a count of 0.
## More Details
  ![alt text](https://github.com/3682himanshu/Trie/blob/master/Images/image1.JPG?raw=true)
  ![alt text](https://github.com/3682himanshu/Trie/blob/master/Images/image2.JPG?raw=true)
