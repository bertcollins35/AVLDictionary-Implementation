// Self-balancing binary search tree (int keys -> double values).
// Insert, search, and remove run in O(log n); range queries in O(k + log n).
#ifndef AVL_HPP
#define AVL_HPP
#include "AVLNode.hpp"
#include "Pair.hpp"
#include <vector>
#include <optional>

class AVL{
    private:
    AVLNode* root;
    
    public:

    void insert(int k, double v);
    std::optional<double> search (int k) const;

    void inorder_traversal() const;
    void postorder_traversal() const;
    void preorder_traversal() const;

    void clear();
    bool is_empty() const;      
    bool contains(int k) const;

    void remove(int k);
    int size() const;
    int height() const;

    std::vector<int> keys() const;
    std::vector<double> values() const;
    std::vector<Pair<int,double>> entries() const;
    std::vector<Pair<int,double>> get_range(int k1, int k2) const;


    AVL();
    ~AVL();
    AVL(const AVL& other);
    AVL& operator=(const AVL& other);

    private:

    void insert(AVLNode* curr, int k, double v);    //recursive functions
    std::optional<double> search(AVLNode* curNode, int k) const;
    void inorder_traversal(AVLNode* curNode) const;
    void preorder_traversal(AVLNode* curNode) const;
    void postorder_traversal(AVLNode* curNode) const;
    int size(AVLNode* curNode) const;
    int height(AVLNode* curNode) const;
    AVLNode* inorder_successor(AVLNode* curNode);
    void clear(AVLNode* curNode);
    void keys(AVLNode* curNode,std::vector<int>* p) const;
    void values(AVLNode* curNode, std::vector<double>* p) const;
    void entries(AVLNode* curNode, std::vector<Pair<int,double>>* p) const;
    void get_range(AVLNode* curNode, int k1, int k2, std::vector<Pair<int,double>>& out) const;
    bool contains(AVLNode* curNode, int k) const;

    AVLNode* rotateRight(AVLNode* curNode);
    AVLNode* rotateLeft(AVLNode* curNode);
    AVLNode* rotateRightLeft(AVLNode* curNode);
    AVLNode* rotateLeftRight(AVLNode* curNode);
    void rebalance_up(AVLNode* curNode);
};

#endif

