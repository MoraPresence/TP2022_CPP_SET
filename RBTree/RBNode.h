// Copyright 2022 mora

#pragma once

enum class rbSupport {
    RED = 0,
    BLACK = 1,
    NULL_NODE = -100,
    LEFT_CHILD = 0,
    RIGHT_CHILD = 1
};


template<typename T>
class rbTreeNode {
public:
    rbTreeNode() = default;

    rbTreeNode(const T &data, rbSupport color)
            : _data(data), _color(color), _parent(nullptr), _l_child(nullptr), _r_child(nullptr) {};

    rbTreeNode(const rbTreeNode &) = default;

    rbTreeNode(rbTreeNode &&)  noexcept = default;

    rbTreeNode &operator=(const rbTreeNode &) = default;

    rbTreeNode &operator=(rbTreeNode &&)  noexcept = default;

    ~rbTreeNode() = default;

public:
    T _data;
    rbSupport _color;
    rbTreeNode *_parent;
    rbTreeNode *_l_child;
    rbTreeNode *_r_child;
};
