#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include "system.h"
#include "student.h"
#include "teacher.h"
#include"QDebug"
#include"student_course.h"

//用户输入的账号和密码
QString account;
QString password;
QString st_name;
QString te_name;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(470,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//设置登陆界面的背景
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/gaitubao_ra_png.png"),QRect());		//传入资源图片路径
}


/**
 * 以下几个函数都是读取账号，密码的函数
 * 老师，学生，管理人员
 *
 */

//读取学生文件
int MainWindow::readstudentfile()
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

int MainWindow::readteacherfile()
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


/**
 * @brief MainWindow::on_btn_signIn_clicked
 *
 * 学生的初始密码：都为学生的学号
 * 教师的初始密码：2222
 * root用户的密码： 0000
 */
void MainWindow::on_btn_signIn_clicked()
{
    account=this->ui->id->text();
    password=this->ui->password->text();

    if(readstudentfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","学生信息读取失败，\n学生账户无法登录，\n可登录管理员账户修改！","确认");
    }
    else if (readteacherfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","教师信息读取失败，\n教师账户无法登录，\n可登录管理员账户修改！","确认");
    }

    int flag=100;

    if(account.at(0)=="2"){
        for (int i=0;i<student_line.length();i++){
            QString line=student_line.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split("\t");
            if(account==linesplit.at(0)&&password==linesplit.at(0)){
                flag = 0;
                st_name = linesplit.at(1);
                break;
            }
        }
        }
    else if(account.at(0)=="t"){
        for (int j=0;j<teacher_line.length();j++) {
                QString line=teacher_line.at(j);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                if(account==linesplit.at(0)&&password=="1111"){
                    flag = 1;
                    te_name = linesplit.at(1);
                    break;
                }
            }
    }
    else if(account=="root"&&password=="0000"){
        flag = 2;
    }
    else if (account.length()<1||password.length()<1)
    {
        QMessageBox::critical(this,"错误","请输入账号和密码！","确认");
        flag=3;
    }

    switch (flag)
    {
    case 0:
    {
        student a;
        this->close();
        a.exec();
        break;
    }
    case 1:
    {
        teacher a;
        this->close();
        a.exec();
        break;
    }
    case 2:{
        class system a;
        this->close();
        a.exec();
        break;
        }
    case 3:{
        break;
        }
    default:{
        QMessageBox::critical(this,"错误","账号密码错误!\n或账号不存在!","确认");
        break;
        }
    }
}


void MainWindow::on_btn_signOut_clicked()
{

    this->close();
}

