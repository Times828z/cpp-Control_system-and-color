#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
#include"QString"
#include <QPaintEvent>

namespace Ui {
class student;
}

class student : public QDialog
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr);
    ~student();
    int readFile();
private slots:
    void on_pushButton_3_clicked();

    void on_btn_search_clicked();

    void on_btn_chooseCourse_clicked();

    void on_btn_back_clicked();

    void on_btn_close_clicked();

private:
    Ui::student *ui;
    QList<QString> score_line;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // STUDENT_H
