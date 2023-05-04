#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <utility>
#include <bits/stdc++.h>
#include <fstream>

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
    string temp;
    stringstream iss(userInput);
    while (iss >> temp) {
        for (int i = 0; i < temp.length(); i++) {
            char ch = tolower((char) temp[i]);
            temp[i] = ch;
            if (i == 0) {
                switch ((char) temp[i]) {
                    case '"':
                        goto CONT1;
                    case '(':
                        goto CONT1;
                    case '$':
                        goto CONT1;
                    default:
                        break;
                    CONT1:
                        temp = temp.substr(1);
                        break;
                }
            }
            if (i == temp.length() - 1) {
                switch ((char) temp[i]) {
                    case ',':
                        goto CONT;
                    case '.':
                        goto CONT;
                    case '?':
                        goto CONT;
                    case '!':
                        goto CONT;
                    case ':':
                        goto CONT;
                    case ';':
                        goto CONT;
                    case ')':
                        goto CONT;
                    case '"':
                        goto CONT;
                    case '$':
                        goto CONT;
                    default:
                        break;
                    CONT:
                        temp = temp.substr(0, temp.length() - 1);
                        break;
                }
            }
        }
        if (words.find(temp) == words.end()) {
            pair<string, int> tempWord = make_pair(temp, 1);
            words.insert(tempWord);
        } else {
            words.find(temp)->second++;      
        }
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
        if (kv.first.length() > temp) {
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
    string tempText;
    ifstream textFile("file.txt");
    while (getline (textFile, tempText)) {
        userInput += tempText;
    }
    // cout << "Please enter or paste text: ";
    // getline(cin, userInput);
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
    textFile.close();
    return 0;
}