#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){ 
        next = nullptr;
        prev = nullptr;
        data = 0;
    }

    Node(T value){
        next = nullptr;
        prev = nullptr;
        data = value;
    }

    void killSelf(){
        delete this;
    }
};

#endif