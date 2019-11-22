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

#include "buildvector.hpp"
#include "config.hpp"
#include "ef.hpp"
#include "errno.hpp"
#include "from_string.hpp"
#include "fs.hpp"
#include "num.hpp"
#include "rwlock.hpp"
#include "to_string.hpp"
#include "version.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include <unistd.h>
#include <sys/stat.h>

#define MINFREESPACE_DEFAULT (4294967295ULL)

using std::string;
using std::vector;

Config Config::_config;

static const vector<string> g_keys =
  buildvector<string>
  ("async_read")
  ("auto_cache")
  ("branches")
  ("cache.attr")
  ("cache.entry")
  ("cache.files")
  ("cache.negative_entry")
  ("cache.open")
  ("cache.readdir")
  ("cache.statfs")
  ("cache.symlinks")
  ("category.action")
  ("category.create")
  ("category.search")
  ("direct_io")
  ("dropcacheonclose")
  ("fsname")
  ("func.access")
  ("func.chmod")
  ("func.chown")
  ("func.create")
  ("func.getattr")
  ("func.getxattr")
  ("func.link")
  ("func.listxattr")
  ("func.mkdir")
  ("func.mknod")
  ("func.open")
  ("func.readlink")
  ("func.removexattr")
  ("func.rename")
  ("func.rmdir")
  ("func.setxattr")
  ("func.symlink")
  ("func.truncate")
  ("func.unlink")
  ("func.utimens")
  ("fuse_msg_size")
  ("ignorepponrename")
  ("kernel_cache")
  ("link_cow")
  ("minfreespace")
  ("mount")
  ("moveonenospc")
  ("nullrw")
  ("posix_acl")
  ("security_capability")
  ("srcmounts")
  ("statfs")
  ("statfs_ignore")
  ("symlinkify")
  ("symlinkify_timeout")
  ("threads")
  ("xattr");

Config::Config()
  :
  open_cache(),

  controlfile("/.mergerfs"),
  version(MERGERFS_VERSION),

  async_read(true),
  branches(),
  cache_attr(1),
  cache_entry(1),
  cache_files(CacheFiles::ENUM::LIBFUSE),
  cache_negative_entry(0),
  cache_readdir(false),
  cache_statfs(0),
  cache_symlinks(false),
  category(func),
  direct_io(false),
  dropcacheonclose(false),
  fsname(),
  fuse_msg_size(FUSE_MAX_MAX_PAGES),
  ignorepponrename(false),
  link_cow(false),
  minfreespace(MINFREESPACE_DEFAULT),
  mount(),
  moveonenospc(false),
  nullrw(false),
  pid(::getpid()),
  posix_acl(false),
  security_capability(true),
  srcmounts(branches),
  statfs(StatFS::ENUM::BASE),
  statfs_ignore(StatFSIgnore::ENUM::NONE),
  symlinkify(false),
  symlinkify_timeout(3600),
  threads(0),
  xattr(XAttr::ENUM::PASSTHROUGH)
{
}

bool
Config::has_key(const std::string &key_)
{
  std::vector<std::string>::const_iterator i;

  i = std::find(g_keys.begin(),g_keys.end(),key_);

  return (i != g_keys.end());
}

void
Config::keys(std::vector<std::string> &k_)
{
  k_.insert(k_.end(),
            g_keys.begin(),
            g_keys.end());
}

#define IFRET(X,Y) if(key_ == X) return std::to_string(Y)

