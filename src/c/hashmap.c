#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DEFAULT_HASH 101 // Should be a prime number


typedef struct hash_entry{

    int key;
    int value;
    int added;
}hash_entry;

#define size_entry sizeof(hash_entry)

typedef struct HashMap{
    int size;
    int capacity; // java kodta N
    float load_factor; // default is 0.6
    int a, b; // MAD parameters
    int Prime; // prime number
    int dhp; // prime for secodn hashing
    hash_entry* ptr;

}HashMap;

void update(HashMap*map);
void resize(int N, HashMap *map);
void map_init(HashMap * map ){
    srand(time(NULL));
    map->size = 0;
    map->capacity = DEFAULT_HASH;
    map->load_factor =0.6f;

    map->ptr = malloc(DEFAULT_HASH*size_entry);
    resize(DEFAULT_HASH-1,map);
    update(map);
}

void add_map(int key, int value, HashMap *map){

}
/** Most basic implementation for the hashcode for the integer
 * Can it be improved ?
 * 
 * 
 * */
int hashCode(int value){
    return value;
}

int map_isEmpty(HashMap * map){
    return (map->size == 0);
}


void new_entry(hash_entry* entry,int key, int value){

    entry->key = key;
    entry->value = value;
    
}

void setKey(hash_entry * entry , int key){
    entry->key = key;
}
int returnKey(hash_entry * entry){
    return entry->key;
}

void setValue(hash_entry* entry , int value){
    entry->value = value;
}

int returnValue(hash_entry* entry ){
    return entry->value ;
}

void print_entry(hash_entry * entry){
    printf("( k: %d  v: %d )",entry->key,entry->value);
}

/** Returns the largest integer bigger than n
 * could be slow for bigger sets ?
 * 
 * 
 * */
int next_prime(int number){
    int prime = 0;
    // first prime
    int first = 2;
    number--;
    // look if number is prime by increasing one by one
    while(!prime){
        number++;

        int n = (int) ceil(sqrt(number));

        prime = 1;

        for (int i = first; i <= n ; i++)
        {
            if(number % i == 0){
                prime = 0;
                break;
            }
        }
    }
    return number;
}



// abs lere gerek olmayabilir
int pr_hash(int hash, HashMap *map){
   return abs(abs((map->a*hash + map->b)%map->Prime) % map->capacity);
}

float load(HashMap * map){
    return  (float) map->size/map->capacity;
}
// abs lere gerek olmayabilir
int sec_hash(int hash, HashMap *map){
    return abs(map->dhp - abs(hash % map->dhp));
}

void resize(int N , HashMap *map){

    map->capacity = next_prime(N);
    map->ptr = realloc(map->ptr, map->capacity*size_entry);
}

int hashValue(int key, int i,HashMap *map){
    int k = abs(hashCode(key));
    return abs(pr_hash(k, map) + i * sec_hash(k,map)) % map->capacity;
}

void update(HashMap *map){

    map->Prime = next_prime(map->capacity-1);
    float a = (float)rand();
    float b = (float)rand();
    int ia = (int)((a / RAND_MAX)* map->capacity-1)+1;
    int ib = (int)((b / RAND_MAX) * map->capacity);
    map->a = ia;
    map->b = ib;
    map->dhp = next_prime(map->capacity/2);
}
void check(HashMap *map){
    if(load(map)> map->load_factor){
        resize(2*map->capacity,map);
        update(map);
    }
}




void put_entry(HashMap * map, int k , int v){
    check(map);
    int iter = 0;

    while (iter != map->capacity-1)
    {
        int hsval = hashValue(k,iter,map);

        if(map->ptr [hsval].key == 0){
            
            if(!(map->ptr ->added ==1)){
                map->size++;
                map->ptr[hsval].key = k;
                map->ptr[hsval].value = v;
                map->ptr[hsval].added =1;
                break;
            } 
        }

        if(map->ptr[hsval].key == k  ){
            map->ptr[hsval].value = v;
        }


        iter++;
    }
    

}




int main(int argc, char const *argv[])
{
    HashMap map;
    map_init(&map);
    put_entry(&map,3,5);
    print_entry(&map.ptr[hashValue(3,0,&map)]);

    return 0;
}


