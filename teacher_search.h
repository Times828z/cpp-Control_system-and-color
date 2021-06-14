#ifndef TEACHER_SEARCH_H
#define TEACHER_SEARCH_H

#include <QDialog>
#include"QStandardItemModel"
#include <QPaintEvent>

extern QString num1;
extern QString name1;
extern QString object1;
extern QString score1;


namespace Ui {
class teacher_search;
}

class teacher_search : public QDialog
{
    Q_OBJECT

public:
    explicit teacher_search(QWidget *parent = nullptr);
    ~teacher_search();
    int readfile();
    void reset();
    void display(int row, QStringList score_line);


private slots:
    void on_btn_back_clicked();

    void on_btn_close_clicked();


    void on_btn_confirm_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::teacher_search *ui;
    QStandardItemModel *model;
    QList<QString> score_line;


protected:
    void paintEvent(QPaintEvent *event);

};

#endif // TEACHER_SEARCH_H
