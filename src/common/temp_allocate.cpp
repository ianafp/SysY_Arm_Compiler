#include"common/temp_allocate.h"
int TempIdAllocater::counter = 1;
int TempIdAllocater:: GetId() { return counter++; }
void TempIdAllocater:: Rewind(){ counter=1;}