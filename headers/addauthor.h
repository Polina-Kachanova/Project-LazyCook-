#ifndef ADDAUTHOR_H
#define ADDAUTHOR_H

#include <QWidget>

namespace Ui {
class addAuthor;
}

class addAuthor : public QWidget
{
    Q_OBJECT

public:
    explicit addAuthor(QWidget *parent = 0);
    ~addAuthor();

private slots:
    void on_OKButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addAuthor *ui;
};

#endif // ADDAUTHOR_H
