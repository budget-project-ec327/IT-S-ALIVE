#include <QApplication>
#include <QPushButton>
#include <QIODevice>
#include <QFile>
#include "listwidget.h"

/*tips and and other stuff
 * press F4 to instantly switch between a .cpp file and its .h file and vice versa
 * put your cursor in the middle of anything and press F1 to pull up the documentation of it
 * click open in help mode at the top of the screen to make it big and put it in help bar
 * use this its a fucking lifesaver
 *
 * so there are a couple unprotected stuff basically a user can put non numbers in value and its weird
 * also they can just not type anything and sometimes it crashes just add some stuff to the buttons to prevent them doing that
 * mayyyyy be buggy hopefully not but yea no promises just fix em
 *
 * also there is no arithmatic whatsoever like values do nothing
 * a balance value is needed obviously sorry i didnt have time to add that
 * my reccomendataion: have another file like balance.txt or something that if it is empty the program will ask the user for a starting balance
 * write that to the file
 * once that number is written to the file wont ask again
 * whenever program is opened reads that number into a float in class listwidget
 * then whenever an item is created in listitems add or subtract from that value
 *
 * if you want to do calculations using an array of floats try
 *
        int values[listitems.count()];
        for(int i = 0; i < listitems.count(); i++) {
            values[i] = listitems.at(i).id;
        }
 *
 * i have no idea how to do anything graphical so good luck!
 */

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    ListWidget window;


    window.setWindowTitle("BUdget");
    window.show();

    //important! if you are ever changing the format of save files you need to completely erase them using this (insert all the files)
    /*QFile saveFile("saved.txt");
    saveFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream s(&saveFile);
    s << "";*/

    return app.exec();
}
