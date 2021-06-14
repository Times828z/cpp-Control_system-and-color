#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


extern QString account;
extern QString password;
extern QString st_name;
extern QString te_name;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int readstudentfile();
    int readteacherfile();
    int readcontroller();

private:
    Ui::MainWindow *ui;
    QList<QString> student_line;
    QList<QString> teacher_line;
    QList<QString> controller_line;


protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void    on_btn_signIn_clicked();
    void    on_btn_signOut_clicked();
};
#endif // MAINWINDOW_H
