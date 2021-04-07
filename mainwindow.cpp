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

    QTimer *Timer = new QTimer(this);                                           // needed to bypass freezes
    connect(Timer, &QTimer::timeout, this, &MainWindow::start_find);
    Timer->start(1);
}

void MainWindow::start_find() {
    if(ReturnLineInput() != start_line) {
        k = 0;
        count_line = 0;                                 // so that there are no freezes
        start_line = ReturnLineInput();
        LineOutput->clear();                            // delete past data
        file.close();                                   // you need to restore the entire file to read it again
        file.open("vocabulary", std::ios_base::in);
    }

    if(start_line != "") {
        CheckSubString();
    }
}

void MainWindow::CheckSubString() {
    std::string subline = ReturnLineInput();
    if(QFile::exists("vocabulary")) {
        std::string line;
        count_line += 250;                                                      // we will read in parts
        do{
            getline(file, line);
            k++;
            if(line.find(subline) != std::string::npos || LCS(line, subline)) { // substring check
                LineOutput->append(QString::fromStdString(line));
            }
        }while(k <= count_line && !file.eof());                                 // either the file ended or a readable chunk
    }
}

bool MainWindow::LCS(const std::string& s1, const std::string& s2) {            // simple LCS
    if(s1.size() < s2.size()) {
        return 0;
    } else {
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
                if(0 < i && 0 < j && lcs2[j] < lcs1[j-1] + 1 && s1[i-1] == s2[j-1]){
                    lcs2[j] = lcs1[j-1] + 1;
                }
                lcs_count = std::max(lcs_count, lcs2[j]);
            }
            std::swap(lcs1, lcs2);
        }
        return lcs_count == s2.size() ? 1 : 0;
    }
}

std::string MainWindow::ReturnLineInput() {
    return LineInput->text().toUtf8().constData();
}

MainWindow::~MainWindow() {
    delete ui;
}
