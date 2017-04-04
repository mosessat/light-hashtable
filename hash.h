#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if D_HASHSIZE < 101
#define LW_HASHSIZE	101
#else
#define LW_HASHSIZE	D_HASHSIZE
#endif

typedef struct HashTable {
	/* table entry: */
	struct HashTable *next;     /* next entry in chain */
	char *name;     /* defined name */
	char *defn;     /* replacement text */
} HashTable;

HashTable **hash_new(void);
int hash_set(HashTable **hash, const char *key, const char *value);
int hash_get(HashTable **hash, const char *key, char *value);
int hash_del(HashTable **hash, const char *key);
void hash_dump(HashTable **hash);

