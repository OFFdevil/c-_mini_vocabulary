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
    Timer->start(1);
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
    if(start_line != ""){
        slot1();
    }
}

void MainWindow::slot1(){
    std::string subline = returnLine();
    if(QFile::exists("vocabulary")) {
        std::string line;
        count_line += 250;
        do{
            getline(file, line);
            k++;
            if(line.find(subline) != std::string::npos || LCS(line, subline)){
                LineOutput->append(QString::fromStdString(line));
            }
        }while(k <= count_line && !file.eof());
    }
}

bool MainWindow::LCS(const std::string& s1, const std::string& s2){
    if(s1.size() < s2.size()){
        return 0;
    }else{
        std::size_t lcs_count = 0;
        std::vector<std::size_t> lcs1(s1.size() + 1, 0), lcs2(s1.size() + 1, 0);
        for(std::size_t i=0; i <= s1.size(); i++){
            for(std::size_t j=0; j <= s2.size(); j++){
                if(0 < j){
                    lcs2[j] = std::max(lcs2[j], lcs2[j-1]);
                }
                if(0 < i){
                    lcs2[j] = std::max(lcs2[j], lcs1[j]);
                }
                if(0 < i && 0 < j && lcs2[j] < lcs1[j-1] + 1 && s1[i] == s2[j]){
                    lcs2[j] = lcs1[j-1] + 1;
                }
                lcs_count = std::max(lcs_count, lcs2[j]);
            }
            std::swap(lcs1, lcs2);
        }
        return lcs_count == s2.size() ? 1 : 0;
    }
}

std::string MainWindow::returnLine(){
    return LineInput->text().toUtf8().constData();
}

MainWindow::~MainWindow()
{
    delete ui;
}
