#include <bits/stdc++.h>
#include <semaphore.h>

using namespace std;

#define NUM_PHILOSOPHERS 5

// Semaphore array to represent chopsticks
sem_t chopsticks[NUM_PHILOSOPHERS];

// Function for each philosopher's behavior
void *philosopher(void *num)
{
    int id = *((int *)num);

    while (true)
    {
        // Thinking phase
        cout << "Philosopher " << id << " is thinking." << endl;
        sleep(1); // Simulate thinking

        // Trying to pick up chopsticks
        int left = id;
        int right = (id + 1) % NUM_PHILOSOPHERS;

        // To avoid deadlock, pick up the lower-numbered chopstick first
        if (id % 2 == 0)
        {
            sem_wait(&chopsticks[left]);  // Pick up left chopstick
            sem_wait(&chopsticks[right]); // Pick up right chopstick
        }
        else
        {
            sem_wait(&chopsticks[right]); // Pick up right chopstick
            sem_wait(&chopsticks[left]);  // Pick up left chopstick
        }

        // Eating phase
        cout << "Philosopher " << id << " is eating." << endl;
        sleep(2); // Simulate eating

        // Putting down chopsticks
        sem_post(&chopsticks[left]);  // Put down left chopstick
        sem_post(&chopsticks[right]); // Put down right chopstick

        cout << "Philosopher " << id << " finished eating and put down chopsticks." << endl;

        // Back to thinking
    }

    pthread_exit(0);
}

int main()
{
    // Initialize semaphores for each chopstick
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create philosopher threads
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], nullptr, philosopher, (void *)&philosopher_ids[i]);
    }

    // Wait for all philosopher threads to complete (they run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], nullptr);
    }

    // Clean up semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}