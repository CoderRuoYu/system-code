#include "BlockQueue.hpp"
#include <pthread.h>
#include <unistd.h>
void *PdFunc(void *argv)
{
    int cn = 0;
    BlockQueue *bqp = (BlockQueue *)argv;
    while (true)
    {
        bqp->ProductData(cn);
        cout << "product:" << cn << endl;
        cn++;
        sleep(1);
    }
}
void *ConFunc(void *argv)
{
    BlockQueue *bqp = (BlockQueue *)argv;
    while (true)
    {
        int tmp = bqp->ConsumeData();
        cout << "consume:" << tmp << endl;
        sleep(1);
    }
}
int main()
{
    BlockQueue q;
    pthread_t Pd, Con;
    pthread_create(&Pd, nullptr, PdFunc, (void *)&q);
    pthread_create(&Con, nullptr, ConFunc, (void *)&q);

    pthread_join(Pd, nullptr);
    pthread_join(Con, nullptr);
    return 0;
}