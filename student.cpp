#include "student.h"
#include "ui_student.h"
#include "QDebug"
#include "QFile"
#include "QMessageBox"
#include "student_course.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>


student::student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    if(readFile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
    }
}

student::~student()
{
    delete ui;
}

void student::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/gaitubao_e_png.png"),QRect());		//传入资源图片路径
}

//读取文件
int student::readFile()
{
    QFile file("D:\\QtProject\\Design\\score.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line=in.readLine();
            score_line.append(line);
        }
    file.close();
    return 0;
}

//查询成绩
void student::on_btn_search_clicked()
{
    QString messagebox_out = "";
    for(int i=0;i<score_line.length();i++)
    {
        QString line=score_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        if(account==linesplit.at(0))
        {
        messagebox_out = messagebox_out + linesplit.at(2) + " " + linesplit.at(3)+"\n";
        }
    }
    messagebox_out = st_name + "\n" + messagebox_out;
    QMessageBox::information(this,"成绩显示",messagebox_out,"确认","取消");
}


//选课
void student::on_btn_chooseCourse_clicked()
{
    this->close();
    student_course a;
    a.exec();
}


void student::on_btn_back_clicked()
{
    MainWindow *main_window=new MainWindow;
    main_window->show();
    this->close();
}


void student::on_btn_close_clicked()
{
    this->close();

}

