/*
 * @Proj:Tiger Compiler
 *
 * @FileDesc:{ /$ Symbol Table Header File$\ }
 * 
 * @Author:{
 *  Name  : Adrian Hu
 *  Email : adrain.f.tepes@gmail.com
 * }
 * 
 *
 * @Progress:{
 * 
 * }
 * 
 * @Module:{
 *  LocalModule:symbolTable
 * }
 * 
 * @CGL:{
 *  Contract: Obey
 * }
 * 
 * @Doc:{
 *
 *  x. Abbreviations:
 *      tg      <->     tiger
 *      st      <->     symbol table
 * }
 ****** THIS LINE IS 80 CHARACTERS WIDE - DO *NOT* EXCEED 80 CHARACTERS! ******/
typedef unsigned long long uint64_t;
typedef unsigned long st_data_t;

typedef st_data_t st_index_t;

#ifdef __cplusplus
#   define ANYARGS ...
#else
#   define ANYARGS
#endif

struct s_st_hashType
{
    int (*compare)(ANYARGS);
    st_index_t (*hash)(ANYARGS);
};
typedef struct s_st_hashType st_hashType_t;

struct s_st_table
{
    const struct s_st_hashType *hashType;
    st_index_t  binsNbr;
    st_index_t  totalEntryNbr;
    struct s_st_tableEntry  **bins;
    struct s_st_tableEntry  *head,*tail;
};
typedef struct s_st_table st_table_t;

/**/

typedef struct s_st_tableEntry st_tableEntry_t;

struct s_st_tableEntry 
{
    st_index_t      hashCode;
    st_data_t       key;
    st_data_t       value;
    st_tableEntry_t   *next;
    st_tableEntry_t   *fore, *back;
};

/* symbol table functions - initiating */
st_table_t * f_st_initTable(const st_hashType_t *hashType,st_index_t size);
int f_st_numCmp(st_data_t, st_data_t);
st_index_t f_st_numHash(st_data_t );

/* symbol table functions - operating */
void f_st_add(st_table_t *,st_data_t ,st_data_t);
int f_st_insert(st_table_t *,st_data_t ,st_data_t );
int f_st_delete(st_table_t *,st_data_t *,st_data_t *);
int f_st_lookup(st_table_t *,st_data_t ,st_data_t *);

/* Hash Functions*/

// murmur hash
uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed );
uint64_t MurmurHash64B ( const void * key, int len, unsigned int seed );

/* Tiger dedicated hash type */
st_index_t f_tg_strHash(st_data_t);
st_index_t f_tg_numHash(st_data_t);
int f_tg_numCmp(st_data_t x, st_data_t y);
