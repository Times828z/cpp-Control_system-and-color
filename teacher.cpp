#include "teacher.h"
#include "ui_teacher.h"
#include"mainwindow.h"
#include"teacher_addscore.h"
#include"teacher_search.h"
#include <QPainter>
#include <QPixmap>
#include"datachange.h"
#include"importscore.h"

teacher::teacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacher)
{
    ui->setupUi(this);
}

teacher::~teacher()
{
    delete ui;
}


void teacher::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/image/gaitubao_build_png.png"),QRect());		//传入资源图片路径
}


void teacher::on_btn_back_clicked()
{
    MainWindow *main_window=new MainWindow;
    main_window->show();
    this->close();
}


void teacher::on_btn_close_clicked()
{
    this->close();
}



void teacher::on_btb_teacher_addScore_clicked()
{
    this->close();
    teacher_addScore a;
    a.exec();
}


void teacher::on_btn_importScore_clicked()
{

    this->close();
    importScore a;
    a.exec();
}


void teacher::on_btn_search_clicked()
{
        this->close();
        teacher_search a;
        a.exec();
}


void teacher::on_btn_change_clicked()
{

    this->close();
    DataChange A;
    A.exec();

}

