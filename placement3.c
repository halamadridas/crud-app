#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100 // Maximum word length (adjust as needed)

// Structure to store word and its frequency
typedef struct {
    char word[MAX_LEN + 1];
    int count;
} WordCount;

// Hash function to map words to indexes in the hash table
int hash(const char* word) {
    int hash_value = 0;
    while (*word) {
        hash_value = (hash_value * 31 + *word) % 100000; // Adjust modulo value as needed
        word++;
    }
    return hash_value;
}

// Compare function for qsort to sort WordCount based on count (descending) and word (ascending)
int compare(const void* a, const void* b) {
    const WordCount* w1 = (const WordCount*)a;
    const WordCount* w2 = (const WordCount*)b;
    if (w1->count != w2->count) {
        return w2->count - w1->count; // Sort by count (descending)
    } else {
        return strcmp(w1->word, w2->word); // Sort by word (ascending)
    }
}

char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) {
    // Hash table to store word counts
    WordCount* hashTable[100000]; // Adjust size as needed
    memset(hashTable, 0, sizeof(hashTable));

    // Build the hash table (count word frequencies)
    for (int i = 0; i < wordsSize; i++) {
        int index = hash(words[i]);
        if (hashTable[index] == NULL) {
            hashTable[index] = malloc(sizeof(WordCount));
            strcpy(hashTable[index]->word, words[i]);
            hashTable[index]->count = 1;
        } else {
            hashTable[index]->count++;
        }
    }

    // Count the number of unique words (non-empty entries in the hash table)
    int uniqueWords = 0;
    for (int i = 0; i < 100000; i++) { // Adjust loop limit as needed
        if (hashTable[i] != NULL) {
            uniqueWords++;
        }
    }

    // Create an array to store WordCount for unique words
    WordCount* wordCounts = malloc(uniqueWords * sizeof(WordCount));
    int j = 0;
    for (int i = 0; i < 100000; i++) { // Adjust loop limit as needed
        if (hashTable[i] != NULL) {
            wordCounts[j] = *hashTable[i];
            j++;
        }
    }

    // Sort the array based on frequency (descending) and word (ascending)
    qsort(wordCounts, uniqueWords, sizeof(WordCount), compare);

    // Allocate memory to store the top k frequent words
    char** result = (char**)malloc(k * sizeof(char*));
    for (int i = 0; i < k; i++) {
        result[i] = (char*)malloc(MAX_LEN + 1);
        strcpy(result[i], wordCounts[i].word);
    }

    // Free memory used by the hash table and wordCounts array
    for (int i = 0; i < 100000; i++) { // Adjust loop limit as needed
        if (hashTable[i] != NULL) {
            free(hashTable[i]);
        }
    }
    free(wordCounts);

    *returnSize = k;
    return result;
}

int main() {
    char* words[] = {"i", "love", "leetcode", "i", "love", "coding"};
    int k = 2;
    int returnSize;

    char** result = topKFrequent(words, sizeof(words) / sizeof(words[0]), k, &returnSize);

    printf("Top %d frequent words:\n", k);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", result);
    }
}
