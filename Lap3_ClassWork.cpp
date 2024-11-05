#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Linear Search with comparison count
void searchLinear(int numbers[], int length, int key, int &compareCount)
{
    for (int index = 0; index < length; index++)
    {
        compareCount++;
        if (numbers[index] == key)
        {
            cout << "Linear Search: Found at position " << index << "\n";
            return;
        }
    }
    cout << "Linear Search: Not found\n";
}

// Binary Search with comparison count
void searchBinary(int numbers[], int length, int key, int &compareCount)
{
    int start = 0, end = length - 1;
    while (start <= end)
    {
        compareCount++;
        int middle = start + (end - start) / 2;
        if (numbers[middle] == key)
        {
            cout << "Binary Search: Found at position " << middle << "\n";
            return;
        }
        else if (numbers[middle] < key)
        {
            start = middle + 1;
        }
        else
        {
            end = middle - 1;
        }
    }
    cout << "Binary Search: Not found\n";
}

// Binary Search for First and Last Occurrence
int findFirstOccurrence(int numbers[], int length, int key)
{
    int start = 0, end = length - 1, result = -1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (numbers[mid] == key)
        {
            result = mid;
            end = mid - 1;
        }
        else if (numbers[mid] < key)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return result;
}

int findLastOccurrence(int numbers[], int length, int key)
{
    int start = 0, end = length - 1, result = -1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (numbers[mid] == key)
        {
            result = mid;
            start = mid + 1;
        }
        else if (numbers[mid] < key)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return result;
}

int countTotalOccurrences(int numbers[], int length, int key)
{
    int first = findFirstOccurrence(numbers, length, key);
    if (first == -1)
        return 0;
    int last = findLastOccurrence(numbers, length, key);
    return last - first + 1;
}

// Jump Search
int executeJumpSearch(int numbers[], int length, int key)
{
    int step = sqrt(length);
    int previous = 0;
    while (numbers[min(step, length) - 1] < key)
    {
        previous = step;
        step += sqrt(length);
        if (previous >= length)
            return -1;
    }
    for (int i = previous; i < min(step, length); i++)
    {
        if (numbers[i] == key)
            return i;
    }
    return -1;
}

// Interpolation Search for Strings
int interpolationSearchStrings(string strings[], int length, const string &key)
{
    int start = 0, end = length - 1;
    while (start <= end && key >= strings[start] && key <= strings[end])
    {
        if (start == end)
            return (strings[start] == key) ? start : -1;
        int pos = start + (key.compare(strings[start]) * (end - start)) / (strings[end].compare(strings[start]));
        if (strings[pos] == key)
            return pos;
        if (strings[pos] < key)
            start = pos + 1;
        else
            end = pos - 1;
    }
    return -1;
}

// Find Missing Number Using Binary Search
int locateMissingNumber(int numbers[], int length)
{
    int start = 0, end = length - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (numbers[mid] == mid)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return start;
}

// Bidirectional Binary Search
int twoWayBinarySearch(int numbers[], int length, int key)
{
    int start = 0, end = length - 1;
    while (start <= end)
    {
        if (numbers[start] == key)
            return start;
        if (numbers[end] == key)
            return end;
        start++;
        end--;
    }
    return -1;
}

