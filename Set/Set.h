// Copyright 2022 mora

#include "RBTree.h"

#include <iostream>

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>> class Set {
    public:
    Set();
    Set(const Set& other);
    Set(Set&& other);
    Set(const std::initializer_list<Key>& elems);
    template <typename Iterator> Set(Iterator first, Iterator last);
    ~Set();

    void insert(const Key&);
    void erase(const Key&);
    auto begin() const;
    auto end() const;
    auto find(const Key&) const;
    auto lower_bound(const Key&) const;
    auto size() const;
    auto empty() const;

    Set& operator=(const Set&);
    Set& operator=(const Set&&) noexcept;

    private:
    RBTree<Key>* _tree;
};

template <class Key, class Compare, class Allocator> Set<Key, Compare, Allocator>::Set() { _tree = new RBTree<Key>(); }

template <class Key, class Compare, class Allocator> Set<Key, Compare, Allocator>::Set(const Set& other) {
    _tree = new RBTree<Key>(other._tree);
}

template <class Key, class Compare, class Allocator> Set<Key, Compare, Allocator>::Set(Set&& other) {
    _tree = new RBTree<Key>(std::move(other._tree));
}

template <class Key, class Compare, class Allocator>
Set<Key, Compare, Allocator>::Set(const std::initializer_list<Key>& elems) : Set() {
    for (auto& it : elems) {
        insert(it);
    }
}

template <class Key, class Compare, class Allocator>
template <typename Iterator>
Set<Key, Compare, Allocator>::Set(const Iterator first, const Iterator last) : Set() {
    for (Iterator it = first; it != last; ++it) {
        insert(*it);
    }
}

template <class Key, class Compare, class Allocator> Set<Key, Compare, Allocator>::~Set() {
    delete _tree;
    _tree = nullptr;
}

template <class Key, class Compare, class Allocator> void Set<Key, Compare, Allocator>::insert(const Key& value) {
    return _tree->insert(value);
}

template <class Key, class Compare, class Allocator> void Set<Key, Compare, Allocator>::erase(const Key& value) {
    return _tree->erase(value);
}

template <class Key, class Compare, class Allocator> auto Set<Key, Compare, Allocator>::begin() const {
    return _tree->begin();
}

template <class Key, class Compare, class Allocator> auto Set<Key, Compare, Allocator>::end() const {
    return _tree->end();
}

template <class Key, class Compare, class Allocator> auto Set<Key, Compare, Allocator>::find(const Key& value) const {
    return _tree->find(value);
}

template <class Key, class Compare, class Allocator>
auto Set<Key, Compare, Allocator>::lower_bound(const Key& value) const {
    return _tree->lower_bound(value);
}

template <class Key, class Compare, class Allocator> auto Set<Key, Compare, Allocator>::size() const {
    return _tree->size();
}

template <class Key, class Compare, class Allocator> auto Set<Key, Compare, Allocator>::empty() const {
    return _tree->empty();
}

template <class Key, class Compare, class Allocator>
Set<Key, Compare, Allocator>& Set<Key, Compare, Allocator>::operator=(const Set& other) {
    if (&other == this) {
        return *this;
    }

    delete _tree;
    _tree = new RBTree<Key>(other._tree);
    return *this;
}

template <class Key, class Compare, class Allocator>
Set<Key, Compare, Allocator>& Set<Key, Compare, Allocator>::operator=(const Set&& other) noexcept {
    _tree->operator=(std::move(other._tree));
    return *this;
}
