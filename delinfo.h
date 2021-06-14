#ifndef DELINFO_H
#define DELINFO_H

#include <QDialog>

namespace Ui {
class delInfo;
}

class delInfo : public QDialog
{
    Q_OBJECT

public:
    explicit delInfo(QWidget *parent = nullptr);
    ~delInfo();
    int readstudentfile();
    int readteacherfile();
    int readcoursefile();
    void deletestudent();
    void deleteteacher();
    void deletecourse();

private slots:
    void on_btn_back_clicked();

    void on_btn_close_clicked();

    void on_pushButton_clicked();

private:
    Ui::delInfo *ui;
    QList<QString> student_line;
    QList<QString> teacher_line;
    QList<QString> course_line;
};

#endif // DELINFO_H
