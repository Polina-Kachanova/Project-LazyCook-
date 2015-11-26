#ifndef ADDGenre_H
#define ADDGenre_H

#include <QWidget>

namespace Ui {
class addGenre;
}

class addGenre : public QWidget
{
    Q_OBJECT

public:
    explicit addGenre(QWidget *parent = 0);
    ~addGenre();

private slots:
    void on_pushButton_2_clicked();

    void on_OKbutton_clicked();

private:
    Ui::addGenre *ui;
};

#endif // ADDGenre_H
