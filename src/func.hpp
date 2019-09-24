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

#pragma once

#include "policy.hpp"
#include "tofrom_string.hpp"

#include <string>

class Func : public ToFromString
{
public:
  Func(const Policy   &policy_,
       const Category &category_)
    : policy(&policy_),
      category(category_)
  {
  }

public:
  int from_string(const std::string &s);
  std::string to_string() const;

public:
  const Policy   *policy;
  const Category &category;
};

class FuncAccess : public Func
{
public:
  FuncAccess()
    : Func(Policy::ff,
           Category::search)
  {
  }
};

class FuncChmod : public Func
{
public:
  FuncChmod()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncChown : public Func
{
public:
  FuncChown()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncCreate : public Func
{
public:
  FuncCreate()
    : Func(Policy::epmfs,
           Category::create)
  {
  }
};

class FuncGetAttr : public Func
{
public:
  FuncGetAttr()
    : Func(Policy::ff,
           Category::search)
  {
  }
};

class FuncGetXAttr : public Func
{
public:
  FuncGetXAttr()
    : Func(Policy::ff,
           Category::search)
  {
  }
};

class FuncLink : public Func
{
public:
  FuncLink()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncListXAttr : public Func
{
public:
  FuncListXAttr()
    : Func(Policy::ff,
           Category::search)
  {
  }
};

class FuncMkdir : public Func
{
public:
  FuncMkdir()
    : Func(Policy::epmfs,
           Category::create)
  {
  }
};

class FuncMknod : public Func
{
public:
  FuncMknod()
    : Func(Policy::epmfs,
           Category::create)
  {
  }
};

class FuncOpen : public Func
{
public:
  FuncOpen()
    : Func(Policy::ff,
           Category::search)
  {
  }
};

class FuncReadlink : public Func
{
public:
  FuncReadlink()
    : Func(Policy::ff,
           Category::search)
  {
  }
};

class FuncRemoveXAttr : public Func
{
public:
  FuncRemoveXAttr()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncRename : public Func
{
public:
  FuncRename()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncRmdir : public Func
{
public:
  FuncRmdir()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncSetXAttr : public Func
{
public:
  FuncSetXAttr()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncSymlink : public Func
{
public:
  FuncSymlink()
    : Func(Policy::epmfs,
           Category::create)
  {
  }
};

class FuncTruncate : public Func
{
public:
  FuncTruncate()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncUnlink : public Func
{
public:
  FuncUnlink()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

class FuncUtimens : public Func
{
public:
  FuncUtimens()
    : Func(Policy::epall,
           Category::action)
  {
  }
};

namespace std
{
  static
  inline
  std::string
  to_string(const Func &func_)
  {
    return func_.to_string();
  }
}
