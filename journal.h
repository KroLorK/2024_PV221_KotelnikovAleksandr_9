#ifndef JOURNAL_H
#define JOURNAL_H

#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Journal;
}
QT_END_NAMESPACE

class Journal : public QObject
{
private:
    QWidget* widget;

    unsigned countRow;
    unsigned countColumn;
    std::string filePath;
    QStandardItemModel* model;
public:
    Journal();
    QPushButton *addRow;
    QPushButton *addColumn;
    QPushButton *saveButton;
    void saveData();
    void show();
    void getTable();
    void addRowFunc();
    void addColumnFunc();
};

#endif // JOURNAL_H
