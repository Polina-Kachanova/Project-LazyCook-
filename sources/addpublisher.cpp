#include "addpublisher.h"
#include "ui_addpublisher.h"
#include "Database.h"
#include <QPalette>
#include <QDir>

addPublisher::addPublisher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addPublisher)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);

    QPalette pal(palette());
    QPixmap pixmap("../../../Images/blue.jpg");
    pal.setBrush((this)->backgroundRole(), QBrush(pixmap));
    (this)->setPalette(pal);
}

addPublisher::~addPublisher()
{
    delete ui;
}


void addPublisher::on_OKbutton_clicked()
{
    Database* db = Database :: getInstance();
    db->AddPublisher(ui->publishName->text(), ui->publishAddress->text());
    close();
}

void addPublisher::on_pushButton_2_clicked()
{
    close();
}
