#ifndef _CC
#define _CC

typedef unsigned int u32_t;
typedef int s32_t;
typedef unsigned short u16_t;
typedef short s16_t;
typedef char s8_t;
typedef unsigned char u8_t;

#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif

#define PACK_STRUCT_STRUCT

typedef u32_t mem_ptr_t;

#endif /* _CC */
