//
// Created by kacper on 08.11.18.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "wallet.h"

Operation::Operation(unsigned long untisAfterOperation): units(untisAfterOperation)
{
    timestamp = std::chrono::system_clock::now();
}

unsigned long Operation::getUnits() const
{
    return units;
}

bool Operation::operator<(const Operation & b)
{
    return timestamp < b.timestamp;
}

bool Operation::operator>(const Operation & b)
{
    return timestamp > b.timestamp;
}

bool Operation::operator==(const Operation & b)
{
    return timestamp == b.timestamp;
}

Wallet::Wallet()
{
    units = 0;
    addNewOperation();
}

Wallet::Wallet(unsigned long numberOfB)
{
    units = numberOfB * UNITS_IN_ONE_B;
    addNewOperation();
}

Wallet::Wallet(const std::string & str)
{
    double tmp = stod(str);
    units = floor(tmp * MULTI);
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
    os << "Wallet[" << std::to_string(wallet.units / MULTI) << " B]";
    return os;
}

unsigned long Wallet::getUnits() const
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

void Wallet::operator+=(Wallet & w1)
{
    unsigned long tmp = w1.units;
    w1.units = 0;
    units = tmp;
    w1.addNewOperation();
    addNewOperation();
}

void Wallet::addNewOperation()
{
    history.push_back(units);
}

std::ostream &operator<<(std::ostream & os, const Operation & operation)
{
    std::time_t tmp = std::chrono::system_clock::to_time_t(operation.timestamp);
    os << "Wallet balance is " << operation.units << " B after operation made at day " << std::put_time(std::localtime(&tmp), "%F");
    return os;
}

const Wallet Empty()
{
    return Wallet();
}
