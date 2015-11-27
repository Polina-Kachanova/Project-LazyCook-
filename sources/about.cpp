#include "about.h"
#include "ui_about.h"
#include <QPalette>
#include <QDir>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    ui->graphicsView->setVisible(true);

    QPalette pal(palette());
    QPixmap pixmap("../../../Images/blue.jpg");
    pal.setBrush((this)->backgroundRole(), QBrush(pixmap));
    (this)->setPalette(pal);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap("../../../Images/totoro.png"));

    ui->graphicsView->setScene(scene);
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_clicked()
{
    close();
}
