#ifndef NEWBRUSHDIALOG_HPP
#define NEWBRUSHDIALOG_HPP

#include <QDialog>

namespace Ui {
class NewBrushDialog;
}

class NewBrushDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewBrushDialog(QWidget *parent = 0);
    ~NewBrushDialog();

private:
    Ui::NewBrushDialog *ui;
};

#endif // NEWBRUSHDIALOG_HPP
