#include <iostream>
#include "Object.h"

using namespace std;

Object :: Object()
{
    id = 0;
    name = 0;
}

Object :: Object(int id, char* name)
{
    this->id = id;
    this->name = new char[strlen(name) + 1];
    memcpy(this->name, name, strlen(name) + 1);
}

Object :: Object(Object& other)
{
    id = other.id;
    name = new char[sizeof(other.name)];
    memcpy(name, other.name, strlen(other.name) + 1);
}

Object :: ~Object()
{
    if (name)
        delete name;
}

int Object :: GetId()
{
    return id;
}

char* Object :: GetName()
{
    return name;
}

void Object :: SetId(int id)         
{
    this->id = id;
}

void Object :: SetName(char* name)
{
    this->name = new char[strlen(name) + 1];
    memcpy(this->name, name, strlen(name) + 1);
}

ostream& operator <<(ostream& out, Object& o)
{
    out << o.GetId() << endl;
    out << o.GetName() << endl;
    return out;
}
