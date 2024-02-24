//
//  Compile: gcc -fPIC -shared -o indexer.so indexer.c
//

#define TABLESIZE 10
#define EPISODETOTAL 3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
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

bool* initTable(bool *bucket, int words, int episodes) {
    int i;
    for (i=0; i<(words*episodes); i++) {
        bucket[i] = false;
    }
    return bucket;
}

void createIndex(char *filename, int words, int episodes) {
    FILE *fptr;
    fptr = fopen(filename, "w");
    int i;
    for (i=0; i<(words*episodes); i++) {
        fprintf(fptr, "%d", 0);
    }
    fclose(fptr);
}

void addElement(char *filename, int word, int episode) {
    int index = (((word-1)*EPISODETOTAL) + (episode));

    FILE *fptro, *fptrn;
    fptro = fopen(filename, "r");
    fptrn = fopen("temp", "w");

    char tmp;

    while ((tmp = fgetc(fptro)) != EOF)  {
        if (ftell(fptro) == (index)) {
            fprintf(fptrn, "%d", 1);
        }
        else { 
            fprintf(fptrn, "%c", tmp);
        }
    }

    fclose(fptro);
    fclose(fptrn);

    remove(filename);
    rename("temp", filename);
}

bool getElement(char *filename, int word, int episode) {
    FILE *fptr;
    fptr = fopen(filename, "r");
    int index = (((word-1)*EPISODETOTAL) + (episode));
    fseek(fptr, index-1, SEEK_SET);
    bool temp = (fgetc(fptr) == '1');
    fclose(fptr);
    return temp;
}

void indexFile(char *indexfile, char *filename, int episode) {
    FILE *fptr;
    fptr = fopen(filename, "r");
    char buffer[20];
    char tmpx, tmpy;
    int i = 0;
    while ((tmpx = fgetc(fptr)) != EOF) {
        
        if (tmpx == ' ') {
            buffer[i+1] = '\0';
            printf("%s\n", buffer);
            addElement(indexfile, getIndex(buffer), episode);
            i = 0;
        }
        else 
            buffer[i] = tmpx;
    }
    fclose(fptr);
}

int main() {
    char *name = "index.i";
    createIndex(name, TABLESIZE, EPISODETOTAL);
    // addElement("index.i", 2, 1);
    
    indexFile("index.i", "testtext.txt", 2);
    printf("%d\n", getElement(name, getIndex("this"), 1));
    printf("%d\n", getElement(name, getIndex("test"), 1));
    printf("%d\n", getElement(name, getIndex("oslo"), 1));
    printf("%d\n", getElement(name, getIndex("gate"), 1));
    printf("----\n");
    printf("%ld\n", getIndex("this"));
    printf("%ld\n", getIndex("test"));
    printf("%ld\n", getIndex("oslo"));
    printf("%ld\n", getIndex("gate"));
    
    return 0;
}


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
