#include "node.h"

template <typename T, typename U>
class LinkedList
{
    public:
    Node<T,U>* pHead;
    LinkedList()
    {
        pHead = nullptr;
    }

    void insertFront(T newData1, U newData2)
    {
        Node<T,U>* newNode = new Node<T,U>(newData1, newData2);
        newNode->pNext = this->pHead;
        this->pHead = newNode;
    }

    Node<T,U>* retrieveNode(int nodeLocation)
    {
        Node<T,U>* curNode = pHead;
        for (int i = 0; i < nodeLocation; i++)
        {
            curNode = curNode->pNext;
            if (curNode == nullptr) break;
        }
        return curNode;
    }

    // search node for matching value in d1, return nullptr if not found
    Node<T,U>* searchNodeD1(std::string searchVal)
    {
        Node<T,U>* curNode = pHead;
        while (curNode != nullptr)
        {
            if (curNode->data1 == searchVal) return curNode;
            curNode = curNode->pNext;
        }
        return nullptr;
    }

    //delete node, searching by data in data1
    void delNode(std::string delVal)
    {
        Node<T,U>* deleteThis = searchNodeD1(delVal);
        Node<T,U>* curNode = pHead;
        if (deleteThis == nullptr) return;
        while (curNode->pNext != deleteThis)
        {
            curNode = curNode->pNext;
        }
        // curnode should be right before delete target.
        curNode->pNext = deleteThis->pNext;
        delete deleteThis;
    }


    void print(std::ostream &outputStream)
    {
        if (pHead != nullptr) pHead->printList(outputStream);
    }
};