#include "mainwindow.h"
#include "seondform.h"
#include "Database.h"
#include "about.h"
#include "Book.h"
#include <vector>
#include "ui_mainwindow.h"
#include "addauthor.h"
#include "addpublisher.h"
#include "addgenre.h"
#include "text.h"
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal(palette());
    QPixmap pixmap(/*QDir::currentPath() + */"../../../Images/blue.jpg");
    pal.setBrush(QPalette::Window,QBrush(pixmap));
    (this)->setPalette(pal);

    ui->listWidget->setVisible(false);
    ui->backButton->setVisible(false);
    ui->descriptionBrowser->setVisible(false);
    ui->deleteButton->setVisible(false);
    ui->readButton->setVisible(false);
    ui->notReadButton->setVisible(false);
    ui->allButton->setVisible(false);
    ui->changeButton->setVisible(false);
    refreshBooks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bookButton_clicked()
{
    SeondForm* f = new SeondForm();
    connect(f, SIGNAL(bookCreated()), this, SLOT(refreshBooks()));
    f->show();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->listWidget->setVisible(false);
    ui->backButton->setVisible(true);
    ui->descriptionBrowser->setVisible(true);
    ui->deleteButton->setVisible(true);
    ui->changeButton->setVisible(true);
    int bookId = item->data(33).toInt();
    Database* db = Database::getInstance();
    Book* book = db->GetOneBook(bookId);
    QString bookDescription = QString()
            .append("Author: ")
            .append(book->GetAuthor()->GetName())
            .append("\n")
            .append("Type of Dish: ")
            .append(book->GetPublisher()->GetName())
            .append("\n")
            .append("Status of Dish: ")
            .append(book->GetStatusString())
            .append("\n")
            .append("Rating: ")
            .append(QString::number(book->GetRating()))
            .append("\n")
            .append("Annotation: ")
            .append(book->GetAnnotation());
    vector<Genre*>* genres = db->GetGenresOfBook(bookId);
    for (vector<Genre*>::iterator g = genres->begin(); g != genres->end(); g++)
    {
        bookDescription.append("\n").append("Ingredients: ").append((*g)->GetName());
    }
    ui->descriptionBrowser->setText(bookDescription);

}

void MainWindow::on_backButton_clicked()
{
    ui->listWidget->setVisible(true);
    ui->backButton->setVisible(false);
    ui->descriptionBrowser->setVisible(false);
    ui->deleteButton->setVisible(false);
    ui->changeButton->setVisible(false);
}

void MainWindow::on_aboutButton_clicked()
{
   About *a = new About();
   a->show();
}

void MainWindow::on_authorButton_clicked()
{
    addAuthor* a = new addAuthor();
    a->show();
}

void MainWindow::refreshBooks()
{
    ui->listWidget->setVisible(true);
    ui->deleteButton->setVisible(false);
    Database* db = Database::getInstance();
    vector<Book*> books = db->GetAllBooks();    // передается запрос в БД (получить все книги, содержащиеся в ней)
    ui->listWidget->clear();
    for (unsigned int i = 0; i < books.size(); i++) {
        QListWidgetItem* item = new QListWidgetItem(books[i]->GetName()); // item содержит название каждой книги из вектора books
        item->setData(33, QVariant(books[i]->GetId())); // и также запоминает их id, чтобы потом к книге можно было обратиться с его помощью
        ui->listWidget->addItem(item);
    }
}

void MainWindow:: deleteBook()
{
    Database* db = Database :: getInstance();   //открывает базу данных
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();
    for (int i = 0; i < selectedItems.size(); i++)
    {
        QListWidgetItem* item = selectedItems[i];   // в item находится название выбранной книги
        int bookId = item->data(33).toInt();    // в bookId заносится id данной книги
        db->DelBook(bookId);    //осуществляется запрос в БД (удалить книгу по id)
    }
    ui->descriptionBrowser->setVisible(false);
    refreshBooks();     // обновляется список книг
    ui->changeButton->setVisible(false);
    ui->backButton->setVisible(false);
}

void MainWindow::on_publisherButton_clicked()
{
    addPublisher* p = new addPublisher();
    p->show();
}

void MainWindow::on_genreButton_clicked()
{
    addGenre * g = new addGenre();
    g->show();
}




