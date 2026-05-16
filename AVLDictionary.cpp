#include "Dictionary.hpp"
#include "AVLDictionary.hpp"
#include "AVL.hpp"
#include "Pair.hpp"
#include "AVLNode.hpp"

AVLDictionary::AVLDictionary(){
    tree = AVL();
}

bool AVLDictionary::insert(int k, double v){
    if(tree.contains(k)){   //self-implemented contains value that works like search but returns a boolean value
        return false;
    }
    tree.insert(k,v);   
    return true;
}

double AVLDictionary::get(int k) const{
   return tree.search(k).value_or(-1.0); //-1.0 if key not found
}

bool AVLDictionary::remove(int k){
    if(!tree.is_empty()){
        if(tree.contains(k)){
            tree.remove(k);
            return true;
        }else{
            return false;
        }
    }
    return false;
}

int AVLDictionary::size() const{
    return tree.size();
}

bool AVLDictionary::is_empty() const{
    if(tree.is_empty()){
        return true;
    }else{
        return false;
    }

}

void AVLDictionary::clear(){
    tree.clear();
}

std::vector<int> AVLDictionary::keys() const{
    return tree.keys();
}

std::vector<double> AVLDictionary::values() const{
    return tree.values();
}

std::vector<Pair<int,double>> AVLDictionary::entries() const{
    return tree.entries();
}

std::vector<Pair<int,double>> AVLDictionary::get_range(int k1, int k2) const{
    return tree.get_range(k1, k2);
}

