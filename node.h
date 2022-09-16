
#include <iostream>


template <typename T, typename U>
class Node
{
    public:
    Node* pNext;
    T data1;
    U data2;

    Node()
    {
        pNext = nullptr;
    };

    Node(T newData1, U newData2)
    {
        pNext = nullptr;
        data1 = newData1;
        data2 = newData2;
    };

    void printList(std::ostream &outputStream)
    {
        outputStream << data1 << ",\"" << data2 << "\""<< std::endl;
        if (pNext != nullptr) pNext->printList(outputStream);
    }


    private:

};