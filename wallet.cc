//
// Created by kacper on 08.11.18.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>

#include "wallet.h"

unsigned long long Wallet::currentLimitOfUnits = MAX_NUMBER_OF_UNITS;

Operation::Operation(unsigned long long unitsAfterOperation): units(unitsAfterOperation)
{
    timestamp = std::chrono::system_clock::now();
}

unsigned long long Operation::getUnits() const
{
    return units;
}

bool Operation::operator<(const Operation & b) const
{
    return timestamp < b.timestamp;
}

bool Operation::operator>(const Operation & b) const
{
    return timestamp > b.timestamp;
}

bool Operation::operator == (const Operation & b) const
{
    return timestamp == b.timestamp;
}

std::ostream &operator<<(std::ostream & os, const Operation & operation)
{
    std::time_t tmp = std::chrono::system_clock::to_time_t(operation.timestamp);
    os << "Wallet balance is " << Wallet::formatUnits(operation.units) <<  " B after operation made at day " <<
        std::put_time(std::localtime(&tmp), "%F");
    return os;
}

Wallet::Wallet()
{
    units = 0;
    addNewUnits(0);
    addNewOperation();
}

Wallet::Wallet(unsigned long numberOfB)
{
    units = 0;

    if (numberOfB > MAX_NUMBER_OF_B)
    {
        throw std::invalid_argument("Argument " + std::to_string(numberOfB) +
            " given to the Wallet's constructor represents too many Bs");
    }

    addNewUnits(UNITS_IN_ONE_B * numberOfB);
    addNewOperation();
}

Wallet::Wallet(int numberOfB)
{
    units = 0;

    if(numberOfB < 0)
    {
        throw std::invalid_argument("Argument " + std::to_string(numberOfB) +
                                    "  given to the Wallet's constructor is negative");
    }

    if (numberOfB > (long long)MAX_NUMBER_OF_B)
    {
        throw std::invalid_argument("Argument " + std::to_string(numberOfB) +
                                    " given to the Wallet's constructor represents too many Bs");
    }

    addNewUnits(UNITS_IN_ONE_B * numberOfB);
    addNewOperation();
}

Wallet::Wallet(const char *str) : Wallet(std::string(str)){}

Wallet::Wallet(const std::string & str)
{
    units = 0;
    std::string in = str;
    // Check if string constains commas
    if(in.find(',') != std::string::npos)
    {
        in.replace(in.find(','), 1, ".");
    }

    if (str.find("-") != std::string::npos)
    {
        throw std::invalid_argument("Argument " + str +
                                    " given to the Wallet's constructor represents negative number of Bs");
    }

    double tmp = stod(in);

    // Plus 1 is added to negate possible floating point inaccuracies.
    if (tmp > (double)MAX_NUMBER_OF_B + 1)
    {
        throw std::invalid_argument("Argument " + str +
            " given to the Wallet's constructor represents too many units.");
    }

    addNewUnits(std::round(tmp * UNITS_IN_ONE_B));
    addNewOperation();
}

Wallet::Wallet(Wallet &&wallet): units(wallet.units), history(std::move(wallet.history))
{
    wallet.units = 0;
    addNewOperation();
}

Wallet::Wallet(Wallet &&wallet1, Wallet &&wallet2)
{
    units = wallet1.units + wallet2.units;
    wallet1.units = 0;
    wallet2.units = 0;

    if (wallet1.history.size() > wallet2.history.size())
    {
        history = std::move(wallet1.history);
        history.insert(history.end(), wallet2.history.begin(), wallet2.history.end());
    }
    else
    {
        history = std::move(wallet2.history);
        history.insert(history.end(), wallet1.history.begin(), wallet1.history.end());
    }

    std::sort(history.begin(), history.end());
    addNewOperation();
}

Wallet & Wallet::operator += (Wallet &wallet)
{
    units += wallet.units;
    wallet.units = 0;

    addNewOperation();
    wallet.addNewOperation();

    return *this;
}

Wallet & Wallet::operator += (Wallet &&wallet)
{
    return (*this) += wallet;
}

Wallet & Wallet::operator -= (Wallet &wallet)
{
    if (units < wallet.units)
    {
        throw std::invalid_argument("Attempt to subtract more units than present in the given wallet.");
    }

    units -= wallet.units;
    wallet.units *= 2ll;

    addNewOperation();
    wallet.addNewOperation();

    return *this;
}

Wallet & Wallet::operator -= (Wallet &&wallet)
{
    return (*this) -= wallet;
}

