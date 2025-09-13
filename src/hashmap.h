typedef struct {
    char* key;
    char* value;
} hm_item;

typedef struct {
    int size;
    int count;
    int base_size;
    hm_item** items;
} hm_hashmap;

hm_hashmap* hm_new();
static hm_item* hm_new_item(const char* key, const char* value);
static void hm_del_item(hm_item* item);
void hm_del_hashmap(hm_hashmap* hashmap);
static int hm_hash(const char* key,const int a, const int size);
static int hm_get_hash(const char* key, const int num_buckets, const int attempt);
void hm_insert(hm_hashmap* hashmap, const char* key, const char* value);
char* hm_search(hm_hashmap* hashmap, const char* key);
void hm_delete(hm_hashmap* hashmap, const char* key);
static hm_hashmap* hm_new_sized(const int base_size);
static void hm_resize(hm_hashmap* hm, const int base_size);
static void hm_resize_up(hm_hashmap* hm);
static void hm_resize_down(hm_hashmap* hm);