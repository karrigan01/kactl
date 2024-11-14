/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */
#pragma once

struct aho
{
    struct TrieNode
    {
        int nxt[26], link;
    };
    vector<TrieNode> Trie;
    vector<int> adj[100005];
    int nTree;

    void insertString(const string &str) {
        int pt(0);
        for (char ch : str) {
            int c(ch - 'a');
            if(!Trie[pt].nxt[c]) {
                Trie[pt].nxt[c] = Trie.size();
                Trie.emplace_back();
            }
            pt = Trie[pt].nxt[c];
        }
    }

    void buildAutomaton(void) {
        queue<int> qu;
        qu.push(0);
        while(qu.size()) {
            int v(qu.front()), u(Trie[v].link);
            qu.pop();

            for (int c = 0; c < 26; ++c) {
                if(Trie[v].nxt[c]) {
                    Trie[Trie[v].nxt[c]].link = (v) ? Trie[u].nxt[c] : 0;
                    qu.push(Trie[v].nxt[c]);
                } else {
                    Trie[v].nxt[c] = Trie[u].nxt[c];
                }
            }
        }
    }
    void buildTree(void) {
        nTree = Trie.size();
        for (int i = 1; i < nTree; ++i)
            adj[Trie[i].link].push_back(i);
    }

};
