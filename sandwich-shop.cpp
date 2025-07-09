#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

sem_t bread_cheese, bread_ham, cheese_ham, empty_table;

void* vendor(void* arg) {
    while (true) {
        int x, y;
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (x == y);

        sem_wait(&empty_table);
        if (x == 0 && y == 1) {
            cout << "Vendor puts bread and cheese on the table." << endl;
            sem_post(&bread_cheese);
        }
        else if (x == 0 && y == 2) {
            cout << "Vendor puts bread and ham on the table." << endl;
            sem_post(&bread_ham);
        }
        else {
            cout << "Vendor puts cheese and ham on the table." << endl;
            sem_post(&cheese_ham);
        }
        sleep(1);
    }
}

void* customerCheeseAndHam(void* arg) {
    while (true) {
        sem_wait(&cheese_ham);
        cout << "Customer takes cheese and ham, leaves the store, assembles and eats the sandwich." << endl << endl;
        sem_post(&empty_table);
    }
}

void* customerBreadAndHam(void* arg) {
    while (true) {
        sem_wait(&bread_ham);
        cout << "Customer takes bread and ham, leaves the store, assembles and eats the sandwich." << endl << endl;
        sem_post(&empty_table);
    }
}

void* customerBreadAndCheese(void* arg) {
    while (true) {
        sem_wait(&bread_cheese);
        cout << "Customer takes bread and cheese, leaves the store, assembles and eats the sandwich." << endl << endl;
        sem_post(&empty_table);
    }
}

int main() {
    srand(time(0));

    sem_init(&bread_cheese, 0, 0);      
    sem_init(&bread_ham, 0, 0);
    sem_init(&cheese_ham, 0, 0);
    sem_init(&empty_table, 0, 1);

    pthread_t vendor_thread;
    pthread_create(&vendor_thread, NULL, vendor, NULL);

    pthread_t customers[3];
    pthread_create(&customers[0], NULL, customerCheeseAndHam, NULL);
    pthread_create(&customers[1], NULL, customerBreadAndCheese, NULL);
    pthread_create(&customers[2], NULL, customerBreadAndHam, NULL);

    pthread_join(vendor_thread, NULL);
    pthread_join(customers[0], NULL);
    pthread_join(customers[1], NULL);
    pthread_join(customers[2], NULL);

    sem_destroy(&cheese_ham);
    sem_destroy(&bread_cheese);
    sem_destroy(&bread_ham);
    sem_destroy(&empty_table);

    return 0;
}
