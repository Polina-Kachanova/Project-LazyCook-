#include "addauthor.h"
#include "ui_addauthor.h"
#include "Database.h"
#include <QPalette>
#include <QDir>

addAuthor::addAuthor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addAuthor)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);

    QPalette pal(palette());
    QPixmap pixmap("../../../Images/blue.jpg");
    pal.setBrush((this)->backgroundRole(), QBrush(pixmap));
    (this)->setPalette(pal);
}

addAuthor::~addAuthor()
{
    delete ui;
}

void addAuthor::on_OKButton_clicked()
{
    Database* db = Database :: getInstance();   //открывает базу данных
    db->AddAuthor(ui->author->text());  //передает в БД запрос (добавить в список авторов из строки author)
    close();
}

void addAuthor::on_pushButton_2_clicked()
{
    close();
}
