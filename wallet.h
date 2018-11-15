//
// Created by kacper on 08.11.18.
//

#ifndef JNP1_ZADANIE3_WALLET_H
#define JNP1_ZADANIE3_WALLET_H

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <boost/operators.hpp>

class Operation
{
private:
    friend class Wallet;

    Operation(unsigned long long);

    std::chrono::system_clock::time_point timestamp;
    unsigned long long units;

public:
    unsigned long long getUnits() const;
    bool operator < (const Operation &);
    bool operator > (const Operation &);
    bool operator == (const Operation &);

    friend std::ostream& operator<< (std::ostream&, const Operation &);
};

class Wallet
{
public:
    static Wallet fromBinary(const std::string &);

    Wallet();
    Wallet(unsigned long);
    Wallet(const std::string &);
    Wallet(Wallet &&);
    Wallet(Wallet &&, Wallet &&);

    Wallet & operator = (Wallet &&);
    Wallet & operator += (Wallet &wallet);
    Wallet & operator -= (Wallet &wallet);
    Wallet & operator *= (unsigned long long multiplier);
    Wallet & operator += (Wallet &&wallet);
    Wallet & operator -= (Wallet &&wallet);

    unsigned long long getUnits() const;
    std::size_t opSize() const;
    const Operation operator[](unsigned long) const;

    friend std::ostream& operator<< (std::ostream&, const Wallet &);
    friend Wallet operator + (Wallet &&wallet1, Wallet &wallet2);
    friend Wallet operator - (Wallet &&wallet1, Wallet &wallet2);
    friend Wallet operator + (Wallet &&wallet1, Wallet &wallet2);
    friend Wallet operator - (Wallet &&wallet1, Wallet &&wallet2);
    friend Wallet operator * (Wallet &&wallet, unsigned long long multiplier);
    friend Wallet operator * (unsigned long long multiplier, Wallet &&wallet);
private:
    static const unsigned long long MAX_NUMBER_OF_B = 2.1e7;
    static const unsigned long long UNITS_IN_ONE_B = 1e8;
    static const unsigned long long MAX_NUMBER_OF_UNITS = MAX_NUMBER_OF_B *
        UNITS_IN_ONE_B;
    static const unsigned int MAX_NUMBER_OF_B_LOG_CEIL = 25;

    unsigned long long units;
    std::vector<Operation> history;

    void addNewOperation();
    void addNewUnits(unsigned long long);
};

const Wallet Empty();

#endif // JNP1_ZADANIE3_WALLET_H
