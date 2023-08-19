#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    struct Node {
        std::string id;
        int balance;
        Node* next;
        Node(std::string _id, int _balance) : id(_id), balance(_balance), next(nullptr) {}
    };
    
    std::vector<Node*> hashTable;
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
