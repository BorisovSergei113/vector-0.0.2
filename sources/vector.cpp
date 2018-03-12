#include <algorithm>
#include <cassert>
#include "vector.hpp"

vector_t::vector_t()
{
    elements_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

vector_t::vector_t(vector_t const & other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = new int [capacity_];
    for (std::size_t i = 0; i<capacity_; i++) {
        elements_[i] = other.elements_[i];
    }
}


vector_t & vector_t::operator =(vector_t const & other)
{
    if (&other == this) return *this;
    if (elements_!=nullptr) {
        delete [] elements_;
    }
    
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_=new int[capacity_];
    for (std::size_t i = 0; i<capacity_; i++) {
        elements_[i] = other.elements_[i];
    }
    return *this;
}

bool vector_t::operator ==(vector_t const & other) const
{
    if(size_==other.size_){
        for (std::size_t i = 0; i<capacity_; i++) {
            if (elements_[i] != other.elements_[i]) return false ;
        }
        return true;
    }
    else return false;
}

vector_t::~vector_t()
{
    if(elements_!=nullptr){
        delete [] elements_;
    }
}

std::size_t vector_t::size() const
{
    return size_;
}

std::size_t vector_t::capacity() const
{
    return capacity_;
}

void vector_t::push_back(int value)
{
    size_++;
    if (size_>capacity_) {
        if(!capacity_){
            capacity_=1;
        }
        else{
            capacity_*=2;
        }
    
    int *elements=new int[capacity_];
    for (std::size_t i = 0; i<size_-1; i++) {
        elements[i]=elements_[i];
    }
    elements[size_-1]=value;
    if (elements_!=nullptr) delete [] elements_;
    elements_=elements;
    }
    else elements_[size_-1]=value;
}

void vector_t::pop_back()
{
    if(!size_) return;
    size_--;
    if (size_<=(capacity_/4)) {
        capacity_=capacity_/2;
        int *elements =new int[capacity_];
        for (std::size_t i = 0; i<size_; i++) {
            elements[i]=elements_[i];
        }
        if (elements_!=nullptr) delete [] elements_;
        elements_=elements;
    }
}

int & vector_t::operator [](std::size_t index)
{
    return elements_[index];
}

int vector_t::operator [](std::size_t index) const
{
    return elements_[index];
}

bool operator !=(vector_t const & lhs, vector_t const & rhs)
{
    if(rhs.size()!=lhs.size()){
        return true;
    }
    for (std::size_t i=0; i<rhs.size(); i++) {
        if (lhs.elements_[i]!=rhs.elements_[i]) {
            return true;
        }
    }
    return false;
}
