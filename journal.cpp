#include "journal.h"
#include "./ui_journal.h"
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QWidget>

Journal::Journal() {
    widget = new QWidget;
    widget->setWindowTitle("Журнал");
    widget->setMinimumHeight(400);
    widget->setMinimumWidth(800);

    countColumn = 0;
    countRow = 0;

    model=  new QStandardItemModel(1, 1);
    model->setHeaderData(0, Qt::Horizontal, "ФИО");
    QTableView *view = new QTableView(widget);
    view->setMinimumSize(800, 200);

    filePath = "B:\\games\\OOP_10\\OOP10\\data.txt";
    std::ifstream file(filePath);
    std::string fileString;
    bool flag = false;
    while(std::getline(file, fileString)) {
        std::istringstream stringStream(fileString);
        std::string s;
        //stringStream >> s;

        while(stringStream >> s) {
            std::cout << s;
            if(flag) {
                if(countRow == 0)
                    model->insertColumn(countColumn + 1);
                countColumn++;
                model->setItem(countRow, countColumn, new QStandardItem(QString::fromStdString(s)));
                model->setHeaderData(countColumn, Qt::Horizontal, "Занятие №" + QString::number(countColumn));
            }

            if(!flag) {
                if(countRow != 0)
                    model->insertRow(countRow);
                model->setItem(countRow, 0, new QStandardItem(QString::fromStdString(s)));
                flag = true;
            }
        }
        countColumn = 0;
        flag = false;
        countRow++;
    }

    addRow = new QPushButton("Добавить студента", this->widget);
    addRow->setGeometry(20, 600, 120, 30);
    saveButton = new QPushButton("Сохранить", this->widget);
    saveButton->setGeometry(280, 600, 120, 30);

    addColumn = new QPushButton("Добавить занятие", this->widget);
    addColumn->setGeometry(150, 600, 120, 30);
    //QStandardItemModel* model=  new QStandardItemModel(1, 2);

    QObject::connect(saveButton, &QPushButton::clicked, this, &Journal::saveData);
    QObject::connect(addRow, &QPushButton::clicked, this, &Journal::addRowFunc);
    QObject::connect(addColumn, &QPushButton::clicked, this, &Journal::addColumnFunc);

    // устанавливаем модель для представления
    view->setModel(model);

}

void Journal::saveData() {
    QFile file(QString::fromStdString(filePath));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) { // Попытка открыть файл для записи текста
        QTextStream stream(&file);
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 0; column < model->columnCount(); ++column) {
                QModelIndex index = model->index(row, column); // Получение индекса для каждой ячейки
                QString cellData = model->data(index).toString(); // Получение данных из ячейки
                stream << cellData;
                if (column < model->columnCount() - 1) {
                    stream << "\t"; // Добавление табуляции как разделителя между ячейками
                }
            }
            stream << "\n"; // Переход на новую строку после каждой строки данных
        }
        file.close(); // Закрытие файла после записи
    }
}


void Journal::show() {
    widget->show();
}

void Journal::addRowFunc() {
    model->insertRow(model->rowCount());
}

void Journal::addColumnFunc() {
    model->insertColumn(model->columnCount());
    model->setHeaderData(model->columnCount() -1, Qt::Horizontal, "Занятие №" + QString::number(model->columnCount() - 1));
}

