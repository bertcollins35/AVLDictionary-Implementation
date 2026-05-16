#ifndef AVLDICTIONARY_HPP
#define AVLDICTIONARY_HPP

#include "Dictionary.hpp"
#include "AVL.hpp"
#include "Pair.hpp"

    class AVLDictionary : public Dictionary{

        private:
        AVL tree;

        public: 

        AVLDictionary();
        bool insert(int k, double v);
        double get(int k) const;
        bool remove(int k);
        std::vector<Pair<int,double>> get_range(int k1, int k2) const;
        int size() const;
        bool is_empty() const;
        void clear();
        std::vector<int> keys() const;
        std::vector<double> values() const; 
        std::vector<Pair<int,double>> entries() const;

    };




#endif
