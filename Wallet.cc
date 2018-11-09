//
// Created by kacper on 08.11.18.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include "Wallet.h"

Operation::Operation(unsigned long untisAfterOperation): units(untisAfterOperation)
{
    time = std::chrono::system_clock::now();
}

unsigned long Operation::getUnits() const
{
    return units;
}

bool Operation::operator<(const Operation & b)
{
    return time < b.time;
}

bool Operation::operator>(const Operation & b)
{
    return time > b.time;
}

bool Operation::operator==(const Operation & b)
{
    return time == b.time;
}

Wallet::Wallet()
{
    units = 0;
    history.push_back(Operation(0));
}

Wallet::Wallet(const std::string & str)
{
    double tmp = stod(str);
    units = floor(tmp * MULTI);
    history.push_back(Operation(units));
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

unsigned long Wallet::opSize() const
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
    std::time_t tmp = std::chrono::system_clock::to_time_t(operation.time);
    os << "Wallet balance is " << operation.units << " B after operation made at day " << std::put_time(std::localtime(&tmp), "%F");
    return os;
}

const Wallet Empty() const
{
    return Wallet();
}

