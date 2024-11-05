#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h> // For Sleep function on Windows

using namespace std;

// Simulated network search request (randomly fails or succeeds)
bool simulatedSearchRequest()
{
    // 30% chance of success
    return rand() % 10 < 3;
}

// Function to perform a search with exponential backoff retry mechanism
bool exponentialBackoffSearch(int maxRetries, int initialWaitTime)
{
    int retries = 0;
    int waitTime = initialWaitTime; // in milliseconds

    while (retries < maxRetries)
    {
        cout << "Attempt " << retries + 1 << " of search..." << endl;

        if (simulatedSearchRequest())
        {
            cout << "Search successful!" << endl;
            return true;
        }

        // If the search fails, increase the wait time and retry
        cout << "Search failed. Retrying in " << waitTime << " ms..." << endl;
        Sleep(waitTime); // Use Windows Sleep function

        // Exponential backoff: double the wait time
        waitTime *= 2;
        retries++;
    }

    cout << "Search failed after " << maxRetries << " retries." << endl;
    return false;
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework_Lap3_Part3\n";
    cout << "\n";
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    int maxRetries, initialWaitTime;
    cout << "Enter the maximum number of retries: ";
    cin >> maxRetries;
    cout << "Enter the initial wait time in milliseconds: ";
    cin >> initialWaitTime;

    bool result = exponentialBackoffSearch(maxRetries, initialWaitTime);

    if (!result)
    {
        cout << "The search operation could not be completed successfully." << endl;
    }
    system("pause");
    return 0;
}