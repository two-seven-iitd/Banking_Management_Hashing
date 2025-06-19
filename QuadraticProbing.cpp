#include "QuadraticProbing.h"

constexpr int prime = 31;
constexpr int mod = 100003;

QuadraticProbing::QuadraticProbing() {
    database_size = 0;
    bankStorage1d.resize(mod);
    for (int i = 0; i < mod; i++) {
        bankStorage1d[i].id = "NULL";
        bankStorage1d[i].balance = 0;
    }
}
// int nextPowerOf2(int m)
// {
//     m--;
//     m |= m >> 1;
//     m |= m >> 2;
//     m |= m >> 4;
//     m |= m >> 8;
//     m |= m >> 16;
//     //m |= m >> 32;
//     m++;
//     return m;
// }
void QuadraticProbing::createAccount(std::string id, int count) {
    int original_hash = hash(id);
    for (long long i = 0; i < mod; ++i) {
        int index = (original_hash + i * i) % mod;
        // (i + i*i)/2 )%nextPowerOf2(mod);
            
        if (bankStorage1d[index].id == id) return; // already exists

        if (bankStorage1d[index].id == "NULL" || bankStorage1d[index].id == "DEL") {
            bankStorage1d[index].id = id;
            bankStorage1d[index].balance = count;
            database_size++;
            return;
        }
    }
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> topBalances;
    if (k <= 0) return topBalances;

    std::vector<int> indices;
    for (long long i = 0; i < mod; ++i) {
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

int QuadraticProbing::getBalance(std::string id) {
    int original_hash = hash(id);
    for (int i = 0; i < mod; ++i) {
        int index = (original_hash + i * i) % mod;

        if (bankStorage1d[index].id == "NULL") break; // not found
        if (bankStorage1d[index].id == id) return bankStorage1d[index].balance;
    }
    return -1;
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int original_hash = hash(id);
    for (long long i = 0; i < mod; ++i) {
        int index = (original_hash + i * i) % mod;

        if (bankStorage1d[index].id == id) {
            bankStorage1d[index].balance += count;
            return;
        }

        if (bankStorage1d[index].id == "NULL" || bankStorage1d[index].id == "DEL") {
            bankStorage1d[index].id = id;
            bankStorage1d[index].balance = count;
            database_size++;
            return;
        }
    }
}

bool QuadraticProbing::doesExist(std::string id) {
    int original_hash = hash(id);
    for (long long i = 0; i < mod; ++i) {
        int index = (original_hash + i * i) % mod;

        if (bankStorage1d[index].id == "NULL") break;
        if (bankStorage1d[index].id == id) return true;
    }
    return false;
}

bool QuadraticProbing::deleteAccount(std::string id) {
    int original_hash = hash(id);
    for (long long i = 0; i < mod; ++i) {
        int index = (original_hash + i * i) % mod;

        if (bankStorage1d[index].id == "NULL") break;
        if (bankStorage1d[index].id == id) {
            bankStorage1d[index].id = "DEL";
            bankStorage1d[index].balance = 0;
            database_size--;
            return true;
        }
    }
    return false;
}

int QuadraticProbing::databaseSize() {
    return database_size;
}

int QuadraticProbing::hash(std::string id) {
    long long sum = 0;
    for (char c : id) {
        sum = (sum * prime + c) % mod;
    }
    return (int)sum;
}
