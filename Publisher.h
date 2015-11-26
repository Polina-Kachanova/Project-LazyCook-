#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "Object.h"


class Publisher : public Object
{
    char* address;

public:

    Publisher();

    Publisher(int id, char* name, char* address);

    Publisher(Publisher& other);
    
    ~Publisher();

    void SetAddress(char*);
};

#endif
