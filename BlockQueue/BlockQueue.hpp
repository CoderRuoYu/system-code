#include <iostream>
#include <queue>
#include <pthread.h>
using std::cout;
using std::endl;
#define DefaultQueueSize 8
class BlockQueue
{
public:
    BlockQueue()
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_not_empty, nullptr);
        pthread_cond_init(&_not_full, nullptr);
    }
    void ProductData(int data)
    {
        pthread_mutex_lock(&_mutex);
        while (_size == _capacity)
        {
            pthread_cond_wait(&_not_full, &_mutex);
        }
        _size++;
        _q.push(data);
        pthread_cond_signal(&_not_empty);
        pthread_mutex_unlock(&_mutex);
    }
    int ConsumeData()
    {
        pthread_mutex_lock(&_mutex);
        while (_size == 0)
        {
            pthread_cond_wait(&_not_empty, &_mutex);
        }
        _size--;
        int res = _q.front();
        _q.pop();
        pthread_cond_signal(&_not_full);
        pthread_mutex_unlock(&_mutex);
        return res;
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_not_full);
        pthread_cond_destroy(&_not_empty);
    }

private:
    std::queue<int> _q;
    int _size = 0;
    int _capacity = DefaultQueueSize;
    pthread_mutex_t _mutex;
    pthread_cond_t _not_full;
    pthread_cond_t _not_empty;
};