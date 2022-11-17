// Copyright 2022 mora

#ifndef TP2022_CPP_SET_RBTREE_H
#define TP2022_CPP_SET_RBTREE_H

#include "RBNode.h"
#include "Iterator.h"

template<typename T>
class RBTree {
public:
    using value_type = T;
    using const_ref_type = const value_type &;
    using node_value_type = rbTreeNode<T>;
    using node_pointer = rbTreeNode<T> *;
    using const_node_pointer = const node_pointer;

public:
    RBTree() : _root(nullptr) {}

    ~RBTree();

    int insert(const_ref_type data);

    int erase(const_ref_type data);

    iterator<T> begin() const;

    iterator<T> end() const;

    iterator<T> find(const_ref_type) const;

    iterator<T> lower_bound(const_ref_type) const;

    void show(struct node **_node, int count);

    void searchUnit(int data, struct node *_node);

    int inorder(struct node *_node);

    int preorder(struct node *_node);

    int postorder(struct node *_node);

private:

    int _insert_(node_pointer parent, rbSupport parent_child_tag, node_pointer current, const_ref_type data);

    int _erase_(node_pointer parent, rbSupport parent_child_tag, node_pointer current_node, const_ref_type data);

    void _insert_handle_balance_(node_pointer current);

    void _erase_handle_balance_(node_pointer current);

    node_pointer _turn_right_(node_pointer current);

    node_pointer _turn_left_(node_pointer current);

    node_pointer _root;
};

template<typename T>
RBTree<T>::~RBTree() {
//    while (_root != nullptr) {
//        erase(_root);
//    }
}

template<typename T>
int RBTree<T>::insert(const_ref_type data) {
    if (_root == nullptr) {
        _root = new rbTreeNode<T>(data, rbSupport::BLACK);
        return 0;
    }

    return _insert_(nullptr, rbSupport::RIGHT_CHILD, _root, data);
}

template<typename T>
int RBTree<T>::_insert_(
        RBTree::node_pointer parent,
        rbSupport parent_child_tag,
        RBTree::node_pointer current,
        const_ref_type data) {
    if (current == nullptr) {
        current = new node_value_type(data, rbSupport::RED);
        parent_child_tag == rbSupport::LEFT_CHILD ? parent->_l_child = current : parent->_r_child = current;
        current->_parent = parent;
        if (parent->_color == rbSupport::RED) {
            _insert_handle_balance_(current);
        }
        return 0;
    } else if (current->_data == data) {
        return -1;
    } else if (current->_data > data) {
        return _insert_(current, rbSupport::LEFT_CHILD, current->_l_child, data);
    } else {
        return _insert_(current, rbSupport::RIGHT_CHILD, current->_r_child, data);
    }
}

