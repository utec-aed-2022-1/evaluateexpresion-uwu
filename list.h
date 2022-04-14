#ifndef LIST_H
#define LIST_H
#include "node.h"
using namespace std;


template <typename T>
class List {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int nodes;
    
    public:
        List() : head(nullptr), tail(nullptr), nodes(0) {};
        virtual ~List() {
            while (this->head != nullptr)
            {
                this->head = this->head->next;
                this->head->killSelf();
            }
        };

        virtual T front() = 0;
        virtual T back() = 0;
        virtual void push_front(T) = 0;
        virtual void push_back(T) = 0;
        virtual T pop_front() = 0;
        virtual T pop_back() = 0;
        virtual void insert(T, int) = 0; 
        virtual void remove(int) = 0;  
        virtual T operator[](int) = 0;
        virtual bool is_empty() = 0;
        virtual int size() = 0;
        virtual void clear() = 0;
        virtual void sort() = 0;
        virtual bool is_sorted() = 0;
        virtual std::string name() = 0;
        virtual void display() = 0;
};

#endif