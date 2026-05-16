#ifndef AVLNode_HPP
#define AVLNode_HPP

class AVLNode{

    public: 

    int key;
    double value;
    int balance_factor;
    int height;

    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

    AVLNode(int k, double v);
    AVLNode(int k, double v, AVLNode* l, AVLNode* r, AVLNode* p);
    AVLNode();
    ~AVLNode();
    AVLNode(const AVLNode& other);
    AVLNode& operator=(const AVLNode& other);
    int calculate_balance_factor();
    void update_height();
};



#endif