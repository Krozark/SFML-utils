#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QCheckBox>
#include <QDebug>
#include "newbrushdialog.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model= new QStandardItemModel();
    connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(a(QStandardItem*)));
    this->ui->listView->setModel(model);
}

void MainWindow::a(QStandardItem* item)
{
    qDebug()<<"blah"<<item;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLayerPushButton_clicked()
{
    static int nb = 1;
    QStandardItem* item = new QStandardItem("Layer_" + QString::number(nb++));
    item->setCheckable(true);
    item->setCheckState(Qt::Checked);
    model->appendRow(item);
}

void MainWindow::on_removeLayerPushButton_clicked()
{
    int i = _getLayerSelectionIndex();
    if(i > 0)
        model->removeRows( i, 1 );
}

void MainWindow::on_moveLayerTopPushButton_clicked()
{
    int i = _getLayerSelectionIndex();
    qDebug()<<"on_moveLayerTopPushButton_clicked";

    if(i <=  0)
        return;

    model->insertRow(i-1,model->takeRow(i));

    //ui->listView->setCurrentIndex(QModelIndex(i-1,0,0));
    //ui->listView->setCurrentIndex(i-1);
    //model->moveRow(_getLayerSelectionIndexModelIndex(),i,_getLayerSelectionIndexModelIndex(),i-1);

}

void MainWindow::on_moveLayerBottomPushButton_clicked()
{
    int i = _getLayerSelectionIndex();
    qDebug()<<"on_moveLayerBottomPushButton_clicked";

    if(i < 0)
        return;

    model->insertRow(i+1,model->takeRow(i));

}

int MainWindow::_getLayerSelectionIndex()const
{
    QItemSelection selection(this->ui->listView->selectionModel()->selection());

    foreach( const QModelIndex & index, selection.indexes())
    {
        return index.row();
    }

    return -1;
}

QModelIndex MainWindow::_getLayerSelectionIndexModelIndex()const
{
    QItemSelection selection(this->ui->listView->selectionModel()->selection());

    foreach( const QModelIndex & index, selection.indexes())
    {
        return index;
    }

    return QModelIndex();

}

void MainWindow::on_createBrushPushButton_clicked()
{
    NewBrushDialog* d = new NewBrushDialog(this);
    d->show();
}
