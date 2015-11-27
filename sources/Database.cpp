#include "Database.h"
#include <iostream>
#include <sstream>

using namespace std;

Database* Database::instance = NULL;

Database :: Database()
{
    int rc;
    rc = sqlite3_open("books.db", &db);
    if (rc) {
        cout << "Can't open DB" << endl;
        sqlite3_close(db);
    }
}

Database :: ~Database()
{
    if(db)
    sqlite3_close(db);
}

Database* Database::getInstance()
{
    if (!instance) 
    {
        instance = new Database();
    }

    return instance;
}

//добавление

int Database::AddAuthor(QString name)
{
	int rc = 0;
	char* errMsg;
    QString query = QString("insert into authors (name) values('").append(name).append("')"); // запрос, передаваемый в базу данных

    rc = sqlite3_exec(db, qPrintable(query), ProcessEmpty, NULL, &errMsg); // db - база данных проекта;
                                                                           //ProcessEmpty - обработчик данного запроса
	if (rc != SQLITE_OK) {
        cout << errMsg << endl; //возвращает ошибку, если доступ к базе данных ограничен или запрос составлен неправильно
		sqlite3_free(errMsg);
		return 0;
	}
	int id = 0;
    rc = sqlite3_exec(db, "SELECT last_insert_rowid();", ProcessInt, &id, &errMsg); //запоминает номер последнего добавленного элемента
    return id; //и возвращает его
}

int Database::AddPublisher(QString name, QString address)
{
	int rc = 0;
	char* errMsg;
    QString query = QString("insert into publishers (name, address) values( '").append(name).append("','").append(address).append("'); ");

    rc = sqlite3_exec(db, qPrintable(query), ProcessEmpty, NULL, &errMsg);
    if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
		return 0;
	}
	int id = 0;
	rc = sqlite3_exec(db, "SELECT last_insert_rowid();", ProcessInt, &id, &errMsg);
	return id;
}

int Database::AddBook(QString name, int author_id, int publisher_id, int rating, QString annotation, bool status_book)
{
    int rc = 0;
    char* errMsg;
    QString query = QString("insert into books (name, author_id, publisher_id, rating, annotation, status_book) values ( '")
            .append(name)
            .append("',")
            .append(QString::number(author_id))
            .append(",")
            .append(QString::number(publisher_id))
            .append(",")
            .append(QString::number(rating))
            .append(",'")
            .append(annotation)
            .append("',")
            .append(QString::number(status_book))
            .append(");");

    rc = sqlite3_exec(db, qPrintable(query), ProcessEmpty, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
        return 0;
    }
    int id = 0;
    rc = sqlite3_exec(db, "SELECT last_insert_rowid();", ProcessInt, &id, &errMsg);
    return id;
}

int Database::AddGenre(QString name)
{
	int rc = 0;
	char* errMsg;
    QString query = QString("insert into genres (name) values( '").append(name).append("'); ");

    rc = sqlite3_exec(db,qPrintable(query), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
		return 0;
	}
	int id = 0;
	rc = sqlite3_exec(db, "SELECT last_insert_rowid();", ProcessInt, &id, &errMsg);
	return id;
}

void Database::AddBookGenre(int bookId, int genreId)
{
    int rc = 0;
    char* errMsg;
    QString query = QString("insert into book_genres (book_id, genre_id) values (").append(QString::number(bookId)).append(",").append(QString::number(genreId)).append(");");

    rc = sqlite3_exec(db,qPrintable(query), ProcessEmpty, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
        return;
    }
    int id = 0;
    rc = sqlite3_exec(db, "SELECT last_insert_rowid();", ProcessInt, &id, &errMsg);
}

//удаление

