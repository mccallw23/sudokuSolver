/* 
 * set.c - CS50 'bag' module
 *
 * see set.h for more information.
 *
 *
 * Mahir Singh, July 21 2020
 *
 * Usage: run the make command while in the set subdirectory and run 
 *./settest to display the funcitonality of the counters
 *
 * cs50 summer 2021
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"
#include "readlinep.h"


//sets up the set and setnode, works like a linked list
typedef struct setnode {
    void *item;
    char *key;
    struct setnode *next; 
} setnode_t;

//

typedef struct set {
    struct setnode *head;
} set_t;


static setnode_t *setnode_new(void *item, char *key);

set_t *
set_new(void)
{
    set_t *set = malloc(sizeof(set_t));

    if (set == NULL) {
        return NULL;
    } else {
      set->head = NULL;
      return set;
  }
}

static setnode_t*
setnode_new(void *item, char *key) {
    setnode_t *node = malloc(sizeof(setnode_t));

    if (node == NULL && key == NULL) {
        return NULL;
    }
    else {
        node->item = item;
        node->key = key;
        return node;
    }
}


//inserts a key value pair (setnode) into the set, if it does not already exist
bool set_insert(set_t *set, const char *key, void *item) 
{
    if (key != NULL && set != NULL && item != NULL) {
        
        char *key_value = malloc(strlen(key)+1);
        strcpy(key_value, key); 

        setnode_t *new = setnode_new(item, key_value);

        if (set_find(set, key_value) == NULL) {
           
            new->next = set->head;
            set->head = new;
            return true;
        }
    }
    else {
        fprintf(stderr, "failed to insert\n");
    }
    return false;
}

//finds and retyrns the value of a set given a key if it exists
void *set_find(set_t *set, const char *key) {

    if (set != NULL && key != NULL) {

    for(setnode_t *node = set->head; node != NULL; node = node->next) {

        if (strcmp(node->key, key) == 0) {
    
                return node->item;
            }
        }
    }
    return NULL;
}

//prints the set
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
        if (fp != NULL) {
            if (set != NULL) {
                fputc('{', fp);
                for (setnode_t *node = set->head; node != NULL; node = node->next) {
                if (itemprint != NULL) {
                    (*itemprint)(fp, node->key, node->item);
                    fputs(", " ,fp);
                    }
                 }
                 fputs("} ", fp);


            } else {
                     fputs("(null)", fp); 
         }
     }
 }
 
//iterates through tge set
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (set != NULL && itemfunc != NULL) {
        for (setnode_t *node = set->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->item);
        }
    }
}


void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    
    if (set != NULL) {
        for (setnode_t *node = set->head; node != NULL; ) {
            if (itemdelete != NULL) {
                (*itemdelete)(node->key);
            }
            setnode_t *next = node->next;
            free(node);
            node = next;
        }
        free(set);
    }
}


/****/



