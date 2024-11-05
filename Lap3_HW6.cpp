#include <iostream>
#include <vector>

using namespace std;

void compute_lps(const string &pattern, int lps[])
{
    int length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pattern.size())
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp_search(const string &text, const string &pattern)
{
    int n = text.size();
    int m = pattern.size();
    int lps[m];

    compute_lps(pattern, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework_Lap3_Part6\n";
    cout << "\n";
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);
    kmp_search(text, pattern);
    system("pause");
    return 0;
}
