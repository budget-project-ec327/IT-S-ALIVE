#include "category.h"
#include "setMatrix.h"
#include <QString>
#include <iostream>

using namespace std;

void Category::setVal(float E, QString C, QString N)
{
    expense = E;
    cat = C;
    name = N;
}
// I WANTED TO USE A SWITCH STATEMENT BUT NOOOOOOOO, QSTRING DOESNT ALLOW THAT
void Category::setTotal(float exp, QString ct)
{
    if (ct == "Other")
    {
        T_O = T_O + exp;
    }
    else if (ct == "Medical")
    {
        T_M = T_M + exp;
    }
    else if (ct == "Transportation")
    {
        T_T = T_T + exp;
    }
    else if (ct == "Fun")
    {
        T_F = T_F + exp;
    }
    else if (ct == "Monthly Bills")
    {
        T_MB = T_MB + exp;
    }
    else if (ct == "Food")
    {
        T_FOO = T_FOO + exp;
    }
    T_TOTAL = T_O + T_M + T_T + T_F + T_MB + T_FOO;
    Available_balance = balance - T_TOTAL;
}

void Category::setBalance(float blnc)
{
    balance = blnc;
    Available_balance = balance - T_TOTAL;
}

float Category::peakExp()
{
    return expense;
}

QString Category::peakDesc()
{
    return name;
}
QString Category::peakCat()
{
    return cat;
}
