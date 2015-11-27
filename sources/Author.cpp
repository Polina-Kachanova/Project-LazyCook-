#include <iostream>
#include "Author.h"
#include "Object.h"

using namespace std;

Author::Author() : Object()
{

}

Author::Author(int id, char* name) : Object(id, name)
{

}

Author:: Author(Author& other) : Object(other)
{

}
