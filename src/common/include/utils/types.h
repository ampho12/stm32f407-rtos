#ifndef INCLUDE_TYPES_h_
#define INCLUDE_TYPES_h_

typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef uint32_t pin_t;


// utils
#define replace_masked(dst, src, mask) \
  ((dst) ^ (((dst) ^ (src)) & mask)) 


// ptr : pointer to member in struct
// type : type of struct 
// member: name of member within this struct
#define container_of(ptr, type, member) \
  ((type) *) (                          \
    (char *) (ptr) -                    \
    (size_t) &((type) 0x0)->(member)     \
    )                                   

#endif // INCLUDE_TYPES_h_
