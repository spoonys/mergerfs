/*
  Copyright (c) 2016, Antonio SJ Musumeci <trapexit@spawn.link>

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

#pragma once

#include "branch.hpp"
#include "enum.hpp"
#include "errno.hpp"
#include "func_category.hpp"
#include "funcs.hpp"
#include "policy.hpp"
#include "policy_cache.hpp"

#include <fuse.h>

#include <string>
#include <vector>

#include <stdint.h>
#include <sys/stat.h>

class Config
{
public:
  enum class StatFSEnum
    {
      INVALID = -1,
      BASE,
      FULL
    };
  typedef Enum<StatFSEnum> StatFS;

  enum class StatFSIgnoreEnum
    {
      INVALID = -1,
      NONE,
      RO,
      NC
    };
  typedef Enum<StatFSIgnoreEnum> StatFSIgnore;

  enum class CacheFilesEnum
    {
      INVALID = -1,
      LIBFUSE,
      OFF,
      PARTIAL,
      FULL,
      AUTO_FULL
    };
  typedef Enum<CacheFilesEnum> CacheFiles;

  enum class XAttrEnum
    {
      INVALID     = -1,
      PASSTHROUGH = 0,
      NOSYS       = ENOSYS,
      NOATTR      = ENOATTR
    };
  typedef Enum<XAttrEnum> XAttr;

public:
  Config();

public:
  mutable PolicyCache open_cache;

public:
  const std::string controlfile;
  const std::string version;

public:
  bool           async_read;
  bool           auto_cache;
  Branches       branches;
  uint64_t       cache_attr;
  uint64_t       cache_entry;
  CacheFiles     cache_files;
  uint64_t       cache_negative_entry;
  bool           cache_readdir;
  uint64_t       cache_statfs;
  bool           cache_symlinks;
  FuncCategories category;
  bool           direct_io;
  bool           dropcacheonclose;
  std::string    fsname;
  Funcs          func;
  uint64_t       fuse_msg_size;
  bool           ignorepponrename;
  bool           kernel_cache;
  bool           link_cow;
  uint64_t       minfreespace;
  std::string    mount;
  bool           moveonenospc;
  bool           nullrw;
  const pid_t    pid;
  bool           posix_acl;
  bool           security_capability;
  SrcMounts      srcmounts;
  StatFS         statfs;
  StatFSIgnore   statfs_ignore;
  bool           symlinkify;
  uint64_t       symlinkify_timeout;
  uint64_t       threads;
  XAttr          xattr;

public:
  static bool has_key(const std::string &key);
  static void keys(std::vector<std::string> &keys);
  std::string get(const std::string &key) const;
  int set_raw(const std::string &key, const std::string &val);
  int set(const std::string &key, const std::string &val);

private:
  static Config _config;

public:
  static
  const
  Config &
  get(void)
  {
    return _config;
  }

  static
  Config &
  get_writable(void)
  {
    return _config;
  }
};
