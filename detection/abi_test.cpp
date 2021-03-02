#include <string>

int main(int argc, char* argv[])
{
  return &std::basic_string<char>::data == &std::__cxx11::basic_string<char>::data ? 0 : 1;
}
