#include "teacher_search.h"
#include "ui_teacher_search.h"
#include"teacher.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QDebug"
#include <QPainter>
#include <QPixmap>
#include"datachange.h"

QString num1;
QString name1;
QString object1;
QString score1;

teacher_search::teacher_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacher_search)
{
    ui->setupUi(this);
    this->model=new QStandardItemModel;

    this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("科目"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("成绩"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,200);
    this->ui->tableView->setColumnWidth(1,100);
    this->ui->tableView->setColumnWidth(2,260);
    this->ui->tableView->setColumnWidth(3,100);
}

teacher_search::~teacher_search()
{
    delete ui;
}

void teacher_search::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/gaitubao_build_png.png"),QRect());		//传入资源图片路径
}


void teacher_search::reset()
{
    this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("科目"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("成绩"));
    this->ui->tableView->setColumnWidth(0,200);
    this->ui->tableView->setColumnWidth(1,100);
    this->ui->tableView->setColumnWidth(2,260);
    this->ui->tableView->setColumnWidth(3,100);
}

int teacher_search::readfile()
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

void teacher_search::display(int row, QStringList score_line)
{
    int i=0;
    for (i=0;i<score_line.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(score_line.at(i)));
    }
}


void teacher_search::on_btn_back_clicked()
{
    teacher *a = new teacher;
    a->show();
    this->close();
}


void teacher_search::on_btn_close_clicked()
{
    this->close();
}


void teacher_search::on_btn_confirm_clicked()
{
    this->model->clear();
    reset();
    readfile();
    int flag=this->ui->cb_choice->currentIndex();
    QString infor=this->ui->lineInfo->text();

    if (infor.length()<1)
    {
            QMessageBox::critical(this,"错误","输入信息错误，请重试！","确认");
    }
    else
    {
            int i=0,row=0;
            for (i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split("\t");
                if(linesplit.at(0)==" "){
                    break;
                }
                switch (flag)
                {
                //学号
                case 0:
                    if(linesplit.at(0).contains(infor,Qt::CaseSensitive))
                    {
                        display(row++, linesplit);
                    }
                    break;
                //姓名
                case 1:
                    if(linesplit.at(1).contains(infor,Qt::CaseSensitive))
                    {
                         display(row++, linesplit);;
                    }
                    break;
                //科目
                case 2:
                    if(linesplit.at(2).contains(infor,Qt::CaseSensitive))
                    {
                         display(row++, linesplit);
                    }
                break;
                default:break;
                }
            }
    }
}


void teacher_search::on_tableView_doubleClicked(const QModelIndex &index)
{
    DataChange a;
    int row=this->ui->tableView->currentIndex().row();
    num1=model->data(model->index(row,0)).toString();
    name1=model->data(model->index(row,1)).toString();
    object1=model->data(model->index(row,2)).toString();
    score1=model->data(model->index(row,3)).toString();
    a.exec();
}

