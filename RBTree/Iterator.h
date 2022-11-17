// Copyright 2022 mora

#pragma once

#include "RBNode.h"

template<class T>
class iterator {
public:
    iterator() = default;

    explicit iterator(rbTreeNode<T> * node) { _node = node; }

    bool operator==(const iterator &it) const { return it._node == _node; }

    bool operator==(const iterator &&it) const { return it._node == _node; }

    bool operator!=(const iterator &it) const { return it._node != _node; }

    bool operator!=(const iterator &&it) const { return it._node != _node; }

    T operator*() const { return _node->_data; }

    T *operator->() const { return &_node->_data; }

    iterator &operator++();

    iterator operator++(int) &;

    iterator &operator--();

    iterator operator--(int) &;

private:
    rbSupport _get_parent_direction_(rbTreeNode<T> * child);

    rbTreeNode<T> * _get_leftest_node_(rbTreeNode<T> * node);

    rbTreeNode<T> * _get_rightest_node_(rbTreeNode<T> * node);

    rbTreeNode<T> * _get_next_node_(rbTreeNode<T> * node);

    rbTreeNode<T> * _get_prev_node_(rbTreeNode<T> * node);

    rbTreeNode<T> * _node = nullptr;
};

template<class T>
iterator<T> &iterator<T>::operator++() {
    _node = _get_next_node_(_node);
    return *this;
}

template<class T>
iterator<T> iterator<T>::operator++(int) &{
    iterator tmp = iterator(_node);
    ++(*this);
    return tmp;
}

template<class T>
iterator<T> &iterator<T>::operator--() {
    _node = _get_prev_node_(_node);
    return *this;
}

template<class T>
iterator<T> iterator<T>::operator--(int) &{
    iterator tmp = iterator(_node);
    --(*this);
    return tmp;
}

template<class T>
rbSupport iterator<T>::_get_parent_direction_(rbTreeNode<T> * child) {
    return child->_parent->_l_child == child ?
           rbSupport::LEFT_CHILD : rbSupport::RIGHT_CHILD;
}

template<class T>
rbTreeNode<T> * iterator<T>::_get_leftest_node_(rbTreeNode<T> * node) {
    for (; node->_l_child != nullptr;) {
        node = node->_l_child;
    }
    return node;
}

template<class T>
rbTreeNode<T> * iterator<T>::_get_rightest_node_(rbTreeNode<T> * node) {
    for (; node->_r_child;) {
        node = node->_r_child;
    }
    return node;
}

template<class T>
rbTreeNode<T> * iterator<T>::_get_next_node_(rbTreeNode<T> * node) {
    if (node->_r_child != nullptr) {
        return _get_leftest_node_(node->_r_child);
    }
    for (; node->_parent;) {
        auto dir = _get_parent_direction_(node);
        node = node->_parent;
        if (dir == rbSupport::LEFT_CHILD) {
            return node;
        }
    }
    return nullptr;
}

template<class T>
rbTreeNode<T> * iterator<T>::_get_prev_node_(rbTreeNode<T> * node) {
    if (node->_l_child != nullptr) {
        return _get_rightest_node_(node->_l_child);
    }
    for (; node->_parent;) {
        auto dir = _get_parent_direction_(node);
        node = node->parent;
        if (dir == rbSupport::RIGHT_CHILD) {
            return node;
        }
    }
    return nullptr;
}
