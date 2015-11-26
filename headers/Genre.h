#ifndef GENRE_H
#define GENRE_H
#include "Object.h"

class Genre : public Object
{

public:

    Genre();

    Genre(int id, char* name);

    Genre(Genre& other);
    
    ~Genre();
};

#endif
