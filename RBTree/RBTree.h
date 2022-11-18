// Copyright 2022 mora

#ifndef RBTREE_RBTREE_H_
#define RBTREE_RBTREE_H_

#include <iostream>

enum class rbSupport {
    RED,
    BLACK,
    LEFT_CHILD,
    RIGHT_CHILD
};

template<
        typename Key,
        class Compare = std::less<Key>,
        class Allocator  = std::allocator<Key>
>
class RBTree {
 public:
    class rbTreeNode {
    public:
        rbTreeNode() = default;
        rbTreeNode(Key data,
                   rbSupport color, rbTreeNode *parent, rbTreeNode *l_child, rbTreeNode *r_child);
        explicit rbTreeNode(rbSupport color) : _color(color) {};
        rbTreeNode(const Key &data, rbSupport color)
                : _data(data), _color(color), _parent(nullptr), _l_child(nullptr), _r_child(nullptr) {};
        rbTreeNode(const rbTreeNode &);
        rbTreeNode(rbTreeNode &&) noexcept;
        rbTreeNode &operator=(const rbTreeNode &);
        rbTreeNode &operator=(rbTreeNode &&) noexcept;
        ~rbTreeNode();

 public:

        Key _data;
        rbSupport _color;
        rbTreeNode *_parent;
        rbTreeNode *_l_child;
        rbTreeNode *_r_child;
    };

 public:
    using value_type = Key;
    using const_ref_type = const value_type &;
    using node_value_type = rbTreeNode;
    using const_node_value_type = const rbTreeNode;
    using node_pointer = rbTreeNode *;
    using const_node_pointer = const node_pointer;

 public:
    class iterator {
    public:
        iterator() = default;
        explicit iterator(node_pointer node) { _node = node; }
        iterator(const iterator &) = default;
        iterator(iterator &&) noexcept = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) noexcept = default;
        ~iterator() = default;
        bool operator==(const iterator &it) const { return it._node == _node; }
        bool operator==(const std::nullptr_t &it) const { return it == _node; }
        bool operator==(const iterator &&it) const { return it._node == _node; }
        bool operator!=(const iterator &it) const { return it._node != _node; }
        bool operator!=(const iterator &&it) const { return it._node != _node; }
        bool operator!=(const std::nullptr_t &it) const { return it != _node; }

        value_type operator*() const { return _node->_data; }
        value_type *operator->() const { return &_node->_data; }

        iterator &operator++();
        iterator operator++(int) &;
        iterator &operator--();
        iterator operator--(int) &;
        iterator right() { return iterator(_get_next_node_(_node)); };
        iterator left() { return iterator(_get_prev_node_(_node)); };

 private:
        rbSupport _get_parent_direction_(node_pointer child);
        node_pointer _get_leftest_node_(node_pointer node);
        node_pointer _get_rightest_node_(node_pointer node);
        node_pointer _get_next_node_(node_pointer node);
        node_pointer _get_prev_node_(node_pointer node);
        node_pointer _node = nullptr;
    };

public:
    RBTree() : _size(0), _root(nullptr), _header(new node_value_type) {}
    RBTree(const RBTree &);
    RBTree(RBTree &&) noexcept;
    RBTree(const RBTree *);
    RBTree &operator=(const RBTree &);
    RBTree &operator=(RBTree &&) noexcept;
    ~RBTree();

    void insert(const_ref_type data);
    void erase(const_ref_type data);
    size_t size();
    bool empty();
    void clear(node_pointer);
    iterator begin() const;
    iterator end() const;
    iterator find(const_ref_type) const;
    iterator lower_bound(const_ref_type) const;
    bool ge(const Key &l, const Key &r) const;
    bool gt(const Key &l, const Key &r) const;
    bool le(const Key &l, const Key &r) const;
    bool lt(const Key &l, const Key &r) const;
    bool eq(const Key &l, const Key &r) const;

    Compare cmp = Compare();
 private:

    void _insert_(node_pointer parent, rbSupport parent_child_tag, node_pointer current, const_ref_type data);
    void _erase_(node_pointer parent, rbSupport parent_child_tag, node_pointer current_node, const_ref_type data);
    void _insert_handle_balance_(node_pointer current);
    void _erase_handle_balance_(node_pointer parent, node_pointer current);
    node_pointer _turn_right_(node_pointer current);
    node_pointer _turn_left_(node_pointer current);

    size_t _size = 0;
    node_pointer _root;
    node_pointer _header;
};

