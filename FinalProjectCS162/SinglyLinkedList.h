#pragma once
#include<functional>
#include <assert.h>
#include <iostream>
using namespace std;
#define sll SinglyLinkedList

template <class T>
class SinglyNode {
public:
    T data;
    SinglyNode<T>* next;
    //default constructor
    SinglyNode();

    SinglyNode(T data);

    SinglyNode(T* data);
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
    SinglyLinkedList();

    ~SinglyLinkedList();

    Iterator begin() const {
        return Iterator(this->dummy->next);
    };

    Iterator end() const {
        return Iterator(nullptr);
    };

    SinglyLinkedList(const SinglyLinkedList<T>& other);

    SinglyLinkedList(SinglyLinkedList<T>&& other);

    void copy(const SinglyLinkedList<T>& other);

    T find(function<bool(T)> cmp);

    int findIndex(function<bool(T)> cmp) const;


    void push_back(const T& d);

    void push_back(T&& d);

    void push_back(T* d);


    void push_front(const T& d);

    T& back();

    T& front();

    int size() const;

    void clear();

    void deleteNode(const function<bool(T)>& cmp);

    void deleteAt(int index);

    void deleteNode(T d);

    //function pop_back
    void pop_back();

    //function pop_front
    void pop_front();

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
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->data;
    };

    const T& operator[](int index) const {
        assert(0 <= index && index < sz);
        SinglyNode<T>* cur = this->dummy->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->data;
    };
};

template<class T>
SinglyLinkedList<T>::SinglyLinkedList() { this->dummy = new SinglyNode<T>(); this->rear = this->dummy; this->sz = 0; }

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    this->clear();
    delete this->dummy;
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
    copy(other);
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) {
    copy(other);
}

template<class T>
void SinglyLinkedList<T>::copy(const SinglyLinkedList<T>& other) {
    this->rear = this->dummy = new SinglyNode<T>();
    this->sz = 0;
    SinglyNode<T>* curr = other.dummy->next;
    while (curr != nullptr) {
        this->push_back(curr->data);
        curr = curr->next;
    }
}

template<class T>
T SinglyLinkedList<T>::find(function<bool(T)> cmp) {
    SinglyNode<T>* cur = this->dummy->next;
    while (cur != NULL) {
        if (cmp(cur->data)) {
            return cur->data;
        }
        cur = cur->next;
    }
    return T();
}

template<class T>
int SinglyLinkedList<T>::findIndex(function<bool(T)> cmp) const {
    SinglyNode<T>* cur = this->dummy->next;
    int index = 0;
    while (cur != NULL) {
        if (cmp(cur->data)) {
            return index;
        }
        cur = cur->next;
        ++index;
    }
    return -1;
}

template<class T>
void SinglyLinkedList<T>::push_back(const T& d) {
    SinglyNode<T>* newNode = new SinglyNode<T>(d);
    this->rear->next = newNode;
    this->rear = newNode;
    sz++;
}

template<class T>
void SinglyLinkedList<T>::push_back(T&& d) {
    SinglyNode<T>* newNode = new SinglyNode<T>(d);
    this->rear->next = newNode;
    this->rear = newNode;
    sz++;
}

template<class T>
void SinglyLinkedList<T>::push_back(T* d) {
    SinglyNode<T>* newNode = new SinglyNode<T>(d);
    this->rear->next = newNode;
    this->rear = newNode;
    sz++;
}

template<class T>
void SinglyLinkedList<T>::push_front(const T& d) {
    SinglyNode<T>* newNode = new SinglyNode<T>(d);
    newNode->next = this->dummy->next;
    this->dummy->next = newNode;
    sz++;
    if (sz == 1) {
        this->rear = newNode;
    }
}

template<class T>
T& SinglyLinkedList<T>::back() {
    assert(this->sz > 0);
    return this->rear->data;
}

template<class T>
T& SinglyLinkedList<T>::front() {
    assert(this->sz > 0);
    return this->dummy->next->data;
}

template<class T>
int SinglyLinkedList<T>::size() const {
    return sz;
}

template<class T>
void SinglyLinkedList<T>::clear() {
    SinglyNode<T>* cur = this->dummy->next;
    while (cur != NULL) {
        SinglyNode<T>* next = cur->next;
        delete cur;
        cur = next;
    }
    this->dummy->next = NULL;
    this->rear = this->dummy;
    sz = 0;
}

template<class T>
void SinglyLinkedList<T>::deleteNode(const function<bool(T)>& cmp) {
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
}

template<class T>
void SinglyLinkedList<T>::deleteAt(int index) {
    SinglyNode<T>* cur = this->dummy;
    for (int i = 0; i < index && cur->next != NULL; ++i) {
        cur = cur->next;
    }
    if (cur->next != NULL) {
        SinglyNode<T>* temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        --sz;
        if (cur->next == NULL) {
            this->rear = cur;
        }
    }
}

template<class T>
void SinglyLinkedList<T>::deleteNode(T d) {
    deleteNode([&d](T data) { return data == d; });
}

//function pop_back
template<class T>
void SinglyLinkedList<T>::pop_back() {
    SinglyNode<T>* cur = this->dummy;
    while (cur->next != NULL && cur->next->next != NULL) {
        cur = cur->next;
    }
    delete cur->next;
    cur->next = NULL;
    this->rear = cur;
    --sz;
}

//function pop_front
template<class T>
void SinglyLinkedList<T>::pop_front() {
    SinglyNode<T>* cur = this->dummy->next;
    this->dummy->next = cur->next;
    delete cur;
    --sz;
    if (sz == 0) this->rear = this->dummy;
}

//default constructor
template<class T>
SinglyNode<T>::SinglyNode() {
    this->next = nullptr;
}

template<class T>
SinglyNode<T>::SinglyNode(T data) {
    this->data = data;
    this->next = nullptr;
}

template<class T>
SinglyNode<T>::SinglyNode(T* data) {
    this->data = *data;
    this->next = nullptr;
}
