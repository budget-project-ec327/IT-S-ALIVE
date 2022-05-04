//#include "FileManager.h"
//#include <iostream>
//#include "listwidget.h"
//#include <QString>
//#include <QCoreApplication>
//#include <QFile>
//#include <QString>
//#include <QDebug>
//#include <QTextStream>

//void Fwrite(QString Filename)
//{



//}

//void Fread(QString Filename)
//{
//    QString dstringList;
//    QFile deletedFile(Filename);
//    deletedFile.open(QFile::ReadWrite | QFile::Text);
//    QTextStream dtextStream(&deletedFile);
//    while (true)
//    {
//        QString line = dtextStream.readLine();
//        if (line.isNull())
//            break;
//        else {
//            dstringList.append(line);
//        }
//    }
//    deletedFile.close();
//}

//void Fget(QString Filename)
//{
//    QString holdT_O, holdT_M, holdT_MB, holdT_F, holdT_FOO, holdT_TOT, hold_balance, holdcat;

//    QList<item> changeditems;
//    QStringList cids;
//    QFile changedFile(Filename);
//    changedFile.open(QFile::ReadWrite | QFile::Text);
//    QTextStream ctextStream(&changedFile);
//    while (true)
//    {
//        QString line = ctextStream.readLine();
//        if (line.isNull())
//            break;
//        else {
//            //puts the data from the file in the list of items
//            cids.append(line);
//            holdT_O = line;
//            line = ctextStream.readLine();
//            holdT_M = line;
//            line = ctextStream.readLine();
//            holdT_MB = line;
//            line = ctextStream.readLine();
//            holdT_F = line;
//            line = ctextStream.readLine();
//            holdT_FOO = line;
//            line = ctextStream.readLine();
//            holdT_TOT = line;
//            line = ctextStream.readLine();
//            hold_balance = line;
//            line = ctextStream.readLine();
//            holdcat = line;
//            changeditems.append(item(holdid.toInt(),holdname,holdvalue.toFloat(),holdcategory));
//        }
//}
//}
