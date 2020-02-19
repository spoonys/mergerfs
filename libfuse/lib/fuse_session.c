/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU LGPLv2.
  See the file COPYING.LIB
*/

#include "fuse_chan.h"
#include "fuse_common_compat.h"
#include "fuse_i.h"
#include "fuse_kernel.h"
#include "fuse_lowlevel_compat.h"
#include "fuse_misc.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct fuse_session *fuse_session_new(struct fuse_session_ops *op, void *data)
{
  struct fuse_session *se = (struct fuse_session *) malloc(sizeof(*se));
  if (se == NULL) {
    fprintf(stderr, "fuse: failed to allocate session\n");
    return NULL;
  }

  memset(se, 0, sizeof(*se));
  se->op = *op;
  se->data = data;

  return se;
}

void
fuse_session_process(struct fuse_session *se,
                     const char          *buf,
                     size_t               len,
                     fuse_chan_t         *ch)
{
  se->op.process(se->data, buf, len, ch);
}

void fuse_session_process_buf(struct fuse_session *se,
			      const struct fuse_buf *buf, fuse_chan_t *ch)
{
  if (se->process_buf) {
    se->process_buf(se->data, buf, ch);
  } else {
    assert(!(buf->flags & FUSE_BUF_IS_FD));
    fuse_session_process(se->data, buf->mem, buf->size, ch);
  }
}

int fuse_session_receive_buf(struct fuse_session *se, struct fuse_buf *buf,
			     fuse_chan_t *ch)
{
  int res;

  if (se->receive_buf) {
    res = se->receive_buf(se, buf, ch);
  } else {
    res = fuse_chan_recv(ch, buf->mem, buf->size);
    if (res > 0)
      buf->size = res;
  }

  return res;
}


void fuse_session_destroy(struct fuse_session *se)
{
  if (se->op.destroy)
    se->op.destroy(se->data);
  if (se->ch != NULL)
    fuse_chan_destroy(se->ch);
  free(se);
}

void fuse_session_exit(struct fuse_session *se)
{
  if (se->op.exit)
    se->op.exit(se->data, 1);
  se->exited = 1;
}

void fuse_session_reset(struct fuse_session *se)
{
  if (se->op.exit)
    se->op.exit(se->data, 0);
  se->exited = 0;
}

int fuse_session_exited(struct fuse_session *se)
{
  if (se->op.exited)
    return se->op.exited(se->data);
  else
    return se->exited;
}

void *fuse_session_data(struct fuse_session *se)
{
  return se->data;
}
