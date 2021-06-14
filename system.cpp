#include "system.h"
#include "ui_system.h"
#include"addstudent.h"
#include"addteacher.h"
#include"addcourse.h"
#include"delInfo.h"
#include"mainwindow.h"

system::system(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::system)
{
    ui->setupUi(this);
    this->setFixedSize(780,500);
    //设置背景色为黑色
    this->setStyleSheet("QDialog{background-color: black;}");
}

system::~system()
{
    delete ui;
}


/**
 * 以下为槽函数
 * on_btn_addStudengt_clicked()
 * 打开添加学生的窗口
 *
 * on_btn_addTeacher_clicked()
 * 打开添加老师的窗口
 *
 * on_btn_addCourse_clicked()
 * 打开添加课程的窗口
 *
 * void system::on_btn_del_clicked()
 * 打开删除信息的窗口
 *
 * on_pushButton_5_clicked()
 * 返回登录界面
 *
 * on_pushButton_6_clicked()
 * 直接退出
 **/

void system::on_btn_addStudengt_clicked()
{
    addStudent a;
    this->close();
    a.exec();
}


void system::on_btn_addTeacher_clicked()
{
    addTeacher a;
    this->close();
    a.exec();
}


void system::on_btn_addCourse_clicked()
{
    addCourse a;
    this->close();
    a.exec();

}


void system::on_btn_del_clicked()
{
    delInfo a;
    this->close();
    a.exec();

}


void system::on_pushButton_6_clicked()
{
    this->close();
}


void system::on_pushButton_5_clicked()
{
    MainWindow *main_window=new MainWindow;
    main_window->show();
    this->close();
}

