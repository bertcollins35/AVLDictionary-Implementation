#include "AVLNode.hpp"
#include <iostream>
#include <algorithm>

AVLNode::AVLNode(){
    left = right = nullptr;
    height = 1;
    key = 0;
    value = 0.0;
    parent = nullptr;
    calculate_balance_factor();
}

AVLNode::AVLNode(int k, double v) : AVLNode(){
    key = k;
    value = v;
}

AVLNode::AVLNode(int k, double v, AVLNode* l, AVLNode* r, AVLNode* p) : AVLNode(k,v){
    left = l;
    right = r;
    parent = p;
    calculate_balance_factor();
}   

AVLNode::~AVLNode(){
     if(left != nullptr) {
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        delete right;
        right = nullptr;
    }
}

AVLNode::AVLNode(const AVLNode &other){
    parent = nullptr;   // overwritten by this node's parent if it has one;
                        // stays null for the root of the copied subtree
    if(other.left == nullptr && other.right == nullptr){
        left = right = nullptr;
        key = other.key;
        value = other.value;
    }else if(other.left == nullptr){
        left = nullptr;
        right = new AVLNode(*(other.right));
        right->parent = this;
        key = other.key;
        value = other.value;
    }else if(other.right == nullptr){
        right = nullptr;
        left = new AVLNode(*(other.left));
        left->parent = this;
        key = other.key;
        value = other.value;
    }else{
        key = other.key;
        value = other.value;
        left = new AVLNode(*(other.left));
        right = new AVLNode(*(other.right));
        left->parent = this;
        right->parent = this;
    }
    update_height();
    calculate_balance_factor();

}

AVLNode& AVLNode::operator=(const AVLNode &other){
    if(this != &other){
        delete left;
        delete right;

        if(other.left == nullptr && other.right == nullptr){
            left = nullptr;
            right = nullptr;
            key = other.key;
            value = other.value;
        }else if(other.left == nullptr){
            left = nullptr;
            right = new AVLNode(*(other.right));
            key = other.key;
            value = other.value;
            right->parent = this;
        }else if(other.right == nullptr){
            right = nullptr;
            left = new AVLNode(*(other.left));
            key = other.key;
            value = other.value;
            left->parent = this;
        }else{
            key = other.key;
            value = other.value;
            left = new AVLNode(*(other.left));
            right = new AVLNode(*(other.right));
            left->parent = this;
            right->parent = this;
        }
    }
    update_height();
    calculate_balance_factor();
    return *this;
}


int AVLNode::calculate_balance_factor(){
    int lh = 0;
    if(left != nullptr){
        lh = left->height;
    }
    int rh = 0;
    if(right != nullptr){
        rh = right->height;
    }
    balance_factor = lh - rh;
    return balance_factor;
}

void AVLNode::update_height(){
    int lh = 0;
    if(left != nullptr){
        lh = left->height;
    }
    int rh = 0;
    if(right != nullptr){
        rh = right->height;
    }
    if(lh > rh){
        height = 1 + lh;
    }else{
        height = 1 + rh;
    }
}