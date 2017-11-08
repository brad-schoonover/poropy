#include <ctime>
#include <iostream>

#include "poropy_config.h"

void print_welcome();

int main(int argc, char **argv)
{
  print_welcome();
  return 0;
}

//----------------------------------------------------------------------------//
void print_welcome()
{
  using std::cout;
  using std::endl;
  std::time_t t;
  std::time(&t);
  cout << endl << endl;
  cout << "  ___  ___  ___  ___  ___       " << endl;
  cout << " |   )|   )|   )|   )|   )\\   ) " << endl;
  cout << " |__/ |__/ |    |__/ |__/  \\_/  " << endl;
  cout << " |                   |      /   " << endl;
  cout << "                                " << endl;
  cout << " poropy -- executable"    << endl;
  cout << " Copyright (C) Jeremy Roberts 2012-2015" << endl;
  cout << " Built on: " << POROPY_COMPILED_M << "/"
                        << POROPY_COMPILED_D << "/"
                        << POROPY_COMPILED_Y << endl;
  cout << " Git SHA1: " << POROPY_GIT_SHA1   << endl;
  cout << "   Run on: " << std::ctime(&t) << endl << endl;
}
