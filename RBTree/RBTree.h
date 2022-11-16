#ifndef TP2022_CPP_SET_RBTREE_H
#define TP2022_CPP_SET_RBTREE_H

const auto RED = 0;
const auto BLACK = 1;
const auto NULL_NODE = -100;
const auto LEFT_CHILD = 0;
const auto RIGHT_CHILD = 1;

template<typename T>
class rbTreeNode {
public:
    rbTreeNode(const T &data, int color)
            : _data(data), _color(color), _parent(nullptr), _l_child(nullptr), _r_child(nullptr) {}

public:
    T _data;
    int _color;
    rbTreeNode *_parent;
    rbTreeNode *_l_child;
    rbTreeNode *_r_child;
};

template<typename T>
class RBTree {
public:
    typedef T value_type;
    typedef const value_type &const_ref_type;
    typedef rbTreeNode<T> node_value_type;
    typedef rbTreeNode<T> *node_pointer;
    typedef const node_pointer const_node_pointer;

public:
    RBTree() : _root(nullptr) {}

    ~RBTree();

    int insert(const_ref_type data);

    int delete_node(const_ref_type data);

    void show(struct node **_node, int count);

    void searchUnit(int data, struct node *_node);

    void deleteUnit(struct node *_node);


    int inorder(struct node *_node);

    int preorder(struct node *_node);

    int postorder(struct node *_node);

private:

    int _insert_(node_pointer parent, int parent_child_tag, node_pointer current, const_ref_type data);

    int _delete_node_(node_pointer parent, int parent_child_tag, node_pointer current_node, const_ref_type data);

    void _insert_handle_balance_(node_pointer current);

    void _delete_handle_balance_(node_pointer current);

    node_pointer _turn_right_(node_pointer current);

    node_pointer _turn_left_(node_pointer current);


    void deleteFix(node *x);

    node_pointer _root;
};

template<typename T>
RBTree<T>::~RBTree() {
    while (_root != NIL) {
        deleteUnit(_root);
    }
}

template<typename T>
int RBTree<T>::insert(const_ref_type data) {
    if (_root == nullptr) {
        _root = new node_value_type(data, BLACK);
        return 0;
    }

    return _insert_(nullptr, RIGHT_CHILD, _root, data);
}

template<typename T>
int RBTree<T>::_insert_(
        RBTree::node_pointer parent,
        int parent_child_tag,
        RBTree::node_pointer current,
        const_ref_type data) {
    if (current == nullptr) {
        current = new node_value_type(data, RED);
        parent_child_tag == LEFT_CHILD ? parent->_l_child = current : parent->_r_child = current;
        current->_parent = parent;
        if (parent->_color == RED) {
            _insert_handle_balance_(current);
        }
        return 0;
    } else if (current->_data == data) {
        //TODO:add copy or not?
        return -1;
    } else if (current->_data > data) {
        return _insert_(current, LEFT_CHILD, current->_l_child, data);
    } else {
        return _insert_(current, RIGHT_CHILD, current->_r_child, data);
    }
}

template<typename T>
void RBTree<T>::_insert_handle_balance_(RBTree::node_pointer current) {
    for (; current->_parent && current->_parent->_parent && current->_parent->_color == RED;) {
        auto parent = current->_parent;
        auto gParent = parent->_parent;
        auto uncle = (gParent->_l_child == parent ? gParent->_r_child : gParent->_l_child);

        if (gParent->_l_child == parent) {
            if (uncle && uncle._color == RED) {
                parent->_color = uncle->_color = BLACK;
                gParent->_color = RED;
                current = gParent;
            } else {
                if (parent->_r_child == current) {
                    _turn_left_(parent);
                    std::swap(current, parent);
                }
                parent->_color = BLACK;
                gParent->_color = RED;
                _turn_right_(gParent);
            }
        } else {
            if (uncle && uncle._color == RED) {
                parent->_color = uncle->_color = BLACK;
                gParent->_color = RED;
                current = gParent;
            } else {
                if (parent->_l_child == current) {
                    _turn_right_(parent);
                    std::swap(current, parent);
                }
                parent->_color = BLACK;
                gParent->_color = RED;
                _turn_left_(gParent);
            }
        }
    }
    _root->_color = BLACK;
}

template<typename T>
int RBTree<T>::delete_node(const_ref_type data) {
    if (_root == nullptr) {
        return -1;
    }

    return _delete_node_(nullptr, RIGHT_CHILD, _root, data);
}

