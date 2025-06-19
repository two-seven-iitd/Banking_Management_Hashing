#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <chrono> 

void testDatabase(BaseClass *db) {
    db->createAccount("Alice", 1000);
    db->createAccount("Bob", 1500);
    db->createAccount("Charlie", 2000);
    std::cout << "Size is: " << db->databaseSize() << std::endl;

    assert(db->getBalance("Alice") == 1000);
    assert(db->getBalance("Bob") == 1500);
    assert(db->getBalance("Charlie") == 2000);

    db->addTransaction("Alice", -200);
    db->addTransaction("Bob", 300);
    db->addTransaction("Charlie", -400);

    assert(db->getBalance("Alice") == 800);
    assert(db->getBalance("Bob") == 1800);
    assert(db->getBalance("Charlie") == 1600);

    std::vector<int> topBalances = db->getTopK(2);
    assert(topBalances.size() == 2);
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1600);

    assert(db->databaseSize() == 3);
    assert(db->doesExist("Alice"));
    assert(!db->doesExist("Eve"));
}

void testHeavyOperations(BaseClass *db) {
    const int N = 90000;
    std::cout << "Starting heavy test..." << std::endl;

    // Initial insertion
    for (int i = 0; i < N; i++) {
        db->createAccount("user" + std::to_string(i), i);
    }
    std::cout << "size is: " << db->databaseSize() << "\n";
    assert(db->databaseSize() - 3 == N);

    // Transactions
    for (int i = 0; i < N; i++) {
        db->addTransaction("user" + std::to_string(i), 1000);
    }

    // Check balances
    for (int i = 0; i < N; i++) {
        int expected = i + 1000;
        int actual = db->getBalance("user" + std::to_string(i));
        assert(actual == expected);
    }

    // Existence
    assert(db->doesExist("user89999"));
    assert(!db->doesExist("non_existing_user"));

    // getTopK correctness
    std::vector<int> top = db->getTopK(10);
    assert(top.size() == 10);
    for (int i = 0; i < 9; i++) {
        assert(top[i] >= top[i + 1]);
    }

    std::cout << "Heavy test passed for size: " << db->databaseSize() << std::endl;

    // Now delete all entries
    for (int i = 0; i < N; ++i) {
        bool deleted = db->deleteAccount("user" + std::to_string(i));
        assert(deleted); // Each delete must succeed
    }
    std::cout << "All accounts deleted. Size now: " << db->databaseSize() << "\n";
    assert(db->databaseSize() == 3); // Only the original 3 from basic test remain

    // Re-insert
    for (int i = 0; i < N; ++i) {
        db->createAccount("user" + std::to_string(i), i + 500);
    }
    std::cout << "Reinserted all accounts. Size now: " << db->databaseSize() << "\n";
    assert(db->databaseSize() - 3 == N); // Confirm all were re-added
}


void runWithTiming(const std::string &name, BaseClass *db) {
    std::cout << "Testing " << name << ":" << std::endl;

    auto startBasic = std::chrono::high_resolution_clock::now();
    testDatabase(db);
    auto endBasic = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> basicTime = endBasic - startBasic;
    std::cout << "Basic test took: " << basicTime.count() << " ms\n";

    auto startHeavy = std::chrono::high_resolution_clock::now();
    testHeavyOperations(db);
    auto endHeavy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> heavyTime = endHeavy - startHeavy;
    std::cout << "Heavy test took: " << heavyTime.count() << " ms\n";
    std::cout << "---------------------------\n";
}

int main() {
    Chaining chainingDB;
    LinearProbing linearProbingDB;
    QuadraticProbing quadraticProbingDB;
    CubicProbing cubicProbingDB;
    Comp compDB;

    runWithTiming("Chaining", &chainingDB);
    runWithTiming("Linear Probing", &linearProbingDB);
    runWithTiming("Quadratic Probing", &quadraticProbingDB);
    runWithTiming("Cubic Probing", &cubicProbingDB);
    runWithTiming("Comp", &compDB);

    return 0;
}
