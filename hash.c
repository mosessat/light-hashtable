#include "hash.h"

/* Static functions declations */
static unsigned _hashval(const char *s);
static int _undef(HashTable **hash, const char *name);
static HashTable *_lookup(HashTable **hash, const char *s);
static HashTable *_install(HashTable **hashtab, const char *name, const char *defn);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : hash_new
 *  Description : This will create new HashTable.
 * =====================================================================================
 */
HashTable **hash_new(void)
{
	HashTable **hash = NULL;

	/* Allocate memory */
	hash = malloc(LW_HASHSIZE * sizeof(HashTable *));
	if (hash == NULL) {
		perror("hash_new: malloc()");
		return NULL;
	}

	/* Initialize all pointers points to NULL */
	int n;
	for (n = 0; n < LW_HASHSIZE; n++) {
		*(hash+n) = NULL;
	}

	return hash;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : hash_get
 *  Description : This will get value from HASH by given KEY.
 * =====================================================================================
 */
int hash_get(HashTable **hash, const char *key, char *value)
{
	HashTable *np;
	if ((np = _lookup(hash, key)) != NULL) {
		strcpy(value, np->defn);
		return 0;	/* found */
	}
	return -1;	/* not found */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : hash_set
 *  Description : This will set value to HASH for the given KEY.
 * =====================================================================================
 */
int hash_set(HashTable **hash, const char *key, const char *value)
{
	if (_install(hash, key, value) != NULL) {
		return 0;
	}
	return -1;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : hash_del
 *  Description : This will remove a key from HASH.
 * =====================================================================================
 */
int hash_del(HashTable **hash, const char *key)
{
	return _undef(hash, key);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : hash_free
 *  Description : This will free all HASH objects.
 * =====================================================================================
 */
int hash_free(HashTable **hash)
{
	int i;
	HashTable *np1, *np2;

	if (hash == NULL)
		return -1;	/* Not a valid 'hash' pointer */

	for (i=0; i < LW_HASHSIZE; i++) {
		for (np1 = np2 = hash[i]; np1 != NULL; np1 = np2) {
			np2 = np1->next;

			/* Free memory */
			free(np1->name);
			free(np1->defn);
			free(np1);
		}
		hash[i] = NULL;
	}

	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : hash_dump
 *  Description : This will dump HASH key-value pairs.
 * =====================================================================================
 */
void hash_dump(HashTable **hash)
{
	int i;
	HashTable *np;

	if (hash == NULL)
		return;	/* Not a valid 'hash' pointer */

	printf("Hash Dump : {\n");
	for (i=0; i < LW_HASHSIZE; i++) {
		for (np = hash[i]; np != NULL; np = np->next)	/* loop through each sub-list */
			printf("\t -> %s : %s,\n", np->name, np->defn);
	}
	printf("}\n\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : _hashval
 *  Description : internal func: form hash value for string "s"
 * =====================================================================================
 */
static unsigned _hashval(const char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % LW_HASHSIZE;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : _lookup
 *  Description : internal func: look for s in HASH
 * =====================================================================================
 */
static HashTable *_lookup(HashTable **hash, const char *s)
{
	HashTable *np;
	for (np = hash[_hashval(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	}
	return NULL;	/* not found */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : _install
 *  Description : internal func: put (name, defn) in hashtab
 * =====================================================================================
 */
static HashTable *_install(HashTable **hash, const char *name, const char *defn)
{
	HashTable *np;
	unsigned hashval;

	if ((np = _lookup(hash, name)) == NULL) { /* not found */
		np = (HashTable *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = _hashval(name);
		np->next = hash[hashval];
		hash[hashval] = np;
	} else	/* already there */
		free((void *) np->defn);	/* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name : _undef
 *  Description : internal func: remove (name) in hashtab
 * =====================================================================================
 */
static int _undef(HashTable **hash, const char *name)
{
	unsigned hashval;
	HashTable *np1, *np2;

	if ((np1 = _lookup(hash, name)) == NULL)
		return -1;	/* name not found */

	hashval = _hashval(name);
	for ( np1 = np2 = hash[hashval]; np1 != NULL;
			np2 = np1, np1 = np1->next ) {
		if ( strcmp(name, np1->name) == 0 ) {  /* name found */

			/* Remove node from list */
			if ( np1 == np2 )
				hash[hashval]= np1->next;
			else
				np2->next = np1->next;

			/* Free memory */
			free(np1->name);
			free(np1->defn);
			free(np1);

			return 0;	/* successfully removed from 'hash' */
		}
	}

	return -1;  /* name not found */
}