std::string
Config::get(const std::string &key_) const
{
  IFRET("async_read",async_read);
  IFRET("auto_cache",auto_cache);
  IFRET("branches",branches);
  IFRET("cache.attr",cache_attr);
  IFRET("cache.entry",cache_entry);
  IFRET("cache.files",cache_files);
  IFRET("cache.negative_entry",cache_negative_entry);
  IFRET("cache.open",open_cache.timeout);
  IFRET("cache.readdir",cache_readdir);
  IFRET("cache.statfs",cache_statfs);
  IFRET("cache.symlinks",cache_symlinks);
  IFRET("category.action",category.action);
  IFRET("category.create",category.create);
  IFRET("category.search",category.search);
  IFRET("direct_io",direct_io);
  IFRET("dropcacheonclose",dropcacheonclose);
  IFRET("fsname",fsname);
  IFRET("func.access",func.access);
  IFRET("func.chmod",func.chmod);
  IFRET("func.chown",func.chown);
  IFRET("func.create",func.create);
  IFRET("func.getattr",func.getattr);
  IFRET("func.getxattr",func.getxattr);
  IFRET("func.link",func.link);
  IFRET("func.listxattr",func.listxattr);
  IFRET("func.mkdir",func.mkdir);
  IFRET("func.mknod",func.mknod);
  IFRET("func.open",func.open);
  IFRET("func.readlink",func.readlink);
  IFRET("func.removexattr",func.removexattr);
  IFRET("func.rename",func.rename);
  IFRET("func.rmdir",func.rmdir);
  IFRET("func.setxattr",func.setxattr);
  IFRET("func.symlink",func.symlink);
  IFRET("func.truncate",func.truncate);
  IFRET("func.unlink",func.unlink);
  IFRET("func.utimens",func.utimens);
  IFRET("fuse_msg_size",fuse_msg_size);
  IFRET("ignorepponrename",ignorepponrename);
  IFRET("kernel_cache",kernel_cache);
  IFRET("link_cow",link_cow);
  IFRET("minfreespace",minfreespace);
  IFRET("mount",mount);
  IFRET("moveonenospc",moveonenospc);
  IFRET("nullrw",nullrw);
  IFRET("posix_acl",posix_acl);
  IFRET("security_capability",security_capability);
  IFRET("srcmounts",srcmounts);
  IFRET("statfs",statfs);
  IFRET("statfs_ignore",statfs_ignore);
  IFRET("symlinkify",symlinkify);
  IFRET("symlinkify_timeout",symlinkify_timeout);
  IFRET("threads",threads);
  IFRET("version",version);
  IFRET("xattr",xattr);

  return std::string();
}

#undef IFRET

template<>
std::string
Config::StatFS::to_string() const
{
  switch(_data)
    {
    case Config::StatFS::ENUM::INVALID:
      break;
    case Config::StatFS::ENUM::BASE:
      return "base";
    case Config::StatFS::ENUM::FULL:
      return "full";
    }

  return "invalid";
}

template<>
int
Config::StatFS::from_string(const std::string &s_)
{
  if(s_ == "base")
    _data = Config::StatFS::ENUM::BASE;
  else if(s_ == "full")
    _data = Config::StatFS::ENUM::FULL;
  else
    return -EINVAL;

  return 0;
}

template<>
std::string
Config::StatFSIgnore::to_string() const
{
  switch(_data)
    {
    case Config::StatFSIgnore::ENUM::INVALID:
      break;
    case Config::StatFSIgnore::ENUM::NONE:
      return "none";
    case Config::StatFSIgnore::ENUM::RO:
      return "ro";
    case Config::StatFSIgnore::ENUM::NC:
      return "nc";
    }

  return "invalid";
}

template<>
int
Config::StatFSIgnore::from_string(const std::string &s_)
{
  if(s_ == "none")
    _data = Config::StatFSIgnore::ENUM::NONE;
  else if(s_ == "ro")
    _data = Config::StatFSIgnore::ENUM::RO;
  else if(s_ == "nc")
    _data = Config::StatFSIgnore::ENUM::NC;
  else
    return -EINVAL;

  return 0;
}

template<>
std::string
Config::CacheFiles::to_string() const
{
  switch(_data)
    {
    case Config::CacheFiles::ENUM::INVALID:
      break;
    case Config::CacheFiles::ENUM::LIBFUSE:
      return "libfuse";
    case Config::CacheFiles::ENUM::OFF:
      return "off";
    case Config::CacheFiles::ENUM::PARTIAL:
      return "partial";
    case Config::CacheFiles::ENUM::FULL:
      return "full";
    case Config::CacheFiles::ENUM::AUTO_FULL:
      return "auto-full";
    }

  return "invalid";
}

template<>
int
Config::CacheFiles::from_string(const std::string &s_)
{
  if(s_ == "libfuse")
    _data = Config::CacheFiles::ENUM::LIBFUSE;
  else if(s_ == "off")
    _data = Config::CacheFiles::ENUM::OFF;
  else if(s_ == "partial")
    _data = Config::CacheFiles::ENUM::PARTIAL;
  else if(s_ == "full")
    _data = Config::CacheFiles::ENUM::FULL;
  else if(s_ == "auto-full")
    _data = Config::CacheFiles::ENUM::AUTO_FULL;
  else
    return -EINVAL;

  return 0;
}

