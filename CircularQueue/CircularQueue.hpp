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
        : _v(DefaultQueueSize),
          _capacity(DefaultQueueSize),
          _consumerStep(0),
          _producerStep(0)
    {
        sem_init(&_dataSpace, 0, DefaultQueueSize);
        sem_init(&_dataNums, 0, 0);
    }
    void ProductGoods(int data)
    {
        sem_wait(&_dataSpace);
        _v[_producerStep] = data;
        _producerStep++;
        _producerStep %= _capacity;
        sem_post(&_dataNums);
    }
    int ConsumeGoods()
    {
        sem_wait(&_dataNums);
        int data = _v[_consumerStep];
        _consumerStep++;
        _consumerStep %= _capacity;
        sem_post(&_dataSpace);
        return data;
    }
    ~CircularQueue()
    {
        sem_destroy(&_dataSpace);
        sem_destroy(&_dataNums);
    }

private:
    std::vector<int> _v;
    int _capacity;
    int _consumerStep;
    int _producerStep;
    sem_t _dataSpace;
    sem_t _dataNums;
};