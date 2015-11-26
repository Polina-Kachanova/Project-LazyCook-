#ifndef SEONDFORM_H
#define SEONDFORM_H

#include <QWidget>

namespace Ui {
class SeondForm;
}

class SeondForm : public QWidget
{
    Q_OBJECT

public:
    explicit SeondForm(QWidget *parent = 0);
    ~SeondForm();

private slots:

    void on_OKButton_clicked();

    void on_cancelButton_clicked();

signals:
    void bookCreated();

private:
    Ui::SeondForm *ui;
};

#endif // SEONDFORM_H
