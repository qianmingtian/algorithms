
/*
 * data structures used by the ad-hoc daemon.
 * include base and user_defined data structures.
 */

#ifndef _ADHOC_TYPES_H  
#define	 _ADHOC_TYPES_H

#define WORDSIZE 64  //os is 64 or 32;

/* types */
typedef unsigned char ui8_t;
typedef unsigned short ui16_t;
typedef unsigned int ui32_t;

typedef signed char i8_t;
typedef signed short i16_t;
typedef signed int i32_t;

#if WORDSIZE == 64
typedef signed long int i64_t;
typedef unsigned long int ui64_t;
#else
typedef signed long long int i64_t;
typedef unsigned long long int ui64_t;
#endif

typedef float fi32_t;
typedef double fi64_t;


#endif /* _ADHOC_TYPES_H */

/*
 * Local Variables:
 * End:
 */


