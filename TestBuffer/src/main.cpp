#include "Buffer.h"
#include <iostream>

int main()
{
buffer::Buffer* testbuffer = new buffer::Buffer();
testbuffer->initBuffer("test6.txt");
int i = 0;
char blubberdiblub;
while(i<204800){
testbuffer->getChar(blubberdiblub);
std::cout << blubberdiblub;
i++;
}
return 0;
}
