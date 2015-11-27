#include "seondform.h"
#include "ui_seondform.h"
#include <vector>
#include <QListWidgetItem>
#include <QMessageBox>
#include "Database.h"
#include "Author.h"
#include <QPalette>
#include <QDir>

SeondForm::SeondForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeondForm)
{
    ui->setupUi(this);

    QPalette pal(palette());
    QPixmap pixmap("../../../Images/blue.jpg");
    pal.setBrush((this)->backgroundRole(), QBrush(pixmap));
    (this)->setPalette(pal);

    Database* db = Database::getInstance();
    vector<Author*> authors = db->GetAllAuthors();
    for (unsigned int i = 0; i < authors.size(); i++) {
        ui->authorBox->addItem(authors[i]->GetName(), QVariant(authors[i]->GetId()));
    }

    vector<Publisher*> publishers = db->GetAllPublishers();
    for (unsigned int i = 0; i < publishers.size(); i++) {
        ui->publisherBox->addItem(publishers[i]->GetName(), QVariant(publishers[i]->GetId()));
    }

    vector<Genre*> genres = db->GetAllGenres();
    for (unsigned int i = 0; i < genres.size(); i++) {
        QListWidgetItem* item = new QListWidgetItem(genres[i]->GetName());
        item->setData(33, genres[i]->GetId());
        ui->genresList->addItem(item);
    }
}

SeondForm::~SeondForm()
{
    delete ui;
}

void SeondForm::on_OKButton_clicked()
{
    QString bookName = ui->bookName->text();
    QString annotation = ui->textEdit->toPlainText();
    bool status = ui->yesButton->isChecked();
    int authorId = ui->authorBox->itemData(ui->authorBox->currentIndex()).toInt(),
        publisherId = ui->publisherBox->itemData(ui->publisherBox->currentIndex()).toInt(),
        rating = ui->numberBox->value();

    Database* db = Database :: getInstance();
    int bookId = db->AddBook(bookName, authorId, publisherId, rating, annotation, status);    //передается запрос в БД (создать новую запись с данным описанием)

    QList<QListWidgetItem*> genres = ui->genresList->selectedItems();
    for (QList<QListWidgetItem*>::iterator g = genres.begin(); g != genres.end(); g++)
    {
        db->AddBookGenre(bookId, (*g)->data(33).toInt());   //поскольку жанров может быть несколько, они заносятся отдельно
    }

    emit bookCreated(); // сигнал о том, что новая запись создана, передается в ListWidget

    close();
}

void SeondForm::on_cancelButton_clicked()
{
    close();
}
