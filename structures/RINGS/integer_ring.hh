#ifndef INTEGER_RING_H
#define INTEGER_RING_H

#include <iostream>
#include <memory>
#include <utility>
#include <cstddef>

namespace huc{

/**
 * @brief Arbitrary Precision Integers, following RingElement Concept
 * @author Huck Kim
 * @since Sat Oct 24 2020
 */
class Integer{
    struct Node{
        typedef std::unique_ptr<Node> NodePtr;
        int data;
        NodePtr next;
        Node *prev;

        Node(int data, NodePtr next, Node *prev);
        ~Node();
        Node(const Node &other);
        Node(Node &&other);
        Node &operator=(const Node &other);
        Node &operator=(Node &&other);
    };
    std::unique_ptr<Node> num = nullptr;
    Node *end_nde = nullptr;
    bool sign = true;
    size_t n = 0;
public:
    Integer();
    Integer(std::initializer_list<int> lst);
    Integer(std::string s);
    Integer(const Integer &other);
    Integer(Integer &&other);
    Integer &operator=(const Integer &other);
    Integer &operator=(Integer &&other);
    ~Integer();

    class iterator{
        Node *nde;
        iterator(Node *nde);
    public:
        int &operator*();
        iterator &operator++();
        bool operator==(const iterator &other) const noexcept;
        bool operator!=(const iterator &other) const noexcept;

        friend class Integer;
    };

    class const_iterator{
        Node *nde;
        const_iterator(Node *nde);
    public:
        const int &operator*() const;
        const_iterator &operator++();
        bool operator==(const const_iterator &other) const noexcept;
        bool operator!=(const const_iterator &other) const noexcept;

        friend class Integer;
    };

    class reverse_iterator{
        Node *nde;
        reverse_iterator(Node *nde);
    public:
        int &operator*();
        reverse_iterator &operator++();
        bool operator==(const reverse_iterator &other) const noexcept;
        bool operator!=(const reverse_iterator &other) const noexcept;
        
        friend class Integer;
    };
    
    class const_reverse_iterator{
        Node *nde;
        const_reverse_iterator(Node *nde);
    public:
        const int &operator*() const;
        const_reverse_iterator &operator++();
        bool operator==(const const_reverse_iterator &other) const noexcept;
        bool operator!=(const const_reverse_iterator &other) const noexcept;

        friend class Integer;
    };

    Integer &operator+=(const Integer &other);
    Integer &operator-(const Integer &other);
    Integer &operator-=(const Integer &other);
    Integer &operator*=(const Integer &other);

    bool operator==(const Integer &other) const;
    bool operator<(const Integer &other) const;
    bool operator<=(const Integer &other) const;
    bool operator>(const Integer &other) const;
    bool operator>=(const Integer &other) const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    void push_front(int data);
    void pop_front();

    void push_back(int data);
    void pop_back();

    size_t length() const noexcept;
    bool empty() const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Integer &a);
};

std::ostream &operator<<(std::ostream &os, const Integer &a);

Integer add(const Integer &a, const Integer &b);
Integer sub(const Integer &a, const Integer &b);

Integer operator+(const Integer &a, const Integer &b);
Integer operator-(const Integer &a, const Integer &b);
Integer operator*(const Integer &a, const Integer &b);

}

#endif
