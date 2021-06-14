#include "delInfo.h"
#include "ui_delInfo.h"
#include"system.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"

delInfo::delInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delInfo)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{background-color: purple;}");
    if(readstudentfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败!","确认");
    }

    if(readteacherfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败!","确认");
    }

    if(readcoursefile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败!","确认");
    }
}

delInfo::~delInfo()
{
    delete ui;
}

QString ID;

void delInfo::on_btn_back_clicked()
{
    this->close();
    class system *aaaa = new class system();
    aaaa->show();
}


void delInfo::on_btn_close_clicked()
{
    this->close();
}




void delInfo::on_pushButton_clicked()
{

    ID=this->ui->del_num->text();
    int flag=100;
    if(ID.at(0)=="2"&&ID.length()==11)
    {
        flag=0;
    }
    else if(ID.at(0)=="t"&&ID.length()==7)
    {
        flag=1;
    }
    else if(ID.length()==8)
    {
        flag=2;
    }
    else
    {
        QMessageBox::critical(this,"错误","ID填写错误或不完整，请修改！","确定");
    }
    switch (flag)
    {
    case 0:
        deletestudent();
        break;
    case 1:
        deleteteacher();
        break;
    case 2:
        deletecourse();
        break;
    default:
        break;
    }
}


//读取学生文件
int delInfo::readstudentfile()
{
    QFile file("D:\\QtProject\\Design\\student.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);

    //读取文件，保存到一个QList中
    while (!in.atEnd()){
       QString line=in.readLine();
       student_line.append(line);
    }
    file.close();
    return 0;
}

int delInfo::readteacherfile()
{
    QFile file("D:\\QtProject\\Design\\teacher.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()){
       QString line=in.readLine();
       teacher_line.append(line);
    }
    file.close();
    return 0;
}


int delInfo::readcoursefile()
{
    QFile file("D:\\QtProject\\Design\\course.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       course_line.append(line);
    }
    file.close();
    return 0;
}


void delInfo::deletestudent()
{
    int i=0;
    for (i=0;i<student_line.length();i++)
    {
        QString line=student_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        if(ID!=linesplit.at(0))
        {
            QFile file("D:\\QtProject\\Design\\student_temp.txt");
            if(!file.open(QIODevice::Append|QIODevice::Text))
            {
               QMessageBox::critical(this,"错误","文件打开失败，学生账号未删除","确认");
               return;
            }
        QTextStream out(&file);
        out<<line+"\n";
        file.close();
        }
    }
    QFile file_old("D:\\QtProject\\Design\\student.txt");
    QFile file_new("D:\\QtProject\\Design\\student_temp.txt");
    if (file_old.exists())
    {
       file_old.remove();
       file_new.rename("D:\\QtProject\\Design\\student.txt");
    }
    else
    {
       QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
    }
    QMessageBox::information(this,"通知","删除成功！","确认");
}

void delInfo::deleteteacher()
{
    int i=0;
    for (i=0;i<teacher_line.length();i++)
    {
        QString line=teacher_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if(ID!=linesplit.at(0))
        {
            QFile file("D:\\QtProject\\Design\\teacher_temp.txt");
            if(!file.open(QIODevice::Append|QIODevice::Text))
            {
               QMessageBox::critical(this,"错误","文件打开失败，教师账号未删除","确认");
               return;
            }
        QTextStream out(&file);
        out<<line+"\n";
        file.close();
        }
    }
    QFile file_old("D:\\QtProject\\Design\\teacher.txt");
    QFile file_new("D:\\QtProject\\Design\\teacher_temp.txt");
    if (file_old.exists())
    {
       file_old.remove();
       file_new.rename("D:\\QtProject\\Design\\teacher.txt");
    }
    else
    {
       QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
    }
    QMessageBox::information(this,"通知","删除成功！","确认");
}

void delInfo::deletecourse()
{
    int i=0;
    for (i=0;i<course_line.length();i++)
    {
        QString line=course_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if(ID!=linesplit.at(0))
        {
            QFile file("D:\\QtProject\\Design\\course_temp.txt");
            if(!file.open(QIODevice::Append|QIODevice::Text))
            {
               QMessageBox::critical(this,"错误","文件打开失败，课程信息未删除","确认");
               return;
            }
        QTextStream out(&file);
        out<<line+"\n";
        file.close();
        }
    }
    QFile file_old("D:\\QtProject\\Design\\course.txt");
    QFile file_new("D:\\QtProject\\Design\\course_temp.txt");
    if (file_old.exists())
    {
       file_old.remove();
       file_new.rename("D:\\QtProject\\Design\\course.txt");
    }
    else
    {
       QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
    }
    QMessageBox::information(this,"通知","删除成功！","确认");
}


