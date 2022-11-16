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

    void show(struct node **_node, int count);

    void searchUnit(int data, struct node *_node);

    void deleteUnit(struct node *_node);


    int inorder(struct node *_node);

    int preorder(struct node *_node);

    int postorder(struct node *_node);

private:

    int insertFix(node_pointer gParent, int gParent_child_tag, node_pointer parent, const_ref_type data);

    void turnRight(node *x);

    void turnLeft(node *x);

    void deleteFix(node *x);

    node_pointer _root;
};

template<typename T>
int RBTree<T>::insert(const_ref_type data) {
    if (_root == nullptr) {
        _root = new node_value_type(data, BLACK);
        return 0;
    }

    return insertFix(nullptr, RIGHT_CHILD, _root, data);
}

template<typename T>
int RBTree<T>::insertFix(
        RBTree::node_pointer gParent,
        int gParent_child_tag,
        RBTree::node_pointer parent,
        const_ref_type data) {
    if(parent == nullptr){
        parent = new node_value_type(data, RED);
        gParent_child_tag == LEFT_CHILD ? gParent->_l_child = parent : gParent->_r_child = parent;
        parent->_parent = gParent;
        if (gParent->_color == RED){
            //TODO:BALANCE
        }
        return 0;
    }else if(parent->_data == data){
        //TODO:add copy or not?
    }else if(parent->_data > data){
        return insertFix(parent, LEFT_CHILD, parent->_l_child, data);
    }else{
        return insertFix(parent, RIGHT_CHILD, parent->_r_child, data);
    }
    return 0;
}

node *RBTree::Insert(int data) {
    node *current, *parent, *x;
    current = _root;
    parent = nullptr;
    while (current != NIL) {
        if (data == current->data) return current;
        parent = current;
        current = (data < current->data) ? current->left : current->right;
    }

    x = new struct node;
    x->data = data;
    x->left = x->right = NIL;
    x->parent = parent;
    x->color = RED;

    if (parent) {
        if (data < parent->data)
            parent->left = x;
        else
            parent->right = x;
    } else {
        _root = x;
    }
    insertFix(x);
    return x;
}

void RBTree::insertFix(node *x) {
    while (x != _root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            node *tmp = x->parent->parent->right; //дядя
            if (tmp->color == RED) { //если дядя красный
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                tmp->color = BLACK;
                x = x->parent->parent;
            } else {  //если дядя черный
                if (x == x->parent->right) {
                    x = x->parent;
                    turnLeft(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                turnRight(x->parent->parent);
            }
        } else {
            node *tmp = x->parent->parent->left;
            if (tmp->color == RED) { //если дядя красный
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                tmp->color = BLACK;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    turnRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                turnLeft(x->parent->parent);
            }
        }
    }
    _root->color = BLACK;
}

void RBTree::show(struct node **_node, int count) {
    if ((*_node) == NIL) {
        std::cout << "<Is Empty>" << std::endl << std::endl;
        return;
    }

    if ((*_node)->right != NIL) {
        show(&(*_node)->right, count + 4);
    }

    for (int i = 0; i < count; ++i) fputs(" ", stdout);

    if ((*_node)->color == RED)
        std::cout << "<" << (*_node)->data << ">" << std::endl;
    else
        std::cout << (*_node)->data << std::endl;


    if ((*_node)->left != NIL) {
        show(&(*_node)->left, count + 4);
    }
}

void RBTree::searchUnit(int data, struct node *_node) {
    if (!_node || _node == NIL) return;
    if (_node->data == data) {
        deleteUnit(_node);
        return;
    }
    if (data > _node->data) searchUnit(data, _node->right);
    else searchUnit(data, _node->left);
}

void RBTree::deleteUnit(struct node *_node) {
    struct node *p = NIL;
    if (!_node || _node == NIL) return;
    //* нет детей *//
    if (_node->left == NIL && _node->right == NIL) {
        if (_node == _root) _root = NIL;
        if (_node->color == BLACK)
            deleteFix(_node);
        if (_node->parent->left == _node) {
            _node->parent->left = NIL;
        } else {
            _node->parent->right = NIL;
        }
        delete _node;
        return;
    }                           //* есть оба ребенка *//
    else if (_node->left != NIL && _node->right != NIL) {
        p = _node->left;
        while (p->right != NIL) p = p->right;
        _node->data = p->data;
        deleteUnit(p);
        return;
    } else {
        if (_node->left == NIL) {
            p = _node->right;
        } else if (_node->right == NIL) {
            p = _node->left;
        }
        if (_node->parent) {
            if (_node->parent->left == _node) {
                _node->parent->left = p;
            } else {
                _node->parent->right = p;
            }
            p->parent = _node->parent;
            p->color = BLACK;//чтобы избежать два красных

        } else
            _root = p;
        free(_node);
    }


}

void RBTree::deleteFix(node *_node) {
    while (_node != _root && _node->color == BLACK) {
        if (_node == _node->parent->left) {
            node *tmp = _node->parent->right; //брат
            if (tmp->color == RED) { //если брат красный
                tmp->color = BLACK;
                _node->parent->color = RED;
                turnLeft(_node->parent);
                tmp = _node->parent->right; //получаем черного брата
            }
            if (tmp->left->color == BLACK && tmp->right->color == BLACK) { //удаляемое значение черное
                tmp->color = RED;   //красим брата в красный              //и брат черный
                _node = _node->parent; //красим отца в черный ниже
            } else { //один из детей не черный
                if (tmp->right->color == BLACK) { //у брата правый ребенок черный
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    turnRight(tmp);
                    tmp = _node->parent->right; //рассматриваем брата
                }//у брата правый ребенок красный
                tmp->color = _node->parent->color; //перекрашиваем брата в цвет отца
                _node->parent->color = BLACK; //перекрашмваем отца в черный
                tmp->right->color = BLACK; //перекоашиваем ребенка отца в черный
                turnLeft(_node->parent);
                _node = _root;
            }
        } else {
            node *tmp = _node->parent->left;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                _node->parent->color = RED;
                turnRight(_node->parent);
                tmp = _node->parent->left;
            }
            if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
                tmp->color = RED;
                _node = _node->parent;
            } else {
                if (tmp->left->color == BLACK) {
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    turnLeft(tmp);
                    tmp = _node->parent->left;
                }
                tmp->color = _node->parent->color;
                _node->parent->color = BLACK;
                tmp->left->color = BLACK;
                turnRight(_node->parent);
                _node = _root;
            }
        }
    }
    _node->color = BLACK;
}

int RBTree::inorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node || _node == NIL) return -1;
    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
        inorder(tmp->left);
        result = printf("%d -> ", tmp->data);
    }
    return result;
}

int RBTree::preorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node || _node == NIL) return printf("Is empty");
    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
        printf("%d -> ", tmp->data);
        result = preorder(tmp->left);
    }
    return result;
}

int RBTree::postorder(struct node *_node) {
    if (_node == NIL) return printf("Is empty");
    postorder(_node->left);
    postorder(_node->right);
    return printf("%d -> ", _node->data);
}

void RBTree::turnRight(node *x) {
    node *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        _root = y;
    }
    y->right = x;
    if (x != NIL) x->parent = y;
}

void RBTree::turnLeft(node *x) {
    node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        _root = y;
    }

    y->left = x;
    if (x != NIL) x->parent = y;
}

RBTree::~RBTree() {
    while (_root != NIL) {
        deleteUnit(_root);
    }
}


#endif //TP2022_CPP_SET_RBTREE_H
