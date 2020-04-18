#include "Desk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Desk w(nullptr);
    w.show();

    return a.exec();
}
