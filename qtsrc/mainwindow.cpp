#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <QDir>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    const QString project_path = QDir::currentPath(); // Get working dir
    std::string startPath = "start " + project_path.toStdString() + "/start.exe"; // !!
    cout << startPath << "\n";
    system(startPath.c_str());
}


void MainWindow::on_pushButton_2_clicked() {

    const QString project_path = QDir::currentPath(); // Get working dir
    std::string stopPath = "start " + project_path.toStdString() + "/stop.exe"; // !!
    cout << stopPath << "\n";
    system(stopPath.c_str());
}

