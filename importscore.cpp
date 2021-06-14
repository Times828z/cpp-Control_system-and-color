#include "importscore.h"
#include "ui_importscore.h"
#include"QFileDialog"
#include"teacher.h"
#include"QPushButton"
#include <QPainter>
#include <QPixmap>
#include"QString"
#include "QFile"
#include "QTextStream"
#include "QStringList"
#include "QDebug"
#include "QMessageBox"


importScore::importScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::importScore)
{
    ui->setupUi(this);
    //点击按钮，弹出对话框
    connect(ui->btn_selectFilm,&QPushButton::clicked,[=](){
        QString filePath =  QFileDialog::getOpenFileName(this,"打开文件","D:\\QtProject\\Design");
        ui->path->setText(filePath);

    });

    this->model=new QStandardItemModel;
    this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("科目"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("成绩"));
    this->ui->tableView->setModel(model);
    this->ui->tableView->setColumnWidth(0,130);
    this->ui->tableView->setColumnWidth(1,100);
    this->ui->tableView->setColumnWidth(2,250);
    this->ui->tableView->setColumnWidth(3,110);

}

importScore::~importScore()
{
    delete ui;
}

void importScore::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/gaitubao_build_png.png"),QRect());		//传入资源图片路径
}

//读取选择的文件
int importScore::readfile(QString filePath)
{
    score_line.clear();
    QFile file(filePath);
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


void importScore::reset()
{
    this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("科目"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("成绩"));

    this->ui->tableView->setColumnWidth(0,130);
    this->ui->tableView->setColumnWidth(1,120);
    this->ui->tableView->setColumnWidth(2,150);
    this->ui->tableView->setColumnWidth(3,100);

}

void importScore::display(int row, QStringList score_line)
{
    int i=0;
    for (i=0;i<score_line.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(score_line.at(i)));
    }
}

void importScore::on_pushButton_clicked()
{
    this->close();
    teacher *a = new teacher;
    a->show();
}


void importScore::on_pushButton_2_clicked()
{
    this->close();
}


void importScore::on_btn_sort_clicked()
{
    this->model->clear();
    reset();
    QString filePath = ui->path->text();
    readfile(filePath);
    QString infor=this->ui->in_object->text();

    if (infor.length()==0)
    {
        int row = 0;
            for (int i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split("\t");
                if(linesplit.at(0)==" "){
                    break;
                }
                     display(row++, linesplit);
            }
    }
    else
    {
        int row = 0;
            for (int i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split("\t");
                if(linesplit.at(0)==" "){
                    break;
                }
                if(linesplit.at(2).contains(infor,Qt::CaseSensitive))
                {
                     display(row++, linesplit);
                }
            }
    }


        int flag=this->ui->cb_sortWay->currentIndex();

        switch (flag) {
        case 1:
            model->sort(0,Qt::DescendingOrder);
            break;
        case 0:
            model->sort(3,Qt::DescendingOrder);
            break;
        case 2:
            break;
        default:
            break;
        }
}


void importScore::on_btn_analyse_clicked()
{
    this->model->clear();
    QString filePath = ui->path->text();
    readfile(filePath);
    on_btn_sort_clicked();
    //总分
    double sum =0;
    //及格率
    double pass = 0;
    //平均分
    double ave=0;
    //方差
    double var=0;
    int row=this->model->rowCount();

    for(int i=0;i<row;i++)//计算总分和通过课程数
    {
        QModelIndex index=model->index(i,3,QModelIndex());
        QString temp= index.data().toString();
        double one=temp.toDouble();
        sum += one;
        if(one>=60)
        {
            pass++;
        }
    }


    pass/=row;
    ave=sum/row;


    for(int i=0;i<row;i++)
    {
        QModelIndex index=model->index(i,6,QModelIndex());
        QString temp= index.data().toString();
        double one=temp.toDouble();
        var += (one-ave)*(one-ave);
    }

    var /=row;

    this->model->setItem(++row,0,new QStandardItem("及格率"));
    this->model->setItem(row,3,new QStandardItem(QString::number(pass)));
    this->model->setItem(++row,0,new QStandardItem("平均分"));
    this->model->setItem(row,3,new QStandardItem(QString::number(ave)));
    this->model->setItem(++row,0,new QStandardItem("方差"));
    this->model->setItem(row,3,new QStandardItem(QString::number(var)));

}

