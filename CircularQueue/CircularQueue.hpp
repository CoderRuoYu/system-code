#include <iostream>
#include <vector>
#include <semaphore.h>


using std::cout;
using std::endl;
#define DefaultQueueSize 8

class CircularQueue
{
public:
    CircularQueue()
    {


    }
    ~CircularQueue()
    {

    }

private:
    std::vector<int> _v;

};