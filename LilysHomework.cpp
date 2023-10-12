#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>
#include <thread>

std::string ltrim(const std::string &);
std::string rtrim(const std::string &);
std::vector<std::string> split(const std::string &);

/*
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
void orderAscending(std::vector<int> arr, int &counter) {
    for(unsigned long i = 0; i < arr.size(); i++) {
        std::vector<int>::iterator minPointer = min_element(arr.begin() + i, arr.end());
        if(minPointer != arr.begin() + i) {
            std::swap(*minPointer, *(arr.begin() + i));
            counter++;
        }
    }
}

void orderDescending(std::vector<int> arr, int &counter) {
    for(unsigned long i = 0; i < arr.size(); i++) {
        std::vector<int>::iterator maxPointer = max_element(arr.begin() + i, arr.end());
        if(maxPointer != arr.begin() + i) {
            std::swap(*maxPointer, *(arr.begin() + i));
            counter++;
        }
    }
}

int lilysHomework(std::vector<int> arr) {
    int counterAsc = 0, counterDesc = 0;

    std::thread threadAsc(orderAscending, arr, std::ref(counterAsc));
    std::thread threadDes(orderDescending, arr, std::ref(counterDesc));

    threadAsc.join();
    threadDes.join();
    
    return std::min(counterAsc, counterDesc);
}

int lilysHomeworkAlt(std::vector<int> arr) {
    int counterAsc = 0, counterDesc = 0;
    std::vector<int> arrCopy(arr);

    for(int i = 0; i < arr.size(); i++) {
        // ascending
        std::vector<int>::iterator minPointer = min_element(arr.begin() + i, arr.end());
        if(minPointer != arr.begin() + i) {
            std::swap(*minPointer, *(arr.begin() + i));
            counterAsc++;
        }
        // descending
        std::vector<int>::iterator maxPointer = max_element(arrCopy.begin() + i, arrCopy.end());
        if(maxPointer != arrCopy.begin() + i) {
            std::swap(*maxPointer, *(arrCopy.begin() + i));
            counterDesc++;
        }
    }
    return std::min(counterAsc, counterDesc);
}

int main()
{
    std::string n_temp;
    std::getline(std::cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    std::string arr_temp_temp;
    std::getline(std::cin, arr_temp_temp);

    std::vector<std::string> arr_temp = split(rtrim(arr_temp_temp));

    std::vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = lilysHomework(arr);

    std::cout << result << "\n";

    return 0;
}

std::string ltrim(const std::string &str) {
    std::string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char c) { return !ispunct(c); })
    );

    return s;
}

std::string rtrim(const std::string &str) {
    std::string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !ispunct(c); }).base(),
        s.end()
    );

    return s;
}

std::vector<std::string> split(const std::string &str) {
    std::vector<std::string> tokens;

    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while ((end = str.find(" ", start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
