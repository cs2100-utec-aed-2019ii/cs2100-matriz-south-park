#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    unsigned x,y;
    T value;
    Node<T> *next, *down;

public:
    explicit Node(){
        next = nullptr;
        down = nullptr;
    }

    explicit Node(unsigned x, unsigned y,T value){
        this -> x = x;
        this -> y = y;
        this -> value = value;
        next = nullptr;
        down = nullptr;
    }

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
