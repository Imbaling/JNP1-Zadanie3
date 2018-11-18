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

class Operation : public boost::equality_comparable<Operation>, public boost::less_than_comparable<Operation>
{
private:
    friend class Wallet;

    std::chrono::system_clock::time_point timestamp;
    unsigned long long units;
    // Zakrywam dostęp do konstruktorów
    Operation(unsigned long long);
    Operation() = default;
public:
    unsigned long long getUnits() const;
    // Pozostałe operatory są generowane automatycznie
    const bool operator < (const Operation &) const;
    const bool operator > (const Operation &) const;
    const bool operator == (const Operation &) const;

    friend std::ostream& operator<< (std::ostream&, const Operation &);
};

class Wallet : public boost::equality_comparable<Wallet, Wallet>, public boost::less_than_comparable<Wallet, Wallet>
{
public:
    static Wallet fromBinary(const std::string &);

    Wallet();
    Wallet(unsigned long);
    explicit Wallet(const std::string &);
    explicit Wallet(Wallet &&);
    explicit Wallet(Wallet &&, Wallet &&);

    const bool operator < (const Wallet &) const;
    const bool operator > (const Wallet &) const;
    //const bool operator == (const Wallet &);

    friend const bool operator == (const Wallet & wallet, const Wallet & wallet1);
    friend const bool operator == (Wallet & wallet,const Wallet & wallet1);

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

    ~Wallet();
private:
    static const unsigned long long MAX_NUMBER_OF_B = 2.1e7;
    static const unsigned long long UNITS_IN_ONE_B = 1e8;
    static const unsigned long long MAX_NUMBER_OF_UNITS = MAX_NUMBER_OF_B *
        UNITS_IN_ONE_B;
    static const unsigned int MAX_NUMBER_OF_B_LOG_CEIL = 25;

    static unsigned long long currentLimitOfUnits;

    unsigned long long units;
    std::vector<Operation> history;

    // This function is used only when we modify (add or remove) new units from
    // the global pool. It adds the given number of units (could be negative)
    // to the given Wallet object. It also keep track of the remaining units
    // in the global pool.
    void addNewUnits(long long);
    void addNewOperation();
};

const Wallet Empty();

#endif // JNP1_ZADANIE3_WALLET_H
