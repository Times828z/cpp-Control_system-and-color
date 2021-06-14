#include "student_course.h"
#include "ui_student_course.h"
#include"QStandardItemModel"
#include"student.h"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include "QDebug"
#include <QPainter>
#include <QPixmap>
#include "mainwindow.h"


//表示已修的总学分
float sum;

student_course::student_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_course)
{
    ui->setupUi(this);

    //创建一个表
    this->model1=new QStandardItemModel;
    this->model1->setHorizontalHeaderItem(0,new QStandardItem("课程编号"));
    this->model1->setHorizontalHeaderItem(1,new QStandardItem("课程名称"));
    this->model1->setHorizontalHeaderItem(2,new QStandardItem("学分"));
    this->model1->setHorizontalHeaderItem(3,new QStandardItem("课时"));
    this->model1->setHorizontalHeaderItem(4,new QStandardItem("课程性质"));
    this->ui->tb_course->setModel(model1);
    this->ui->tb_course->setColumnWidth(0,190);
    this->ui->tb_course->setColumnWidth(1,250);
    this->ui->tb_course->setColumnWidth(2,100);
    this->ui->tb_course->setColumnWidth(3,100);
    this->ui->tb_course->setColumnWidth(4,100);

    //以单元格的方式选中
    this->ui->tb_course->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不能修改表格内容
    this->ui->tb_course->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //创建一个表
    this->model2=new QStandardItemModel;
    this->model2->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model2->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model2->setHorizontalHeaderItem(2,new QStandardItem("课程名称"));
    this->model2->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model2->setHorizontalHeaderItem(4,new QStandardItem("课时"));
    this->model2->setHorizontalHeaderItem(5,new QStandardItem("课程性质"));
    this->ui->tb_select->setModel(model2);
    this->ui->tb_select->setColumnWidth(0,100);
    this->ui->tb_select->setColumnWidth(1,190);
    this->ui->tb_select->setColumnWidth(2,250);
    this->ui->tb_select->setColumnWidth(3,100);
    this->ui->tb_select->setColumnWidth(4,100);
    this->ui->tb_select->setColumnWidth(5,100);
    //以单元格的方式选中
    this->ui->tb_course->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不能修改表格内容
    this->ui->tb_course->setEditTriggers(QAbstractItemView::NoEditTriggers);


    if(readcoursefile()==-1)
    {
        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
    }

    if(readselectedfile()==-1)
    {
        this->close();
//        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
    }

    //将表存入已选择的课
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        display1(r++, linesplit);
    }

    this->ui->sumPoint->setText(QString("%1").arg(sum));


}

void student_course::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/gaitubao_e_png.png"),QRect());		//传入资源图片路径
}


//重新设置表一
void student_course::reset()
{
    this->model1=new QStandardItemModel;
    this->model1->setHorizontalHeaderItem(0,new QStandardItem("课程编号"));
    this->model1->setHorizontalHeaderItem(1,new QStandardItem("课程名称"));
    this->model1->setHorizontalHeaderItem(2,new QStandardItem("学分"));
    this->model1->setHorizontalHeaderItem(3,new QStandardItem("课时"));
    this->model1->setHorizontalHeaderItem(4,new QStandardItem("课程性质"));
    this->ui->tb_course->setModel(model1);
    this->ui->tb_course->setColumnWidth(0,190);
    this->ui->tb_course->setColumnWidth(1,250);
    this->ui->tb_course->setColumnWidth(2,100);
    this->ui->tb_course->setColumnWidth(3,100);
    this->ui->tb_course->setColumnWidth(4,100);

}

void student_course::reset1()
{
    this->model2=new QStandardItemModel;
    this->model2->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model2->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model2->setHorizontalHeaderItem(2,new QStandardItem("课程名称"));
    this->model2->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->model2->setHorizontalHeaderItem(4,new QStandardItem("课时"));
    this->model2->setHorizontalHeaderItem(5,new QStandardItem("课程性质"));

    this->ui->tb_select->setModel(model2);
    this->ui->tb_select->setColumnWidth(0,100);
    this->ui->tb_select->setColumnWidth(1,190);
    this->ui->tb_select->setColumnWidth(2,250);
    this->ui->tb_select->setColumnWidth(3,100);
    this->ui->tb_select->setColumnWidth(4,100);
    this->ui->tb_select->setColumnWidth(5,100);
}

