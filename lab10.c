//Enzo Alisson Lima Barros
//Lab 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
    struct Trie *children[26];
    int count; // New field to count occurrences
};

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->count = 0;
        for (int i = 0; i < 26; i++) {
            trie->children[i] = NULL;
        }
    }
    return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    while (*word) {
        int index = *word - 'a';
        if (!current->children[index]) {
            current->children[index] = createTrie(); // Create a new Trie node if it doesn't exist
        }
        current = current->children[index];
        word++;
    }
    current->count++; // Increment the count for the word
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    while (*word) {
        int index = *word - 'a';
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index];
        word++;
    }
    return current->count; // Return the count of the word
}

// Deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie) {
        for (int i = 0; i < 26; i++) {
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL; // Return NULL after deallocation
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    int numWords;
    if (fscanf(file, "%d", &numWords) != 1) {
        fclose(file);
        fprintf(stderr, "Error reading number of words from file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numWords; ++i) {
        char word[256];
        if (fscanf(file, "%s", word) != 1) {
            fclose(file);
            fprintf(stderr, "Error reading word from file");
            exit(EXIT_FAILURE);
        }
        pInWords[i] = strdup(word);
    }

    fclose(file); 
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
