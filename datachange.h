#ifndef DATACHANGE_H
#define DATACHANGE_H

#include <QDialog>
#include"QPaintEvent"

namespace Ui {
class DataChange;
}

class DataChange : public QDialog
{
    Q_OBJECT

public:
    explicit DataChange(QWidget *parent = nullptr);
    ~DataChange();
    void writeIn(QString information);
    int readfile();

private slots:
    void on_pushButton_clicked();

    void on_btn_change_clicked();

    void on_btb_back_clicked();

    void on_btn_close_clicked();

    void on_btn_import_clicked();

private:
    Ui::DataChange *ui;


protected:
    void paintEvent(QPaintEvent *event);
    QList<QString> score_line;

};

#endif // DATACHANGE_H
