#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

using namespace std;

int wordCount = 0;
string userInput;
int charCount;
string commonWord;
string longestWord;
string shortestWord;
int averageWordLength = 0;
bool doneAdding = false;
condition_variable cv;
mutex mx;

void addWordsToMap() {
    unique_lock lock(mx);
    // Do Function

    doneAdding = true;
    cv.notify_all();
    lock.unlock();
}

void wordCountFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    // do Function
    lock.unlock();
}

void averageWordLengthFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    // do Function
    lock.unlock();
}

void longestWordFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    // do Function
    lock.unlock();
}

void shortestWordFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    // do Function
    lock.unlock();
}

void commonWordFn() {
    unique_lock<mutex> lock(mx);
    while (!doneAdding) {
        cv.wait(lock);
    }
    // do Function
    lock.unlock();
}

int main () {
    cout << "Please enter or paste text: ";
    getline(cin, userInput);
    charCount = userInput.length();
    cout << "length is: " << charCount << endl;
    cout << userInput << endl;
    thread addToMap(addWordsToMap);
    thread doWorkCount(wordCountFn);
    thread doAverageWord(averageWordLengthFn);
    thread doLongestWord(longestWordFn);
    thread doShortestWord(shortestWordFn);
    thread doCommonWord(commonWordFn);

    addToMap.join();
    doWorkCount.join();
    doAverageWord.join();
    doLongestWord.join();
    doShortestWord.join();
    doCommonWord.join();
    return 0;
}