// Kth Smallest Element Using Quick Select
void exchange(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

int partitionNumbers(int numbers[], int start, int end)
{
    int pivot = numbers[end];
    int i = start;
    for (int j = start; j < end; j++)
    {
        if (numbers[j] <= pivot)
        {
            exchange(numbers[i], numbers[j]);
            i++;
        }
    }
    exchange(numbers[i], numbers[end]);
    return i;
}

int quickSelectKth(int numbers[], int start, int end, int k)
{
    if (start <= end)
    {
        int pivotIndex = partitionNumbers(numbers, start, end);
        if (pivotIndex == k)
            return numbers[pivotIndex];
        else if (pivotIndex < k)
            return quickSelectKth(numbers, pivotIndex + 1, end, k);
        else
            return quickSelectKth(numbers, start, pivotIndex - 1, k);
    }
    return -1;
}

int findKthElement(int numbers[], int length, int k)
{
    return quickSelectKth(numbers, 0, length - 1, k - 1);
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Exercise-Lap3\n";
    cout << "\n";
    int option;

    do
    {
        cout << "\nOptions:\n";
        cout << "1. Count Total Occurrences\n";
        cout << "2. Adaptive Step Jump Search\n";
        cout << "3. Interpolation Search for Strings\n";
        cout << "4. Locate Missing Number\n";
        cout << "5. Compare Linear and Binary Searches\n";
        cout << "6. Bidirectional Binary Search\n";
        cout << "7. Find Kth Smallest Element\n";
        cout << "8. Exit\n";
        cout << "Select an option: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            int length, key;
            cout << "Enter array length: ";
            cin >> length;
            int numbers[length];
            cout << "Enter " << length << " sorted numbers: ";
            for (int i = 0; i < length; i++)
                cin >> numbers[i];
            cout << "Enter number to count: ";
            cin >> key;
            int count = countTotalOccurrences(numbers, length, key);
            cout << "Occurrences of " << key << " is: " << count << "\n";
            break;
        }
        case 2:
        {
            int length, key;
            cout << "Enter array length: ";
            cin >> length;
            int numbers[length];
            cout << "Enter " << length << " sorted numbers: ";
            for (int i = 0; i < length; i++)
                cin >> numbers[i];
            cout << "Enter number to find using Jump Search: ";
            cin >> key;
            int index = executeJumpSearch(numbers, length, key);
            if (index != -1)
                cout << "Found at position: " << index << "\n";
            else
                cout << "Not found\n";
            break;
        }
        case 3:
        {
            int length;
            cout << "Enter the number of strings: ";
            cin >> length;
            string strings[length];
            cout << "Enter " << length << " lexicographically sorted strings: ";
            for (int i = 0; i < length; i++)
                cin >> strings[i];
            string key;
            cout << "Enter string to search: ";
            cin >> key;
            int index = interpolationSearchStrings(strings, length, key);
            if (index != -1)
                cout << "Found at position: " << index << "\n";
            else
                cout << "Not found\n";
            break;
        }
        case 4:
        {
            int length;
            cout << "Enter array length (excluding missing number): ";
            cin >> length;
            int numbers[length];
            cout << "Enter " << length << " sorted elements with one missing (0 to n): ";
            for (int i = 0; i < length; i++)
                cin >> numbers[i];
            int missing = locateMissingNumber(numbers, length);
            cout << "Missing number is: " << missing << "\n";
            break;
        }
        case 5:
        {
            int length, key;
            cout << "Enter array length: ";
            cin >> length;
            int numbers[length];
            cout << "Enter " << length << " sorted numbers: ";
            for (int i = 0; i < length; i++)
                cin >> numbers[i];
            cout << "Enter number to search: ";
            cin >> key;

            int linearCompare = 0, binaryCompare = 0;
            searchLinear(numbers, length, key, linearCompare);
            searchBinary(numbers, length, key, binaryCompare);

            cout << "Linear Search Comparisons: " << linearCompare << "\n";
            cout << "Binary Search Comparisons: " << binaryCompare << "\n";
            break;
        }
        case 6:
        {
            int length, key;
            cout << "Enter array length: ";
            cin >> length;
            int numbers[length];
            cout << "Enter " << length << " sorted numbers: ";
            for (int i = 0; i < length; i++)
                cin >> numbers[i];
            cout << "Enter number to find using Bidirectional Binary Search: ";
            cin >> key;
            int index = twoWayBinarySearch(numbers, length, key);
            if (index != -1)
                cout << "Found at position: " << index << "\n";
            else
                cout << "Not found\n";
            break;
        }
        case 7:
        {
            int length, k;
            cout << "Enter array length: ";
            cin >> length;
            int numbers[length];
            cout << "Enter " << length << " unsorted numbers: ";
            for (int i = 0; i < length; i++)
                cin >> numbers[i];
            cout << "Enter k to find kth smallest element: ";
            cin >> k;
            if (k > 0 && k <= length)
            {
                int result = findKthElement(numbers, length, k);
                cout << "The " << k << "th smallest element is: " << result << "\n";
            }
            else
            {
                cout << "Invalid k\n";
            }
            break;
        }
        case 8:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 8);
    system("pause");
    return 0;
}
