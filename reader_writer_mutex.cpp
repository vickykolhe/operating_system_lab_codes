#include <bits/stdc++.h>
using namespace std;

int readcount = 0;
pthread_mutex_t pthreadMutex = PTHREAD_MUTEX_INITIALIZER;      // Renamed mutex
pthread_mutex_t pthreadWriteMutex = PTHREAD_MUTEX_INITIALIZER; // Renamed writeMutex

int shar = 0;

void *readers(void *arg)
{
    int id = *((int *)arg);
    // Readers
    pthread_mutex_lock(&pthreadMutex);
    readcount++;
    if (readcount == 1)
    {
        pthread_mutex_lock(&pthreadWriteMutex);
    }
    pthread_mutex_unlock(&pthreadMutex);

    cout << "reader " << id << " is reading the resources " << shar << endl;

    // All readers finish reading
    pthread_mutex_lock(&pthreadMutex);
    readcount--;
    if (readcount == 0)
    {
        pthread_mutex_unlock(&pthreadWriteMutex);
    }
    pthread_mutex_unlock(&pthreadMutex);
    pthread_exit(0);
}

void *writerss(void *arg)
{
    int id = *((int *)arg);

    // Writer enters
    pthread_mutex_lock(&pthreadWriteMutex);
    shar += 10;
    cout << "writer " << id << " is writing the resources " << shar << endl;
    pthread_mutex_unlock(&pthreadWriteMutex);
    pthread_exit(0);
}

int main()
{
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

    return 0;
}