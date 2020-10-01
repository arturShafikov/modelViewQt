#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DataModel *dataModel = new DataModel();
    dataModel->InitModel();

    tableModel = new TableModel(&dataModel->getCompanyList());
    ui->tableView->setModel(tableModel);

    ComboBoxItemDelegate *comboBoxDelegate =
            new ComboBoxItemDelegate(ui->tableView, &dataModel->getCountryList());
    ui->tableView->setItemDelegateForColumn(1, comboBoxDelegate);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(ui->removeRowsButton, SIGNAL(clicked()), this, SLOT(removeRows()));
    connect(ui->generateHtmlButton, SIGNAL(clicked()), this, SLOT(showHtml()));
    connect(ui->hideHtml, SIGNAL(clicked()), this, SLOT(hideHtml()));

    ui->htmlBrowser->hide();
    ui->hideHtml->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::generateHtml()
{
    QString strStream;
    QTextStream out(&strStream);
    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "Table"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < tableModel->columnCount(); column++) {
            out << QString("<th>%1</th>").arg(tableModel->headerData(column, Qt::Horizontal).toString());
    }
    out << "</tr></thead>\n";

    for (int row = 0; row < tableModel->rowCount(); row++) {
        out << "<tr onClick=\"showInfo(this)\">";
        for (int column = 0; column < tableModel->columnCount(); column++) {
            QString data = tableModel->data(tableModel->index(row, column), Qt::DisplayRole).toString().simplified();
            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
        }
        out << "</tr>\n";
    }
    out << "</table>\n"
           "<script>"
           "function showInfo(x) {"
           "alert(\"Row is \" + x.rowIndex);"
           "}"
           "</script>"
           "</body>\n"
           "</html>";
    QFile file("table.html");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(strStream.toUtf8());
    file.close();
    return strStream;
}

void MainWindow::addRow()
{
    tableModel->insertRow(tableModel->rowCount());
}

void MainWindow::removeRows()
{
    const QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    if ((indexes.size() == 0) || (indexes.size() == tableModel->rowCount())) {
        return;
    }
    std::vector<int> vIndexes;
    foreach(QModelIndex index, indexes) {
        vIndexes.push_back(index.row());
    }
    std::sort(vIndexes.begin(), vIndexes.end());
    std::vector<int>::reverse_iterator rit = vIndexes.rbegin();
    for (; rit!= vIndexes.rend(); ++rit) {
        tableModel->removeRow(*rit);
    }
}

void MainWindow::showHtml()
{
    ui->htmlBrowser->show();
    ui->htmlBrowser->setOpenExternalLinks(true);
    ui->htmlBrowser->setHtml(generateHtml());
    ui->hideHtml->show();
}

void MainWindow::hideHtml()
{
    ui->htmlBrowser->hide();
    ui->hideHtml->hide();
}
