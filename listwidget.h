#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#pragma once

#include "item.h"
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QIODevice>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QComboBox>
#include <QSpacerItem>
#include <QLegend>

class ListWidget : public QWidget
{

    Q_OBJECT

public:
    // put any more important variables here
    // like a total balance of money!
    QList<item> listitems;
    int numitems;
    ListWidget(QWidget *parent = 0);
    // void filestuff();
    // QPieSeries *series;
    float balance = 1000,
          T_total = 0,
          T_food = 0,
          T_bills = 0,
          T_fun = 0,
          T_trans = 0,
          T_med = 0,
          T_other = 0;
    // static ListWidget * Get() { return widgets; }

private slots:
    // put buttons here
    void addItem();
    void editItem();
    void removeItem();
    void setBudget();

private:
    // this is where you add new text boxes
    QLabel *totalbudget,
        *totalfood,
        *totalbills,
        *totalfun,
        *totaltrans,
        *totalmedical,
        *totalother,
        *amtremaining;
    QPieSlice *leftslice;
    QPieSeries *series;
    QListWidget *allnames,
        *allvalues,
        *allcategories,
        *allids;
    // this is new buttons
    QPushButton *add,
        *edit,
        *remove,
        *budget;

    // static ListWidget * widgets;

    QCalendarWidget *calendar;
};

#endif // LISTWIDGET_H
