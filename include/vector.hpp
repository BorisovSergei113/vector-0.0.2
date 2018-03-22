#include <iostream>
#include <algorithm>
#include <cassert>

template <typename  Type>
class vector_t;

template <class  Type>
bool operator !=(vector_t<Type> const & lhs, vector_t<Type> const & rhs);

template <typename  Type>
class vector_t
{
private:
    Type * elements_;//указатель на массив
    std::size_t size_;// кол-во элементов находящийся в массиве
    std::size_t capacity_; //кол-во эл для выделения памяти
public:
    vector_t();
    vector_t(vector_t const & other);
    vector_t & operator =(vector_t const & other);
    ~vector_t();
    
    std::size_t size() const;
    std::size_t capacity() const;
    
    void push_back(Type value);
    void pop_back();
    Type at(std::size_t index) const ;
    Type& at(std::size_t index);
    
    Type & operator [](std::size_t index);
    Type operator [](std::size_t index) const;
    bool operator ==(vector_t const & other) const;
    //Специализация шаблона,поэтому выносим объявление перед шаблоном класса
    friend  bool operator  != <Type>(vector_t<Type> const & lhs, vector_t<Type> const & rhs);
    //При после инстанциации будет нешаблонная friend декларация и останется одна шаблонная.Из-за этого компилятор не находит реализацию friend декларации
};


///////////////////////////////////////////////////////////////////////////////////////////////

template <typename  Type>
vector_t<Type>::vector_t()
{
    elements_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template <typename  Type>
vector_t<Type>::vector_t(vector_t const & other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = new Type [capacity_];
    for (std::size_t i = 0; i<capacity_; i++) {
        elements_[i] = other.elements_[i];
    }
}

template <typename  Type>
vector_t<Type> & vector_t<Type>::operator =(vector_t const & other)
{
    if (&other == this) return *this;
    if (elements_!=nullptr) {
        delete [] elements_;
    }
    
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = new Type [capacity_];
    for (std::size_t i = 0; i<capacity_; i++) {
        elements_[i] = other.elements_[i];
    }
    return *this;
}

template <typename  Type>
bool vector_t<Type>::operator ==(vector_t const & other) const
{
    if(size_==other.size_){
        for (std::size_t i = 0; i<capacity_; i++) {
            if (elements_[i] != other.elements_[i]) return false ;
        }
        return true;
    }
    else return false;
}

template <typename  Type>
vector_t<Type>::~vector_t()
{
    if(elements_!=nullptr){
        delete [] elements_;
    }
}

template <typename  Type>
std::size_t vector_t<Type>::size() const
{
    return size_;
}

template <typename  Type>
std::size_t vector_t<Type>::capacity() const
{
    return capacity_;
}

template <typename  Type>
void vector_t<Type>::push_back( Type value )
{
    size_++;
    if (size_>capacity_) {
        if(!capacity_){
            capacity_=1;
        }
        else{
            capacity_*=2;
        }
        
        Type *elements = new Type [capacity_];
        for (std::size_t i = 0; i<size_-1; i++) {
            elements[i]=elements_[i];
        }
        elements[size_-1]=value;
        if (elements_!=nullptr) delete [] elements_;
        elements_=elements;
    }
    else elements_[size_-1]=value;
}

template <typename  Type>
void vector_t<Type>::pop_back()
{
    if(!size_) return;
    size_--;
    if (size_<=(capacity_/4)) {
        capacity_=capacity_/2;
        Type *elements =new Type [capacity_];
        for (std::size_t i = 0; i<size_; i++) {
            elements[i]=elements_[i];
        }
        if (elements_!=nullptr) delete [] elements_;
        elements_=elements;
    }
}

template <typename  Type>
Type & vector_t<Type>::operator [](std::size_t index)
{
    return elements_[index];
}

template <typename  Type>
Type vector_t<Type>::operator [](std::size_t index) const
{
    return elements_[index];
}

template <class  Type>
bool operator !=(vector_t<Type> const & lhs, vector_t<Type> const & rhs)
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

template<typename Type>
Type  vector_t<Type>::at(std::size_t index) const
{
    if(index>=size_){
        throw "Out of range";
    }
    return elements_[index];
}

template<typename Type>
Type& vector_t<Type>::at(std::size_t index)
{
    if(index>=size_){
        throw "Out of range";
    }
    return elements_[index];
}