template<typename Key, class Compare, class Allocator>
bool RBTree<Key, Compare, Allocator>
        ::ge(const Key &l, const Key &r) const {
    return !cmp(l, r);
}

template<typename Key, class Compare, class Allocator>
bool RBTree<Key, Compare, Allocator>
        ::gt(const Key &l, const Key &r) const {
    return cmp(r, l);
}

template<typename Key, class Compare, class Allocator>
bool RBTree<Key, Compare, Allocator>
        ::le(const Key &l, const Key &r) const {
    return !gt(l, r);
}

template<typename Key, class Compare, class Allocator>
bool RBTree<Key, Compare, Allocator>
        ::lt(const Key &l, const Key &r) const {
    return cmp(l, r);
}

template<typename Key, class Compare, class Allocator>
bool RBTree<Key, Compare, Allocator>
        ::eq(const Key &l, const Key &r) const {
    return !(cmp(l, r) || cmp(r, l));
}

template<class Key, class Compare, class Allocator>
bool operator<(typename RBTree<Key, Compare, Allocator>
        ::const_node_value_type &c1,
               typename RBTree<Key, Compare, Allocator>
                       ::const_node_value_type &c2) {
    return cmp(c1._data, c2._data);
}

template<class Key, class Compare, class Allocator>
bool operator==(typename RBTree<Key, Compare, Allocator>
        ::const_node_value_type &c1,
                typename RBTree<Key, Compare, Allocator>
                        ::const_node_value_type &c2) {
    return !((c1 < c2) || (c2 < c1));
}

template<class Key, class Compare, class Allocator>
bool operator!=(typename RBTree<Key, Compare, Allocator>
        ::const_node_value_type &c1,
                typename RBTree<Key, Compare, Allocator>
                        ::const_node_value_type &c2) {
    return !(operator==(c1, c2));
}

template<class Key, class Compare, class Allocator>
bool operator>(typename RBTree<Key, Compare, Allocator>
        ::const_node_value_type &c1,
               typename RBTree<Key, Compare, Allocator>
                       ::const_node_value_type &c2) {
    return operator<(c2, c1);
}

template<class Key, class Compare, class Allocator>
bool operator<=(typename RBTree<Key, Compare, Allocator>
        ::const_node_value_type &c1,
                typename RBTree<Key, Compare, Allocator>
                        ::const_node_value_type &c2) {
    return !(operator>(c1, c2));
}

template<class Key, class Compare, class Allocator>
bool operator>=(typename RBTree<Key, Compare, Allocator>
        ::const_node_value_type &c1,
                typename RBTree<Key, Compare, Allocator>
                        ::const_node_value_type &c2) {
    return !(operator<(c1, c2));
}

template<class Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::RBTree(const RBTree &other) : RBTree() {
    for (auto it: other) {
        insert(it);
    }
}

template<class Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::RBTree(RBTree &&other) noexcept
: RBTree(other) {
    other._size = 0;
    other = nullptr;
}

template<class Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::RBTree(const RBTree *other)
: RBTree(*other) {
}

template<class Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator> &RBTree<Key, Compare, Allocator>
::operator=(const RBTree &other) {
    if (&other == this) {
        return *this;
    }

    clear(_root);
    _size = 0;

    for (auto &it: other) {
        insert(it);
    }
    return *this;
}

