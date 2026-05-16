#include <iostream>
#include "AVLNode.hpp"  
#include "AVL.hpp"
#include <vector>
#include <optional>

AVL::AVL(){
    root = nullptr;
}

AVL::~AVL(){
    clear();
}

AVL::AVL(const AVL &other){
    if (other.root != nullptr) {
        root = new AVLNode(*other.root);
    } else {
        root = nullptr;
    }
}

AVL& AVL::operator=(const AVL& other){
    if(this == &other){
        return *this;
    }
    if (root != nullptr){
        delete root;
        root = nullptr;
    }
    if (other.root != nullptr) {
        root = new AVLNode(*other.root);
    } else {
        root = nullptr;
    }
    return *this;
}

void AVL::insert(int k, double v){
    if(root == nullptr){            
        root = new AVLNode(k,v);
    }else{
        insert(root,k,v);
    }  
}

void AVL::insert(AVLNode* curNode, int k, double v){
    if (k == curNode->key) return;
    if (k <= curNode->key) {
        if (curNode->left != nullptr) {
            return insert(curNode->left, k, v);
        }
        curNode->left = new AVLNode(k,v);
        curNode->left->parent = curNode;
        rebalance_up(curNode);
        return;
    } else {
        if (curNode->right != nullptr) {
            return insert(curNode->right, k, v);
        }
        curNode->right = new AVLNode(k,v);
        curNode->right->parent = curNode;
        rebalance_up(curNode);
        return;
    }
}

std::optional<double> AVL::search(int k) const{
    return search(root,k);
}

std::optional<double> AVL::search(AVLNode* curNode, int k) const{
    if (curNode == nullptr){
        return std::nullopt;
    }
    if(k == curNode->key){
        return curNode->value;
    }
    if(k < curNode->key){
        return search(curNode->left,k);
    }else{
        return search(curNode->right,k);
    }
}

void AVL::inorder_traversal() const{
    inorder_traversal(root);
}

void AVL::inorder_traversal(AVLNode* curNode) const{
    if(curNode == nullptr){
        return;
    }else{
        inorder_traversal(curNode->left);
        std::cout << "(" << curNode->key << "," << curNode->value << ")" << std::endl;
        inorder_traversal(curNode->right);
    }    
}

void AVL::preorder_traversal() const{
    preorder_traversal(root);
}

void AVL::preorder_traversal(AVLNode* curNode) const{
    if(curNode == nullptr){
        return;
    }else{
        std::cout << "(" << curNode->key << "," << curNode->value << ")" << std::endl;
        preorder_traversal(curNode->left);
        preorder_traversal(curNode->right);
    }
}

void AVL::postorder_traversal() const{
    postorder_traversal(root);
}

void AVL::postorder_traversal(AVLNode* curNode) const{
    if(curNode == nullptr){
        return;
    }else{
        postorder_traversal(curNode->left);
        postorder_traversal(curNode->right);
        std::cout << "(" << curNode->key << "," << curNode->value << ")" << std::endl;
    }
}

int AVL::size() const{
    return size(root);
}

int AVL::size(AVLNode* curNode) const{
    if(curNode == nullptr){
        return 0;
    }
    return 1 + size(curNode->left) + size(curNode->right);
}

int AVL::height() const{
    return height(root);
}

int AVL::height(AVLNode* curNode) const{
    if(curNode == nullptr){
        return 0;
    }
    int leftTree = height(curNode->left);
    int rightTree = height(curNode->right);

    int biggest = 0;
    if(leftTree > rightTree){
        biggest = leftTree;
    }else{
        biggest = rightTree;
    }
    return 1 + biggest;
}

void AVL::remove(int k){
    // find the node holding k
    AVLNode* target = root;
    while(target != nullptr && target->key != k){
        if(k < target->key){
            target = target->left;
        }else{
            target = target->right;
        }
    }
    if(target == nullptr){
        return;                 // key not in tree, nothing to do
    }

    // if the node has two children, copy the in-order successor's data
    // into it and re-target deletion at the successor, which has <= 1 child
    if(target->left != nullptr && target->right != nullptr){
        AVLNode* ios = inorder_successor(target->right);
        target->key = ios->key;
        target->value = ios->value;
        target = ios;
    }

    // target now has at most one child; pick it (may be nullptr)
    AVLNode* child = nullptr;
    if(target->left != nullptr){
        child = target->left;
    }else{
        child = target->right;
    }

    AVLNode* parent = target->parent;

    // splice target out: link child to parent in target's place
    if(child != nullptr){
        child->parent = parent;
    }
    if(parent == nullptr){
        root = child;           // target was the root
    }else if(parent->left == target){
        parent->left = child;
    }else{
        parent->right = child;
    }

    // detach target's children before deleting, so ~AVLNode does not
    // recursively delete the subtree we just kept
    target->left = nullptr;
    target->right = nullptr;
    delete target;

    // rebalance once, climbing from the splice point to the root
    if(parent != nullptr){
        rebalance_up(parent);
    }
}

AVLNode* AVL::inorder_successor(AVLNode* curNode){
    AVLNode* iter = curNode;
    while (iter->left != nullptr) {
        iter = iter->left;
    }
    return iter;
    
}

void AVL::clear(AVLNode* curNode){
    if(curNode == nullptr) return;
    clear(curNode->left);
    clear(curNode->right);
    curNode->left = nullptr;
    curNode->right = nullptr;
    delete curNode;
}

void AVL::clear(){
    clear(root);
    root = nullptr;
}

