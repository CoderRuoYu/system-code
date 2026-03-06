#include "CircularQueue.hpp"
#include <unistd.h>
#include <pthread.h>
void *Producer(void *arg)
{
    CircularQueue *cq = (CircularQueue *)arg;

    int data = 1;
    while (true)
    {
        cq->ProductGoods(data);
        cout << "Producer produce: " << data << endl;
        data++;

        sleep(1);
    }
}

void *Consumer(void *arg)
{
    CircularQueue *cq = (CircularQueue *)arg;

    while (true)
    {
        int data = cq->ConsumeGoods();
        cout << "Consumer consume: " << data << endl;

        sleep(2);
    }
}

int main()
{
    CircularQueue cq;

    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer, nullptr, Producer, &cq);
    pthread_create(&consumer, nullptr, Consumer, &cq);

    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    return 0;
}