template<typename Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator> &RBTree<Key, Compare, Allocator>
::operator=(RBTree &&other) noexcept {

    *this = other;

    other._root = nullptr;
    other._size = 0;
}

template<class Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::~RBTree() {
    for (; _root != nullptr;) {
        erase(_root->_data);
    }
    delete _header;
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::insert(const_ref_type data) {
    if (_root == nullptr) {
        _root = new node_value_type(data, rbSupport::BLACK);
        _header->_l_child = _header->_r_child = _root;
        _root->_parent = _header;
        _size++;
        return;
    }

    return _insert_(nullptr,
                    rbSupport::LEFT_CHILD, _root, data);
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::_insert_(
        RBTree::node_pointer parent,
        rbSupport parent_child_tag,
        RBTree::node_pointer current,
        const_ref_type data) {
    if (current == nullptr) {
        current = new node_value_type(data, rbSupport::RED);
        parent_child_tag == rbSupport
        ::LEFT_CHILD ? parent->_l_child = current : parent->_r_child = current;
        current->_parent = parent;
        if (parent->_color == rbSupport::RED) {
            _insert_handle_balance_(current);
        }
        _size++;
        return;
    } else if (lt(current->_data, data)) {
        return _insert_(current,
                        rbSupport
                        ::RIGHT_CHILD, current->_r_child, data);
    } else if (gt(current->_data, data)) {
        return _insert_(current,
                        rbSupport
                        ::LEFT_CHILD, current->_l_child, data);
    } else {
        return;
    }
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::_insert_handle_balance_(node_pointer current) {
    for (; current->_parent != _header && current->_parent->_parent != _header &&
           current->_parent->_color == rbSupport::RED;) {
        auto parent = current->_parent;
        auto gParent = parent->_parent;
        auto uncle = (gParent->_l_child == parent ? gParent->_r_child
                : gParent->_l_child);

        if (gParent->_l_child == parent) {
            if (uncle && uncle != _header && uncle->_color == rbSupport::RED) {
                parent->_color = uncle->_color = rbSupport::BLACK;
                gParent->_color = rbSupport::RED;
                current = gParent;
            } else {
                if (parent->_r_child == current) {
                    _turn_left_(parent);
                    std::swap(current, parent);
                }
                parent->_color = rbSupport::BLACK;
                gParent->_color = rbSupport::RED;
                _turn_right_(gParent);
            }
        } else {
            if (uncle && uncle != _header && uncle->_color == rbSupport::RED) {
                parent->_color = uncle->_color = rbSupport::BLACK;
                gParent->_color = rbSupport::RED;
                current = gParent;
            } else {
                if (parent->_l_child == current) {
                    _turn_right_(parent);
                    std::swap(current, parent);
                }
                parent->_color = rbSupport::BLACK;
                gParent->_color = rbSupport::RED;
                _turn_left_(gParent);
            }
        }
    }
    _root->_color = rbSupport::BLACK;
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::erase(const_ref_type data) {
    if (_root == nullptr) {
        return;
    }

    return _erase_(nullptr, rbSupport
    ::LEFT_CHILD, _root, data);
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::_erase_(
        RBTree::node_pointer parent,
        rbSupport parent_child_tag,
        RBTree::node_pointer current_node,
        const_ref_type data) {
    if (current_node == nullptr) {
        return;
    } else if (eq(current_node->_data, data)) {
        node_pointer tmp_nil = nullptr;
        auto delete_node_color = current_node->_color;
        node_pointer &ref_p = (parent ?
                               (parent_child_tag == rbSupport
                               ::LEFT_CHILD ? parent->_l_child : parent->_r_child)
                                      : _root);

        if (current_node->_l_child && current_node->_r_child) {
            auto prev = current_node->_l_child;
            auto curr = prev;
            for (; curr && curr->_r_child; prev = curr, curr = curr->_r_child);
            delete_node_color = curr->_color;
            if (curr == prev) {
                current_node->_data = curr->_data;
                current_node->_l_child = curr->_l_child;

                if (curr->_l_child) {
                    curr->_l_child->_parent = current_node;
                }

                parent = current_node;
                current_node = current_node->_l_child;
                parent_child_tag = rbSupport::LEFT_CHILD;
                delete curr;
            } else {
                current_node->_data = curr->_data;
                parent = prev;
                parent_child_tag = rbSupport::RIGHT_CHILD;
                current_node = prev->_r_child = curr->_l_child;
                if (curr->_l_child) {
                    curr->_l_child->_parent = prev;
                }
                delete curr;
            }
        } else if (current_node->_l_child) {
            ref_p = current_node->_l_child;
            current_node->_l_child->_parent = parent;
            delete current_node;
            current_node = ref_p;
        } else if (current_node->_r_child) {
            ref_p = current_node->_r_child;
            current_node->_r_child->_parent = parent;
            delete current_node;
            current_node = ref_p;
        } else {
            delete current_node;
            current_node = ref_p = nullptr;
        }

        if (delete_node_color == rbSupport::BLACK && parent) {
            if (current_node == nullptr) {
                tmp_nil = current_node = new node_value_type(rbSupport::BLACK);
                current_node->_parent = parent;
                parent_child_tag == rbSupport
                ::LEFT_CHILD ? parent->_l_child = current_node
                        : parent->_r_child = current_node;
            }

            _erase_handle_balance_(parent, current_node);

            if (tmp_nil) {
                if (tmp_nil->_parent->_l_child == tmp_nil) {
                    tmp_nil->_parent->_l_child = nullptr;
                } else {
                    tmp_nil->_parent->_r_child = nullptr;
                }
                delete tmp_nil;
            }
        }
        _size--;
        return;
    } else if (data < current_node->_data) {
        return _erase_(current_node,
                       rbSupport::LEFT_CHILD,
                       current_node->_l_child, data);
    } else {
        return _erase_(current_node,
                       rbSupport::RIGHT_CHILD,
                       current_node->_r_child, data);
    }
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::_erase_handle_balance_(
        RBTree::node_pointer parent,
        RBTree::node_pointer current_node) {
    for (; (current_node == _header || current_node->_color
                                       == rbSupport::BLACK)
                                       && current_node != _root;) {
        if (current_node == parent->_l_child) {
            auto tmp = parent->_r_child;
            if (tmp && tmp->_color == rbSupport::RED) {
                tmp->_color = rbSupport::BLACK;
                parent->_color = rbSupport::RED;
                _turn_left_(parent);
                tmp = parent->_r_child;
            }

            if ((tmp->_l_child == nullptr || tmp->_l_child->_color
            == rbSupport::BLACK)
            && (tmp->_r_child == nullptr || tmp->_r_child->_color
            == rbSupport::BLACK)) {
                tmp->_color = rbSupport::RED;
                current_node = parent;
                parent = current_node->_parent;
            } else {
                if (tmp->_r_child == nullptr || tmp->_r_child->_color
                == rbSupport::BLACK) {
                    tmp->_l_child ? tmp->_l_child->_color = rbSupport
                            ::BLACK : rbSupport::RED;
                    tmp->_color = rbSupport::RED;
                    _turn_right_(tmp);
                    tmp = parent->_r_child;
                }

                tmp->_color = parent->_color;
                parent->_color = rbSupport::BLACK;
                tmp->_r_child->_color = rbSupport::BLACK;
                _turn_left_(parent);
                current_node = _root;
            }
        } else {
            auto tmp = parent->_l_child;
            if (tmp && tmp->_color == rbSupport::RED) {
                tmp->_color = rbSupport::BLACK;
                parent->_color = rbSupport::RED;
                _turn_right_(parent);
                tmp = parent->_r_child;
            }
            if ((tmp->_l_child == nullptr || tmp->_l_child->_color
            == rbSupport::BLACK)
            && (tmp->_r_child == nullptr || tmp->_r_child->_color
            == rbSupport::BLACK)) {
                tmp->_color = rbSupport::RED;
                current_node = parent;
                parent = current_node->_parent;
            } else {
                if (tmp->_l_child == nullptr || tmp->_l_child->_color
                == rbSupport::BLACK) {
                    tmp->_r_child ? tmp->_r_child->_color
                    = rbSupport::BLACK : rbSupport::RED;
                    tmp->_color = rbSupport::RED;
                    _turn_left_(tmp);
                    tmp = parent->_l_child;
                }

                tmp->_color = parent->_color;
                parent->_color = rbSupport::BLACK;
                tmp->_l_child->_color = rbSupport::BLACK;
                _turn_right_(parent);
                current_node = _root;
            }
        }
    }
    current_node->_color = rbSupport::BLACK;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>::node_pointer
RBTree<Key, Compare, Allocator>
        ::_turn_right_(RBTree::node_pointer current) {
    auto left_child = current->_l_child;
    current->_l_child = left_child->_r_child;

    if (left_child->_r_child) {
        left_child->_r_child->_parent = current;
    }

    left_child->_parent = current->_parent;
    if (current->_parent == _header) {
        _root = left_child;
        _header->_l_child = _header->_r_child = _root;
    } else if (current->_parent->_l_child == current) {
        current->_parent->_l_child = left_child;
    } else {
        current->_parent->_r_child = left_child;
    }

    left_child->_r_child = current;
    current->_parent = left_child;

    return left_child;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>::node_pointer
RBTree<Key, Compare, Allocator>
        ::_turn_left_(RBTree::node_pointer current) {
    auto right_child = current->_r_child;
    current->_r_child = right_child->_l_child;

    if (right_child->_l_child) {
        right_child->_l_child->_parent = current;
    }

    right_child->_parent = current->_parent;
    if (current->_parent == _header) {
        _root = right_child;
        _header->_l_child = _header->_r_child = _root;
    } else if (current->_parent->_l_child == current) {
        current->_parent->_l_child = right_child;
    } else {
        current->_parent->_r_child = right_child;
    }

    right_child->_l_child = current;
    current->_parent = right_child;

    return right_child;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator RBTree<Key, Compare, Allocator>::begin() const {
    if (!_root) {
        return iterator(_header);
    }
    node_pointer node = _root;
    for (; node->_l_child != nullptr;) {
        node = node->_l_child;
    }
    return iterator(node);
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator RBTree<Key, Compare, Allocator>::end() const {
    return iterator(_header);
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator RBTree<Key, Compare, Allocator>::find(const_ref_type target) const {
    auto node = _root;
    for (; node;) {
        if (lt(node->_data, target)) {
            node = node->_r_child;
        } else if (gt(node->_data, target)) {
            node = node->_l_child;
        } else {
            return iterator(node);
        }
    }
    return end();
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>::iterator
RBTree<Key, Compare, Allocator>
::lower_bound(const_ref_type target) const {
    auto curr = begin();
    auto prev = end();
    for (; curr != nullptr && curr != prev;) {
        if (*curr < target) {
            curr = curr.right();
        } else {
            prev = curr;
            curr = curr.left();
        }
    }
    return prev;
}


template<class Key, class Compare, class Allocator>
size_t RBTree<Key, Compare, Allocator>::size() {
    return _size;
}

template<class Key, class Compare, class Allocator>
bool RBTree<Key, Compare, Allocator>::empty() {
    return _size == 0;
}

template<class Key, class Compare, class Allocator>
void RBTree<Key, Compare, Allocator>::clear(node_pointer node) {
    if (node == nullptr) {
        return;
    }
    clear(node->_l_child);
    clear(node->_r_child);
    delete node;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator &RBTree<Key, Compare, Allocator>::iterator::operator++() {
    _node = _get_next_node_(_node);
    return *this;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator RBTree<Key, Compare, Allocator>::iterator::operator++(int) &{
    iterator tmp = iterator(_node);
    ++(*this);
    return tmp;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator &RBTree<Key, Compare, Allocator>::iterator::operator--() {
    if (_node->_parent == nullptr) {
        _node = _get_rightest_node_(_node->_l_child);
    } else {
        _node = _get_prev_node_(_node);
    }
    return *this;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
::iterator RBTree<Key, Compare, Allocator>::iterator::operator--(int) &{
    iterator tmp = iterator(_node);
    --(*this);
    return tmp;
}

template<class Key, class Compare, class Allocator>
rbSupport RBTree<Key, Compare, Allocator>
::iterator::_get_parent_direction_(node_pointer child) {
    return child->_parent->_l_child == child ?
           rbSupport::LEFT_CHILD : rbSupport::RIGHT_CHILD;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
        ::node_pointer RBTree<Key, Compare, Allocator>
::iterator::_get_leftest_node_(node_pointer node) {
    for (; node->_l_child != nullptr;) {
        node = node->_l_child;
    }
    return node;
}


template<typename Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
        ::node_pointer RBTree<Key, Compare, Allocator>
::iterator::_get_rightest_node_(RBTree::node_pointer node) {
    for (; node->_r_child;) {
        node = node->_r_child;
    }
    return node;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
        ::node_pointer RBTree<Key, Compare, Allocator>
::iterator::_get_next_node_(node_pointer node) {
    if (node->_r_child != nullptr) {
        return _get_leftest_node_(node->_r_child);
    }
    for (; node->_parent != nullptr;) {
        auto dir = _get_parent_direction_(node);
        node = node->_parent;
        if (dir == rbSupport::LEFT_CHILD) {
            return node;
        }
    }
    return nullptr;
}

template<class Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
        ::node_pointer RBTree<Key, Compare, Allocator>
::iterator::_get_prev_node_(node_pointer node) {
    if (node->_l_child != nullptr) {
        return _get_rightest_node_(node->_l_child);
    }
    for (; node->_parent != nullptr;) {
        auto dir = _get_parent_direction_(node);
        node = node->_parent;
        if (dir == rbSupport::RIGHT_CHILD) {
            return node;
        }
    }
    return nullptr;
}

template<typename Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::rbTreeNode::rbTreeNode(
        Key data,
        rbSupport color,
        RBTree::rbTreeNode *parent,
        RBTree::rbTreeNode *l_child,
        RBTree::rbTreeNode *r_child):
        _data(data),
        _color(color),
        _parent(parent),
        _l_child(l_child),
        _r_child(r_child) {
}

template<typename Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::rbTreeNode
::rbTreeNode(const rbTreeNode &other)
        : _data(other._data),
          _color(other._color),
          _parent(other._parent),
          _l_child(other._l_child),
          _r_child(other._r_child) {
}

template<typename Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::rbTreeNode
::rbTreeNode(rbTreeNode &&other) noexcept
        : rbTreeNode(other) {
    delete other;
    other = nullptr;
}

template<typename Key, class Compare, class Allocator>
RBTree<Key, Compare, Allocator>::rbTreeNode
::~rbTreeNode() {
    _parent = nullptr;
    _l_child = nullptr;
    _r_child = nullptr;
}

template<typename Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
        ::rbTreeNode &RBTree<Key, Compare, Allocator>
::rbTreeNode::operator=(const RBTree::rbTreeNode &other) {
    _data = other._data;
    _color = other._color;
    _parent = other._parent;
    _l_child = other._l_child;
    _r_child = other._r_child;
}

template<typename Key, class Compare, class Allocator>
typename RBTree<Key, Compare, Allocator>
        ::rbTreeNode &RBTree<Key, Compare, Allocator>
::rbTreeNode::operator=(rbTreeNode &&other) noexcept {
    *this = other;

    other._parent = nullptr;
    other._l_child = nullptr;
    other._r_child = nullptr;
}

#endif //RBTREE_RBTREE_H_
