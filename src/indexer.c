//
//  Compile: gcc -fPIC -shared -o indexer.so indexer.c
//

#define TABLESIZE 10000
#define EPISODETOTAL 5

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (c = *str++) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

unsigned long getIndex(char *str) {
  unsigned long index = (hash(str) % TABLESIZE) + 1;
  return index;
}

bool *initTable(bool *bucket, int words, int episodes) {
  int i;
  for (i = 0; i < (words * episodes); i++) {
    bucket[i] = false;
  }
  return bucket;
}

void createIndex(char *filename, int words, int episodes) {
  FILE *fptr;
  fptr = fopen(filename, "w");
  int i;
  for (i = 0; i < (words * episodes); i++) {
    fprintf(fptr, "%d", 0);
  }
  fclose(fptr);
}

void addElement(char *filename, int word, int episode, int episode_total) {
  int index = (((word - 1) * episode_total) + (episode));

  FILE *fptro, *fptrn;
  fptro = fopen(filename, "r");
  fptrn = fopen("temp", "w");

  char tmp;

  while ((tmp = fgetc(fptro)) != EOF) {
    if (ftell(fptro) == (index)) {
      fprintf(fptrn, "%d", 1);
    } else {
      fprintf(fptrn, "%c", tmp);
    }
  }

  fclose(fptro);
  fclose(fptrn);

  remove(filename);
  rename("temp", filename);
}

bool getElement(char *filename, int word, int episode, int episode_total) {
  FILE *fptr;
  fptr = fopen(filename, "r");
  int index = (((word - 1) * episode_total) + (episode));
  // should probably be index not (index-1)
  fseek(fptr, (index - 1), SEEK_SET);
  bool temp = (fgetc(fptr) == '1');
  fclose(fptr);
  return temp;
}

void indexFile(char *indexfile, char *filename, int episode,
               int episode_total) {
  FILE *fptr;
  fptr = fopen(filename, "r");
  char buffer[20];
  char tmpx, tmpy;
  int i = 0;
  while ((tmpx = fgetc(fptr)) != EOF) {

    if (tmpx == ' ') {
      buffer[i] = '\0';
      // printf("%s: %ld\n", buffer, getIndex(buffer));
      //  Change buffer)-1
      addElement(indexfile, getIndex(buffer), episode, episode_total);
      i = 0;
    } else {
      buffer[i] = tmpx;
      i++;
    }
    // printf("c: %c\n", tmpx);
  }
  fclose(fptr);
}

// Fills retarr with the episode numbers which contain the word
void searchWord(char *indexFile, char *word, int *retarr, int episode_total) {
  int i;
  int j = 0;
  for (i = 0; i < episode_total; i++) {
    if (getElement(indexFile, getIndex(word), i, episode_total)) {
      retarr[j] = (i + 1);
      j++;
      if (j > 8) {
        retarr[j] = -1;
        return;
      }
      printf("Found %s in episode: %d\n", word, i);
    }
  }
  if (j > 0) {
    retarr[j] = -1;
    return;
  }
  retarr[0] = -1;
  return;
}

int wordProximity(char *textfile, char *a, char *b) {
  if (strcmp(a, b))
    return 0;
  int dist = strlen(textfile);
  int textlen = dist;
  int i;
  for (i = 0; i < textlen; i++) {
    // !(a and b) == (!a) or (!b)
    // TODO: Have to check which one is best for optimizing later (compiler
    // probably solves this anyway)
    if (!((strcmp(a, b)) && (strcmp(a, b))))
      printf("test");
  }
}

void printSearchresults(int *retarr) {
  int tmp;
  int i;
  for (i = 0; (tmp = retarr[i]) != -1; i++) {
    printf("%d - ", tmp);
  }
}

