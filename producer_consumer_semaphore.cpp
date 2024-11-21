#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

queue<int> buffer;
const int SIZE = 5;
sem_t emptyy;
sem_t full;
sem_t mutexx;

void *producers(void *arg)
{
    int id = *((int *)arg);
    while (true)
    {
        int items = rand() % 100;
        sem_wait(&emptyy);
        sem_wait(&mutexx);

        buffer.push(items);
        cout << "producer " << id << "pushed item " << items << endl;

        sem_post(&mutexx);
        sem_post(&full);
    }

    pthread_exit(0);
}

void *consumers(void *arg)
{
    int id = *((int *)arg);
    while (true)
    {

        sem_wait(&full);
        sem_wait(&mutexx);

        int items = buffer.front();
        cout << "consumer " << id << "consumed item " << items << endl;

        sem_post(&mutexx);
        sem_post(&emptyy);
    }

    pthread_exit(0);
}

int main()
{
    sem_init(&emptyy, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutexx, 0, 1);
    int pro;
    cin >> pro;
    int com;
    cin >> com;

    pthread_t producer[pro], consumer[com];
    int producerid[pro], consumerid[com];

    for (int i = 0; i < pro; i++)
    {
        producerid[i] = i + 1;
        pthread_create(&producer[i], nullptr, producers, (void *)&producerid[i]);
    }
    for (int i = 0; i < com; i++)
    {
        consumerid[i] = i + 1;
        pthread_create(&consumer[i], nullptr, consumers, (void *)&consumerid[i]);
    }

    for (int i = 0; i < pro; i++)
    {
        pthread_join(producer[i], nullptr); // Corrected this line
    }
    for (int i = 0; i < com; i++)
    {
        pthread_join(consumer[i], nullptr); // Corrected this line
    }

    sem_destroy(&emptyy);
    sem_destroy(&full);
    sem_destroy(&mutexx);

    return 0;
}