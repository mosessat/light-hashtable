# light-hashtable
Light Weight HashTable implementation in C.

### Description


### Functions to use

  - `hash_new()` - Initializes new HashTable
  - `hash_set()` - To add key & value. (If key is already present, then it will update new value )
  - `hash_get()` - Fetch value from HashTable
  - `hash_del()` - Remove key from HashTable
  - `hash_dump()` - Dump HashTable
  - `hash_free()` - Removes all keys & values, finally frees memory

### Here the declarations

```
HashTable **hash_new(void);
int hash_set(HashTable **hash, const char *key, const char *value);
int hash_get(HashTable **hash, const char *key, char *value);
int hash_del(HashTable **hash, const char *key);
void hash_dump(HashTable **hash);
int hash_free(HashTable **hash);
```

### Installation

```sh
$ make
```

After successful completion of `make`, you will get both static and dynamic library (`liblhash.so` and `liblhash.a`) in the
current directory. You can add these library files in your code and start using this.

### How to use

You will get examples to know more about the usage.

```sh
$ ls examples/
```
Execute: 
```sh
$ ./examples/test.out
Hash Dump : {
	 -> key1 : val1,
	 -> key2 : val2,
	 -> key3 : val3,
	 -> key4 : val4,
	 -> key5 : val5,
}

Hash Dump : {
	 -> key2 : val2,
	 -> key3 : val3,
	 -> key5 : val5,
}

Hash Dump : {
}
```

