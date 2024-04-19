#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie* next[26];    
    int num;
};

void insert(struct Trie* pTrie, char* word);
struct Trie* deallocateTrie(struct Trie* pTrie);
int numberOfOccurrences(struct Trie* pTrie, char* word);
struct Trie* createTrie();
int readDictionary(char* filename, char** pInWords);


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL) return;
    int len = strlen(word);
    struct Trie* curr = pTrie;
    for(int i = 0; i < len; ++i) {
        int index = word[i] - 'a';
        if(curr->next[index] == NULL) {
            curr->next[index] = createTrie();
        }
        curr = curr->next[index];
    }
    curr->num++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL) return 0;
    int len = strlen(word);
    struct Trie *curr = pTrie;
    for(int i = 0; i < len; ++i) {
        int index = word[i] - 'a';
        if(curr->next[index] == NULL) {
            return 0;
        }
        curr = curr->next[index];
    }
    return curr->num;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < 26; ++i)
    {
        if (pTrie->next[i] != NULL)
        {
            deallocateTrie(pTrie->next[i]);
            pTrie->next[i] = NULL;
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    if(newTrie == NULL){
        printf("createTrie() failed");
        return NULL;
    }
    newTrie->num = 0;
    for(int i = 0; i < 26; ++i){
        newTrie->next[i] = NULL;
    }
    return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return -1;
    }
    int count = 0;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = (char*)malloc(strlen(word) + 1);
        strcpy(pInWords[count], word);
        count++;
    }
    fclose(file);
    return count;
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
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
