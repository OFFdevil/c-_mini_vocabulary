#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool LCS(const std::string& s1, const std::string& s2);
    ~MainWindow();

private slots:
    void new_function();
    void slot1();
    std::string returnLine();

private:
    Ui::MainWindow *ui;
    QLineEdit *LineInput;
    QTextEdit *LineOutput;
    std::ifstream file;
    std::size_t k = 0;
    std::size_t count_line = 0;
    std::string start_line = "";
};
#endif // MAINWINDOW_H
