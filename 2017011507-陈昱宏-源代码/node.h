//节点类模板
#ifndef NODE_H
#define NODE_H

/*template<class T>
class Node
{
    Node<T> *next;
public:
    T data;

    Node(const T &data, Node<T> *next=nullptr):data(data), next(next){}
    void insertAfter(Node<T> *ptr);
    Node<T> *nextNode(){return next;}
    Node<T> *deleteAfter();
};

template<class T>
void Node<T>::insertAfter(Node<T> *ptr)
{
    ptr->next = next;
    next = ptr;
}

template<class T>
Node<T>* Node<T>::deleteAfter()
{
    if (next != nullptr)
    {
        Node<T> *temp = next;
        next = temp->next;
        return temp;
    }
    return nullptr;
}*/
template <class T> //node类模版
class Node {
    Node<T> *right;
    Node<T> *down;
    T data;
public:
    Node (const T &data, Node<T>*right = nullptr, Node<T>*down = nullptr)
        :data(data), right(right), down(down){} //构造函数
    Node<T>* getright(){return right;} //取得right指针
    Node<T>* getdown(){return down;} //取得down指针
    void changeright(Node<T>* ptr){right = ptr;} //修改right指针
    void changedown(Node<T>* ptr){down = ptr;} //修改down指针
    T getdata(){return data;} //得到节点data
    void changedata(const T &d); //修改节点data
};

template <class T>
void Node<T>::changedata(const T &d)
{
    data = d;
}
#endif // NODE_H
