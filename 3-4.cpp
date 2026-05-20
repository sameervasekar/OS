#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

int readCount = 0;
mutex mtx;      // Protects readCount
mutex wrt;      // Controls writer access

// 🔵 Reader Function
void reader(int id)
{
    // Entry Section
    mtx.lock();
    readCount++;

    if (readCount == 1)
        wrt.lock();   // First reader blocks writers

    mtx.unlock();

    // Critical Section
    cout << "Reader " << id << " is READING\n";

    // Exit Section
    mtx.lock();
    readCount--;

    if (readCount == 0)
        wrt.unlock(); // Last reader allows writer

    mtx.unlock();
}

// 🔴 Writer Function
void writer(int id)
{
    wrt.lock();   // Only one writer allowed

    cout << "Writer " << id << " is WRITING\n";

    wrt.unlock();
}

int main()
{
    int n;

    cout << "Enter number of readers/writers: ";
    cin >> n;

    vector<thread> readersList, writersList;

    // Create Reader Threads
    for (int i = 0; i < n; i++)
        readersList.push_back(thread(reader, i+1));

    // Create Writer Threads
    for (int i = 0; i < n; i++)
        writersList.push_back(thread(writer, i+1));

    // Join Readers
    for (int i = 0; i < n; i++)
        readersList[i].join();

    // Join Writers
    for (int i = 0; i < n; i++)
        writersList[i].join();

    return 0;
}
