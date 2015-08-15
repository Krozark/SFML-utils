#include "newbrushdialog.hpp"
#include "ui_newbrushdialog.h"

#include <QGraphicsScene>

NewBrushDialog::NewBrushDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBrushDialog)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene();


    QImage img("trees.png");
    QBrush brush(img);
    scene->setBackgroundBrush(brush);
    this->ui->graphicsView->setScene(scene);

    //this->ui->graphicsView->fitInView(QRectF(0, 0, 600,600), Qt::KeepAspectRatio);
    //scene->update();
}

NewBrushDialog::~NewBrushDialog()
{
    delete ui;
}
