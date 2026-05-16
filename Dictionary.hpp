#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <vector>
#include "Pair.hpp"

class Dictionary {
    public:
    
    virtual ~Dictionary() = default;
    virtual bool insert(int k, double v) = 0;
    virtual double get(int k) const = 0;
    virtual bool remove(int k) = 0;
    virtual std::vector<Pair<int,double>> get_range(int k1, int k2) const = 0;
    virtual int size() const = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
    virtual std::vector<int> keys() const = 0;
    virtual std::vector<double> values() const = 0;
    virtual std::vector<Pair<int,double>> entries() const = 0;
};

#endif
