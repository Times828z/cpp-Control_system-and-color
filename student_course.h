#ifndef STUDENT_COURSE_H
#define STUDENT_COURSE_H

#include <QDialog>
#include"QStandardItemModel"

namespace Ui {
class student_course;
}

class student_course : public QDialog
{
    Q_OBJECT

public:
    explicit student_course(QWidget *parent = nullptr);
    ~student_course();
    int readcoursefile();
    int readselectedfile();
    void reset();
    void reset1();
    void display(int row, QStringList course_line);
    void display1(int row, QStringList selected_line);
    void writeIn(QString info);

private slots:
    void on_btn_back_clicked();

    void on_btn_close_clicked();

    void on_confirm_clicked();

    void on_showAll_clicked();

    void on_tb_course_doubleClicked(const QModelIndex &index);

    void on_tb_select_doubleClicked(const QModelIndex &index);

private:
    Ui::student_course *ui;
    QStandardItemModel *model1;
    QStandardItemModel *model2;
    QList<QString> course_line;
    QList<QString> selected_line;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // STUDENT_COURSE_H
