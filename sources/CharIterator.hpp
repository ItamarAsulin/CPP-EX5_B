//
// Created by itamarq on 5/24/22.
//

#ifndef EX5_B_CHARITERATOR_HPP
#define EX5_B_CHARITERATOR_HPP

#include <queue>
#include <stack>
#include "Node.hpp"
#include "IterationOrder.hpp"

namespace ariel {
    class ChartIterator{
    private:
        Node *currentNode;
    public:
        ChartIterator(Node *iterationHead){
            currentNode = iterationHead;
        }
        ChartIterator& operator++(){
            currentNode = currentNode->nextInIteration;
            return *this;
        }

        ChartIterator operator++(int){
            ChartIterator temp = *this;
            ++*this;
            return temp;
        }

        string& operator*() const{
            return currentNode->key;
        }
        string* operator->()const{
            return &(currentNode->key);
        }

        bool operator==( const ChartIterator& other){
            return currentNode == other.currentNode;
        }
        bool operator!=(const ChartIterator& other){
            return currentNode != other.currentNode;
        }
    };

}


#endif //EX5_B_CHARITERATOR_HPP
