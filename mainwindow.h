#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamodel.h"
#include "iostream"
#include "QMetaProperty"
#include "comboboxitemdelegate.h"
#include "tablemodel.h"
#include "QTextStream"
#include "QTextDocument"
#include "QFile"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    TableModel *tableModel;

    QString generateHtml();

private slots:
    void addRow();
    void removeRows();
    void showHtml();
    void hideHtml();
};

#endif // MAINWINDOW_H
