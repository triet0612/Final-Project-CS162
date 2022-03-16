#pragma once
#include<functional>
#include <assert.h>
#include <iostream>
using namespace std;

template <class T>
class SinglyNode {
public:
    T data;
    SinglyNode<T>* next;
    //default constructor
    SinglyNode() {
        next = nullptr;
    }

    SinglyNode(T data) {
        this->data = data;
        next = nullptr;
    }

    SinglyNode(T* data) {
        this->data = *data;
        next = nullptr;
    }
};

//singly linked list iterator
template <class SinglyLinkedList>
class SinglyLinkedListIterator {

public:
    using ValueType = typename SinglyLinkedList::ValueType;
    using PointerType = typename SinglyLinkedList::PointerType;
    using ReferenceType = typename SinglyLinkedList::ValueType&;
private:
    PointerType m_Ptr;
public:
    SinglyLinkedListIterator(PointerType ptr) : m_Ptr(ptr) {}
    //operator overload for ++
    SinglyLinkedListIterator<SinglyLinkedList>& operator++() {
        if (m_Ptr) m_Ptr = m_Ptr->next;
        return *this;
    }
    //operator overload for *
    ReferenceType operator*() {
        return m_Ptr->data;
    }
    //operator overload for ==
    bool operator==(const SinglyLinkedListIterator<SinglyLinkedList>& rhs) {
        return m_Ptr == rhs.m_Ptr;
    }
    //operator overload for !=
    bool operator!=(const SinglyLinkedListIterator<SinglyLinkedList>& rhs) {
        return m_Ptr != rhs.m_Ptr;
    }

    //operator []
    ReferenceType operator[](int index) {
        SinglyLinkedListIterator<SinglyLinkedList> temp = *this;
        for (int i = 0; i < index && temp.m_Ptr; i++) {
            temp++;
        }
        return temp->data;
    }
    //operator overload for ->
    PointerType operator->() {
        return m_Ptr;
    }
    //operator overload for ++it
    SinglyLinkedListIterator<SinglyLinkedList> operator++(int) {
        SinglyLinkedListIterator<SinglyLinkedList> temp = *this;
        if (m_Ptr) m_Ptr = m_Ptr->next;
        return temp;
    }


    //operator overload for +=
    SinglyLinkedListIterator<SinglyLinkedList>& operator+=(int n) {
        for (int i = 0; i < n && m_Ptr; i++) {
            m_Ptr = m_Ptr->next;
        }
        return *this;
    }

    //operator overload for +
    SinglyLinkedListIterator<SinglyLinkedList> operator+(int n) {
        SinglyLinkedListIterator<SinglyLinkedList> temp = *this;
        for (int i = 0; i < n && temp.m_Ptr; i++) {
            temp.m_Ptr = temp.m_Ptr->next;
        }
        return temp;
    }

};

template <class T>
class SinglyLinkedList
{
private:
    SinglyNode<T>* dummy, * rear;
    int sz;
public:
    using ValueType = T;
    using PointerType = SinglyNode<T>*;
    using Iterator = SinglyLinkedListIterator<SinglyLinkedList<T>>;

public:
    SinglyLinkedList() { this->dummy = new SinglyNode<T>(); this->rear = this->dummy; this->sz = 0; }

    ~SinglyLinkedList() {
        this->clear();
        delete this->dummy;
    };

    Iterator begin() const {
        return Iterator(this->dummy->next);
    };

    Iterator end() const {
        return Iterator(nullptr);
    };

    SinglyLinkedList(const SinglyLinkedList<T>& other) {
        copy(other);
    };

    SinglyLinkedList(SinglyLinkedList<T>&& other) {
        copy(other);
    };

    void copy(const SinglyLinkedList<T>& other) {
        this->rear = this->dummy = new SinglyNode<T>();
        this->sz = 0;
        SinglyNode<T>* curr = other.dummy->next;
        while (curr != nullptr) {
            this->push_back(curr->data);
            curr = curr->next;
            this->sz++;
        }
    };

    T find(function<bool(T)> cmp) {
        SinglyNode<T>* cur = this->dummy->next;
        while (cur != NULL) {
            if (cmp(cur->data)) {
                return cur->data;
            }
            cur = cur->next;
        }
        return T();
    };


    void push_back(T& d) {
        SinglyNode<T>* newNode = new SinglyNode<T>(d);
        this->rear->next = newNode;
        this->rear = newNode;
        sz++;
    };

    void push_back(T&& d) {
        SinglyNode<T>* newNode = new SinglyNode<T>(d);
        this->rear->next = newNode;
        this->rear = newNode;
        sz++;
    };

    void push_back(T* d) {
        SinglyNode<T>* newNode = new SinglyNode<T>(d);
        this->rear->next = newNode;
        this->rear = newNode;
        sz++;
    };


    void push_front(T& d) {
        SinglyNode<T>* newNode = new SinglyNode<T>(d);
        newNode->next = this->dummy->next;
        this->dummy->next = newNode;
        sz++;
        if (sz == 1) {
            this->rear = newNode;
        }
    };

    T back() {
        assert(this->sz > 0);
        return this->rear->data;
    };

    T front() {
        assert(this->sz > 0);
        return this->dummy->next->data;
    };

    int size() {
        return sz;
    };

    void clear() {
        SinglyNode<T>* cur = this->dummy->next;
        while (cur != NULL) {
            SinglyNode<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        this->dummy->next = NULL;
        this->rear = this->dummy;
        sz = 0;
    };

    void deleteNode(function<bool(T)> cmp) {
        SinglyNode<T>* cur = this->dummy;
        while (cur->next != NULL) {
            if (cmp(cur->next->data)) {
                SinglyNode<T>* temp = cur->next;
                cur->next = cur->next->next;
                delete temp;
                --sz;
                if (cur->next == NULL) {
                    this->rear = cur;
                }
                return;
            }
            else cur = cur->next;
        }
    };

    void deleteNode(T d) {
        deleteNode([&d](T data) { return data == d; });
    };

    //function pop_back
    void pop_back() {
        SinglyNode<T>* cur = this->dummy;
        while (cur->next != NULL && cur->next->next != NULL) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = NULL;
        this->rear = cur;
        --sz;
    };

    //function pop_front
    void pop_front() {
        SinglyNode<T>* cur = this->dummy->next;
        this->dummy->next = cur->next;
        delete cur;
        --sz;
        if (sz == 0) this->rear = this->dummy;
    };

    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& list) {
        if (this == &list) {
            return *this;
        }
        this->clear();
        delete this->dummy;
        copy(list);
        return *this;
    };

    T& operator[](int index) {
        assert(0 <= index && index < sz);
        SinglyNode<T>* cur = this->dummy->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        return cur->data;
    };

    const T& operator[](int index) const {
        assert(0 <= index && index < sz);
        SinglyNode<T>* cur = this->dummy->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        return cur->data;
    };
};
