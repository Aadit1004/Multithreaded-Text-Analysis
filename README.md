# Multithreading-Text-Analysis
A mini project to practice multithreading with multiple functions when reading text to get word count, average word length, longest word, shorted word, most common word, and how many unique words there are. This should prove useful for large files of text where it would be hard to get such information. In this project, I used a map data structure where I stored the words and their number of occurences where it would make it easier to compute the functions stated above.

At the end of the project, I had it so that the user could put a .txt file into the folder and the program will run it from the words on the file. Using the multithreaded code, you can paste large amounts of text and it will compute everything very quickly, which was the purpose of this project. The hardest part of this project was reading the words from a string and having different cases with punctuation. In the end, I ended up learning about a string stream which made it very quick to get the words from a long string (such as essays, or articles).


# Sample Cases
Input: Hi Rodrick! How are you today, rodrick? 

Time taken to execute: 0.012s

Output: 

The word count is: 7 <br>
The number of unique words is: 6 <br>
The average word length is: 4.28571 <br>
The Longest word is: rodrick <br>
The shortest word is: hi <br>
The most common word is: rodrick <br>

---

Input: "This is a quote" (cited by someone)

Time taken to execute: 0.012s

Output: 

The word count is: 7 <br>
The number of unique words is: 7 <br>
The average word length is: 3.71429 <br>
The Longest word is: someone <br>
The shortest word is: a <br>
The most common word is: This <br>

---

Input: *Copied my own essay into text file*

Time taken to execute: 0.013s

Output: 

The word count is: 1826 <br>
The number of unique words is: 526 <br>
The average word length is: 4.80997 <br>
The Longest word is: multidimensional <br>
The shortest word is: a <br>
The most common word is: and <br>