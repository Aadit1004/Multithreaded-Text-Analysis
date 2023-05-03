#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <utility>

using namespace std;

unsigned int wordCount = 0;
string userInput;
unsigned int charCount = 0;
string commonWord = "";
string longestWord = "";
string shortestWord = "";
double averageWordLength = 0;
unsigned int uniqueWords = 0;

bool doneAdding = false;
condition_variable cv;
mutex mx;
map<string, int> words;

void addWordsToMap() {
    unique_lock lock(mx);
    // Do Function
    int i = 0;
    while (i < charCount) {
        string temp;
        int num = i;
        while (true) {
            bool temp = false;
            switch((char) userInput[num]) {
                case ' ':
                    goto CONT;
                case '.':
                    goto CONT;
                case '?':
                    goto CONT;
                case ',':
                    goto CONT;
                case '!':
                    goto CONT;
                case ':':
                    goto CONT;
                case ';':
                    goto CONT;
                default:
                    num++; // increase length of word by 1
                    break;
                CONT:
                    temp = true;
                    break;
            }
            if (temp) break;
            if (num >= charCount) break;
        }
        temp = userInput.substr(i, num - i);
        for (int i = 0; i < temp.length(); i++) {
            char ch = tolower((char) temp[i]);
            temp[i] = ch;
        }
        if (words.find(temp) == words.end()) {
            pair<string, int> tempWord = make_pair(temp, 1);
            words.insert(tempWord);
        } else {
            words.find(temp)->second++;      
        }
        i = num + 1;
        // TO DO
    }
    doneAdding = true;
    cv.notify_all();
    lock.unlock();
}

void wordCountFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    for (const auto& kv : words) {
        wordCount += kv.second;
    }
    lock.unlock();
}

void averageWordLengthFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    // number of letters divided by number of words
    double numLetters;
    double numWords;
    for (const auto& kv : words) {
        numLetters += (kv.first.length() * kv.second);
        numWords += kv.second;
    }
    averageWordLength = numLetters / numWords;
    lock.unlock();
}

void longestWordFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    unsigned int temp = 0;
    for (const auto& kv : words) {
        if (kv.first.length() > 0) {
            temp = kv.first.length();
            longestWord = kv.first;
        }
    }
    lock.unlock();
}

void shortestWordFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    unsigned int temp = 1000;
    for (const auto& kv : words) {
        if (kv.first.length() < temp) {
            temp = kv.first.length();
            shortestWord = kv.first;
        }
    }
    lock.unlock();
}

void commonWordFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    unsigned int tempMax = 0;
    for (const auto& kv : words) {
        if (kv.second > tempMax) {
            tempMax = kv.second;
            commonWord = kv.first;
        }
    }
    lock.unlock();
}

void uniqueWordsFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    uniqueWords = words.size();
    lock.unlock();
}

int main () {
    cout << "Please enter or paste text: ";
    getline(cin, userInput);
    charCount = userInput.length();
    thread addToMap(addWordsToMap);
    thread doWorkCount(wordCountFn);
    thread doAverageWord(averageWordLengthFn);
    thread doLongestWord(longestWordFn);
    thread doShortestWord(shortestWordFn);
    thread doCommonWord(commonWordFn);
    thread doUniqueWords(uniqueWordsFn);

    addToMap.join();
    doWorkCount.join();
    doAverageWord.join();
    doLongestWord.join();
    doShortestWord.join();
    doCommonWord.join();
    doUniqueWords.join();

    cout << "The word count is: " << wordCount << endl;
    cout << "The number of unique words is: " << uniqueWords << endl;
    cout << "The average word length is: " << averageWordLength << endl;
    cout << "The Longest word is: " << longestWord << endl;
    cout << "The shortest word is: " << shortestWord << endl;
    cout << "The most common word is: " << commonWord << endl;
    return 0;
}