#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <QString>
#include "Book.h"
#include "sqlite3.h"

using namespace std;

class Database 
{
    sqlite3* db;
    static Database* instance;

    Database();

    static int ProcessBookRow (void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessOneBook (void* notUsed, int colCount, char** colData, char** colNames);

	static int ProcessAuthorsRow(void* notUsed, int colCount, char** colData, char** colNames);

	static int ProcessOneAuthor(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessPublishersRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessOnePublisher(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessAuthorBooksRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessPublisherBooksRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessGenresRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessOneGenre(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessGenresBooksRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessStatusBooksRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessNameBooksRow(void* notUsed, int colCount, char** colData, char** colNames);

    static int ProcessGenresOfBooksRow(void* notUsed, int colCount, char** colData, char** colNames);

	static int ProcessEmpty(void* notUsed, int colCount, char** colData, char** colNames);

	static int ProcessInt(void* notUsed, int colCount, char** colData, char** colNames);


public:
    static Database* getInstance();

    ~Database();

    vector<Book*> GetAllBooks();
    Book * GetOneBook(int id);
	vector<Author*> GetAllAuthors();
	Author* GetOneAuthor(int id);
    vector<Publisher*> GetAllPublishers();
    vector<Book*> GetBooksOfAuthor(QString name);
    vector<Genre*> GetAllGenres();
    Publisher* GetOnePublisher(int id);
    Genre* GetOneGenre(int id);
    vector<Book*> GetBooksOfPublisher(QString name);
    vector<Book*> GetBooksOfGenre(QString name);
    vector<Book*> GetBooksOfStatus(bool status);
    vector<Book*> GetBooksOfName(QString name);
    vector<Genre*>* GetGenresOfBook(int id);

    int AddAuthor(QString name);
    int AddPublisher(QString name, QString address);
    int AddBook(QString name, int author_id, int Publisher_id, int rating, QString annotation, bool status_Book);
    int AddGenre(QString name);
    void AddBookGenre(int BookId, int genreId);
	void DelAuthor(char* name);
    void DelBook(int id);
    void DelPublisher(char* name);
    void DelGenre(char* name);
	void ChangeAuthor(int id, char* name);
    void ChangePublisher(int id, char* name);
    void ChangeGenre(int id, char* name);
    void ChangeBookName(int id, char* name);
    void ChangeBookStatus(int id, bool status);
};

#endif
