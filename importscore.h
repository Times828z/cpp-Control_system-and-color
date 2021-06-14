#ifndef IMPORTSCORE_H
#define IMPORTSCORE_H

#include <QDialog>
#include <QPaintEvent>
#include"QString"
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class importScore;
}

class importScore : public QDialog
{
    Q_OBJECT

public:
    explicit importScore(QWidget *parent = nullptr);
    ~importScore();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btn_sort_clicked();

    void on_btn_analyse_clicked();

private:
    Ui::importScore *ui;
    int readfile(QString);
    void reset();
    void display(int row, QStringList score_line);


protected:
    void paintEvent(QPaintEvent *event);
    QStandardItemModel *model;
    QList<QString> score_line;
};

#endif // IMPORTSCORE_H
