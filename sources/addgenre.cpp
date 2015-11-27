#include "addgenre.h"
#include "ui_addgenre.h"
#include "Database.h"
#include <QPalette>
#include <QDir>

addGenre::addGenre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addGenre)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);

    QPalette pal(palette());
    QPixmap pixmap("../../../Images/blue.jpg");
    pal.setBrush((this)->backgroundRole(), QBrush(pixmap));
    (this)->setPalette(pal);
}

addGenre::~addGenre()
{
    delete ui;
}

void addGenre::on_pushButton_2_clicked()
{
    close();
}

void addGenre::on_OKbutton_clicked()
{
    Database* db = Database :: getInstance();
    db->AddGenre(ui->genre->text());
    close();
}
