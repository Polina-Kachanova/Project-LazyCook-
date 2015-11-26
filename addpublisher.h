#ifndef ADDPUBLISHER_H
#define ADDPUBLISHER_H

#include <QWidget>

namespace Ui {
class addPublisher;
}

class addPublisher : public QWidget
{
    Q_OBJECT

public:
    explicit addPublisher(QWidget *parent = 0);
    ~addPublisher();

private slots:

    void on_OKbutton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addPublisher *ui;
};

#endif // ADDPUBLISHER_H
