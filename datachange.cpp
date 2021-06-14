#include "datachange.h"
#include "ui_datachange.h"
#include"teacher.h"
#include <QPainter>
#include <QPixmap>
#include"teacher_search.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"

DataChange::DataChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataChange)
{
    ui->setupUi(this);
    this->setFixedSize(410,470);
}

DataChange::~DataChange()
{
    delete ui;
}


void DataChange::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/black.png"),QRect());		//传入资源图片路径
}


int DataChange::readfile()
{
    score_line.clear();
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

void DataChange::writeIn(QString information)
{
    this->ui->studengt_num->clear();
    this->ui->student_name->clear();
    this->ui->student_object->clear();
    this->ui->student_score->clear();
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

//删除信息
void DataChange::on_pushButton_clicked()
{
    QString del_name=this->ui->student_name->text();
    QString del_num=this->ui->studengt_num->text();
    QString del_object=this->ui->student_object->text();
    QString del_score=this->ui->student_score->text();
    readfile();
    int i=0;
    for (i=0;i<score_line.length();i++)
    {
        QString line=score_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        if(del_num != linesplit.at(0))
        {
            QFile file("D:\\QtProject\\Design\\score_temp.txt");
            if(!file.open(QIODevice::Append|QIODevice::Text))
            {
               QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
               return;
            }
        QTextStream out(&file);
        out<<line+"\n";
        file.close();
        }
    }
    QFile file_old("D:\\QtProject\\Design\\score.txt");
    QFile file_new("D:\\QtProject\\Design\\score_temp.txt");
    if (file_old.exists())
    {
       file_old.remove();
       file_new.rename("D:\\QtProject\\Design\\score.txt");
    }
    else
    {
       QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
    }
    QMessageBox::information(this,"通知","删除成功！","确认");
    this->close();

}


void DataChange::on_btn_change_clicked()
{
    QString change_name=this->ui->student_name->text();
    QString change_num=this->ui->studengt_num->text();
    QString change_object=this->ui->student_object->text();
    QString change_score=this->ui->student_score->text();
    QString messagebox_out= "姓名：" + change_name + "\n" + "学号：" + change_num + "\n" + "科目：" + change_object + "\n"+"分数："+change_score+"\n";
    QString information = change_num + " " +change_name + " " + change_object + " " + change_score;

    bool charge=change_name.length()<1||change_num.length()<9||change_object.length()<1;
    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，无法修改！","确定");
    }
    else
    {
         int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
         if(ret==0)
         {
         if(readfile()==-1)
         {
              this->close();
              QMessageBox::critical(this,"错误","文件读取失败，信息没有删除","确认");
         }
         else
         {
            int i=0;
            for (i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split("/t");
                if(change_num != linesplit.at(0))
                {
                     QFile file("D:\\QtProject\\Design\\score_temp.txt");
                     if(!file.open(QIODevice::Append|QIODevice::Text))
                     {
                         QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
                         return;
                     }
                     QTextStream out(&file);
                     out<<line+"\n";
                     file.close();
                 }
              }
          QFile file_old("D:\\QtProject\\Design\\score.txt");
          QFile file_new("D:\\QtProject\\Design\\score_temp.txt");
          if (file_old.exists())
          {
            file_old.remove();
            file_new.rename("D:\\QtProject\\Design\\score.txt");
          writeIn(information);
          }
          else
          {
            QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
          }
          QMessageBox::information(this,"通知","修改成功！","确认");
          this->close();
          }
          }
    }

}


void DataChange::on_btb_back_clicked()
{
    this->close();
    teacher *a = new teacher;
    a->show();

}


void DataChange::on_btn_close_clicked()
{
    this->close();
}


void DataChange::on_btn_import_clicked()
{
    this->ui->student_name->setText(name1);
    this->ui->studengt_num->setText(num1);
    this->ui->student_object->setText(object1);
    this->ui->student_score->setText(score1);
}

