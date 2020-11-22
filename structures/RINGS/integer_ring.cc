#include "integer_ring.hh"

#include <iomanip>

#define INT_BASE 1000000000
#define INT_BASE_LEN 9

namespace huc{

Integer::Node::Node(int data, NodePtr next, Node* prev): data{data}, next{std::move(next)}, prev{prev}{

}

Integer::Node::~Node(){}

Integer::Node::Node(const Node &other):data{other.data}, next{other.next? std::make_unique<Node>(*other.next):nullptr}{
    if(next){
        next->prev = this;
    }
}

Integer::Node::Node(Node &&other):data{other.data}, next{std::move(other.next)}, prev{other.prev}{
    other.next = nullptr;
}

Integer::Node &Integer::Node::operator=(const Node &other){
    Node tmp = other;
    std::swap(data, tmp.data);
    std::swap(next, tmp.next);
    return *this;
}

Integer::Node &Integer::Node::operator=(Node &&other){
    std::swap(next, other.next);
    std::swap(data, other.data);
    return *this;
}

Integer::Integer(){}

Integer::Integer(std::initializer_list<int> lst):sign{true}{
    for(auto a : lst){
        push_back(a);
    }
}

Integer::Integer(std::string s){
    size_t len = s.length()/INT_BASE_LEN;
    size_t b = s.length() - INT_BASE_LEN*len;
    std::stringstream ss;
    if(b){
        push_front(std::stoi(s.substr(0,b)));
        s = s.substr(b);
    }
    for(size_t i = 0; i < len; ++i){
        push_front(std::stoi(s.substr(0,INT_BASE_LEN)));
        s = s.substr(INT_BASE_LEN);
    }
}

Integer::Integer(const Integer &other):num{std::make_unique<Node>(*other.num)},sign{other.sign}, n{other.n} {
    Node *tmp = num.get();
    while(tmp && tmp->next){
        tmp = tmp->next.get();
    }
    end_nde = tmp;
}

Integer::Integer(Integer &&other): num{std::move(other.num)}, end_nde{other.end_nde}, sign{other.sign}, n{other.n} {}

Integer &Integer::operator=(const Integer &other){
    Integer tmp;
    std::swap(num, tmp.num);
    std::swap(end_nde, tmp.end_nde);
    std::swap(sign, tmp.sign);
    std::swap(n, tmp.n);
    return *this;
}
Integer &Integer::operator=(Integer &&other){
    std::swap(num, other.num);
    std::swap(end_nde, other.end_nde);
    std::swap(sign, other.sign);
    std::swap(n, other.n);
    return *this;
}

Integer::~Integer(){}

Integer::iterator::iterator(Node* nde):nde{nde} {}
int &Integer::iterator::operator*(){ return nde->data; }
Integer::iterator &Integer::iterator::operator++(){
    nde = nde->next.get();
    return *this;
}
bool Integer::iterator::operator==(const iterator &other) const noexcept { return other.nde == nde; }
bool Integer::iterator::operator!=(const iterator &other) const noexcept { return other.nde != nde; }

Integer::const_iterator::const_iterator(Node* nde):nde{nde} {}
const int &Integer::const_iterator::operator*() const { return nde->data; }
Integer::const_iterator &Integer::const_iterator::operator++(){
    nde = nde->next.get();
    return *this;
}
bool Integer::const_iterator::operator==(const const_iterator &other) const noexcept { return other.nde == nde;}
bool Integer::const_iterator::operator!=(const const_iterator &other) const noexcept { return other.nde != nde;}

Integer::reverse_iterator::reverse_iterator(Node *nde):nde{nde} {}
int &Integer::reverse_iterator::operator*() { return nde->data; }
Integer::reverse_iterator &Integer::reverse_iterator::operator++(){
    nde = nde->prev;
    return *this;
}
bool Integer::reverse_iterator::operator==(const reverse_iterator &other) const noexcept { return other.nde == nde; }
bool Integer::reverse_iterator::operator!=(const reverse_iterator &other) const noexcept { return other.nde != nde; }

Integer::const_reverse_iterator::const_reverse_iterator(Node *nde):nde{nde} {}
const int &Integer::const_reverse_iterator::operator*() const { return nde->data; }
Integer::const_reverse_iterator &Integer::const_reverse_iterator::operator++(){
    nde = nde->prev;
    return *this;
}
bool Integer::const_reverse_iterator::operator==(const const_reverse_iterator &other) const noexcept { return other.nde == nde; }
bool Integer::const_reverse_iterator::operator!=(const const_reverse_iterator &other) const noexcept { return other.nde != nde; }

Integer::iterator Integer::begin() noexcept { return iterator{num.get()}; }
Integer::iterator Integer::end() noexcept { return iterator{nullptr}; }
Integer::const_iterator Integer::begin() const noexcept { return const_iterator{num.get()}; }
Integer::const_iterator Integer::end() const noexcept { return const_iterator{nullptr}; }

Integer::reverse_iterator Integer::rbegin() noexcept { return reverse_iterator{end_nde}; }
Integer::reverse_iterator Integer::rend() noexcept { return reverse_iterator{nullptr}; }
Integer::const_reverse_iterator Integer::rbegin() const noexcept { return const_reverse_iterator{end_nde}; }
Integer::const_reverse_iterator Integer::rend() const noexcept { return const_reverse_iterator{nullptr}; }

void Integer::push_front(int data){
    if(num){
        num = std::make_unique<Node>(Node(data, std::move(num), nullptr));
        num->next.get()->prev = num.get();
    }
    else{
        num = std::make_unique<Node>(Node(data,nullptr, nullptr));
        end_nde = num.get();
    }
    ++n;
}

void Integer::pop_front(){
    if(end_nde == num.get()){
        end_nde = nullptr;
    }
    std::unique_ptr<Node> tmp = std::move(num);
    num = std::move(tmp->next);
    if(num){
        num->prev = nullptr;
    }
    --n;
}

void Integer::push_back(int data){
    if(end_nde){
        end_nde->next = std::make_unique<Node>(Node(data, nullptr, end_nde));
        end_nde = end_nde->next.get();
    }
    else{
        num = std::make_unique<Node>(Node(data, nullptr, nullptr));
        end_nde = num.get();
    }
    ++n;
}

void Integer::pop_back(){
    if(end_nde == num.get()){
        std::unique_ptr<Node> tmp = std::move(num);
    }
    else{
        std::unique_ptr<Node> tmp = std::move(end_nde->prev->next);
        end_nde = end_nde->prev;
    }
    --n;
}

size_t Integer::length() const noexcept { return n; }

bool Integer::empty() const noexcept { return begin() == end(); }


// Requires a and b to be both non-negative
Integer add(const Integer &a, const Integer &b){
    Integer n_int; 
    auto a_it = a.begin();
    auto b_it = b.begin();
    int carry = 0;
    int normed = 0;
    int sum = 0;
    while(a_it != a.end() || b_it != b.end()){
        if(a_it == a.end()){
            sum = *b_it + carry;
            ++b_it;
        }
        else if(b_it == b.end()){
            sum = *a_it + carry;
            ++a_it;
        }
        else{
            sum = *a_it + *b_it + carry;
            ++a_it;
            ++b_it;
        }
        normed = sum % INT_BASE; 
        carry = sum / INT_BASE;
        n_int.push_back(normed);
    }
    return n_int;
}


// Requires a and b to be both non-negative and  a >= b
Integer sub(const Integer &a, const Integer &b){
    Integer n_int;
    auto a_it = a.begin();
    auto b_it = b.begin();
    int diff = 0;
    int normed = 0;
    int borrow = 0;
    while(a_it != a.end()){
        if(b_it == b.end()){
            diff = *a_it + borrow;
            ++a_it;
        }
        else{
            diff = *a_it - *b_it + borrow;
            ++a_it;
            ++b_it;
        }
        if(diff < 0){
            borrow = -1;
            normed = diff + INT_BASE;
        }
        else{
            borrow = 0;
            normed = diff;
        }
        n_int.push_back(normed);
    }
    // remove leading 0
    auto chk = n_int.rbegin();
    while(chk != n_int.rend()){
        auto it = n_int.rbegin();
        if(*it == 0){
            n_int.pop_back();
        }
        else break;
        chk = n_int.rbegin();
    }
    
    return n_int;
}

// Requires a and b to be both non-negative
Integer mult(const Integer &a, const Integer &b){

}

Integer operator+(const Integer &a, const Integer &b){

}
Integer operator-(const Integer &a, const Integer &b){

}
Integer operator*(const Integer &a, const Integer &b){

}

Integer &Integer::operator+=(const Integer &other){
    return *this;
}
bool Integer::operator==(const Integer &other)const {
    if(n != other.n) return false;
    else{
        auto a_it = begin();
        auto b_it = other.begin();
        while(a_it != end()){
            if(*a_it != *b_it) return false;
            ++a_it;
            ++b_it;
        }
        return true;
    }
}

bool Integer::operator<(const Integer &other) const{
    if(n < other.n) return true;
    else{
        auto a_it = begin();
        auto b_it = other.begin();
        while(a_it != end()){
            if(*a_it < *b_it) return true;
            else if(*a_it > *b_it) return false;
            ++a_it;
            ++b_it;
        }
        return false;
    }
}
bool Integer::operator<=(const Integer &other) const{
    if(n < other.n) return true;
    else{
        auto a_it = begin();
        auto b_it = other.begin();
        while(a_it != end()){
            if(*a_it < *b_it) return true;
            else if(*a_it > *b_it) return false;
            ++a_it;
            ++b_it;
        }
        return true;
    }
}
bool Integer::operator>(const Integer &other) const{
    if(n > other.n) return true;
    else{
        auto a_it = begin();
        auto b_it = other.begin();
        while(a_it != end()){
            if(*a_it > *b_it) return true;
            else if(*a_it < *b_it) return false;
            ++a_it;
            ++b_it;
        }
        return false;
    }
}
bool Integer::operator>=(const Integer &other)const{
    if(n > other.n) return true;
    else{
        auto a_it = begin();
        auto b_it = other.begin();
        while(a_it != end()){
            if(*a_it > *b_it) return true;
            else if(*a_it < *b_it) return false;
            ++a_it;
            ++b_it;
        }
        return true;
    }
}

std::ostream &operator<<(std::ostream &os, const Integer &a){
    if(a.empty()){
        os<<"0";
    }
    else{
        bool first = true;
        for(auto it = a.rbegin(); it != a.rend(); ++it){
            if(first){
                os<<*it;
                first = false;
            }
            else{
                os<<std::internal<<std::setfill('0')<<std::setw(INT_BASE_LEN)<<*it;
            }
        }
    }
    return os;
}

}
