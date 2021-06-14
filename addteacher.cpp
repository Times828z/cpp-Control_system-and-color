#include "addteacher.h"
#include "ui_addteacher.h"
#include"system.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"

addTeacher::addTeacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTeacher)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{background-color: purple;}");
}

addTeacher::~addTeacher()
{
    delete ui;
}

void addTeacher::on_btn_Confirm_clicked()
{
    QString teaNum = this->ui->teacher_num->text();
    QString teaName = this->ui->teacher_name->text();
    QString teaCourse1 = this->ui->teacher_course1->text();
    QString teaCourse2 = this->ui->teacher_course2->text();
    QString teaCourse3 = this->ui->teacher_course3->text();
    QString messagebox_out = "工号：" + teaNum + "\n"+"姓名：" + teaName + "\n"+"教授课程1：" + teaCourse1 + "\n"+"教授课程2：" + teaCourse2 + "教授课程3：" + teaCourse3;
    QString info="\n"+ teaNum + "    " + teaName + "    " + teaCourse1 + "    " + teaCourse2+"    " + teaCourse3;
    bool charge=teaNum.length()<1||teaName.length()<1||teaCourse1.length()<1||teaCourse2.length()<1 || teaCourse3.length()<1;
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

void addTeacher::writeIn(QString info)
{
    this->ui->teacher_course1->clear();
    this->ui->teacher_course2->clear();
    this->ui->teacher_course3->clear();
    this->ui->teacher_name->clear();
    this->ui->teacher_num->clear();

    QFile mFile("D:\\QtProject\\Design\\teacher.txt");
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

void addTeacher::on_btn_back_clicked()
{
    this->close();
    class system *aaaa = new class system();
    aaaa->show();
}


void addTeacher::on_btn_close_clicked()
{
    this->close();
}

