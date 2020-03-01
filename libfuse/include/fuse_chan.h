#pragma once

#include <stdint.h>
#include <sys/uio.h>

typedef struct fuse_chan_t fuse_chan_t;
struct fuse_chan_t
{
  int fd;
  uint64_t bufsize;
};

fuse_chan_t         *fuse_chan_new(int fd, uint64_t bufsize);
void                 fuse_chan_destroy(fuse_chan_t *ch);

int                  fuse_chan_fd(fuse_chan_t *ch);
uint64_t             fuse_chan_bufsize(fuse_chan_t *ch);

int                  fuse_chan_recv(fuse_chan_t *ch, char *buf, uint64_t size);
int                  fuse_chan_send(fuse_chan_t *ch, const struct iovec iov[], uint64_t count);

fuse_chan_t         *fuse_chan_clone(fuse_chan_t *ch);
