#include "teacher_addscore.h"
#include "ui_teacher_addscore.h"
#include"teacher.h"
#include "QString"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include <QPainter>
#include <QPixmap>

teacher_addScore::teacher_addScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacher_addScore)
{
    ui->setupUi(this);
}

teacher_addScore::~teacher_addScore()
{
    delete ui;
}

void teacher_addScore::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/black.png"),QRect());		//传入资源图片路径
}

void teacher_addScore::writeIn(QString information)
{
    this->ui->t_student_nameLine->clear();
    this->ui->t_student_numLine->clear();
    this->ui->t_student_objectLine->clear();
    this->ui->t_student_scoreLine->clear();
    this->ui->t_student_nameLine->setFocus();
    QFile mFile("D:\\QtProject\\Design\\score.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<information<<"\n";
    mFile.flush();
    mFile.close();
}

//确认
void teacher_addScore::on_pushButton_clicked()
{
    QString name = this->ui->t_student_nameLine->text();
    QString num = this->ui->t_student_numLine->text();
    QString stuObject = this->ui->t_student_objectLine->text();
    QString score = this->ui->t_student_scoreLine->text();

    QString messagebox_out = "姓名：" + name + "\n" + "学号："+num+"\n"+"科目：" + stuObject + "\n" + "分数" +score;
    QString information=num + "\t" + name + "\t" + stuObject + "\t" + score;

    bool charge=name.length()<1||num.length()!=11||stuObject.length()<1||score.length()<1;

    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请重新填写","确定");
    }
    else
    {
       int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
       if(ret==0)
          {
             writeIn(information);
          }
    }

}


//返回
void teacher_addScore::on_pushButton_2_clicked()
{

    teacher *a = new teacher;
    a->show();
    this->close();
}

//关闭
void teacher_addScore::on_pushButton_3_clicked()
{
    this->close();
}

