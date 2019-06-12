#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <typeinfo>

using namespace std;

int main(int argc, char const *argv[]) {

  const char * path = "test_file.txt";
  string s;
  ifstream f(path,ios::in);
  // std::cout << typeid(f).name()<< '\n';

  if (! f.is_open())
    {
    cout << "open file failed! the programmer will exit!" << endl;
    exit(-1);
    }
    //
    while (getline(f, s))
    {
    // use line
     cout << s.c_str() << "\n";


    const char *d = ",";
    char *p;
    char *a = &s[0u];
    // strcpy(a, s.c_str());
    // char *cstr = str.c_str();/
    // cout << a << endl;
    p = strtok(a, d);

    // cout << a << endl;

    while(p){
      // _content.push_back(p);
      std::cout << p << '\n';
      p=strtok(NULL,d);
    }
  }


  return 0;
}
