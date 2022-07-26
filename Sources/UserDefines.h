
#ifndef _USER_DEFINES_H_
#define _USER_DEFINES_H_

#include <stdint.h>
#include <stdbool.h>

/* RT-Thread version information */
#define SW_VERSION                      1L              /**< major version number */
#define SW_SUBVERSION                   0L              /**< minor version number */
#define SW_REVISION                     1L              /**< revise version number */

/* USE PRINT DEBUG*/
#define USE_PRINT_DEBUG                 1L
#if(USE_PRINT_DEBUG)
    #define PRINT_INSTANCE              INST_LPUART1    /* according to real hardware setting */
#endif

#endif
