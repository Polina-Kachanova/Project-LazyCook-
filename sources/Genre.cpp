#include <iostream>
#include "Genre.h"
#include "Object.h"

using namespace std;

Genre::Genre() : Object()
{

}

Genre::Genre(int id, char* name) : Object(id, name)
{

}

Genre:: Genre(Genre& other) : Object(other)
{

}
