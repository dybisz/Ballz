/**
 * 
 * This library is used to keep all functions used 
 * for input/output and signal handling.
 * 
 * */

#ifndef _IO_H_
#define _IO_H_

#include "../util/macros.h"

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

int64_t  bulk_read(int fd, char *buf, size_t count);

int64_t  bulk_write(int fd, char *buf, size_t count);

int sethandler( void (*f)(int), int sigNo);

#endif
