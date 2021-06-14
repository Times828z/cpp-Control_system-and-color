#ifndef TEACHER_H
#define TEACHER_H

#include <QDialog>
#include <QPaintEvent>

namespace Ui {
class teacher;
}

class teacher : public QDialog
{
    Q_OBJECT

public:
    explicit teacher(QWidget *parent = nullptr);
    ~teacher();



private slots:
    void on_btn_back_clicked();

    void on_btn_close_clicked();

    void on_btb_teacher_addScore_clicked();

    void on_btn_importScore_clicked();

    void on_btn_search_clicked();

    void on_btn_change_clicked();


private:
    Ui::teacher *ui;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // TEACHER_H
