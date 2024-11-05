#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <numeric>
#include <vector>

using namespace std;

// Structure for each stock data entry
struct StockData
{
    string date;
    double open;
    double high;
    double low;
    double close;
    long volume;
};

// Class to handle real-time stock data updates and queries
class RealTimeStockData
{
private:
    deque<StockData> dataWindow;       // Stores the latest stock data entries
    map<string, StockData> dataByDate; // Sorted access by date for older entries
    size_t windowSize;                 // Moving window size for recent data queries

public:
    RealTimeStockData(size_t wSize) : windowSize(wSize) {}

    // Add a new stock data entry
    void addData(const StockData &newData)
    {
        // Add to data window and map
        dataWindow.push_back(newData);
        dataByDate[newData.date] = newData;

        // Maintain the moving window size
        if (dataWindow.size() > windowSize)
        {
            StockData oldData = dataWindow.front();
            dataByDate.erase(oldData.date); // Remove the oldest entry from the map
            dataWindow.pop_front();         // Remove the oldest entry from the window
        }
    }

    // Retrieve recent prices in the window
    vector<double> getRecentPrices()
    {
        vector<double> prices;
        for (const auto &entry : dataWindow)
        {
            prices.push_back(entry.close);
        }
        return prices;
    }

    // Calculate average closing price in the current window
    double calculateAverageClose()
    {
        if (dataWindow.empty())
            return 0.0;
        double sum = accumulate(dataWindow.begin(), dataWindow.end(), 0.0,
                                [](double acc, const StockData &data)
                                { return acc + data.close; });
        return sum / dataWindow.size();
    }

    // Find stock data by date
    bool findDataByDate(const string &date, StockData &result)
    {
        auto it = dataByDate.find(date);
        if (it != dataByDate.end())
        {
            result = it->second;
            return true;
        }
        return false;
    }

    // Display the recent stock data window
    void displayRecentData()
    {
        cout << "Recent stock data (up to " << windowSize << " entries):" << endl;
        for (const auto &entry : dataWindow)
        {
            cout << "Date: " << entry.date << ", Close: " << entry.close << ", Volume: " << entry.volume << endl;
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework_Lap3_Part5\n";
    cout << "\n";
    // Initialize the RealTimeStockData with a window size of 5
    RealTimeStockData stockData(5);

    // Simulate incoming stock data
    stockData.addData({"20210625", 45.1, 46.0, 44.7, 45.55, 2572300});
    stockData.addData({"20210624", 45.4, 45.9, 45.0, 45.2, 2110700});
    stockData.addData({"20210623", 44.9, 46.4, 44.9, 45.4, 2574200});
    stockData.addData({"20210622", 45.3, 45.45, 44.9, 45.0, 2781900});
    stockData.addData({"20210621", 45.0, 46.0, 44.85, 45.0, 4237600});
    stockData.addData({"20210620", 45.1, 45.8, 44.95, 45.3, 2997800}); // This will push out the oldest data

    // Display recent data in the window
    stockData.displayRecentData();

    // Calculate and display the average closing price
    cout << "Average closing price in current window: " << stockData.calculateAverageClose() << endl;

    // Retrieve specific data by date
    StockData result;
    if (stockData.findDataByDate("20210622", result))
    {
        cout << "Found data for 20210622 - Close: " << result.close << ", Volume: " << result.volume << endl;
    }
    else
    {
        cout << "Data for 20210622 not found in the current dataset." << endl;
    }

    return 0;
}
