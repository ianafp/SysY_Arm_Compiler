#include"common/temp_allocate.h"
int TempIdAllocater::counter = 0;
int TempIdAllocater:: GetId() { return counter++; }
void TempIdAllocater:: Rewind(){ counter=0;}
void TempIdAllocater::Increase(){counter++;}