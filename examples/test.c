#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main() {
	int rc;
	HashTable **h;

	/* Creating new hash */
	h = hash_new();

	/* Adding more key : value to Hash */
	hash_set(h, "key1", "val1");
	hash_set(h, "key2", "val2");
	hash_set(h, "key3", "val3");
	hash_set(h, "key4", "val4");
	hash_set(h, "key5", "val5");
	hash_dump(h);

	/* Deleting specific key */
	rc = hash_del(h, "key1");
	rc = hash_del(h, "key4");
	hash_dump(h);

	/* Removing all hash keys & values */
	rc = hash_free(h);
	hash_dump(h);

	return EXIT_SUCCESS;
}