void MainWindow::on_deleteButton_clicked()
{
    QMessageBox::StandardButton reply;  //создание стандартной формы подтверждения
      reply = QMessageBox::question(this, "Sure?", "Are you sure?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)    //при получении утвердительного ответа
      {
        deleteBook();   //вызывается функция удаления книги
      }

}

void MainWindow::on_searchButton_clicked()
{
    Database * db = Database::getInstance();
    int searchPublisher = ui->sortBox->currentIndex();
    QString searchString = ui->searchLine->text();
    switch (searchPublisher)
    {
    case 0: //если критерий посика - название книги
            {
                vector<Book*> books = db->GetBooksOfName(searchString);     // передается запрос в БД (найти книгу по ее названию)
                ui->listWidget->clear();

                for (unsigned int i = 0; i < books.size(); i++)
                {
                    QListWidgetItem* item = new QListWidgetItem(books[i]->GetName());   // item запоминает имя каждой книги из вектора books
                    item->setData(33, QVariant(books[i]->GetId()));
                    ui->listWidget->addItem(item);      // и возвращает в ListWidget их названия
                }
                break;
            }
    case 1:
            {
                vector<Book*> books = db->GetBooksOfAuthor(searchString);
                ui->listWidget->clear();

                for (unsigned int i = 0; i < books.size(); i++)
                {
                    QListWidgetItem* item = new QListWidgetItem(books[i]->GetName());
                    item->setData(33, QVariant(books[i]->GetId()));
                    ui->listWidget->addItem(item);
                }
                break;
            }
     case 2:
            {
                vector<Book*> books = db->GetBooksOfPublisher(searchString);
                ui->listWidget->clear();

                for (unsigned int i = 0; i < books.size(); i++)
                {
                    QListWidgetItem* item = new QListWidgetItem(books[i]->GetName());
                    item->setData(33, QVariant(books[i]->GetId()));
                    ui->listWidget->addItem(item);
                }
                break;
            }

      case 3:
            {
                break;
            }

      case 4:
            {
                vector<Book*> books = db->GetBooksOfGenre(searchString);
                ui->listWidget->clear();

                for (unsigned int i = 0; i < books.size(); i++)
                {
                    QListWidgetItem* item = new QListWidgetItem(books[i]->GetName());
                    item->setData(33, QVariant(books[i]->GetId()));
                    ui->listWidget->addItem(item);
                }
                break;
            }

    }
}

void MainWindow::on_resetButton_clicked()
{
    ui->searchLine->setText("");
    ui->allButton->setChecked(true);
    refreshBooks();
}

void MainWindow::on_sortBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 3:
            ui->searchLine->setVisible(false);
            ui->searchButton->setVisible(false);
            ui->readButton->setVisible(true);
            ui->notReadButton->setVisible(true);
            ui->allButton->setVisible(true);
            break;
        default:
        ui->searchLine->setVisible(true);
        ui->searchButton->setVisible(true);
        ui->readButton->setVisible(false);
        ui->notReadButton->setVisible(false);
        ui->allButton->setVisible(false);
    }
}

void MainWindow::on_readButton_clicked()
{
    Database* db = Database:: getInstance();
    vector<Book*> books = db->GetBooksOfStatus(1);
    ui->listWidget->clear();

    for (unsigned int i = 0; i < books.size(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem(books[i]->GetName());
        item->setData(33, QVariant(books[i]->GetId()));
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_notReadButton_clicked()
{
    Database* db = Database:: getInstance();
    vector<Book*> books = db->GetBooksOfStatus(0);
    ui->listWidget->clear();

    for (unsigned int i = 0; i < books.size(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem(books[i]->GetName());
        item->setData(33, QVariant(books[i]->GetId()));
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_changeButton_clicked()
{
    Database* db = Database :: getInstance();   //открывает базу данных
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();
    for (int i = 0; i < selectedItems.size(); i++)
    {
        QListWidgetItem* item = selectedItems[i];   // в item находится название выбранной книги
        int bookId = item->data(33).toInt();    // в bookId заносится id данной книги
        db->ChangeBookStatus(bookId, 1);    //осуществляется запрос в БД (удалить книгу по id)
    }
    ui->descriptionBrowser->setVisible(false);
    refreshBooks();
    ui->changeButton->setVisible(false);
    ui->backButton->setVisible(false);
}

void MainWindow::on_allButton_clicked()
{
    refreshBooks();
}