Wallet & Wallet::operator *= (unsigned long long multiplier)
{
    if (multiplier >= (MAX_NUMBER_OF_UNITS / units) + 1ll)
    {
        throw std::invalid_argument("Multiplier " + std::to_string(multiplier) +
            " is too large");
    }

    addNewUnits(units * (multiplier - 1ll));
    addNewOperation();

    return *this;
}

Wallet & Wallet::operator = (Wallet &&wallet)
{
    if (this == &wallet)
    {
        return *this;
    }

    units = wallet.units;
    wallet.units = 0;
    history = std::move(wallet.history);

    addNewOperation();
    return *this;
}

std::ostream &operator<<(std::ostream & os, const Wallet & wallet)
{
    os << "Wallet[" << Wallet::formatUnits(wallet.units) << " B]";
    return os;
}

unsigned long long Wallet::getUnits() const
{
    return units;
}

const Operation Wallet::operator[](unsigned long i) const
{
    return history.at(i);
}

std::size_t Wallet::opSize() const
{
    return history.size();
}

bool operator < (const Wallet & wallet, const Wallet & wallet1)
{
    return wallet.units < wallet1.units;
}

bool operator == (const Wallet & wallet,const Wallet & wallet1)
{
    return wallet.units == wallet1.units;
}


Wallet operator + (Wallet &&wallet1, Wallet &wallet2)
{
    Wallet result = std::move(wallet1 += wallet2);
    result.history.pop_back();
    return result;
}

 Wallet operator + (Wallet &&wallet1, Wallet &&wallet2)
{
    return std::move(wallet1) + wallet2;
}

Wallet operator - (Wallet &&wallet1, Wallet &wallet2)
{
    Wallet result = std::move(wallet1 -= wallet2);
    result.history.pop_back();
    return result;
}

Wallet operator - (Wallet &&wallet1, Wallet &&wallet2)
{
    return std::move(wallet1) - wallet2;
}

Wallet &&operator * (Wallet &&wallet, unsigned long long multiplier)
{
    return wallet * multiplier;
}

Wallet &&operator * (unsigned long long multiplier, Wallet &&wallet)
{
    return wallet * multiplier;
}

Wallet &&operator * (Wallet &wallet, unsigned long long multiplier)
{
    return std::move(wallet *= multiplier);
}

Wallet &&operator * (unsigned long long multiplier, Wallet &wallet)
{
    return wallet * multiplier;
}

Wallet::~Wallet()
{
    addNewUnits(-((long long)units));
}

const Wallet & Empty()
{
    static const Wallet *wallet = new Wallet();
    return *wallet;
}

Wallet Wallet::fromBinary(const std::string &str)
{
    if (!std::all_of(str.begin(), str.end(), [](char c){return c == '0' || c == '1';}))
    {
        throw std::invalid_argument("Wallet::fromBinary: Argument " +
            str + " is not a walid binary number.");
    }

    std::size_t firstOne = 0;
    std::size_t index = 0;
    for (char ch : str)
    {
        index++;

        if (ch == '1')
        {
            firstOne = index;
            break;
        }
    }

    if ((firstOne > 0) && (str.size() - firstOne + 1 > MAX_NUMBER_OF_B_LOG_CEIL))
    {
        throw std::invalid_argument("Argument "
          + str + " represents too large binary number.");
    }

    if (firstOne == 0)
    {
        return Wallet();
    }
    else
    {
        return Wallet((unsigned long) std::stol(str, nullptr, 2));
    }
}

void Wallet::addNewOperation()
{
    history.push_back(units);
}

void Wallet::addNewUnits(long long newUnits)
{
    if (newUnits > (long long)currentLimitOfUnits)
    {
        throw std::invalid_argument("Number of new units exceeded \
the current limit.");
    }

    units += newUnits;
    currentLimitOfUnits -= newUnits;
}
// Returns string formated for printing
std::string Wallet::formatUnits(unsigned long units)
{
    std::string in = std::to_string(units / (double)Wallet::UNITS_IN_ONE_B);
    // Check if string contains commas
    unsigned long index = in.find('.');
    if(index != std::string::npos)
    {
        in.replace(index, 1, ",");
    }
    unsigned long i = in.size() - 1;
    // Removes trailing 0
    while (in[i] == '0')
    {
        i--;
    }

    if(i + 2 < in.size())
    {
        in.erase(i + 2, in.size() - i);
    }

    return in;
}