template<typename T>
void RBTree<T>::_insert_handle_balance_(RBTree::node_pointer current) {
    for (; current->_parent && current->_parent->_parent && current->_parent->_color == rbSupport::RED;) {
        auto parent = current->_parent;
        auto gParent = parent->_parent;
        auto uncle = (gParent->_l_child == parent ? gParent->_r_child : gParent->_l_child);

        if (gParent->_l_child == parent) {
            if (uncle && uncle->_color == rbSupport::RED) {
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
            if (uncle && uncle->_color == rbSupport::RED) {
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

template<typename T>
int RBTree<T>::erase(const_ref_type data) {
    if (_root == nullptr) {
        return -1;
    }

    return _erase_(nullptr, rbSupport::RIGHT_CHILD, _root, data);
}

template<typename T>
int RBTree<T>::_erase_(
        RBTree::node_pointer parent,
        rbSupport parent_child_tag,
        RBTree::node_pointer current_node,
        const_ref_type data) {
    if (current_node == nullptr) {
        return -1;
    } else if (current_node->_data == data) {
        node_pointer tmp_nil = nullptr;
        auto delete_node_color = current_node->_color;
        node_pointer &ref_p = (parent ?
                               (parent_child_tag == rbSupport::LEFT_CHILD ? parent->_l_child : parent->_r_child)
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
            current_node = ref_p = nullptr;
        }

        if (delete_node_color == rbSupport::BLACK && parent) {
            if (current_node == nullptr) {
                tmp_nil = current_node = new rbTreeNode<T>(0, rbSupport::BLACK);
                current_node->_parent = parent;
                parent_child_tag == rbSupport::LEFT_CHILD ? parent->_l_child = current_node
                                                          : parent->_r_child = current_node;
            }

            _erase_handle_balance_(current_node);

            if (tmp_nil) {
                if (tmp_nil->_parent->_l_child == tmp_nil) {
                    tmp_nil->_parent->_l_child = nullptr;
                } else {
                    tmp_nil->_parent->_r_child = nullptr;
                }
                delete tmp_nil;
            }
        }
        return 0;
    } else if (data < current_node->_data) {
        return _erase_(current_node, rbSupport::LEFT_CHILD, current_node->_l_child, data);
    } else {
        return _erase_(current_node, rbSupport::RIGHT_CHILD, current_node->_r_child, data);
    }
}

template<typename T>
void RBTree<T>::_erase_handle_balance_(RBTree::node_pointer current_node) {
    for (; (current_node == nullptr || current_node->_color == rbSupport::BLACK) && current_node != _root;) {
        if (current_node == current_node->_parent->_l_child) {
            auto tmp = current_node->_parent->_r_child;
            if (tmp && tmp->_color == rbSupport::RED) {
                tmp->_color = rbSupport::BLACK;
                current_node->_parent->_color = rbSupport::RED;
                _turn_left_(current_node->_parent);
                tmp = current_node->_parent->_r_child;
            }

            if ((tmp->_l_child == nullptr || tmp->_l_child->_color == rbSupport::BLACK)
                && (tmp->_r_child == nullptr || tmp->_r_child->_color == rbSupport::BLACK)) {
                tmp->_color = rbSupport::RED;
                auto tmp_curr = current_node;
                current_node = current_node->_parent;
                tmp_curr->_parent = current_node->_parent;
            } else {
                if (tmp->_r_child == nullptr || tmp->_r_child->_color == rbSupport::BLACK) {
                    tmp->_l_child ? tmp->_l_child->_color = rbSupport::BLACK : rbSupport::RED;
                    tmp->_color = rbSupport::RED;
                    _turn_right_(tmp);
                    tmp = current_node->_parent->_r_child;
                }

                tmp->_color = current_node->_parent->_color;
                current_node->_parent->_color = rbSupport::BLACK;
                tmp->_r_child->_color = rbSupport::BLACK;
                _turn_left_(current_node->_parent);
                current_node = _root;
            }
        } else {
            auto tmp = current_node->_parent->_l_child;
            if (tmp && tmp->_color == rbSupport::RED) {
                tmp->_color = rbSupport::BLACK;
                current_node->_parent->_color = rbSupport::RED;
                _turn_right_(current_node->_parent);
                tmp = current_node->_parent->_r_child;
            }
            if ((tmp->_l_child == nullptr || tmp->_l_child->_color == rbSupport::BLACK)
                && (tmp->_r_child == nullptr || tmp->_r_child->_color == rbSupport::BLACK)) {
                tmp->_color = rbSupport::RED;
                auto tmp_curr = current_node;
                current_node = current_node->_parent;
                tmp_curr->_parent = current_node->_parent;
            } else {
                if (tmp->_l_child == nullptr || tmp->_l_child->_color == rbSupport::BLACK) {
                    tmp->_r_child ? tmp->_r_child->_color = rbSupport::BLACK : rbSupport::RED;
                    tmp->_color = rbSupport::RED;
                    _turn_left_(tmp);
                    tmp = current_node->_parent->_l_child;
                }

                tmp->_color = current_node->_parent->_color;
                current_node->_parent->_color = rbSupport::BLACK;
                tmp->_l_child->_color = rbSupport::BLACK;
                _turn_right_(current_node->_parent);
                current_node = _root;
            }
        }
    }
    current_node->_color = rbSupport::BLACK;
}

template<typename T>
typename RBTree<T>::node_pointer RBTree<T>::_turn_right_(RBTree::node_pointer current) {
    auto left_child = current->_l_child;
    current->_l_child = left_child->_r_child;

    if (left_child->_r_child) {
        left_child->_r_child->_parent = current;
    }

    left_child->_parent = current->_parent;
    if (current->_parent == nullptr) {
        _root = left_child;
    } else if (current->_parent->_l_child == current) {
        current->_parent->_l_child = left_child;
    } else {
        current->_parent->_r_child = left_child;
    }

    left_child->_r_child = current;
    current->_parent = left_child;

    return left_child;
}

template<typename T>
typename RBTree<T>::node_pointer RBTree<T>::_turn_left_(RBTree::node_pointer current) {
    auto right_child = current->_r_child;
    current->_r_child = right_child->_l_child;

    if (right_child->_l_child) {
        right_child->_l_child->_parent = current;
    }

    right_child->_parent = current->_parent;
    if (current->_parent == nullptr) {
        _root = right_child;
    } else if (current->_parent->_l_child == current) {
        current->_parent->_l_child = right_child;
    } else {
        current->_parent->_r_child = right_child;
    }

    right_child->_l_child = current;
    current->_parent = right_child;

    return right_child;
}

template<typename T>
iterator<T> RBTree<T>::begin() const {
    node_pointer node = _root;
    for (; node->_l_child;) {
        node = node->_l_child;
    }
    return iterator(node);
}

template<typename T>
iterator<T> RBTree<T>::end() const { return iterator(_root); }

template<typename T>
iterator<T> RBTree<T>::find(const_ref_type target) const {
    auto node = _root->_l_child;
    for (; node;) {
        if (node->_data < target) {
            node = node->_r_child;
        } else if (node->_data > target) {
            node = node->_l_child;
        } else {
            return iterator(node);
        }
    }
    return iterator(node);
}

template<typename T>
iterator<T> RBTree<T>::lower_bound(const_ref_type target) const {
    auto curr = _root->_l_child;
    auto prev = _root;
    for (; curr;) {
        if (curr->_data < target) {
            curr = curr->_r_child;
        } else {
            prev = curr;
            curr = curr->_l_child;
        }
    }
    return iterator(prev);
}


//void RBTree::searchUnit(int data, struct _node *_node) {
//    if (!_node || _node == NIL) return;
//    if (_node->data == data) {
//        deleteUnit(_node);
//        return;
//    }
//    if (data > _node->data) searchUnit(data, _node->right);
//    else searchUnit(data, _node->left);
//}

//int RBTree::inorder(struct _node *_node) {
//    struct _node *tmp;
//    int result = 0;
//    if (!_node || _node == NIL) return -1;
//    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
//        inorder(tmp->left);
//        result = printf("%d -> ", tmp->data);
//    }
//    return result;
//}
//
//int RBTree::preorder(struct _node *_node) {
//    struct _node *tmp;
//    int result = 0;
//    if (!_node || _node == NIL) return printf("Is empty");
//    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
//        printf("%d -> ", tmp->data);
//        result = preorder(tmp->left);
//    }
//    return result;
//}
//
//int RBTree::postorder(struct _node *_node) {
//    if (_node == NIL) return printf("Is empty");
//    postorder(_node->left);
//    postorder(_node->right);
//    return printf("%d -> ", _node->data);
//}
//
//void RBTree::show(struct _node **_node, int count) {
//    if ((*_node) == NIL) {
//        std::cout << "<Is Empty>" << std::endl << std::endl;
//        return;
//    }
//
//    if ((*_node)->right != NIL) {
//        show(&(*_node)->right, count + 4);
//    }
//
//    for (int i = 0; i < count; ++i) fputs(" ", stdout);
//
//    if ((*_node)->color == RED)
//        std::cout << "<" << (*_node)->data << ">" << std::endl;
//    else
//        std::cout << (*_node)->data << std::endl;
//
//
//    if ((*_node)->left != NIL) {
//        show(&(*_node)->left, count + 4);
//    }
//}


#endif //TP2022_CPP_SET_RBTREE_H