void pythonsearch(int *retarr, int arrsize, char *indexFile, char *word,
                  int episode_total) {
  // printf("pythonsearch()\n");
  int i;
  int j = 0;
  for (i = 1; i <= episode_total; i++) {
    // printf("Loopitr %d\n", i);
    if (getElement(indexFile, getIndex(word), i, episode_total)) {
      retarr[j] = (i);

      if (j >= (arrsize - 1)) {
        retarr[j] = -1;
        return;
      }
      j++;

      // printf("Found %s in episode: %d\n", word, i);
    }
  }
  if (j > 0) {
    retarr[j] = -1;
    return;
  }
  retarr[0] = -1;
  // searchWord(indexFile, word, retarr);
  // printSearchresults(retarr);
  return;
}
/*
int main() {
    char *name = "index.i";

    //addElement("index.i", getIndex("elizabeth"), 1, EPISODETOTAL);
    //printf("%d\n", getElement(name, 2, 2, EPISODETOTAL));

    // createIndex(name, TABLESIZE, EPISODETOTAL);
    // printf("Indexing\n");
    // indexFile("index.i", "../oneline_backup/2024-2-6.txt", 1, EPISODETOTAL);
    // printf("Indexing\n");
    // indexFile("index.i", "../oneline_backup/2024-2-9.txt", 2, EPISODETOTAL);
    // printf("Indexing\n");
    // indexFile("index.i", "../oneline_backup/2024-2-13.txt", 3, EPISODETOTAL);
    // printf("Indexing\n");
    // indexFile("index.i", "../oneline_backup/2024-2-16.txt", 4, EPISODETOTAL);
    // printf("Indexing\n");
    // indexFile("index.i", "../oneline_backup/2024-2-21.txt", 5, EPISODETOTAL);
    // printf("----\n");
    printf("%d\n", getElement(name, getIndex("eliabeth"), 1, EPISODETOTAL));
    printf("%d\n", getElement(name, getIndex("eliabeth"), 2, EPISODETOTAL));
    printf("%d\n", getElement(name, getIndex("eliabeth"), 3, EPISODETOTAL));
    printf("%d\n", getElement(name, getIndex("eliabeth"), 4, EPISODETOTAL));
    printf("%d\n", getElement(name, getIndex("eliabeth"), 5, EPISODETOTAL));
    printf("----\n");
    printf("%ld\n", getIndex("elizabeth"));
    printf("%d\n", getElement(name, 7726, 1, EPISODETOTAL));
    // printf("%d\n", getElement(name, getIndex("is"), 2));
    // printf("%d\n", getElement(name, getIndex("so"), 2));
    // printf("%d\n", getElement(name, getIndex("tables"), 2));
    // printf("----\n");
    // printf("%ld\n", getIndex("this"));
    // printf("%ld\n", getIndex("test"));
    // printf("%ld\n", getIndex("kongen"));
    // printf("%ld\n", getIndex("memory"));
    // printf("----\n");
    int retarr[10] = {10,10,10,10,10,10,10,10,10,10};
    //searchWord(name, "elizabeth", retarr, 5);
    pythonsearch(retarr, 10, name, "elizabeth", 5);
    printSearchresults(retarr);

    return 0;
}*/

//  - Old Functions -
/*    -------------

typedef struct {
    bool *exists;
} table;

int testfunc() {
    return 2;
}



unsigned long key(char *str, unsigned int tablesize) {
    unsigned long temp = hash(str);
    return (temp % tablesize);
}

void initTable_old(table *bucket, unsigned int words, unsigned int episodes) {
    // Allocate enough table elements for every word
    bucket = malloc(words * sizeof(bucket));

    int i, j;
    for (i=0;i<words;i++) {
        // Allocates enough space for bool of every episode
        bucket[i].exists = malloc(episodes * sizeof(bool));
        for (j=0;j<episodes;j++) {
            // Initializes every value to false
            bucket[i].exists[j] = 0;
        }
    }
}



// Add selected element to hash map
void addElement(table *bucket, char *key, unsigned int episode) {
    bucket[hash(key) % TABLESIZE].exists[episode] = 1;
}

bool getElement(table *bucket, char *key, unsigned int episode) {
    return bucket[hash(key)%TABLESIZE].exists[episode];
}

int main() {
    table *bucket;

    // Episode 0 - "hello table"
    // Episode 1 - "table world"

    char *word1 = "hello";
    char *word2 = "world";
    char *word3 = "table";

    initTable(bucket, TABLESIZE, 2);
    //addElement(bucket, word1, 0);
    //addElement(bucket, word3, 0);
    //addElement(bucket, word3, 1);
    addElement(bucket, word1, 1);

    //printf("%d\n", getElement(bucket, word1, 0));
}

// test = 6385723493
// teste = 210728875370

*/
