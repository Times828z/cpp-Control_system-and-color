#ifndef SYSTEM_H
#define SYSTEM_H

#include <QDialog>

namespace Ui {
class system;
}

class system : public QDialog
{
    Q_OBJECT

public:
    explicit system(QWidget *parent = nullptr);
    ~system();

private slots:
    void on_btn_addStudengt_clicked();

    void on_btn_addTeacher_clicked();

    void on_btn_addCourse_clicked();

    void on_btn_del_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::system *ui;
};

#endif // SYSTEM_H
