#include "addcourse.h"
#include "ui_addcourse.h"
#include"system.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"

addCourse::addCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCourse)
{
    ui->setupUi(this);
    //设置背景为紫色
    this->setStyleSheet("QDialog{background-color: purple;}");
}

addCourse::~addCourse()
{
    delete ui;
}


//确认按钮
void addCourse::on_btn_Confirm_clicked()
{
    QString id=this->ui->course_num->text();
    QString name=this->ui->course_name->text();
    QString nature=this->ui->course_nature->currentText();
    QString credit=this->ui->course_credit->currentText();
    QString time = this->ui->course_time->text();
    QString messagebox_out="课程编号："+id+"\n"+"课程名称："+name+"\n"+"课程学分："+credit+"\n"+"课程学时："+time+"\n"+"课程性质："+nature;
    QString info="\n"+id + "    " + name + "    " + credit + "    " + time + "    " + nature;
    bool charge=name.length()<1||id.length()<1||time.length()==0;
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


void addCourse::writeIn(QString info)
{
    this->ui->course_name->clear();
    this->ui->course_num->clear();
    this->ui->course_time->clear();

    QFile mFile("D:\\QtProject\\Design\\course.txt");
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

//退出按钮
void addCourse::on_btn_close_clicked()
{
    this->close();
}

//返回按钮
void addCourse::on_btn_back_clicked()
{
    this->close();
    class system *aaaa = new class system();
    aaaa->show();
}