template<typename T>
int RBTree<T>::_delete_node_(
        RBTree::node_pointer parent,
        int parent_child_tag,
        RBTree::node_pointer current_node,
        const_ref_type data) {
    if (current_node == nullptr) {
        return -1;
    } else if (current_node->_data == data) {
        node_pointer tmp_nil = nullptr;
        auto delete_node_color = current_node->color_;
        node_pointer &ref_p = (parent ?
                               (parent_child_tag == LEFT_CHILD ? parent->l_child_ : parent->r_child_)
                                      : _root);

        if (current_node->_l_child && current_node->_r_child) {
            auto prev = current_node->_l_child;
            auto curr = prev;
            for (; curr && curr->r_child_; prev = curr, curr = curr->r_child_);
            delete_node_color = curr->_color;
            if (curr == prev) {
                current_node->_data = curr->_data;
                current_node->_l_child = curr->_l_child;

                if (curr->_l_child) {
                    curr->_l_child->_parent = current_node;
                }

                parent = current_node;
                current_node = current_node->_l_child;
                parent_child_tag = LEFT_CHILD;
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

        if (delete_node_color == BLACK && parent) {
            if (current_node == nullptr) {
                tmp_nil = current_node = new node_value_type(NULL_NODE, BLACK);
                current_node->_parent = parent;
                parent_child_tag == LEFT_CHILD ? parent->_l_child = current_node : parent->_r_child = current_node;
            }
            //TODO:balance

            if (tmp_nil) {
                if (tmp_nil->_parent->_l_child == tmp_nil) {
                    tmp_nil->_parent->_l_child = nullptr;
                } else {
                    tmp_nil->_parent->r_child_ = nullptr;
                }
                delete tmp_nil;
            }
        }
        return 0;
    } else if (data < current_node->_data) {
        return _delete_node_(current_node, LEFT_CHILD, current_node->_l_child, data);
    } else {
        return _delete_node_(current_node, RIGHT_CHILD, current_node->_r_child, data);
    }
}

template<typename T>
void RBTree<T>::_delete_handle_balance_(RBTree::node_pointer current) {

}


void RBTree::deleteFix(node *_node) {
    while (_node != _root && _node->color == BLACK) {
        if (_node == _node->parent->left) {
            node *tmp = _node->parent->right; //брат
            if (tmp->color == RED) { //если брат красный
                tmp->color = BLACK;
                _node->parent->color = RED;
                _turn_left_(_node->parent);
                tmp = _node->parent->right; //получаем черного брата
            }
            if (tmp->left->color == BLACK && tmp->right->color == BLACK) { //удаляемое значение черное
                tmp->color = RED;   //красим брата в красный              //и брат черный
                _node = _node->parent; //красим отца в черный ниже
            } else { //один из детей не черный
                if (tmp->right->color == BLACK) { //у брата правый ребенок черный
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    _turn_right_(tmp);
                    tmp = _node->parent->right; //рассматриваем брата
                }//у брата правый ребенок красный
                tmp->color = _node->parent->color; //перекрашиваем брата в цвет отца
                _node->parent->color = BLACK; //перекрашмваем отца в черный
                tmp->right->color = BLACK; //перекоашиваем ребенка отца в черный
                _turn_left_(_node->parent);
                _node = _root;
            }
        } else {
            node *tmp = _node->parent->left;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                _node->parent->color = RED;
                _turn_right_(_node->parent);
                tmp = _node->parent->left;
            }
            if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
                tmp->color = RED;
                _node = _node->parent;
            } else {
                if (tmp->left->color == BLACK) {
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    _turn_left_(tmp);
                    tmp = _node->parent->left;
                }
                tmp->color = _node->parent->color;
                _node->parent->color = BLACK;
                tmp->left->color = BLACK;
                _turn_right_(_node->parent);
                _node = _root;
            }
        }
    }
    _node->color = BLACK;
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






//void RBTree::searchUnit(int data, struct node *_node) {
//    if (!_node || _node == NIL) return;
//    if (_node->data == data) {
//        deleteUnit(_node);
//        return;
//    }
//    if (data > _node->data) searchUnit(data, _node->right);
//    else searchUnit(data, _node->left);
//}

//int RBTree::inorder(struct node *_node) {
//    struct node *tmp;
//    int result = 0;
//    if (!_node || _node == NIL) return -1;
//    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
//        inorder(tmp->left);
//        result = printf("%d -> ", tmp->data);
//    }
//    return result;
//}
//
//int RBTree::preorder(struct node *_node) {
//    struct node *tmp;
//    int result = 0;
//    if (!_node || _node == NIL) return printf("Is empty");
//    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
//        printf("%d -> ", tmp->data);
//        result = preorder(tmp->left);
//    }
//    return result;
//}
//
//int RBTree::postorder(struct node *_node) {
//    if (_node == NIL) return printf("Is empty");
//    postorder(_node->left);
//    postorder(_node->right);
//    return printf("%d -> ", _node->data);
//}
//
//void RBTree::show(struct node **_node, int count) {
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
