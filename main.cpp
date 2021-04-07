#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Vocabulary");
    w.show();
    return a.exec();
}
