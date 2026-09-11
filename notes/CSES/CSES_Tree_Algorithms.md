# Tree Algorithms

## Subordinates

**Problem:** Given the structure of a company, your task is to calculate for each employee the number of their subordinates.

**Topic:** `DP`

**Time Complexity:** $O(n)$






## Tree Diameter

**Problem:** You are given a tree consisting of $n$ nodes.

The ***diameter*** of a tree is the maximum distance between two nodes. Your task is to determine the diameter of the tree.

**Topic:** `Tree Diameter`

**Time Complexity:** $O(n)$





## Tree Distances I

**Problem:** You are given a tree consisting of $n$ nodes.

Your task is to determine for each node the maximum distance to another node.

**Topic:** `Tree Diameter`

**Time Complexity:** $O(n)$





## Company Queries I

**Problem:** find the node resulting of ascending $k$ levels higher up in the hierachy, probably going out of bounds (create a sentinel node).

**Topic:** `Binary Lifting`

**Time Complexity:** $\log(n)$ per query

**Time Complexity:** $q \log(n)$






## Tree Matching

**Problem:** You are given a tree consisting of $n$ nodes.

A ***matching*** is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?

**Topic:** `DP` `DP on Trees`

**Time Complexity:** $O(n)$




## Company Queries II

**Problem:** find LCA between two tree nodes $a$ and $b$.

**Topic:** `LCA`

**Time Complexity:** $O(\log(n))$ per query

**Time Complexity:** $O(n \log(n) + q \log(n))$





## Tree Distances II

**Problem:** You are given a tree consisting of $n$ nodes.

Your task is to determine for each node the sum of the distances from the node to all other nodes.

**Topic:** `DP` `Rerooting DP`

**Time Complexity:** $O(n)$





## Distance Queries

**Problem:** You are given a tree consisting of $n$ nodes.

Your task is to process $q$ queries of the form: what is the distance between nodes $a$ and $b$?

**Topic:** `LCA`

**Time Complexity:** $n \log(n)$





## Subtree Queries

**Problem:** You are given a rooted tree consisting of $n$ nodes. The nodes are numbered $1,2,...,n$, and node $1$ is the root. Each node has a value.

Your task is to process following types of queries:
1. change the value of node $s$ to $x$.
2. calculate the sum of values in the subtree of node $s$.

**Topic:** `Euler Tour Technique`

**Time Complexity:** $\log(n)$ per query

**Time Complexity:** $n \log(n)$






## Counting Paths

**Problem:** You are given a tree consisting of $n$ nodes, and $m$ paths in the tree.

Your task is to calculate for each node the number of paths containing that node.

**Topic:** `LCA`

**Time Complexity:** $n \log(n)$






## Path Queries

**Problem:** You are given a rooted tree consisting of $n$ nodes. The nodes are numbered $1,2,...,n$, and node $1$ is the root. Each node has a value.

Your task is to process following types of queries:

1. change the value of node $s$ to $x$.

2. calculate the sum of values on the path from the root to node $s$.

**Topic:** `Euler Tour Technique`

**Time Complexity:** $O(\log(n))$ per query

**Time Complexity:** $O(n \log(n))$




## Distinct Colors

**Problem:** You are given a rooted tree consisting of $n$ nodes. The nodes are numbered $1,2,...,n$, and node 1 is the root. Each node has a color.

Your task is to determine for each node the number of distinct colors in the subtree of the node.

**Topic:** Small-To-Large Merging

**Time Complexity:** $O(n \log^{2} n)$




## Finding a Centroid

**Problem:** Given a tree of $n$ nodes, your task is to find a ***centroid***, i. e., a node such that when it is appointed the root of the tree, each subtree has at most $\left\lfloor \frac{n}{2} \right\rfloor$ nodes.

**Topic:** Free

**Time Complexity:** $O(n)$






## Path Queries II

**Problem:** Single node updates, max path queries

**Topic:** `Heavy-Light Decomposition`

**Time Complexity:** $O(\log^{2} n)$ per query

**Time Complexity:** $O(n \log^{2} n)$






## Fixed-Length Paths I

**Problem:** Given a tree of $n$ nodes, your task is to count the number of distinct paths that consist of exactly $k$ edges.

**Topic:** `Centroid Decomposition`

**Time Complexity:** $O(n \log(n))$





## Fixed-Length Paths II

**Problem:** Given a tree of $n$ nodes, your task is to count the number of distinct paths that have at least $k_1$ and at most $k_2$ edges.

**Topic:** `Centroid Decomposition`

**Time Complexity:** $O(n \log(n))$ or $O(n)$



















# Topics

## DP on Trees - Introduction

### Resources

* https://usaco.guide/gold/dp-trees

### Problems

* [Tree Matching](https://cses.fi/problemset/task/1130)









## DP on Trees - Solving For All Roots

### Resources

* https://usaco.guide/gold/all-roots

### Problems

* [Tree Distances II](https://cses.fi/problemset/task/1133)







## Binary Jumping

### Resources

* https://usaco.guide/plat/binary-jump

### Problems

* [Counting Paths](https://cses.fi/problemset/task/1136)









## Euler Tour Technique

Flattening a tree into an array to easily query and update subtrees.

### Resources

* https://usaco.guide/gold/tree-euler

### Problems

* [Path Queries](https://cses.fi/problemset/task/1138)






## Small-To-Large Merging

### Resources

* https://usaco.guide/plat/merging

### Problems

* [Distinct Colors](https://cses.fi/problemset/task/1139)









## Heavy-Light Decomposition

### Resources

* https://usaco.guide/plat/hld

### Problems

* [Path Queries II](https://cses.fi/problemset/task/2134)






## Centroid Decomposition

### Resources

* https://usaco.guide/plat/centroid

### Problems

* [Fixed-Length Paths I](https://cses.fi/problemset/task/2080)
* [Fixed-Length Paths II](https://cses.fi/problemset/task/2081)
