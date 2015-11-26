#ifndef Object_H
#define Object_H

class Object
{

protected:
    int id;
    char* name;

public:

    Object();

    Object(int id, char* name);

    Object(Object& other);
    
    ~Object();

    int GetId();

    char* GetName();

    void SetId(int id);

    void SetName(char* name);

};

#endif
