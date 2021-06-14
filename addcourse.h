#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QDialog>
#include"QString"

namespace Ui {
class addCourse;
}

class addCourse : public QDialog
{
    Q_OBJECT

public:
    explicit addCourse(QWidget *parent = nullptr);
    ~addCourse();
    void writeIn(QString);

private slots:
    void on_btn_Confirm_clicked();

    void on_btn_close_clicked();

    void on_btn_back_clicked();

private:
    Ui::addCourse *ui;
};

#endif // ADDCOURSE_H
