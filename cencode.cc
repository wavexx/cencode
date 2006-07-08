/*
 * cencode - A simple file-to-Cstring encoder
 * Copyright(c) 2006 of wave++ (Yuri D'Elia)
 * Distributed under GNU LGPL without ANY warranty.
 */

// system headers
#include <iostream>
using std::cout;
using std::cerr;
using std::cin;

#include <fstream>
using std::ifstream;
using std::istream;

// c system headers
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


int
iscesc(int c)
{
  switch(c)
  {
  case '\a': return 'a';
  case '\b': return 'b';
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


int
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
  if(prev != istream::traits_type::eof() && !iscesc(prev)
      && !isprint(prev) && isdigit(cur))
  {
    buf[0] = '"';
    buf[1] = '"';
    len = 2;
  }

  buf[len++] = cur;
  return len;
}


void
encode(istream& fd, const char* sym)
{
  cout << "const char " << sym << "[] =\n  \"";
  int len;
  int col = 3;
  int prev = istream::traits_type::eof();
  char buf[8];

  for(int cur = fd.get(); fd; cur = fd.get())
  {
    len = escapeChar(buf, prev, cur);

    if(col + len > 76)
    {
      len = escapeChar(buf, istream::traits_type::eof(), cur);
      cout << "\"\n  \"";
      col = 3;
    }

    cout.write(buf, len);
    col += len;
    prev = cur;
  }
  if(!fd && !fd.eof())
    throw 0;

  cout << "\";\n";
}


int
main(int argc, char* argv[]) try
{
  if(argc != 2 && argc != 3)
  {
    cerr << argv[0] << " usage: " << argv[0] << " symbol [file]\n";
    return EXIT_FAILURE;
  }

  const char* sym = argv[1];
  const char* file = argv[2];

  if(!file)
    encode(cin, sym);
  else
  {
    ifstream fd(file);
    if(!fd) throw 0;
    encode(fd, sym);
  }

  return EXIT_SUCCESS;
}
catch(int)
{
  perror(argv[0]);
  return EXIT_FAILURE;
}
