#include "Chaining.h"
// const int prime = 31;              
// const int mod = 1000003;         
void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int token = hash(id);
    while(databaseSize()<=token) {
        bankStorage2d.push_back({});
    }
    Account account;
    account.id = id;    
    account.balance = count;
    bankStorage2d[token].push_back(account);
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> topBalances;

    for (int i = 0; i < bankStorage2d.size(); ++i) {
        for (int j = 0; j < bankStorage2d[i].size(); ++j) {
            int balance = bankStorage2d[i][j].balance;

            if (topBalances.size() < k) {
                topBalances.push_back(balance);
            } else {
                //smallest balance 
                int minBalance = topBalances[0];
                int minIndex = 0;
                for (int l = 1; l < k; ++l) {
                    if (topBalances[l] < minBalance) {
                        minBalance = topBalances[l];
                        minIndex = l;
                    }
                }

                if (balance > minBalance) {
                    topBalances[minIndex] = balance;
                }
            }
        }
    }

    //selection sort
    for (int i = 0; i < topBalances.size() - 1; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < topBalances.size(); ++j) {
            if (topBalances[j] > topBalances[maxIndex]) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            std::swap(topBalances[i], topBalances[maxIndex]);
        }
    }

    return topBalances;
}


int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int token = hash(id);
    if(token>=databaseSize()) {
        return -1;
    }
    for(int it = 0; it<bankStorage2d[token].size(); it++) {
        if(bankStorage2d[token][it].id == id) {
            return bankStorage2d[token][it].balance; 
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int token = hash(id);
    if(token>=databaseSize()) {
        return;
    }
    for(int it = 0; it<bankStorage2d[token].size(); it++) {
        if(bankStorage2d[token][it].id == id) {
            bankStorage2d[token][it].balance+=count;
            return;
        }
    }
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int token = hash(id);
    if(token>=databaseSize()) {
        return false;
    }
    for(int it = 0; it<bankStorage2d[token].size(); it++) {
        if(bankStorage2d[token][it].id == id) {
            return true;
        }
    }
    
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int token = hash(id);
    if(token>=databaseSize()) {
        return false;
    }
    for(int it = 0; it<bankStorage2d[token].size(); it++) {
        if(bankStorage2d[token][it].id == id) {
            bankStorage2d[token].erase(bankStorage2d[token].begin() + it);
            return true;
        }
    }
    
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    int size = 0;
    for(auto& chain:bankStorage2d) {
        size += chain.size();
    }
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    long long sum = 0;
    for(char c:id) {
        sum = (sum*prime + c)%mod;
    }
    return (int)sum; // Placeholder return value
}

