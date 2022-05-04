#include "listwidget.h"
#include "item.h"
#include "category.h"
//#include "FileManager.h"
#include <QDebug>
// this gets run at the begining of the program, sets everything up
ListWidget::ListWidget(QWidget *parent) : QWidget(parent)
{
    // some graphical stuff
    calendar = new QCalendarWidget;
    calendar->setGridVisible(true);
    QLabel *itemname = new QLabel("Label");
    QLabel *itemid = new QLabel("Item ID");
    QLabel *itemcategory = new QLabel("Category");
    QLabel *itemvalue = new QLabel("Amount (USD)");
    QHBoxLayout *layoutTop = new QHBoxLayout();
    QVBoxLayout *layoutFull = new QVBoxLayout();
    QHBoxLayout *layouttotal = new QHBoxLayout();
    QHBoxLayout *layoutfood = new QHBoxLayout();
    QHBoxLayout *layoutfun = new QHBoxLayout();
    QHBoxLayout *layoutother = new QHBoxLayout();
    QHBoxLayout *layoutmed = new QHBoxLayout();
    QHBoxLayout *layouttrans = new QHBoxLayout();
    QHBoxLayout *layoutbills = new QHBoxLayout();
    QHBoxLayout *layoutremaining = new QHBoxLayout();
    QVBoxLayout *layoutNumbers = new QVBoxLayout();
    QVBoxLayout *layoutNumLabels = new QVBoxLayout();
    QVBoxLayout *layoutbuttons = new QVBoxLayout();
    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *layoutLabels = new QVBoxLayout();
    QVBoxLayout *layoutId = new QVBoxLayout();
    QVBoxLayout *layoutCat = new QVBoxLayout();
    QVBoxLayout *layoutAmt = new QVBoxLayout();
    // important!! when adding a new text box add it here or it'll crash!
    allnames = new QListWidget;
    allnames->setStyleSheet("QListWidget::item { background-color: white;border-bottom: 1px solid gray; }"
                            "QListWidget::item:selected{color: #333538;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #cdcdcd, stop: 1 #ababab); border-top: 1px solid;border-top-color: #a8abad;border-bottom: 1px solid;border-bottom-color: #bfc7ce;}");
    allvalues = new QListWidget;
    allvalues->setStyleSheet("QListWidget::item { background-color: white;border-bottom: 1px solid black; }"
                             "QListWidget::item:selected{color: #333538;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #cdcdcd, stop: 1 #ababab); border-top: 1px solid;border-top-color: #a8abad;border-bottom: 1px solid;border-bottom-color: #bfc7ce;}");
    allcategories = new QListWidget;
    allcategories->setStyleSheet("QListWidget::item { background-color: white;border-bottom: 1px solid black; }"
                                 "QListWidget::item:selected{color: #333538;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #cdcdcd, stop: 1 #ababab); border-top: 1px solid;border-top-color: #a8abad;border-bottom: 1px solid;border-bottom-color: #bfc7ce;}");
    allids = new QListWidget;
    allids->setStyleSheet("QListWidget::item { background-color: white;border-bottom: 1px solid black; }"
                          "QListWidget::item:selected{color: #333538;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #cdcdcd, stop: 1 #ababab); border-top: 1px solid;border-top-color: #a8abad;border-bottom: 1px solid;border-bottom-color: #bfc7ce;}");
    // sets up all the balances stuff
    // some variables
    QStringList dstringList;
    numitems = 0;
    QString holdname,
        holdvalue,
        holdcategory,
        holdid;
    // reads the saved balance
    QFile balanceFile("balance.txt");
    balanceFile.open(QFile::ReadWrite | QFile::Text);
    QTextStream btextStream(&balanceFile);
    while (true)
    {
        QString line = btextStream.readLine();
        if (line.isNull())
            break;
        else
        {
            balance = line.toFloat();
        }
    }
    balanceFile.close();
    // keeps just the most recent starting balance
    QFile killbalance("balance.txt");
    killbalance.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream b(&killbalance);
    b << QString::number(balance) << "\n";
    killbalance.close();
    // reads any deletes made last session
    QFile deletedFile("deleted.txt");
    deletedFile.open(QFile::ReadWrite | QFile::Text);
    QTextStream dtextStream(&deletedFile);
    while (true)
    {
        QString line = dtextStream.readLine();
        if (line.isNull())
            break;
        else
        {
            dstringList.append(line);
        }
    }
    deletedFile.close();
    // erases delete file to be refilled
    QFile killdeleted("deleted.txt");
    killdeleted.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream d(&killdeleted);
    d << "";
    killdeleted.close();
    // reads any changes made last session
    // puts them in a list of items to copy from
    QList<item> changeditems;
    QStringList cids;
    QFile changedFile("changed.txt");
    changedFile.open(QFile::ReadWrite | QFile::Text);
    QTextStream ctextStream(&changedFile);
    while (true)
    {
        QString line = ctextStream.readLine();
        if (line.isNull())
            break;
        else
        {
            // puts the data from the file in the list of items
            cids.append(line);
            holdid = line;
            line = ctextStream.readLine();
            holdname = line;
            line = ctextStream.readLine();
            holdvalue = line;
            line = ctextStream.readLine();
            holdcategory = line;
            changeditems.append(item(holdid.toInt(), holdname, holdvalue.toFloat(), holdcategory));
        }
    }
    // erases change file to be refilled
    QFile killchanged("changed.txt");
    killchanged.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream c(&killchanged);
    c << "";
    killchanged.close();
    // now reads save file and loads in all the stuff
    QFile savedFile("saved.txt");
    savedFile.open(QFile::ReadWrite | QFile::Text);
    QTextStream textStream(&savedFile);
    while (true)
    {
        // reads the id of each saved item
        QString line = textStream.readLine();
        // if file is finished exit the process
        if (line.isNull())
            break;
        // if the item trying to be loaded in was deleted last session skips the rest of information about that item
        else if (dstringList.contains(line))
        {
            for (int i = 0; i < 3; i++)
            {
                line = textStream.readLine();
            }
        }
        // if the item was edited just copies directly from list of edited items
        else if (cids.contains(line))
        {
            for (int i = 0; i < 3; i++)
            {
                line = textStream.readLine();
            }
            item h = changeditems.at(0);
            for (int i = 0; i < changeditems.count(); i++)
            {
                if (changeditems.at(i).id == line.toInt())
                {
                    h = changeditems.at(i);
                }
            }
            numitems++;
            // writes to text boxes
            allids->addItem(QString::number(numitems));
            allnames->addItem(h.name);
            allvalues->addItem(QString::number(h.value));
            allcategories->addItem(h.category);
            // writes to list of items
            listitems.append(item(numitems, h.name, h.value, h.category));
        }
        // if not changed and not deleted its loaded in normally
        else
        {
            // writes to text boxes
            numitems++;
            allids->addItem(QString::number(numitems));
            line = textStream.readLine();
            allnames->addItem(line);
            holdname = line;
            line = textStream.readLine();
            allvalues->addItem(line);
            holdvalue = line;
            line = textStream.readLine();
            allcategories->addItem(line);
            holdcategory = line;
            // writes to list of items
            listitems.append(item(numitems, holdname, holdvalue.toFloat(), holdcategory));
        }
    }
    savedFile.close();
    // now erase old save file to be refilled
    QFile killsave("saved.txt");
    killsave.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream s(&killsave);
    s << "";
    killsave.close();
    // refills save file with all the items in listitem
    QFile resave("saved.txt");
    resave.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream rs(&resave);
    for (int i = 0; i < listitems.count(); i++)
    {
        item h = listitems.at(i);
        rs << h.id << "\n"
           << h.name << "\n"
           << h.value << "\n"
           << h.category << "\n";
    }
    resave.close();
    float curval;
    QString curcat;
    for (int i = 0; i < listitems.count(); i++)
    {
        curval = listitems.at(i).value;
        curcat = listitems.at(i).category;
        T_total += curval;
        if (curcat == "Food")
        {
            T_food += curval;
        }
        if (curcat == "Monthly Bills")
        {
            T_bills += curval;
        }
        if (curcat == "Fun")
        {
            T_fun += curval;
        }
        if (curcat == "Transportation")
        {
            T_trans += curval;
        }
        if (curcat == "Medical")
        {
            T_med += curval;
        }
        if (curcat == "Other")
        {
            T_other += curval;
        }
    }
    series = new QPieSeries;
    series->append("Food", T_food);
    series->append("Monthly Bills", T_bills);
    series->append("Fun", T_fun);
    series->append("Transportation", T_trans);
    series->append("Medical", T_med);
    series->append("Other", T_other);
    series->append("Remaining", balance - (T_total));
    leftslice = series->slices().at(6);
    leftslice->setBrush(Qt::green);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Budget breakdown:");
    chart->legend()->show();
    chart->legend()->setAlignment(Qt::AlignRight);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(475, 350);
    // makes the buttons, probably same thing about crashing if you don't do this right
    add = new QPushButton("Add", this);
    edit = new QPushButton("Edit", this);
    remove = new QPushButton("Remove", this);
    budget = new QPushButton("Set Budget", this);
    // extra UI stuff e.g. spacers
    QSpacerItem *spacer1 = new QSpacerItem(500, 300, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem *spacer2 = new QSpacerItem(100, 100, QSizePolicy::Minimum, QSizePolicy::Minimum);
    totalbudget = new QLabel(QString::number(balance));
    totalfood = new QLabel(QString::number(T_food));
    totalbills = new QLabel(QString::number(T_bills));
    totalfun = new QLabel(QString::number(T_fun));
    totaltrans = new QLabel(QString::number(T_trans));
    totalmedical = new QLabel(QString::number(T_med));
    totalother = new QLabel(QString::number(T_other));
    amtremaining = new QLabel(QString::number(QString::number(balance - (T_total), 'f', 2). toDouble(), 'g', 10));
    QLabel *labelbudget = new QLabel("Total budget: ");
    QLabel *labelfood = new QLabel("Food: ");
    QLabel *labelbills = new QLabel("Monthly bills: ");
    QLabel *labelfun = new QLabel("Fun: ");
    QLabel *labeltrans = new QLabel("Transportation: ");
    QLabel *labelmedical = new QLabel("Medical: ");
    QLabel *labelother = new QLabel("Other: ");
    QLabel *labelremaining = new QLabel("Remaining: ");
    layoutNumLabels->addWidget(labelbudget);
    layoutNumbers->addWidget(totalbudget, Qt::AlignRight);
    layoutNumLabels->addWidget(labelfood);
    layoutNumbers->addWidget(totalfood, Qt::AlignRight);
    layoutNumLabels->addWidget(labelbills);
    layoutNumbers->addWidget(totalbills, Qt::AlignRight);
    layoutNumLabels->addWidget(labelfun);
    layoutNumbers->addWidget(totalfun, Qt::AlignRight);
    layoutNumLabels->addWidget(labeltrans);
    layoutNumbers->addWidget(totaltrans, Qt::AlignRight);
    layoutNumLabels->addWidget(labelmedical);
    layoutNumbers->addWidget(totalmedical, Qt::AlignRight);
    layoutNumLabels->addWidget(labelother);
    layoutNumbers->addWidget(totalother, Qt::AlignRight);
    layoutNumLabels->addWidget(labelremaining);
    layoutNumbers->addWidget(amtremaining, Qt::AlignRight);
    layoutNumbers->addLayout(layouttotal);
    layoutNumbers->addLayout(layoutfood);
    layoutNumbers->addLayout(layoutbills);
    layoutNumbers->addLayout(layoutfun);
    layoutNumbers->addLayout(layouttrans);
    layoutNumbers->addLayout(layoutmed);
    layoutNumbers->addLayout(layoutother);
    layoutNumbers->addLayout(layoutremaining);
    // lotsa graphical stuff, heres where you add new buttons/text boxes
    layoutLabels->addWidget(itemname, 1, Qt::AlignCenter);
    layoutLabels->addWidget(allnames, 12, Qt::AlignCenter);
    layoutId->addWidget(itemid, 1, Qt::AlignCenter);
    layoutId->addWidget(allids, 12, Qt::AlignCenter);
    layoutAmt->addWidget(itemvalue, 1, Qt::AlignCenter);
    layoutAmt->addWidget(allvalues, 12, Qt::AlignCenter);
    layoutCat->addWidget(itemcategory, 1, Qt::AlignCenter);
    layoutCat->addWidget(allcategories, 12, Qt::AlignCenter);
    // buttons over here
    layoutbuttons->setSpacing(3);
    layoutbuttons->addStretch(1);
    layoutbuttons->addWidget(add);
    layoutbuttons->addWidget(edit);
    layoutbuttons->addWidget(remove);
    layoutbuttons->addWidget(budget);
    layoutbuttons->addStretch(1);
    // text boxes over here
    // layout1->addSpacerItem(spacer3);
    layout1->addLayout(layoutId);
    layout1->addLayout(layoutLabels);
    layout1->addLayout(layoutAmt);
    layout1->addLayout(layoutCat);
    layout1->addLayout(layoutbuttons);
    layoutTop->addWidget(chartView);
    layoutTop->addSpacerItem(spacer1);
    layoutTop->addLayout(layoutNumLabels);
    layoutTop->addLayout(layoutNumbers);
    layoutTop->addSpacerItem(spacer1);
    layoutFull->addLayout(layoutTop);
    layoutFull->addSpacerItem(spacer2);
    layoutFull->addLayout(layout1);
    allnames->setSelectionMode(QAbstractItemView::NoSelection);
    allvalues->setSelectionMode(QAbstractItemView::NoSelection);
    allcategories->setSelectionMode(QAbstractItemView::NoSelection);
    // more important button stuff probably
    connect(add, &QPushButton::clicked, this, &ListWidget::addItem);
    connect(edit, &QPushButton::clicked, this, &ListWidget::editItem);
    connect(remove, &QPushButton::clicked, this, &ListWidget::removeItem);
    connect(budget, &QPushButton::clicked, this, &ListWidget::setBudget);
    // final graphical thing?
    setLayout(layoutFull);
    setFixedSize(950, 700);
}
// called when "Add" is pressed
void ListWidget::addItem()
{
    QString holdname,
        holdvalue,
        holdcategory;
    // important button things if you want to make a button copy paste from this or remove theres a lot of important parts
    QDialog dialog(this);
    QFormLayout form(&dialog);
    // this displays a message before the buttons
    form.addRow(new QLabel("Add a new transaction"));
    // this the names of the buttons
    QList<QLineEdit *> fields;
    for (int i = 0; i < 2; ++i)
    {
        // yes i know you can use a break statement but it didn't work so
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        if (i == 0)
        {
            QString label = QString("Name");
            form.addRow(label, lineEdit);
        }
        if (i == 1)
        {
            QString label = QString("Value");
            form.addRow(label, lineEdit);
        }
        // writes whatever the user wrote to this thing to grab it later
        fields << lineEdit;
    }
    QComboBox *comboBox = new QComboBox(&dialog);
    comboBox->insertItem(1, "Food");
    comboBox->insertItem(2, "Monthly Bills");
    comboBox->insertItem(3, "Fun");
    comboBox->insertItem(4, "Transportation");
    comboBox->insertItem(5, "Medical");
    comboBox->insertItem(6, "Other");
    QString label = QString("Category");
    form.addRow(label, comboBox);
    // this makes the ok/cancel buttons at bottom
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // if ok was pressed do this stuff
    if (dialog.exec() == QDialog::Accepted)
    {
        int count = 0;
        // grabs data from user input and puts it into a bunch of QStrings to use
        foreach (QLineEdit *lineEdit, fields)
        {
            if (count == 0)
            {
                holdname = lineEdit->text();
            }
            if (count == 1)
            {
                holdvalue = lineEdit->text();
            }
            count++;
        }
        holdcategory = comboBox->currentText();
        // writes to lisitems
        numitems++;
        listitems.append(item(numitems, holdname, holdvalue.toFloat(), holdcategory));
        // writes to text boxes
        allids->addItem(QString::number(numitems));
        allids->setCurrentRow(allids->count() - 1);
        allnames->addItem(holdname);
        allnames->setCurrentRow(allnames->count() - 1);
        allvalues->addItem(holdvalue);
        allvalues->setCurrentRow(allvalues->count() - 1);
        allcategories->addItem(holdcategory);
        allcategories->setCurrentRow(allcategories->count() - 1);
        // update pie chart values
        T_total += holdvalue.toFloat();
        if (holdcategory == "Food")
        {
            T_food += holdvalue.toFloat();
        }
        if (holdcategory == "Monthly Bills")
        {
            T_bills += holdvalue.toFloat();
        }
        if (holdcategory == "Fun")
        {
            T_fun += holdvalue.toFloat();
        }
        if (holdcategory == "Transportation")
        {
            T_trans += holdvalue.toFloat();
        }
        if (holdcategory == "Medical")
        {
            T_med += holdvalue.toFloat();
        }
        if (holdcategory == "Other")
        {
            T_other += holdvalue.toFloat();
        }
        // saves the new item in the save file
        QFile savedFile("saved.txt");
        savedFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        QTextStream s(&savedFile);
        s << QString::number(numitems) << "\n"
          << holdname << "\n"
          << holdvalue << "\n"
          << holdcategory << "\n";
        savedFile.close();
    }
    series->clear();
    series->append("Food", T_food);
    series->append("Monthly Bills", T_bills);
    series->append("Fun", T_fun);
    series->append("Transportation", T_trans);
    series->append("Medical", T_med);
    series->append("Other", T_other);
    series->append("Remaining", balance - (T_total));
    leftslice = series->slices().at(6);
    leftslice->setBrush(Qt::green);
    totalbudget->setText(QString::number(balance));
    totalfood->setText(QString::number(T_food));
    totalbills->setText(QString::number(T_bills));
    totalfun->setText(QString::number(T_fun));
    totaltrans->setText(QString::number(T_trans));
    totalmedical->setText(QString::number(T_med));
    totalother->setText(QString::number(T_other));
    amtremaining->setText(QString::number(QString::number(balance - (T_total), 'f', 2). toDouble(), 'g', 10));
}
// called when "edit" is pressed
void ListWidget::editItem()
{
    if (allids->currentItem())
    {
        // important button things if you want to make a button copy paste from this or remove theres a lot of important parts
        QDialog dialog(this);
        QFormLayout form(&dialog);
        form.addRow(new QLabel("What is the ID of transaction you want to edit? (leave blank what you don't want to changed)"));
        QString holdname,
            holdvalue,
            holdcategory;
        QString holdid = allids->currentItem()->text();
        QList<QLineEdit *> fields;
        for (int i = 1; i < 3; ++i)
        {
            QLineEdit *lineEdit = new QLineEdit(&dialog);
            lineEdit->setPlaceholderText("No Change");
            if (i == 1)
            {
                QString label = QString("Name");
                form.addRow(label, lineEdit);
            }
            if (i == 2)
            {
                QString label = QString("Value");
                form.addRow(label, lineEdit);
            }
            fields << lineEdit;
        }
        QComboBox *comboBox = new QComboBox(&dialog);
        comboBox->insertItem(1, "No Change");
        comboBox->insertItem(2, "Food");
        comboBox->insertItem(3, "Monthly Bills");
        comboBox->insertItem(4, "Fun");
        comboBox->insertItem(5, "Transportation");
        comboBox->insertItem(6, "Medical");
        comboBox->insertItem(7, "Other");
        QString label = QString("Category");
        form.addRow(label, comboBox);
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
        // if ok was pressed do this stuff
        if (dialog.exec() == QDialog::Accepted)
        {
            int count = 1;
            // grabs data from user input and puts it into a bunch of QStrings to use
            foreach (QLineEdit *lineEdit, fields)
            {
                if (count == 1)
                {
                    holdname = lineEdit->text();
                }
                if (count == 2)
                {
                    holdvalue = lineEdit->text();
                }
                count++;
            }
            holdcategory = comboBox->currentText();
            // puts the QStrings into a new item in listitems
            // this is the item that youre editing
            item h = listitems.at(0); // this is just so it doesnt yell at me, but is a bug cuz doesnt stop user from inputting number out of bounds
            for (int i = 0; i < listitems.count(); i++)
            {
                if (listitems.at(i).id == holdid.toInt())
                {
                    h = listitems.at(i); // this is the real value
                    // subtracks old pie chart values
                    float curval = listitems.at(i).value;
                    QString curcat = listitems.at(i).category;
                    T_total -= curval;
                    if (curcat == "Food")
                    {
                        T_food -= curval;
                    }
                    if (curcat == "Monthly Bills")
                    {
                        T_bills -= curval;
                    }
                    if (curcat == "Fun")
                    {
                        T_fun -= curval;
                    }
                    if (curcat == "Transportation")
                    {
                        T_trans -= curval;
                    }
                    if (curcat == "Medical")
                    {
                        T_med -= curval;
                    }
                    if (curcat == "Other")
                    {
                        T_other -= curval;
                    }
                }
            }
            // this is the row youre rewriting in the text boxes
            // I had an aneurysm writing this line ignore the possible warning
            int r = allids->row(allids->findItems(holdid, Qt::MatchExactly).first());
            // if the user didnt input a change for one of the datavalues its left alone
            if (!(holdname == ""))
            {
                h.name = holdname;
                QListWidgetItem *dname = allnames->takeItem(r);
                delete dname;
                allnames->insertItem(r, holdname);
            }
            if (!(holdvalue == ""))
            {
                h.value = holdvalue.toFloat();
                QListWidgetItem *dval = allvalues->takeItem(r);
                delete dval;
                allvalues->insertItem(r, holdvalue);
            }
            if (!(holdcategory == "No Change"))
            {
                h.category = holdcategory;
                QListWidgetItem *dcat = allcategories->takeItem(r);
                delete dcat;
                allcategories->insertItem(r, holdcategory);
            }
            // writes to change file
            QFile changeFile("changed.txt");
            changeFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
            QTextStream s(&changeFile);
            s << h.id << "\n"
              << h.name << "\n"
              << h.value << "\n"
              << h.category << "\n";
            changeFile.close();
            // adds in new pie chart values
            T_total += h.value;
            if (h.category == "Food")
            {
                T_food += h.value;
            }
            if (h.category == "Monthly Bills")
            {
                T_bills += h.value;
            }
            if (h.category == "Fun")
            {
                T_fun += h.value;
            }
            if (h.category == "Transportation")
            {
                T_trans += h.value;
            }
            if (h.category == "Medical")
            {
                T_med += h.value;
            }
            if (h.category == "Other")
            {
                T_other += h.value;
            }
        }
    }
    series->clear();
    series->append("Food", T_food);
    series->append("Monthly Bills", T_bills);
    series->append("Fun", T_fun);
    series->append("Transportation", T_trans);
    series->append("Medical", T_med);
    series->append("Other", T_other);
    series->append("Remaining", balance - (T_total));
    leftslice = series->slices().at(6);
    leftslice->setBrush(Qt::green);
    totalbudget->setText(QString::number(balance));
    totalfood->setText(QString::number(T_food));
    totalbills->setText(QString::number(T_bills));
    totalfun->setText(QString::number(T_fun));
    totaltrans->setText(QString::number(T_trans));
    totalmedical->setText(QString::number(T_med));
    totalother->setText(QString::number(T_other));
    amtremaining->setText(QString::number(QString::number(balance - (T_total), 'f', 2). toDouble(), 'g', 10));
}
// called when "Remove" is pressed
void ListWidget::removeItem()
{
    if (allids->currentItem())
    {
        // important button things, copy paste from this if making a new button
        QDialog dialog(this);
        QFormLayout form(&dialog);
        form.addRow(new QLabel("Are you sure you want to remove this item?"));
        QString holdid = allids->currentItem()->text();
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
        // heres the if they pressed ok do stuff
        if (dialog.exec() == QDialog::Accepted)
        {
            // removes the item from listitems
            for (int i = 0; i < listitems.count(); i++)
            {
                if (listitems.at(i).id == holdid.toInt())
                {
                    // update pie chart values
                    float curval = listitems.at(i).value;
                    QString curcat = listitems.at(i).category;
                    T_total -= curval;
                    if (curcat == "Food")
                    {
                        T_food -= curval;
                    }
                    if (curcat == "Monthly Bills")
                    {
                        T_bills -= curval;
                    }
                    if (curcat == "Fun")
                    {
                        T_fun -= curval;
                    }
                    if (curcat == "Transportation")
                    {
                        T_trans -= curval;
                    }
                    if (curcat == "Medical")
                    {
                        T_med -= curval;
                    }
                    if (curcat == "Other")
                    {
                        T_other -= curval;
                    }
                    listitems.remove(i, 1);
                }
            }
            int r = allids->row(allids->findItems(holdid, Qt::MatchExactly).first());
            // stops all the text boxes from showing the item
            QListWidgetItem *dname = allnames->takeItem(r);
            delete dname;
            QListWidgetItem *dval = allvalues->takeItem(r);
            delete dval;
            QListWidgetItem *dcat = allcategories->takeItem(r);
            delete dcat;
            QListWidgetItem *did = allids->takeItem(r);
            delete did;
            // adds the deletion to the save files
            QFile deletedFile("deleted.txt");
            deletedFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
            QTextStream s(&deletedFile);
            s << holdid << "\n";
            deletedFile.close();
        }
        else
        {
            QString holdid = allids->currentItem()->text();
        }
    }
    series->clear();
    series->append("Food", T_food);
    series->append("Monthly Bills", T_bills);
    series->append("Fun", T_fun);
    series->append("Transportation", T_trans);
    series->append("Medical", T_med);
    series->append("Other", T_other);
    series->append("Remaining", balance - (T_total));
    leftslice = series->slices().at(6);
    leftslice->setBrush(Qt::green);
    totalbudget->setText(QString::number(balance));
    totalfood->setText(QString::number(T_food));
    totalbills->setText(QString::number(T_bills));
    totalfun->setText(QString::number(T_fun));
    totaltrans->setText(QString::number(T_trans));
    totalmedical->setText(QString::number(T_med));
    totalother->setText(QString::number(T_other));
    amtremaining->setText(QString::number(QString::number(balance - (T_total), 'f', 2). toDouble(), 'g', 10));
}
void ListWidget::setBudget()
{
    QString holdamount;
    Category category;
    // important button things if you want to make a button copy paste from this or remove theres a lot of important parts
    QDialog dialog(this);
    QFormLayout form(&dialog);
    // this displays a message before the buttons
    form.addRow(new QLabel("Enter budget amount:"));
    // this the names of the buttons
    QList<QLineEdit *> fields;
    // for(int i = 0; i < 2; ++i) {
    // yes i know you can use a break statement but it didn't work so
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    // if(i == 0) {
    QString label = QString("Amount: ");
    form.addRow(label, lineEdit);
    // writes whatever the user wrote to this thing to grab it later
    fields << lineEdit;
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // if ok was pressed do this stuff
    if (dialog.exec() == QDialog::Accepted)
    {
        holdamount = lineEdit->text();
        category.setBalance(holdamount.toFloat());
        QFile balanceFile("balance.txt");
        balanceFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        QTextStream s(&balanceFile);
        s << holdamount << "\n";
        balanceFile.close();
        balance = holdamount.toFloat();
    }
    series->clear();
    series->append("Food", T_food);
    series->append("Monthly Bills", T_bills);
    series->append("Fun", T_fun);
    series->append("Transportation", T_trans);
    series->append("Medical", T_med);
    series->append("Other", T_other);
    series->append("Remaining", balance - (T_total));
    leftslice = series->slices().at(6);
    leftslice->setBrush(Qt::green);
    totalbudget->setText(QString::number(balance));
    totalfood->setText(QString::number(T_food));
    totalbills->setText(QString::number(T_bills));
    totalfun->setText(QString::number(T_fun));
    totaltrans->setText(QString::number(T_trans));
    totalmedical->setText(QString::number(T_med));
    totalother->setText(QString::number(T_other));
    amtremaining->setText(QString::number(QString::number(balance - (T_total), 'f', 2). toDouble(), 'g', 10));
}