//读取课程文件
int student_course::readcoursefile()
{
    course_line.clear();
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

//读取已选课程的文件
int student_course::readselectedfile()
{
    sum=0;
    selected_line.clear();
    QFile file("D:\\QtProject\\Design\\selected.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       selected_line.append(line);
       QStringList linesplit=line.split("\t");
       sum+=linesplit.at(3).toFloat();
    }
    file.close();
    return 0;
}


/**
 * @brief student_course::display
 * @param row 表示读入的行数
 * @param course_line 从course文件读入的list
 *
 * 以下两函数用于展示table
 */

void student_course::display(int row, QStringList course_line)
{
    int i=0;
    for (i=0;i<course_line.length();i++)
    {
        this->model1->setItem(row,i,new QStandardItem(course_line.at(i)));
    }
}



void student_course::display1(int row, QStringList selected_line)
{
    int i=0;
    for (i=0;i<selected_line.length();i++)
    {
        this->model2->setItem(row,i,new QStandardItem(selected_line.at(i)));
    }
}


//写入选课文件
void student_course::writeIn(QString info)
{
    QFile mFile("D:\\QtProject\\Design\\selected.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，课程没有添加","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<info<<"\n";
    mFile.flush();
    mFile.close();
}




student_course::~student_course()
{
    delete ui;
}

//点击返回
void student_course::on_btn_back_clicked()
{
    this->close();
    student *a = new student;
    a->show();

}

//点击退出
void student_course::on_btn_close_clicked()
{
    this->close();
}

//点击确认选课
void student_course::on_confirm_clicked()
{

    this->model1->clear();
    reset();
    //0->course_num 1->course_name 2->course_point 3->course_point 4->course_nature
    int flag=this->ui->cb_queryway->currentIndex();
    //输入的信息
    QString cname=this->ui->cin_name->text();

    if (cname.length()<1)
    {
        QMessageBox::critical(this,"错误","输入信息错误，请重试！","确认");
    }
    else
    {
        int row=0;
        for (int i=0;i<course_line.length();i++)
        {
            QString line=course_line.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split("\t");
            switch (flag)
            {
            // as course_num
            case 0:
                if(linesplit.at(0).contains(cname,Qt::CaseSensitive))
                {
                    display(row++, linesplit);
                }
                break;
            //as course_name
            case 1:
                if(linesplit.at(1).contains(cname,Qt::CaseSensitive))
                {
                    display(row++, linesplit);
                }
                break;
            //as course_point
            case 2:
                if(linesplit.at(2).contains(cname,Qt::CaseSensitive))
                {
                    display(row++, linesplit);
                }
                break;
            //as course_time
            case 3:
                if(linesplit.at(3).contains(cname,Qt::CaseSensitive))
                {
                    display(row++, linesplit);
                }
                break;
            //as course_nature
            case 4:
                if(linesplit.at(4).contains(cname,Qt::CaseSensitive))
                {
                    display(row++, linesplit);
                }
                break;
            default:
                break;
            }
        }
    }
}


//点击显示全部
void student_course::on_showAll_clicked()
{

    this->model1->clear();
    reset();
    readcoursefile();
    int r=0;
    for(int i=0;i<course_line.length();i++)
    {
        QString line=course_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        display(r++, linesplit);
    }
}


//双击选课表
void student_course::on_tb_course_doubleClicked(const QModelIndex &index)
{

    int flag=0;
    int row=this->ui->tb_course->currentIndex().row();
    QString course_num = model1->data(model1->index(row,0)).toString();
    QString course_name = model1->data(model1->index(row,1)).toString();
    QString course_point = model1->data(model1->index(row,2)).toString();
    QString course_time = model1->data(model1->index(row,3)).toString();
    QString course_nature = model1->data(model1->index(row,4)).toString();

    readselectedfile();

    //循环遍历selectd 确认是否学生选课
    for(int i=0;i<selected_line.length();i++)
    {
        if(selected_line.at(i) == " "){
            break;
        }

        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        if(course_num==linesplit.at(1) && st_name ==linesplit.at(0))
        {
            QMessageBox::critical(this,"错误","不可重复选择课程！","确认");
            flag=1;
        }
    }

    if(flag==0)
    {

    QString messagebox_out="课程编号："+course_num+"\n"+"课程名称："+course_name+"\n"+"学分："+course_point+"\n"+
                           "课时："+course_time+"\n"+"课程性质："+course_nature+"\n";

    QString info=st_name+ "\t" + course_num + "\t" + course_name + "\t" + course_point + "\t" + course_time + "\t"+course_nature;

    int ret=QMessageBox::question(this,"请确认",messagebox_out,"选课","取消");

    if(ret==0)
       {
          writeIn(info);
       }


    this->model2->clear();
    reset1();
    readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        display1(r++, linesplit);
    }
    this->ui->sumPoint->setText(QString("%1").arg(sum));
    }

}


//双击已选课程表
void student_course::on_tb_select_doubleClicked(const QModelIndex &index)
{


    int row=this->ui->tb_select->currentIndex().row();
    //name表示课程编号
    QString name=model2->data(model2->index(row,1)).toString();
    int ret=QMessageBox::question(this,"请确认","确定退出当前课程？","退课","取消");
    if(ret==0)
    {
        for (int i=0;i<selected_line.length();i++)
        {
            if(selected_line.at(0) == " "){
                break;
            }
            QString line=selected_line.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split("\t");
            if(name!=linesplit.at(1) || st_name !=linesplit.at(0))
            {
                QFile file("D:\\QtProject\\Design\\selected_temp.txt");
                if(!file.open(QIODevice::Append|QIODevice::Text))
                {
                   QMessageBox::critical(this,"错误","文件打开失败！","确认");
                   return;
                }
            QTextStream out(&file);
            out<<line+"\n";
            file.close();
            }
        }
        QFile file_old("D:\\QtProject\\Design\\selected.txt");
        QFile file_new("D:\\QtProject\\Design\\selected_temp.txt");
        if (file_old.exists())
        {
           file_old.remove();
           file_new.rename("D:\\QtProject\\Design\\selected.txt");
        }
        else
        {
           QMessageBox::critical(this,"错误","未有信息保存为文件，无法退课","确认");
        }
        QMessageBox::information(this,"通知","退课成功！","确认");
    }

    this->model2->clear();
    reset1();
    readselectedfile();
    int r=0;
    for(int i=0;i<selected_line.length();i++)
    {
        if(selected_line.at(0) == " "){
            break;
        }
        QString line=selected_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split("\t");
        display1(r++, linesplit);
    }
    this->ui->sumPoint->setText(QString("%1").arg(sum));
}

