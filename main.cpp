#include <iostream>
#include <map>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

using namespace std;

int wordCount = 0;
string userInput;
string commonWord;
string longestWord;
string shortestWord;
int averageWordLength = 0;
bool doneAdding = false;
condition_variable doneCounting;
mutex counting_mx;

void addWordsToMap() {
    counting_mx.lock();
    // Do Function
    doneAdding = true;
    doneCounting.notify_all();
    counting_mx.unlock();
}

void wordCountFn() {
    counting_mx.lock();
    while (!doneAdding) {
        wait(doneCounting);
    }
    // do Function
    counting_mx.unlock();
}

void averageWordLengthFn() {
    counting_mx.lock();
    while (!doneAdding) {
        wait(doneCounting);
    }
    // do Function
    counting_mx.unlock();
}

void longestWordFn() {
    counting_mx.lock();
    while (!doneAdding) {
        wait(doneCounting);
    }
    // do Function
    counting_mx.unlock();
}

void shortestWordFn() {
    counting_mx.lock();
    while (!doneAdding) {
        wait(doneCounting);
    }
    // do Function
    counting_mx.unlock();
}

void commonWordFn() {
    counting_mx.lock();
    while (!doneAdding) {
        wait(doneCounting);
    }
    // do Function
    counting_mx.unlock();
}

int main () {
    cout << "Please enter or paste text: ";
    cin >> userInput >> endl;
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