#include <iostream>
#include "Publisher.h"
#include "Object.h"

using namespace std;

Publisher::Publisher() : Object()
{
    address = 0;
}

Publisher::Publisher(int id, char* name, char* add) : Object(id, name)
{
    this->address = new char[strlen (add)+1];
    memcpy(this->address, add, strlen(add) + 1);
}

Publisher:: Publisher(Publisher& other) : Object(other)
{

}

void Publisher::SetAddress(char* addr)
{
    this->address = new char[strlen(addr) + 1];
    memcpy(this->address, addr, strlen(addr) + 1);
}
