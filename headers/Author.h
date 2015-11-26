#ifndef AUTHOR_H
#define AUTHOR_H
#include "Object.h"


class Author : public Object
{

public:

    Author();

    Author(int id, char* name);

    Author(Author& other);
    
    ~Author();
};

#endif
