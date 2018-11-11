//
// Created by kacper on 08.11.18.
//

#ifndef JNP1_ZADANIE3_WALLET_H
#define JNP1_ZADANIE3_WALLET_H

#define MULTI 100000000.0

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <boost/operators.hpp>

class Operation
{
private:
    std::chrono::system_clock::time_point timestamp;
    unsigned long units;
public:
    Operation(unsigned long);

    unsigned long getUnits() const;
    bool operator < (const Operation &);
    bool operator > (const Operation &);
    bool operator == (const Operation &);

    friend std::ostream& operator<< (std::ostream&, const Operation &);
};

class Wallet
{
public:
    Wallet();
    Wallet(unsigned long);
    Wallet(const std::string &);
    Wallet(Wallet &&);
    Wallet(Wallet &&, Wallet &&);

    Wallet & operator = (Wallet &&);
    unsigned long getUnits() const;
    std::size_t opSize() const;
    const Operation operator[](unsigned long) const;
    void operator += (Wallet &);

    friend std::ostream& operator<< (std::ostream&, const Wallet &);
private:
    static const unsigned long UNITS_IN_ONE_B = 1e8;

    unsigned long units;
    std::vector<Operation> history;

    void addNewOperation();
};

const Wallet Empty();

#endif // JNP1_ZADANIE3_WALLET_H