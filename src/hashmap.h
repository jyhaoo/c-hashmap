typedef struct {
    char* key;
    char* value;
} hm_item;

typedef struct {
    int size;
    int count;
    hm_item** items;
} hm_hashmap;

hm_hashmap* hm_new();
static hm_item* hm_new_item(const char* key, const char* value);
static void hm_free_item(hm_item* item);
static void hm_free_hashmap(hm_hashmap* hashmap);
static int hm_hash(const char* key,const int a, const int size);
static int hm_get_hash(const char* key, const int num_buckets, const int attempt);