bool AVL::is_empty() const{
    if (root == nullptr){
        return true;
    }else{
        return false;
    }
}
std::vector<int> AVL::keys() const{
    std::vector<int> k;
    std::vector<int>* pk = &k;  //Creates a pointer that points to address of k
    keys(root,pk);
    return k;
} 

void AVL::keys(AVLNode* curNode, std::vector<int>* p) const{
    std::vector<int>& k2 = *p;  //pointer is dereferenced and k2 is use as a reference for k (in original function)
    if(curNode == nullptr){
        return;
    }
    keys(curNode->left,p);
    k2.push_back(curNode->key);     //k is able to be editied due to the reference of k2
    keys(curNode->right,p);
}

std::vector<double> AVL::values() const{
    std::vector<double> v;
    std::vector<double>* pv = &v;      //same logic with keys is applied to values
    values(root,pv);
    return v;
}

void AVL::values(AVLNode* curNode, std::vector<double>* p) const{
    std::vector<double>& v2 = *p;
    if(curNode == nullptr){
        return;
    }
    values(curNode->left,p);
    v2.push_back(curNode->value);
    values(curNode->right,p);

}

std::vector<Pair<int,double>> AVL::entries() const{
    std::vector<Pair<int,double>> e;
    std::vector<Pair<int,double>>* pe = &e; //same logic applied to entries as well (from keys and values)
    entries(root,pe);
    return e;
}

void AVL::entries(AVLNode* curNode, std::vector<Pair<int,double>>* p) const{
    std::vector<Pair<int,double>>& e2 = *p;
    if(curNode == nullptr){
        return;
    }
    entries(curNode->left, p);
    Pair<int,double> tmp (curNode->key,curNode->value); //temporary Pair created to store key and value
    e2.push_back(tmp);
    entries(curNode->right,p);
}

bool AVL::contains(int k) const{
    return contains(root,k);
}

bool AVL::contains(AVLNode* curNode, int k) const{
    if (curNode == nullptr){
        return false;
    }
    if(k == curNode->key){
        return true;
    }
    if(k < curNode->key){
        return contains(curNode->left,k);
    }else{
        return contains(curNode->right,k);
    }
}

AVLNode* AVL::rotateLeft(AVLNode* curNode){
    AVLNode* temp1 = curNode;
    AVLNode* temp3 = curNode->right;
    AVLNode* temp4 = curNode->right->left;

    curNode->right->left = temp1;
    curNode->right->parent = temp1->parent;
    curNode->right = temp4;
    curNode->parent = temp3;
    if(temp4 != nullptr){
        temp4->parent = temp1;
    }
    temp1->update_height();   // lower node first
    temp3->update_height();   // new subtree root, depends on temp1
    return temp3;
}
AVLNode* AVL::rotateRight(AVLNode* curNode){
    AVLNode* temp1 = curNode;
    AVLNode* temp3 = curNode->left;
    AVLNode* temp4 = curNode->left->right;

    curNode->left->right = temp1;
    curNode->left->parent = temp1->parent;
    curNode->left = temp4;
    curNode->parent = temp3;
    if(temp4 != nullptr){
        temp4->parent = temp1;
    }
    temp1->update_height();   // lower node first
    temp3->update_height();   // new subtree root, depends on temp1
    return temp3;
}

AVLNode* AVL::rotateLeftRight(AVLNode* curNode){
    curNode->left = rotateLeft(curNode->left);
    return rotateRight(curNode);
}

AVLNode* AVL::rotateRightLeft(AVLNode* curNode){
    curNode->right = rotateRight(curNode->right);
    return rotateLeft(curNode);
}

void AVL::rebalance_up(AVLNode* curNode){
    AVLNode* curr = curNode;
    while(curr != nullptr){
        curr->update_height();
        curr->calculate_balance_factor();
        AVLNode* p = curr->parent;
        AVLNode* newRoot = curr;
        if(curr->balance_factor > 1){//left heavy
            // recompute child's balance factor: it may be stale, and the
            // single-vs-double rotation choice depends on it
            curr->left->calculate_balance_factor();
            if(curr->left->balance_factor >= 0){//single rotation
                newRoot = rotateRight(curr);
            }else{
                newRoot = rotateLeftRight(curr);
            }
        }else if(curr->balance_factor < -1){//right heavy
            curr->right->calculate_balance_factor();
            if(curr->right->balance_factor <= 0){//single rotation
                newRoot = rotateLeft(curr);
            }else{
                newRoot = rotateRightLeft(curr);
            }
        }
        if(newRoot != curr){
            if(p == nullptr){
                root = newRoot;  
            }else if(p->left == curr){      //initialize new root in case it gets moved
                p->left = newRoot;
            }else{
                p->right = newRoot;
            }
        }
            curr = p;
    }
}

std::vector<Pair<int,double>> AVL::get_range(int k1, int k2) const{
    std::vector<Pair<int,double>> out;
    get_range(root, k1, k2, out);
    return out;
}

void AVL::get_range(AVLNode* curNode, int k1, int k2, std::vector<Pair<int,double>>& out) const{
    if (curNode == nullptr){
        return;
    }
    if (curNode->key > k1){ 
        get_range(curNode->left, k1, k2, out);
    }
    if (curNode->key >= k1 && curNode->key <= k2){
        out.emplace_back(curNode->key, curNode->value);
    }
    if (curNode->key < k2){
        get_range(curNode->right, k1, k2, out);
    }
}
