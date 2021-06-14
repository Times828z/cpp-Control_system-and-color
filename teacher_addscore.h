#ifndef TEACHER_ADDSCORE_H
#define TEACHER_ADDSCORE_H

#include <QDialog>
#include <QPaintEvent>

namespace Ui {
class teacher_addScore;
}

class teacher_addScore : public QDialog
{
    Q_OBJECT

public:
    explicit teacher_addScore(QWidget *parent = nullptr);
    ~teacher_addScore();
    void writeIn(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::teacher_addScore *ui;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // TEACHER_ADDSCORE_H
