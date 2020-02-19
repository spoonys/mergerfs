/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU LGPLv2.
  See the file COPYING.LIB
*/

#include "fuse_chan.h"
#include "fuse_i.h"
#include "fuse_kernel.h"
#include "fuse_lowlevel.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

fuse_chan_t*
fuse_kern_chan_new(int fd_)
{
  long pagesize;
  size_t bufsize;

  pagesize = sysconf(_SC_PAGESIZE);

  bufsize = ((FUSE_MAX_MAX_PAGES * pagesize) + 0x1000);

  return fuse_chan_new(fd_,bufsize);
}
