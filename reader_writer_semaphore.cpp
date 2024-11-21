#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

int readcount = 0;
sem_t mutexx;
sem_t write_lock;

int shar = 0;

void *readers(void *arg)
{
    int id = *((int *)arg);

    sem_wait(&mutexx);
    readcount++;
    if (readcount == 1)
    {
        sem_wait(&write_lock);
    }
    sem_post(&mutexx);

    cout << "reader " << id << " is reading the resources " << shar << endl;

    sem_wait(&mutexx);
    readcount--;
    if (readcount == 0)
    {
        sem_post(&write_lock);
    }
    sem_post(&mutexx);

    pthread_exit(0);
}

void *writerss(void *arg)
{
    int id = *((int *)arg);

    // Writer enters
    sem_wait(&write_lock);
    shar += 10;
    cout << "writer " << id << " is writing the resources " << shar << endl;
    sem_post(&write_lock);
    pthread_exit(0);
}

int main()
{

    sem_init(&mutexx, 0, 1);
    sem_init(&write_lock, 0, 1);
    int read;
    cin >> read;
    int write;
    cin >> write;

    pthread_t reader[read], writer[write];
    int readerid[read], writerid[write];

    for (int i = 0; i < read; i++)
    {
        readerid[i] = i + 1;
        pthread_create(&reader[i], nullptr, readers, (void *)&readerid[i]);
    }
    for (int i = 0; i < write; i++)
    {
        writerid[i] = i + 1;
        pthread_create(&writer[i], nullptr, writerss, (void *)&writerid[i]);
    }

    for (int i = 0; i < read; i++)
    {
        pthread_join(reader[i], nullptr); // Corrected this line
    }
    for (int i = 0; i < write; i++)
    {
        pthread_join(writer[i], nullptr); // Corrected this line
    }

    sem_destroy(&mutexx);
    sem_destroy(&write_lock);

    return 0;
}
