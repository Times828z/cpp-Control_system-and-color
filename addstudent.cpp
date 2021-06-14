#include "addstudent.h"
#include "ui_addstudent.h"
#include"system.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"

addStudent::addStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStudent)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{background-color: purple;}");
}

addStudent::~addStudent()
{
    delete ui;
}

void addStudent::on_btn_Confirm_clicked()
{
    QString stuNum = this->ui->student_num->text();
    QString stuName = this->ui->student_name->text();
    QString stuClass = this->ui->student_class->text();
    QString stuMajor = this->ui->student_major->text();
    QString messagebox_out = "学号：" + stuNum + "\n"+"姓名：" + stuName + "\n"+"班级：" + stuClass + "\n"+"专业：" + stuMajor;
    QString info="\n"+ stuNum + "    " + stuName + "    " + stuClass + "    " + stuMajor;
    bool charge=stuNum.length()<1||stuName.length()<1||stuClass.length()<1||stuMajor.length()<1;
    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }
    else
    {
       int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
       if(ret==0)
          {
             writeIn(info);
          }
    }
}


void addStudent::writeIn(QString info)
{
    this->ui->student_class->clear();
    this->ui->student_major->clear();
    this->ui->student_name->clear();
    this->ui->student_num->clear();

    QFile mFile("D:\\QtProject\\Design\\student.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<info<<"\n";
    mFile.flush();
    mFile.close();
}


void addStudent::on_btn_back_clicked()
{
    this->close();
    class system *aaaa = new class system();
    aaaa->show();
}


void addStudent::on_btn_close_clicked()
{
    this->close();
}

