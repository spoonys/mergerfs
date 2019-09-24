/*
  ISC License

  Copyright (c) 2019, Antonio SJ Musumeci <trapexit@spawn.link>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "funcpolicies.hpp"

void
FuncPolicies::funcs(std::vector<std::string> *vec_) const
{
  vec_->push_back("access");
  vec_->push_back("chmod");
  vec_->push_back("chown");
  vec_->push_back("create");
  vec_->push_back("getattr");
  vec_->push_back("getxattr");
  vec_->push_back("link");
  vec_->push_back("listxattr");
  vec_->push_back("mkdir");
  vec_->push_back("mknod");
  vec_->push_back("open");
  vec_->push_back("readlink");
  vec_->push_back("removexattr");
  vec_->push_back("rename");
  vec_->push_back("rmdir");
  vec_->push_back("setxattr");
  vec_->push_back("symlink");
  vec_->push_back("truncate");
  vec_->push_back("unlink");
  vec_->push_back("utimens");
}

const
Policy*
FuncPolicies::policy(const std::string &func_) const
{
  if(func_ == "access")
    return &access;
  if(func_ == "chmod")
    return &chmod;
  if(func_ == "chown")
    return &chown;
  if(func_ == "create")
    return &create;
  if(func_ == "getattr")
    return &getattr;
  if(func_ == "getxattr")
    return &getxattr;
  if(func_ == "link")
    return &link;
  if(func_ == "listxattr")
    return &listxattr;
  if(func_ == "mkdir")
    return &mkdir;
  if(func_ == "mknod")
    return &mknod;
  if(func_ == "open")
    return &open;
  if(func_ == "readlink")
    return &readlink;
  if(func_ == "removexattr")
    return &removexattr;
  if(func_ == "rename")
    return &rename;
  if(func_ == "rmdir")
    return &rmdir;
  if(func_ == "setxattr")
    return &setxattr;
  if(func_ == "symlink")
    return &symlink;
  if(func_ == "truncate")
    return &truncate;
  if(func_ == "unlink")
    return &unlink;
  if(func_ == "utimens")
    return &utimens;

  return NULL;
}
