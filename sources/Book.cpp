#include <iostream>
#include "Book.h"
#include "Object.h"
#include "Author.h"
#include "Publisher.h"
#include "Genre.h"

using namespace std;

Book:: Book () : Object()
{
    rating = 0;
    annotation = 0;
    status_book = 0;
}

Book::Book(int id, char* name, int num, char* ann, bool status): Object(id, name)
{
    this->rating = num;
    this->annotation = new char[strlen (ann)+1];
    memcpy(this->annotation, ann, strlen(ann) + 1);
    this->status_book = status;
}

Book:: Book (Book& other) : Object(other)
{
    rating = other.rating;
    annotation = new char[strlen (other.annotation)+1];
    memcpy(annotation, other.annotation, strlen(other.annotation) + 1);
}

int Book:: GetRating()
{
    return rating;
}

char* Book :: GetAnnotation()
{
    return annotation;
}

bool Book:: GetStatus()
{
    return status_book;
}

Author* Book :: GetAuthor()
{
    return author;
}

Publisher* Book :: GetPublisher()
{
    return publisher;
}

Genre* Book :: GetGenre()
{
    return genre;
}

const char* Book :: GetStatusString()
{
    if(this->GetStatus() == 0)
        return "Not Cooked";
    return "Cooked";

}

void Book:: SetRating(int rating)
{
    this->rating = rating;
}

void Book :: SetAnnotation(char* ann)
{
    this->annotation = new char[strlen(ann) + 1];
    memcpy(this->annotation, ann, strlen(ann) + 1);
}

void Book :: SetStatus(bool status)
{
    this->status_book = status;
}

void Book :: SetAuthor(Author* author)
{
    this->author = author;
}

void Book :: SetPublisher(Publisher* publisher)
{
    this->publisher = publisher;
}

void Book :: SetGenre(Genre* genre)
{
    this->genre = genre;
}

 ostream & operator << (ostream& out, Book* b)
 {
    out << b->GetId() <<"  " << b->GetName() << "  " << b->GetAnnotation() << "  " << b->GetRating() << "  " << b->GetStatus() << endl;
    return out;
 }
