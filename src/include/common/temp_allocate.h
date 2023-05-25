#ifndef _TEMP_ALLOCATER_
#define _TEMP_ALLOCATER_
class TempIdAllocater
{
private:
    static int counter;

public:
    static int GetId();
    static void Rewind();
    static void Increase();
};

#endif