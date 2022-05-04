#ifndef CATEGORY_H
#define CATEGORY_H
#include "setMatrix.h"
#include <QString>
#include <iostream>

class Category
{
private:
    float total = 0;
    int temp_c = 0;
    setMatrix *instA;
    setMatrix *instB;

public:
    float expense = 0;
    float balance;
    float Available_balance; // the value you would show
    // totals
    float T_O = 0;   // other
    float T_M = 0;   // Medical
    float T_T = 0;   // Transpo
    float T_F = 0;   // Fun
    float T_MB = 0;  // Monthly bills
    float T_FOO = 0; // Food
    float T_TOTAL = 0;
    // percentages
    float P_O = T_O / T_TOTAL;
    float P_M = T_M / T_TOTAL;
    float P_T = T_T / T_TOTAL;
    float P_F = T_F / T_TOTAL;
    float P_MB = T_MB / T_TOTAL;
    float P_FOO = T_FOO / T_TOTAL;
    QString cat;
    QString name;

    void setVal(float E, QString C, QString N);
    void setTotal(float expense, QString ct);
    void setBalance(float blnc);
    void setPerc(float partial);
    void set_category(float value, QString catg);
    float peakExp();
    QString peakDesc();
    QString peakCat();
};

#endif // CATEGORY_H
