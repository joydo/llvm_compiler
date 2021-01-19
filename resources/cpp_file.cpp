#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <utility>

class JdongVisitor
{
public:
  JdongVisitor(int age):age(age){}
  JdongVisitor(const JdongVisitor&other):JdongVisitor(other.age){}
  JdongVisitor(JdongVisitor&&other):age(std::exchange(other.age,0)){}
  JdongVisitor& operator=(const JdongVisitor&other)
  {
    return *this = JdongVisitor(other);
  }
  JdongVisitor& operator=(JdongVisitor&& other)
  {
    std::swap(age,other.age);
    return *this;
  }
private:
  int age;
}

int main(int argc,char* argv[])
{
  return 0;
}
