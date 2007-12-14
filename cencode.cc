/*
 * cencode - A simple file-to-Cstring encoder - utility
 * Copyright(c) 2007 of wave++ (Yuri D'Elia)
 * Distributed under Revised BSD license without ANY warranty.
 */

// local headers
#include "cencode.h"

// system headers
#include <iostream>
using std::cout;
using std::cerr;
using std::cin;

#include <fstream>
using std::ifstream;
using std::istream;

// c system headers
#include <unistd.h>


void
encode(istream& fd, const char* sym)
{
  int len;
  int col = 3;
  int prev = EOF;
  char buf[8];

  if(sym)
    cout << "const char " << sym << "[] =\n  \"";

  for(int cur = fd.get(); fd; cur = fd.get())
  {
    len = escapeChar(buf, prev, cur);

    if(sym && col + len > 77)
    {
      len = escapeChar(buf, EOF, cur);
      cout << "\"\n  \"";
      col = 3;
    }

    cout.write(buf, len);
    col += len;
    prev = cur;
  }
  if(!fd && !fd.eof())
    throw 0;

  if(sym)
    cout << "\";\n";
}


int
usage(const char* prg)
{
  cerr << prg << " usage: " << prg << " [-s symbol] [file ...]\n";
  return EXIT_FAILURE;
}


int
main(int argc, char* argv[]) try
{
  const char* sym = NULL;

  // args
  int arg;
  while((arg = getopt(argc, argv, "hs:")) != -1)
    switch(arg)
    {
    case 's':
      sym = optarg;
      break;

    case 'h':
    default:
      return usage(argv[0]);
    }

  // encode
  const char* file = argv[optind++];
  if(!file)
    encode(cin, sym);
  else do
  {
    ifstream fd(file);
    if(!fd) throw 0;
    encode(fd, sym);
  }
  while(file = argv[optind++]);

  return EXIT_SUCCESS;
}
catch(int)
{
  perror(argv[0]);
  return EXIT_FAILURE;
}
