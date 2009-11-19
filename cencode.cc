/*
 * cencode - A simple file-to-Cstring encoder - utility
 * Copyright(c) 2007-2008 of wave++ (Yuri D'Elia)
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
#include <string.h>


struct EncodeParams
{
  const char* sym;
  const char* qualifiers;
  unsigned columns;
  bool packed;
};


void
encode(istream& fd, const EncodeParams& params)
{
  int len;
  unsigned col = 0;
  int prev = EOF;
  char buf[8];

  if(params.sym)
  {
    if(params.qualifiers)
    {
      cout << params.qualifiers;
      col = strlen(params.qualifiers);
    }

    cout << " char ";
    col += 6;

    cout << params.sym;
    col += strlen(params.sym);

    if(params.packed)
    {
      cout << "[]=\"";
      col += 4;
    }
    else
    {
      cout << "[] =\n  \"";
      col = 3;
    }
  }

  for(int cur = fd.get(); fd; cur = fd.get())
  {
    len = escapeChar(buf, prev, cur);

    if(params.sym && col + len + 2 > params.columns)
    {
      len = escapeChar(buf, EOF, cur);

      if(params.packed)
      {
	cout << "\"\n\"";
	col = 1;
      }
      else
      {
	cout << "\"\n  \"";
	col = 3;
      }
    }

    cout.write(buf, len);
    col += len;
    prev = cur;
  }
  if(!fd && !fd.eof())
    throw 0;

  if(params.sym)
  {
    if(col + 3 > params.columns)
      cout << "\"\n;\n";
    else
      cout << "\";\n";
  }
}


int
usage(const char* prg)
{
  cerr << prg << " usage: " << prg << " [-hrp] [-c cols] [-q qualifiers] [-s sym] [file ...]\n";
  return EXIT_FAILURE;
}


int
main(int argc, char* argv[]) try
{
  const char* columns = NULL;
  EncodeParams params;
  params.sym = NULL;
  params.qualifiers = "const";
  params.packed = true;

  // args
  int arg;
  while((arg = getopt(argc, argv, "hs:c:rpq:")) != -1)
    switch(arg)
    {
    case 's':
      params.sym = optarg;
      break;

    case 'c':
      columns = optarg;
      break;

    case 'r':
      params.packed = false;
      break;

    case 'p':
      params.packed = true;
      break;

    case 'q':
      params.qualifiers = optarg;
      break;

    case 'h':
    default:
      return usage(argv[0]);
    }

  if(columns)
    params.columns = strtoul(columns, NULL, 0);
  else
    params.columns = (params.packed? 255: 79);

  // encode
  const char* file = argv[optind++];
  if(!file)
    encode(cin, params);
  else do
  {
    ifstream fd(file);
    if(!fd) throw 0;
    encode(fd, params);
    if(params.sym) break;
  }
  while(file = argv[optind++]);

  return EXIT_SUCCESS;
}
catch(int)
{
  perror(argv[0]);
  return EXIT_FAILURE;
}
