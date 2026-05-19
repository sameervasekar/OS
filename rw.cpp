#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstdlib>
using namespace std;


int readCount = 0;
int sharedData = 0;

// Mutex
mutex mtx;   
mutex wrt;   

// Reader function
void reader(int id) {
    // Entry section
    mtx.lock();
    readCount++;
    if (readCount == 1) {
        wrt.lock(); // first reader blocks writers
    }
    mtx.unlock();

    // Critical section
    cout << "Reader " << id << " is reading data = " << sharedData << endl;

    // Exit section
    mtx.lock();
    readCount--;
    if (readCount == 0) {
        wrt.unlock(); // last reader allows writers
    }
    mtx.unlock();
}

// Writer function
void writer(int id) {
    wrt.lock(); // exclusive access

    sharedData++;
    cout << "Writer " << id << " is writing data = " << sharedData << endl;

    wrt.unlock();
}

int main() {
    int r, w;

    cout << "Enter number of readers: ";
    cin >> r;

    cout << "Enter number of writers: ";
    cin >> w;

    vector<thread> readers;
    vector<thread> writers;

    // Create reader threads
    for (int i = 0; i < r; i++) {
        readers.emplace_back(reader, i + 1);
    }

    // Create writer threads
    for (int i = 0; i < w; i++) {
        writers.emplace_back(writer, i + 1);
    }

    // Join threads
    for (auto &t : readers) t.join();
    for (auto &t : writers) t.join();

    // 🔴 Keep terminal open
    cout << "\nProgram finished. Press ENTER to exit...";
    cin.ignore();
    cin.get();
system("pause");
    return 0;
}