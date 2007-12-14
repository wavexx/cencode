/*
 * cencode - A simple file-to-Cstring encoder
 * Copyright(c) 2007 of wave++ (Yuri D'Elia)
 * Distributed under Revised BSD license without ANY warranty.
 */

#ifndef cencode_h
#define cencode_h

// system headers
#include <ctype.h>
#include <stdio.h>


static inline int
iscesc(int c)
{
  switch(c)
  {
  case '\a': return 'a';
  case '\b': return 'b';
  case '\e': return 'e';
  case '\f': return 'f';
  case '\n': return 'n';
  case '\r': return 'r';
  case '\t': return 't';
  case '\v': return 'v';
  case '\\': return '\\';
  case '\"': return '"';
  }

  return 0;
}


static inline int
isctrig(int prev, int cur)
{
  return (prev == '?' && cur == '?');
}


static inline int
escapeChar(char buf[8], int prev, int cur)
{
  if(int esc = iscesc(cur))
  {
    buf[0] = '\\';
    buf[1] = esc;
    return 2;
  }
  if(!isprint(cur))
    return sprintf(buf, "\\%o", cur);

  int len = 0;
  if(prev != EOF && (isctrig(prev, cur) ||
	  (!iscesc(prev) && !isprint(prev) && isdigit(cur))))
  {
    buf[0] = '"';
    buf[1] = '"';
    len = 2;
  }

  buf[len++] = cur;
  return len;
}

#endif