template<>
std::string
Config::XAttr::to_string() const
{
  switch(_data)
    {
    case Config::XAttr::ENUM::INVALID:
      break;
    case Config::XAttr::ENUM::PASSTHROUGH:
      return "passthrough";
    case Config::XAttr::ENUM::NOSYS:
      return "nosys";
    case Config::XAttr::ENUM::NOATTR:
      return "noattr";
    }

  return "invalid";
}

template<>
int
Config::XAttr::from_string(const std::string &s_)
{
  if(s_ == "passthrough")
    _data = Config::XAttr::ENUM::PASSTHROUGH;
  else if(s_ == "nosys")
    _data = Config::XAttr::ENUM::NOSYS;
  else if(s_ == "noattr")
    _data = Config::XAttr::ENUM::NOATTR;
  else
    return -EINVAL;

  return 0;
}

namespace str
{
  static
  int
  from(const std::string &value_,
       Branches          *branches_)
  {
    int rv;

    rv = branches_->from_string(value_);
    if(rv < 0)
      return rv;

    return 0;
  }

  static
  int
  from(const std::string &value_,
       ToFromString      *obj_)
  {
    return obj_->from_string(value_);
  }
}

#define IFRET(X,Y) if(key_ == X) return str::from(value_,&Y)

int
Config::set_raw(const std::string &key_,
                const std::string &value_)
{
  IFRET("async_read",async_read);
  IFRET("auto_cache",auto_cache);
  IFRET("branches",branches);
  IFRET("cache.attr",cache_attr);
  IFRET("cache.entry",cache_entry);
  IFRET("cache.files",cache_files);
  IFRET("cache.negative_entry",cache_negative_entry);
  IFRET("cache.open",open_cache.timeout);
  IFRET("cache.readdir",cache_readdir);
  IFRET("cache.statfs",cache_statfs);
  IFRET("cache.symlinks",cache_symlinks);
  IFRET("category.action",category.action);
  IFRET("category.create",category.create);
  IFRET("category.search",category.search);
  IFRET("direct_io",direct_io);
  IFRET("dropcacheonclose",dropcacheonclose);
  IFRET("fsname",fsname);
  IFRET("func.access",func.access);
  IFRET("func.chmod",func.chmod);
  IFRET("func.chown",func.chown);
  IFRET("func.create",func.create);
  IFRET("func.getattr",func.getattr);
  IFRET("func.getxattr",func.getxattr);
  IFRET("func.link",func.link);
  IFRET("func.listxattr",func.listxattr);
  IFRET("func.mkdir",func.mkdir);
  IFRET("func.mknod",func.mknod);
  IFRET("func.open",func.open);
  IFRET("func.readlink",func.readlink);
  IFRET("func.removexattr",func.removexattr);
  IFRET("func.rename",func.rename);
  IFRET("func.rmdir",func.rmdir);
  IFRET("func.setxattr",func.setxattr);
  IFRET("func.symlink",func.symlink);
  IFRET("func.truncate",func.truncate);
  IFRET("func.unlink",func.unlink);
  IFRET("func.utimens",func.utimens);
  IFRET("fuse_msg_size",fuse_msg_size);
  IFRET("ignorepponrename",ignorepponrename);
  IFRET("kernel_cache",kernel_cache);
  IFRET("link_cow",link_cow);
  IFRET("minfreespace",minfreespace);
  IFRET("mount",mount);
  IFRET("moveonenospc",moveonenospc);
  IFRET("nullrw",nullrw);
  IFRET("posix_acl",posix_acl);
  IFRET("security_capability",security_capability);
  IFRET("srcmounts",srcmounts);
  IFRET("statfs",statfs);
  IFRET("statfs_ignore",statfs_ignore);
  IFRET("symlinkify",symlinkify);
  IFRET("symlinkify_timeout",symlinkify_timeout);
  IFRET("threads",threads);
  IFRET("version",version);
  IFRET("xattr",xattr);

  return -ENOATTR;
}

#undef IFRET

int
Config::set(const std::string &key_,
            const std::string &value_)
{
  if(key_ == "mount")
    return -EINVAL;
  if(key_ == "fsname")
    return -EINVAL;
  if(key_ == "fuse_msg_size")
    return -EINVAL;
  if(key_ == "nullrw")
    return -EINVAL;
  if(key_ == "threads")
    return -EINVAL;

  return set_raw(key_,value_);
}
