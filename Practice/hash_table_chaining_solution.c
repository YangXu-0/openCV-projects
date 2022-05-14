#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 100
#define ALPHA 0.7
#define PRINT_DEBUG 1

/**
String hashes used in practise often utilize bitwise operators.

Although encryption methods are not necessarily relation to the
hash table abstract data type, they can still be used as valid 
hash functions.

https://en.wikipedia.org/wiki/SHA-1#SHA-1_pseudocode
https://en.wikipedia.org/wiki/MD5#Pseudocode

Here, we do not attempt to implement any sort of standardized 
hash, and instead make one up.
*/

typedef struct Cargo {
	char name[NAME_LEN];
	unsigned int personnel_num; // hash based on personnel number
	struct Cargo* next;
} Cargo;

typedef struct HashTable {
	int num_buckets;
	int num_keys;
	Cargo** buckets; // replace upon collision
} HashTable;

//==================================================================
//
//		FUNCTIONS TO PRINT/DISPLAY THE HASH TABLE AND DATA
//
//==================================================================
void print_cargo(Cargo* cargo){
	fprintf(stdout, "%s %u\t", cargo->name, cargo->personnel_num);
}

void print_hash_table(HashTable* ht){
	Cargo* tmp = NULL;
	fprintf(stdout, "====== HASH TABLE WITH %d BUCKETS ======\n", ht->num_buckets);
	for (int i=0; i < ht->num_buckets; i++){
		fprintf(stdout, "BUCKET INDEX: %d\t CARGO: ", i);
		if (ht->buckets[i] != NULL){
			tmp = ht->buckets[i];
			while (tmp != NULL){
				print_cargo(tmp);
				tmp = tmp->next;
			}
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "========================================\n");
}


//==================================================================
//
//		FUNCTION TO CREATE CARGO
//
//==================================================================

Cargo* make_cargo(char name[], unsigned int personnel_num){
	Cargo* c = (Cargo*)malloc(sizeof(Cargo));
	strcpy(c->name, name);
	c->personnel_num = personnel_num;
	c->next = NULL;
	return c;
}


//==================================================================
//
//		HASH TABLE UTILITIES
//
//==================================================================

HashTable* initialize_hash_table(int starting_size){
	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
	ht->buckets = (Cargo**)calloc(starting_size, sizeof(Cargo *));
	ht->num_buckets = starting_size;
	ht->num_keys = 0;
	return ht;
}

float get_load_factor(HashTable* ht){
	/**
	Calculate the load factor of the hash table, alpha
	*/
	return ((float)ht->num_keys) / ((float)ht->num_buckets);
}

unsigned int hash_int(HashTable* ht, int val){
	/**
	Modulo hash function
	*/
	return val % ht->num_buckets;
}

unsigned int hash_string(HashTable* ht, char* s){
	unsigned int key = 0x67452301; // one of the SHA1 hash constants
	unsigned int result = 0;
	unsigned int ch;
	
	int i = 0;
	while (s[i] != '\0'){
		ch = s[i]; // give it additional left bits to rotate into
		result += ((ch ^ key) | ((ch << 5) ^ key));
		i++;
	}
	if (PRINT_DEBUG){
		fprintf(stdout, "Result of hash before modulo: %u\n", result);
		fprintf(stdout, "Result of hash after modulo: %u\n", result % ht->num_buckets);
	}
	return result % ht->num_buckets;
}

void insert(HashTable* ht, Cargo* val){
	/**
	Insert "helper", not meant to be used as interface with the 
	hash table.

	In the case of a collision, the cargos are chained as a linked
	list.
	*/
	Cargo* tmp = NULL;
	unsigned int i = hash_string(ht, val->name);
	
	if (PRINT_DEBUG){
		fprintf(stdout, "Now inserting record for: ");
		print_cargo(val);
		fprintf(stdout, "Attempting insert at bucket index %d ...\n", i);
	}
	
	if (ht->buckets[i] != NULL){
		if (PRINT_DEBUG){
			fprintf(stdout, "Collision found! Chaining record.\n");
		}
		
		tmp = ht->buckets[i];
		while (tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = val;
		
	} else {
		ht->buckets[i] = val;
		val->next = NULL;
	}
	ht->num_keys++;
}

void resize(HashTable* ht){
	/**
	Resizes the hash table in-place such that it has double the number
	of buckets. Re-hashes every key and moves every pre-existing 
	cargo in the table.
	*/
	
	// new bucket count should be double
	int new_size = ht->num_buckets * 2;
	int old_size = ht->num_buckets;

	Cargo* displaced_head = NULL;
	Cargo* displaced_tail = NULL;
	Cargo* tmp = NULL;
	
	ht->buckets = realloc(ht->buckets, sizeof(Cargo**) * new_size);
	for (int i=old_size; i<new_size; i++){
		ht->buckets[i] = NULL;
	}
	ht->num_buckets = new_size;
	ht->num_keys = 0;
	
	for (int i=0; i<old_size; i++){
		tmp = ht->buckets[i]; // a linked list of values
		if (tmp != NULL){
			ht->buckets[i] = NULL;
			// just store it and insert it later
			if (displaced_head == NULL){
				displaced_head = tmp;
				displaced_tail = tmp;
			} else {
				displaced_tail->next = tmp; // joins the two linked lists
			}
			while (displaced_tail->next != NULL){
				displaced_tail = displaced_tail->next; 
			}
		}
	}
	
	while (displaced_head != NULL){
		// essentially performs a dequeue from the head until nothing is left
		tmp = displaced_head;
		displaced_head = displaced_head->next;
		tmp->next = NULL;
		insert(ht, tmp);
		ht->num_keys++;
	}
}

void insert_with_resize(HashTable* ht, Cargo* val){
	/**
	Insert maintaining load factor alpha with in-place resize.

	In the case of a collision, the original cargo is removed and replaced
	with the new cargo. The original cargo is returned.
	*/
	fprintf(stdout, "Hash table current load factor: %0.2f\n", get_load_factor(ht));
	if (get_load_factor(ht) >= ALPHA){
		if (PRINT_DEBUG){
			fprintf(stdout, "Load factor %0.2f exceeds alpha %0.2f. Resizing...\n", get_load_factor(ht), ALPHA);
			fprintf(stdout, "Original # buckets: %d\n", ht->num_buckets);
		}
		resize(ht);
		if (PRINT_DEBUG){
			fprintf(stdout, "Resize complete.\n");
			fprintf(stdout, "New # buckets: %d\n", ht->num_buckets);
		}
	}
	insert(ht, val);
}

Cargo* delete_key(HashTable* ht, char* val){
	/**
	Remove the key, if it exists, from the hash table.
	Note that this function should not free any memory
	associated with the Cargo.
	*/
	unsigned int i = hash_string(ht, val);
	Cargo* tmp = NULL;
	Cargo* prev = tmp;
	
	if (PRINT_DEBUG){
		fprintf(stdout, "Now removing key: %s\n", val);
	}
	
	tmp = ht->buckets[i];
	while (tmp != NULL && strcmp(tmp->name, val) != 0){
		// search the LL
		prev = tmp;
		tmp = tmp->next;
	}
	
	if (tmp != NULL){
		if (ht->buckets[i] == tmp){
			ht->buckets[i] = tmp->next;
		} else {
			prev->next = tmp->next;
		}
		tmp->next = NULL;
	}

	return tmp;
}

Cargo* lookup(HashTable* ht, char* name){
	/**
	Return the Cargo, if it exists, associated with personnel_num
	*/
	if (PRINT_DEBUG){
		fprintf(stdout, "Now looking for personnel: %s\n", name);
	}
	Cargo* result = NULL;
	Cargo* tmp = NULL;
		
	unsigned int i = hash_string(ht, name);
	tmp = ht->buckets[i];
	
	while (tmp != NULL && strcmp(tmp->name, name) != 0){
		tmp = tmp->next;
	} 
	
	if (tmp != NULL){
		result = tmp;
		if (PRINT_DEBUG){
			fprintf(stdout, ".. Person found: ");
			print_cargo(result);
			fprintf(stdout, "\n ");
		}
	} else if (PRINT_DEBUG){
		fprintf(stdout, ".. Person NOT found.\n");
	}
	return result;
}

void destroy(HashTable** ht){
	/**
	Free all memory allocated for the hash table to allow
	program termination.
	*/
	Cargo* tmp = NULL;
	Cargo* prev = NULL;
	for (int i=0;i<(*ht)->num_buckets;i++){
		tmp = (*ht)->buckets[i];
		while (tmp != NULL){
			prev = tmp;
			tmp = tmp->next;
			free(prev);
		}
		(*ht)->buckets[i] = NULL;
	}
	free((*ht)->buckets);
	free((*ht));
	*ht = NULL;
}

int main(){

	HashTable* ht = initialize_hash_table(1);
	Cargo* c; 
	
	c = make_cargo("Bob Bilbert", 10119);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Dob Dilbert", 50119);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Rob Rupert", 19876);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Gof Gilbert", 50118);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Joj Jiljert", 50136);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Lol Lillert", 50138);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Gov Gillert", 50135);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Zoz Zuzzert", 34135);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	print_hash_table(ht);
	
	c = make_cargo("Him Hubbarb", 21135);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Jim Jabber", 11131);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Kim Kardababber", 11131);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	c = make_cargo("Kim Crabber", 11130);
	insert_with_resize(ht, c);
	print_hash_table(ht);
	
	lookup(ht, "Lol Lillert");
	lookup(ht, "Joj Jiljert");
	lookup(ht, "Joj Jiljerhh");
	
	c = delete_key(ht, "Lol Lillert");
	print_hash_table(ht);
	free(c);
	
	destroy(&ht);
}