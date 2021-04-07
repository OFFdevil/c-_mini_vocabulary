#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LineInput  = new QLineEdit("", this);
    LineOutput = new QTextEdit("", this);
    LineInput->setFixedHeight(40);
    LineOutput->setReadOnly(true);
    ui->layout->addWidget(LineInput);
    ui->layout->addWidget(LineOutput);
    setLayout(ui->layout);

    QTimer *Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &MainWindow::new_function);
    Timer->start(10);
}

void MainWindow::new_function(){
    if(returnLine() != start_line){
        k = 0;
        count_line = 0;
        start_line = returnLine();
        LineOutput->clear();
        file.close();
        file.open("vocabulary", std::ios_base::in);
    }
    slot1();
}

void MainWindow::slot1(){
    std::string subline = returnLine();
    if(QFile::exists("vocabulary")) {
        std::string line;
        count_line += 100;
        do{
            getline(file, line);
            k++;
            if(line.find(subline) != std::string::npos){
                LineOutput->append(QString::fromStdString(line));
            }
        }while(k <= count_line && !file.eof());
    }
}

std::string MainWindow::returnLine(){
    return LineInput->text().toUtf8().constData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*while(getline(file, line)){
    k++;
    std::cout<<line <<std::endl;
    char *pch = std::strstr(subline, line);
    if(pch != NULL){
        LineOutput->append(QString::fromStdString(line));
    }
    if(k % 3000 == 0){
        break;
    }
}*/

