#ifndef BOOK_H
#define BOOK_H
#include "Object.h"
#include "Author.h"
#include "Genre.h"
#include "Publisher.h"

class Book : public Object
{
    int rating;
    char* annotation;
    bool status_book;
    Author* author;
    Publisher* publisher;
    Genre* genre;

public:

    Book ();

    Book(int id, char* name, int num, char* ann, bool status = 0);

    Book (Book& other);

    int GetRating();

    char* GetAnnotation();

    bool GetStatus();

    Author* GetAuthor ();

    Publisher* GetPublisher();

    Genre* GetGenre();

    const char* GetStatusString();

    void SetRating(int rating);

    void SetAnnotation(char* ann);

    void SetStatus(bool status);

    void SetAuthor(Author* author);

    void SetPublisher(Publisher* publisher);

    void SetGenre(Genre* genre);
};

#endif
