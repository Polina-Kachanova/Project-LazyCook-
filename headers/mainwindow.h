#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void refreshBooks();

    void deleteBook();

private slots:
    void on_bookButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_backButton_clicked();

    void on_aboutButton_clicked();

    void on_authorButton_clicked();

    void on_publisherButton_clicked();

    void on_genreButton_clicked();

    void on_deleteButton_clicked();

    void on_searchButton_clicked();

    void on_resetButton_clicked();

    void on_sortBox_currentIndexChanged(int index);

    void on_readButton_clicked();

    void on_notReadButton_clicked();

    void on_changeButton_clicked();

    void on_allButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
