#include <bits/stdc++.h>
using namespace std;

queue<int> buffer;
const int MAXSIZE = 5;
pthread_mutex_t Mutexx = PTHREAD_MUTEX_INITIALIZER; // Renamed mutex
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

void *producers(void *arg)
{
    int id = *((int *)arg);

    while (true)
    {
        pthread_mutex_lock(&Mutexx);

        // check buffer_not_empty

        while (buffer.size() == MAXSIZE)
        {
            pthread_cond_wait(&buffer_not_full, &Mutexx);
        }

        int items = rand() % 100;
        buffer.push(items);
        cout << "producer " << id << "pushed item " << items << endl;

        pthread_cond_signal(&buffer_not_empty);

        pthread_mutex_unlock(&Mutexx);
    }
    pthread_exit(0);
}

void *consumers(void *arg)
{
    int id = *((int *)arg);

    while (true)
    {
        pthread_mutex_lock(&Mutexx);

        // check buffer is not full
        while (buffer.empty())
        {
            pthread_cond_wait(&buffer_not_empty, &Mutexx);
        }

        int items = buffer.front();
        buffer.pop();
        cout << "consumer " << id << "consumed item " << items << endl;

        pthread_cond_signal(&buffer_not_full);

        pthread_mutex_unlock(&Mutexx);
    }
    pthread_exit(0);
}

int main()
{
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

    return 0;
}