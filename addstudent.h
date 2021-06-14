#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QDialog>
#include"QString"

namespace Ui {
class addStudent;
}

class addStudent : public QDialog
{
    Q_OBJECT

public:
    explicit addStudent(QWidget *parent = nullptr);
    ~addStudent();
    void writeIn(QString);

private slots:
    void on_btn_Confirm_clicked();

    void on_btn_back_clicked();

    void on_btn_close_clicked();

private:
    Ui::addStudent *ui;
};

#endif // ADDSTUDENT_H
