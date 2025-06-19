#include "LinearProbing.h"


constexpr int prime = 31;
constexpr int mod = 100003;

LinearProbing::LinearProbing() { 
    bankStorage1d.resize(100003);
    database_size = 0;
    // balance = -1 && empty account name = deleted
    // balance = 0 && empty account = not present
    for(int i=0; i<bankStorage1d.size(); i++) {
        bankStorage1d[i].id = "NULL";
        bankStorage1d[i].balance = 0;
    }
}

void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int index = hash(id);
    int start = index;
    while(true) {
        if(bankStorage1d[index].id == id ) {
            return;
            // already present
        }
        if(bankStorage1d[index].id == "NULL" || bankStorage1d[index].id == "DEL") {
            Account account;
            account.id = id; account.balance = count;
            bankStorage1d[index] = account;
            database_size++;
            return;
        }
        index = (index+1)%mod;
        if(start == index) {
            break;
            // no more accounts can be added
        }
    }

}

std::vector<int> LinearProbing::getTopK(int k) {
    std::vector<int> topBalances;
    if (k <= 0) return topBalances;

    std::vector<int> indices;
    for (int i = 0; i < mod; ++i) {
        if (bankStorage1d[i].id != "NULL" && bankStorage1d[i].id != "DEL") {
            indices.push_back(i);
        }
    }

    for (int i = 0; i < k && i < indices.size(); ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < indices.size(); ++j) {
            if (bankStorage1d[indices[j]].balance > bankStorage1d[indices[maxIndex]].balance) {
                maxIndex = j;
            }
        }
        int temp = indices[i];
        indices[i] = indices[maxIndex];
        indices[maxIndex] = temp;
        topBalances.push_back(bankStorage1d[indices[i]].balance);
    }

    return topBalances;
}


int LinearProbing::getBalance(std::string id) {
    int index = hash(id);
    int start = index;

    while(bankStorage1d[index].id!="NULL") {
        
        if(bankStorage1d[index].id == id) {
            return bankStorage1d[index].balance;
        }
        index = (index+1)%mod;

        if(start == index) {
            break;
        }
    }
    return -1;
    
    
}

void LinearProbing::addTransaction(std::string id, int count) {
    int index = hash(id);
    int start = index;

    while (true) {
        if (bankStorage1d[index].id == id) {
            bankStorage1d[index].balance += count;
            return;
        }

        if (bankStorage1d[index].id == "NULL" ) {
            bankStorage1d[index].id = id;
            bankStorage1d[index].balance = count;
            database_size++;
            return;
        }

        index = (index + 1) % mod;
        if (index == start) break; // table full
    }
}


bool LinearProbing::doesExist(std::string id) {
    int index = hash(id);
    int start = index;

    while(bankStorage1d[index].id != "NULL") {
        
        if(bankStorage1d[index].id == id) {
            return true;
        }
        index = (index+1)%mod;

        if(start == index) {
            break;
        }
    }
    return false;
}


bool LinearProbing::deleteAccount(std::string id) {
    if (!doesExist(id)) return false;

    int index = hash(id);
    int start = index;

    while(bankStorage1d[index].id !="NULL") {
        
        if(bankStorage1d[index].id == id) {
            bankStorage1d[index].id = "DEL";
            bankStorage1d[index].balance = 0;
            database_size--;
            return true;
         }
        index = (index + 1)%mod;
        if(start == index) {
            break;
        }
    }

    return false;
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return database_size; // Placeholder return value
}


int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    long long sum = 0;
    for(char c:id) {
        sum = (sum*prime + c)%mod;
    }
    return (int)sum; // Placeholder return value
}
