#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 100
#define ALPHA 0.7
#define PRINT_DEBUG 1


typedef struct Cargo {
    char name[NAME_LEN];
    unsigned int personnel_num; // hash based on personnel number
    struct Cargo* next;
} Cargo;


typedef struct HashTable {
    int num_buckets;
    int num_keys;
    Cargo **buckets; // replace upon collisions
} HashTable;


// Printing
void print_cargo(Cargo *cargo) {
    printf("%s %u\t", cargo->name, cargo->personnel_num);
}


void print_hash_table(HashTable * ht) {
    Cargo *tmp = NULL;
    printf("====== HASH TABLE WITH %d BUCKETS =======\n", ht->num_buckets);
    for (int i = 0; i<ht->num_buckets; i++) {
        printf("BUCKET INDEX: %d\t  CARGO: ", i);
        if (ht->buckets[i] != NULL) {
            tmp = ht->buckets[i];
            while (tmp != NULL) {
                print_cargo(tmp);
                tmp = tmp->next;
            }
        }
        printf("\n");
    }
    printf("=========================================\n");
}


// Creating cargo
Cargo *make_cargo(char name[], unsigned int personnel_num) {
    Cargo *c = (Cargo*)malloc(sizeof(Cargo));
    strcpy(c->name, name);
    c->personnel_num = personnel_num;
    c->next = NULL;
    return c;
}


// Hash table utilities
HashTable *initialize_hash_table(int starting_size) {
    HashTable *new = (HashTable *)malloc(sizeof(HashTable));
    new->num_buckets = starting_size;
    new->buckets = (Cargo **)malloc(sizeof(Cargo *) * starting_size);
    new->num_keys = 0;
    return new;
}


float get_load_factor(HashTable *ht) {
    return ((float) ht->num_keys)/((float) ht->num_buckets); // need to cast to float otherwise returns ints
}


unsigned int hash_int(HashTable *ht, int val) {
    return val % ht->num_buckets;
}


unsigned int hash_string(HashTable *ht, char *s) {
    unsigned int key = 0x67452301;
    unsigned int result = 0;
    unsigned int ch;

    int i = 0;
    while (s[i] != '\0') {
        ch = s[i];
        result += ((ch ^ key) | ((ch << 5) ^ key));
        i++;
    }
    return result % ht->num_buckets;
}


void insert(HashTable * ht, Cargo *val) {
    Cargo *tmp = NULL;
    unsigned int i = hash_string(ht, val->name);

    if (ht->buckets[i] != NULL) {
        tmp = ht->buckets[i];
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = val;
        val->next = NULL;
    }
    else {
        ht->buckets[i] = val;
        val->next = NULL;
    }
    ht->num_keys++;
}


void resize(HashTable *ht) {
    // Resizes in place
    int new_size = ht->num_buckets * 2;
    int old_size = ht->num_buckets;

    Cargo *displaced_head = NULL;
    Cargo *displaced_tail = NULL;
    Cargo *tmp = NULL;

    ht->buckets = realloc(ht->buckets, sizeof(Cargo*) * new_size); // update size of buckets
    for (int i = old_size; i < new_size; i++) { // initializing all values to NULL
        ht->buckets[i] = NULL;
    }
    ht->num_buckets = new_size;
    ht->num_keys = 0;

    for (int i = 0; i<old_size; i++) { // compiles every item into 1 big list and resets buckets completely
        tmp = ht->buckets[i]; // linked list
        if (tmp != NULL) {
            ht->buckets[i] = NULL;

            if (displaced_head == NULL) {
                displaced_head = tmp;
                displaced_tail = tmp;
            }
            else {
                displaced_tail->next = tmp;
            }

            while (displaced_tail->next != NULL) {
                displaced_tail = displaced_tail->next;
            }
        }
    }

    while (displaced_head != NULL) { // insert everything back
        tmp = displaced_head;
        displaced_head = displaced_head->next;
        insert(ht, tmp);
        ht->num_keys++;
    }
}


void insert_with_resize(HashTable* ht, Cargo* val) {
    // Insert maintaining load factor alpha with in-place resize
    // Implemented with overwritting

    printf("Hash table current load factor: %0.2f\n", get_load_factor(ht));
    if (get_load_factor(ht) >= ALPHA) {
        resize(ht);
    }

    insert(ht, val); // shouldnt you technically insert and then resize? otherwise after you insert load factor may be over

    return;
}


Cargo* delete_key(HashTable* ht, char* val) {
    // Remove the key if exists, don't free (return)

    unsigned int i = hash_string(ht, val);

    Cargo *prev = NULL;
    Cargo *tmp = ht->buckets[i];

    while (tmp != NULL && strcmp(tmp->name, val) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    // Cases: 
    // 1. First node
    // 2. Empty first node
    // 3. Middle of node and last node
    // 4. Not in list

    if (tmp != NULL) { 
        if (prev == NULL) {
            ht->buckets[i] = tmp->next;
        }
        else {
            prev = tmp->next;
        }
        tmp->next = NULL;
    }

    return tmp;
}


Cargo *lookup(HashTable *ht, char *name) {
    // Return cargo if exists with associated personnel_num

    unsigned int i = hash_string(ht, name);

    Cargo *tmp = ht->buckets[i];
    
    while (tmp != NULL && strcmp(tmp->name, name) != 0) {
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        printf("Not found");
        return NULL;
    }
    else {
        printf("Cargo exists, personnel_num: %d", tmp->personnel_num);
        return tmp;
    }
}


void destroy(HashTable **ht) {
    // Free all memory

    for (int i = 0; i < (*ht)->num_buckets; i++) {
        Cargo *tmp = (*ht)->buckets[i];
        Cargo *prev = NULL;
        while (tmp != NULL) {
            prev = tmp;
            tmp = tmp->next;
            free(prev);
        }
    }

    free((*ht)->buckets);
    free(*ht);
    (*ht) = NULL;
}


int main(void) {
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

    return 0;
}