/*#ifndef LIST_H
#define LIST_H

#include "node.h"

template <class T>
class List {
    Node<T> *head, *last; //头、尾指针
    Node<T> *prevptr, *currptr; //遍历链表时记录当前和前一节点
    int size_w; //宽度
    int size_h; //高度

public:
    List(const int &s = 0); //构造函数
    void reset(){prevptr = nullptr; currptr = head;} //重设遍历时的指针
    Node<T>* getprevptr(){return prevptr;} //取得prevptr
    Node<T>* getcurrptr(){return currptr;} //取得currptr
    void changeprevptr(Node<T> *ptr){prevptr = ptr;} //修改prevptr
    void changecurrptr(Node<T> *ptr){currptr = ptr;} //修改currptr
    void insertnodeRear(const T &item); //尾端插入节点
    void insertnodeFront(const T &item); //首端插入节点
    void insertnodeanyway(Node<T> *prevptr, const T &item); //任意位置(prevptr后)插入节点
    void changehead(Node<T> *ptr){head = ptr;} //修改头指针
    void changelast(Node<T> *ptr){last = ptr;} //修改尾指针
    Node<T>* gethead(){return head;} //取得头指针
    Node<T>* getlast(){return last;} //取得尾指针
    void change_node_data(const int &pos, const T &item); //修改节点data
    ~List();
};

template <class T>
List<T>::List(const int &s):size(s)
{
    if (s != 0)
    {
        Node<T> *ptr1, *ptr2;
        head = new Node<T>(0);
        ptr2 = head;
        for (int i = 1; i < s; i ++)
        {
            ptr1 = new Node<T>(0);
            ptr2->changenext(ptr1);
            ptr2 = ptr1;
        }
        last = ptr2;
    }
    else
    {
        head = nullptr;
        last = nullptr;
    }
    prevptr = nullptr;
    currptr = head;
}

template <class T>
void List<T>::insertnodeRear(const T &item)
{
    Node<T> *ptr;
    ptr = new Node<T>(item, nullptr);
    last->changenext(ptr);
    last = ptr;
    size += 1;
}

template <class T>
void List<T>::insertnodeFront(const T &item)
{
    Node<T> *ptr;
    ptr = new Node<T>(item);
    ptr->changenext(head);
    head = ptr;
    size += 1;
}

template <class T>
void List<T>::insertnodeanyway(Node<T> *prevptr, const T &item)
{
    if (prevptr)
    {
        Node<T> *ptr;
        ptr = new Node<T>(item);
        ptr->changenext(prevptr->getnext());
        prevptr->changenext(ptr);
    }
    else
    {
        insertnodeFront(item);
    }
}

template <class T>
void List<T>::change_node_data(const int &pos, const T &item)
{
    Node<T> *ptr = head;
    for (int i = 0; i < pos; i ++)
    {
        ptr = ptr->getnext();
    }
    ptr->changedata(item);
}

template <class T>
List<T>::~List<T>()
{
    for (int i = 0; i < size; i ++)
    {
        delete_headnode();
    }
}

#endif // LIST_H*/
