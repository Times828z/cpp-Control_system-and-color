#ifndef ADDTEACHER_H
#define ADDTEACHER_H

#include <QDialog>
#include"QString"

namespace Ui {
class addTeacher;
}

class addTeacher : public QDialog
{
    Q_OBJECT

public:
    explicit addTeacher(QWidget *parent = nullptr);
    ~addTeacher();
    void writeIn(QString);

private slots:
    void on_btn_Confirm_clicked();

    void on_btn_back_clicked();

    void on_btn_close_clicked();

private:
    Ui::addTeacher *ui;
};

#endif // ADDTEACHER_H
