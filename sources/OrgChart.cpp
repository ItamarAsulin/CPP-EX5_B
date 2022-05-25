//
// Created by itamarq on 5/24/22.
//
#include "OrgChart.hpp"
#include <vector>

using namespace std;
namespace ariel {
    vector<string> invalidArguments = {"\n", "\t", "\r", "", " "};

    OrgChart::OrgChart() {
        this->head = nullptr;
        this->iterationNode = nullptr;
    }

    OrgChart::OrgChart(OrgChart &other) {
        if (other.head == nullptr) {
            this->head = nullptr;
            this->iterationNode = nullptr;
            return;
        }
        queue<Node *> queue;
        queue.push(other.head);
        this->head = new Node(other.head->key);
        this->iterationNode = nullptr;
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == nullptr) {
                continue;
            }
            while (currentLeftMostSon != nullptr) {
                queue.push(currentLeftMostSon);
                this->add_sub(currentNode->key, currentLeftMostSon->key);
                currentLeftMostSon = currentLeftMostSon->next;
            }

        }
    }

    OrgChart::~OrgChart() {
        this->free();
    }

    void OrgChart::free() {
        if(this->head == nullptr){
            return;
        }
        queue<Node *> queue;
        queue.push(head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            Node *currentLeftMostSon = currentNode->leftMostSon;
            while (currentLeftMostSon != nullptr) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
            delete currentNode;
        }
    }

    OrgChart &OrgChart::add_root(const string &rootName) {
        validateName(rootName);
        if(head == nullptr) {
            this->head = new Node(rootName);
            return *this;
        }
        head->key = rootName;
        return *this;
    }

    OrgChart &OrgChart::add_sub(const string &superiorName, const string &subordinateName) {
        validateName(subordinateName);
        validateRoot();
        Node *superiorNode = getSuperior(superiorName);
        superiorNode->addSon(subordinateName);
        return *this;
    }

    Node *OrgChart::getSuperior(const string &superiorName) {
        queue<Node *> queue;
        queue.push(this->head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            if (currentNode->key == superiorName) {
                return currentNode;
            }
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == nullptr) {
                continue;
            }
            while (currentLeftMostSon != nullptr) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
        }
        throw invalid_argument("Superior Name Does Not Exist In Organization Chart!\n");
    }

    Node *OrgChart::getHead() {
        return this->head;
    }

    ChartIterator OrgChart::begin() {
        validateRoot();
        updateNodesForLevelOrder();
        return ChartIterator(iterationNode);
    }

    ChartIterator OrgChart::end() {
        validateRoot();
        updateNodesForLevelOrder();
        return ChartIterator(nullptr);
    }

    ChartIterator OrgChart::begin_level_order() {
        return begin();
    }

    ChartIterator OrgChart::end_level_order() {
        return end();
    }

    ChartIterator OrgChart::begin_reverse_order() {
        validateRoot();
        updateNodesForReverseLevelOrder();
        return ChartIterator(iterationNode);
    }

    ChartIterator OrgChart::reverse_order() {
        validateRoot();
        updateNodesForReverseLevelOrder();
        return ChartIterator(nullptr);
    }

    ChartIterator OrgChart::begin_preorder() {
        validateRoot();
        updateNodesForPreorder();
        return ChartIterator(iterationNode);
    }

    ChartIterator OrgChart::end_preorder() {
        validateRoot();
        updateNodesForPreorder();
        return ChartIterator(nullptr);
    }

    void OrgChart::updateNodesForLevelOrder() {
        iterationNode = head;
        queue<Node *> queue;
        queue.push(head);
        while (!queue.empty()) {
            Node *temp = queue.front();
            queue.pop();
            Node *currentSon = temp->leftMostSon;
            while (currentSon != nullptr) {
                queue.push(currentSon);
                currentSon = currentSon->next;
            }
            if (queue.empty()) {
                temp->nextInIteration = nullptr;
                return;
            }
            temp->nextInIteration = queue.front();
        }
    }

    void OrgChart::updateNodesForReverseLevelOrder() {
        queue<Node *> queue;
        queue.push(head);
        head->nextInIteration = nullptr;
        Node *lastInQueue = nullptr;
        while (!queue.empty()) {
            Node *temp = queue.front();
            queue.pop();
            Node *currentSon = nullptr;
            if (temp->rightMostSon == nullptr) {
                currentSon = temp->leftMostSon;
            } else {
                currentSon = temp->rightMostSon;
            }
            while (currentSon != nullptr) {
                queue.push(currentSon);
                currentSon = currentSon->prev;
            }
            if (queue.empty()) {
                temp->nextInIteration = lastInQueue;
                iterationNode = temp;
                return;
            }
            queue.front()->nextInIteration = temp;
            lastInQueue = temp;
        }
    }


    void OrgChart::updateNodesForPreorder() {
        iterationNode = head;
        stack<Node *> stack;
        stack.push(head);
        while (!stack.empty()) {
            Node *temp = stack.top();
            stack.pop();
            Node *currentSon = nullptr;
            if (temp->rightMostSon == nullptr) {
                currentSon = temp->leftMostSon;
            } else {
                currentSon = temp->rightMostSon;
            }
            while (currentSon != nullptr) {
                stack.push(currentSon);
                currentSon = currentSon->prev;
            }
            if (stack.empty()) {
                temp->nextInIteration = nullptr;
                return;
            }
            temp->nextInIteration = stack.top();
        }
    }

        std::ostream &operator<<(std::ostream &output, const OrgChart &chart) {
            if (chart.head == NULL) {
                return output;
            }
            queue<Node *> q;
            q.push(chart.head);
            while (!q.empty()) {
                int n = q.size();
                // If this node has children
                while (n > 0) {
                    // Dequeue an item from queue and print it
                    Node *currentNode = q.front();
                    q.pop();
                    output << currentNode->key << " ";

                    // Enqueue all children of the dequeued item
                    Node *currentSon = currentNode->leftMostSon;
                    while (currentSon != nullptr) {
                        q.push(currentSon);
                        currentSon = currentSon->next;
                    }
                    n--;
                }
                output << endl;
            }
            return output;
        }

        void validateName(const string &name) {
            for (uint i = 0; i < invalidArguments.size(); ++i) {
                if (name == invalidArguments[i]) {
                    throw invalid_argument("The Name Given Is Not In The Right Format!\n");
                }
            }
        }

        void OrgChart::validateRoot() {
            if (this->head == nullptr) {
                throw logic_error("Empty Tree Can Not Be Iterated Over!\n");
            }
        }

    }
