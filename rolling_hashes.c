#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LEN 500
#define P 997

int hash_cmp(int *p, int *q){
    int a = *p, b = *q;
    if( a < b)
        return -1;
    if(a == b)
        return 0;
    return 1;
}

int running_hash_soution(char *str){
    size_t l = strlen(str), i, sz;
    unsigned int powmod[MAX_LEN], rolling_hash[MAX_LEN + 1], subhashes[MAX_LEN * MAX_LEN / 2];
    unsigned int hash_value;
    unsigned int cnt = 0;
    int ans;
    /* char tmp[MAX_LEN]; */
    memset(rolling_hash, 0, sizeof(rolling_hash));
    assert(l < MAX_LEN);

    rolling_hash[0] = 0;
    for(i = 0; i < l; ++i)
        rolling_hash[i + 1] = rolling_hash[i] * P + str[i];

    /* printf("rolling_hash: "); */
    /* for(i = 0; i < l + 1; ++i) */
    /*     printf("%lx ", rolling_hash[i]); */
    /* printf("\n"); */
    
    powmod[0] = 1;
    for(i = 1; i < MAX_LEN; ++i)
        powmod[i] = powmod[i - 1] * P;

    /* printf("powmod: "); */
    /* for(i = 0; i < l + 1; ++i) */
    /*     printf("%lx ", rolling_hash[i]); */
    /* printf("\n"); */

    cnt = 0;
    for(i = 0; i < l; ++i)
        for(sz = 1; i + sz <= l; ++sz){
            hash_value = rolling_hash[i + sz] - rolling_hash[i] * powmod[sz];
            subhashes[cnt] = hash_value;
            ++cnt;
            /* memset(tmp, 0, sizeof(tmp)); */
            /* memcpy(tmp, str + i, sz); */
            /* printf("str[%d..%d] = %s -> %lx\n", i, i + sz, tmp, hash_value); */
        }
    qsort(subhashes, cnt, sizeof(subhashes[0]), hash_cmp);
    
    ans = 1;
    for(i = 0; i + 1 < cnt; ++i)
        if(subhashes[i] != subhashes[i + 1])
            ++ans;
    return ans;
}

int qsort_solution(char* str){
    int i, sz, cnt = 0, ans, l = strlen(str);
    char items[MAX_LEN * MAX_LEN / 2][MAX_LEN];
    printf("# items %lld\n", sizeof(items));
    memset(items, 0, sizeof(items));
    assert(l < MAX_LEN);
    
    for(i = 0; i < l; ++i)
        for(sz = 1; i + sz <= l; ++sz){
            memcpy(items[cnt], str + i, sz);
            ++cnt;
        }
    /* printf("cnt = %d\n", cnt); */
    /* printf("size = %d\n", (int)sizeof(items[0])); */
    
    qsort(items, cnt, sizeof(items[0]), strcmp);
    
    /* for(i = 0; i < cnt; ++i) */
    /*     printf("%s\n", items[i]); */

    ans = 1;
    for(i = 0; i + 1 < cnt; ++i)
        if(strcmp(items[i], items[i + 1]))
            ++ans;
    return ans;
}

int main(){
    char str[MAX_LEN];
    scanf("%s", str);
    
    printf("%d with qsort\n", qsort_solution(str));
    printf("%d with running hashes\n", running_hash_soution(str));
}