void Database::DelAuthor(char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
	ss << "delete from authors where name = '" << name << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::DelPublisher(char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "delete from publishers where name = '" << name << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::DelBook(int id)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "delete from books where id = '" << id << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::DelGenre(char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "delete from genres where name = '" << name << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

//получение всей таблицы

vector<Book*> Database::GetAllBooks()
{
    vector<Book*> *books = new vector<Book*>();
	int rc = 0;
	char* errMsg;
    rc = sqlite3_exec(db, "select b.name, b.id, b.rating, b.annotation, a.name, a.id from books as b join authors as a on b.author_id = a.id;", ProcessBookRow, books, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *books;
}

vector<Author*> Database::GetAllAuthors()
{
	vector<Author*> *authors = new vector<Author*>();
	int rc = 0;
	char* errMsg;
	rc = sqlite3_exec(db, "select * from authors as a order by a.id; ", ProcessAuthorsRow, authors, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
	return *authors;
}

vector<Publisher*> Database::GetAllPublishers()
{
    vector<Publisher*> *publishers = new vector<Publisher*>();
	int rc = 0;
	char* errMsg;
    rc = sqlite3_exec(db, "select * from publishers as p order by p.id, p.address;", ProcessPublishersRow, publishers, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *publishers;
}

vector<Genre*> Database::GetAllGenres()
{
    vector<Genre*> *genres = new vector<Genre*>();//  создаетс€ вектор из элементов типа Genre*
    int rc = 0;
    char* errMsg;
    rc = sqlite3_exec(db, "select * from genres as g order by g.id, g.name;", ProcessGenresRow, genres, &errMsg); //передаетс€ запрос в базу данных
    if (rc != SQLITE_OK) {
        cout << errMsg << endl; //в случае ошибки возвращаетс€ ошибка
        sqlite3_free(errMsg);
    }
    return *genres; //возвращаетс€ вектор жанров
}


//получить один элемент

Book* Database::GetOneBook(int id)
{
    Book *book = new Book();
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "select b.name, b.id, b.status_book, b.annotation, a.name, a.id, p.id, p.name, p.address, b.rating from books as b join authors as a on b.author_id = a.id join publishers as p on p.id = b.publisher_id where b.id = " << id << ";";

    rc = sqlite3_exec(db, ss.str().c_str(), ProcessOneBook, book, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return book;
}

Author* Database::GetOneAuthor(int id)
{
	Author *author = new Author();
	int rc = 0;
	char* errMsg;
	stringstream ss;
	ss << "select a.id, a.name from authors as a where a.id = " << id << "; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessOneAuthor, author, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
	return author;
}

Publisher* Database::GetOnePublisher(int id)
{
    Publisher *publisher = new Publisher();
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "select p.id, p.name from publishers as p where p.id = " << id << "; ";

    rc = sqlite3_exec(db, ss.str().c_str(), ProcessOnePublisher, publisher, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return publisher;
}

Genre* Database::GetOneGenre(int id)
{
    Genre *genre = new Genre();
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "select p.id, p.name from genres as p where p.id = " << id << "; ";

    rc = sqlite3_exec(db, ss.str().c_str(), ProcessOneGenre, genre, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return genre;
}

//изменение элементов

void Database::ChangeAuthor(int id, char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
	ss << "update authors  set name = '" << name << "' where id = '" << id << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::ChangePublisher(int id, char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "update publishers  set name = '" << name << "' where id = '" << id << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::ChangeGenre(int id, char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "update genres  set name = '" << name << "' where id = '" << id << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::ChangeBookName(int id, char* name)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "update books  set name = '" << name << "' where id = '" << id << "'; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

void Database::ChangeBookStatus(int id, bool status)
{
	int rc = 0;
	char* errMsg;
	stringstream ss;
    ss << "update books  set status_book = " << status << " where id = " << id << "; ";

	rc = sqlite3_exec(db, ss.str().c_str(), ProcessEmpty, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

//получение книги по критерию

vector<Book*> Database::GetBooksOfAuthor(QString name)
{
    vector<Book*> *books = new vector<Book*>();
	int rc = 0;
	char* errMsg;
    QString query = QString("select b.id, b.name from books as b join authors as a on a.id = b.author_id where upper(a.name) like upper ('%").append(name).append("%') order by b.name; ");
    rc = sqlite3_exec(db,qPrintable(query), ProcessAuthorBooksRow, books, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *books;
}

vector<Book*> Database::GetBooksOfPublisher(QString name)
{
    vector<Book*> *books = new vector<Book*>();
	int rc = 0;
    char* errMsg;
    QString query = QString("select b.id, b.name from books as b join publishers as p on p.id = b.publisher_id where upper(p.name) like upper ('%").append(name).append("%') order by b.name;");
    rc = sqlite3_exec(db,qPrintable(query), ProcessPublisherBooksRow, books, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *books;
}

vector<Book*> Database::GetBooksOfGenre(QString name)
{
    vector<Book*> *books = new vector<Book*>();
	int rc = 0;
	char* errMsg;
    QString query = QString("select b.id, b.name from books as b join book_genres as bg on b.id = bg.book_id join genres as g on g.id = bg.genre_id where upper(g.name) like upper ('%").append(name).append("%') order by g.name;");
    rc = sqlite3_exec(db,qPrintable(query), ProcessPublisherBooksRow, books, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *books;
}

vector<Book*> Database::GetBooksOfName(QString name)
{
    vector<Book*> *books = new vector<Book*>();
	int rc = 0;
	char* errMsg;
    QString query = QString("select b.id, b.name from books as b where upper(b.name) like upper('%").append(name).append("%') order by b.name; ");
    rc = sqlite3_exec(db,qPrintable(query), ProcessNameBooksRow, books, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *books;
}

vector<Book*> Database::GetBooksOfStatus(bool status)
{
    vector<Book*> *books = new vector<Book*>();
	int rc = 0;
	char* errMsg;
    QString query = QString ("select b.id, b.name from books as b where b.status_book = ").append(QString::number(status)).append(" order by b.name; ");
    rc = sqlite3_exec(db, qPrintable(query), ProcessStatusBooksRow, books, &errMsg);
	if (rc != SQLITE_OK) {
		cout << errMsg << endl;
		sqlite3_free(errMsg);
	}
    return *books;
}

vector<Genre*>* Database::GetGenresOfBook(int id)
{
    vector<Genre*>* genres = new vector<Genre*>();
    int rc = 0;
    char* errMsg;
    stringstream ss;
    ss << "select g.name from genres as g join book_genres as bg on bg.genre_id = g.id where bg.book_id ="<< id <<" order by g.name; ";
    rc = sqlite3_exec(db, ss.str().c_str(), ProcessGenresOfBooksRow, genres, &errMsg);
    if (rc != SQLITE_OK) {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return genres;
}




int Database::ProcessBookRow (void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Book*>* v = (vector<Book*>*) notUsed;

    Book* b = new Book(atoi(colData[1]), colData[0], atoi(colData[2]), colData[3]);

    Author* a = new Author(atoi(colData[5]), colData[4]);

    b->SetAuthor(a);

    v->push_back(b);

    return 0;
}

int Database::ProcessOneBook (void* notUsed, int colCount, char** colData, char** colNames)
{
    Book* b = (Book*) notUsed;

    b->SetId(atoi(colData[1]));
    b->SetName(colData[0]);
    b->SetAnnotation(colData[3]);
    b->SetStatus(atoi(colData[2]));
    b->SetRating(atoi(colData[9]));

    Author* a = new Author(atoi(colData[5]), colData[4]);
    Publisher* p = new Publisher(atoi (colData[6]), colData[7], colData[8]);

    b->SetAuthor(a);
    b->SetPublisher(p);

    return 0;
}

int Database::ProcessAuthorsRow(void* notUsed, int colCount, char** colData, char** colNames) {
	vector<Author*>* a = (vector<Author*>*) notUsed;

	Author* au = new Author(atoi(colData[0]), colData[1]);

	a->push_back(au);

	return 0;
}

int Database::ProcessOneAuthor(void* notUsed, int colCount, char** colData, char** colNames)
{
	Author* a = (Author*)notUsed;

	a->SetId(atoi(colData[0]));
	a->SetName(colData[1]);

	return 0;
}

int Database::ProcessPublishersRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Publisher*>* p = (vector<Publisher*>*) notUsed;


    Publisher* publ = new Publisher(atoi(colData[0]), colData[1], colData[2]);

	p->push_back(publ);

    return 0;
}

int Database::ProcessOnePublisher(void* notUsed, int colCount, char** colData, char** colNames)
{
    Publisher* a = (Publisher*)notUsed;

	a->SetId(atoi(colData[0]));
	a->SetName(colData[1]);

	return 0;
}

int Database::ProcessGenresRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Genre*>* g = (vector<Genre*>*) notUsed; //создаетс€ вектор эелементов типа Genre*

    Genre* gnr = new Genre(atoi(colData[0]), colData[1]); //в каждый элемент типа Genre* заноситс€ id  и название жанра

    g->push_back(gnr); // элемент заноситс€ в вектор

	return 0;
}

int Database::ProcessOneGenre(void* notUsed, int colCount, char** colData, char** colNames)
{
    Genre* a = (Genre*)notUsed;

	a->SetId(atoi(colData[0]));
	a->SetName(colData[1]);

	return 0;
}

int Database::ProcessAuthorBooksRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Book*>* b = (vector<Book*>*) notUsed;


    Book* book = new Book ();
    book->SetId(atoi(colData[0]));
    book->SetName(colData[1]);

    b->push_back(book);

	return 0;
}

int Database::ProcessPublisherBooksRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Book*>* b = (vector<Book*>*) notUsed;

    Book* book = new Book();
    book->SetId(atoi(colData[0]));
    book->SetName(colData[1]);

    b->push_back(book);

	return 0;
}

int Database::ProcessGenresBooksRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Book*>* b = (vector<Book*>*) notUsed;

    Book* book = new Book();
    book->SetId(atoi(colData[0]));
    book->SetName(colData[1]);

    b->push_back(book);

	return 0;
}

int Database::ProcessStatusBooksRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Book*>* b = (vector<Book*>*) notUsed;

    Book* book = new Book();
    book->SetId(atoi(colData[0]));
    book->SetName(colData[1]);

    b->push_back(book);

	return 0;
}

int Database::ProcessNameBooksRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Book*>* b = (vector<Book*>*) notUsed;

    Book* book = new Book();
    book->SetId(atoi(colData[0]));
    book->SetName(colData[1]);

    b->push_back(book);

	return 0;
}

int Database::ProcessGenresOfBooksRow(void* notUsed, int colCount, char** colData, char** colNames) {
    vector<Genre*>* b = (vector<Genre*>*) notUsed;

    Genre* genre = new Genre();
    genre->SetName(colData[0]);

    b->push_back(genre);

    return 0;
}


int Database::ProcessEmpty(void* notUsed, int colCount, char** colData, char** colNames)
{
	return 0;
}

int Database::ProcessInt(void* notUsed, int colCount, char** colData, char** colNames)
{
	int* id = (int*) notUsed;
	*id = atoi(colData[0]);
	return 0;
}



