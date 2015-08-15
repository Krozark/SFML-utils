#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QStandardItem;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void a(QStandardItem*);

    void on_addLayerPushButton_clicked();

    void on_removeLayerPushButton_clicked();

    void on_moveLayerTopPushButton_clicked();

    void on_moveLayerBottomPushButton_clicked();

    void on_createBrushPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;

    int _getLayerSelectionIndex()const;
    QModelIndex _getLayerSelectionIndexModelIndex()const;
};

#endif // MAINWINDOW_HPP
