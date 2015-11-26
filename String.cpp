#include "String.h"
#include <sstream>


namespace Ramsey {

  //String::String() { }



  // String::String(const String &s) {  _internal = s._internal; }

String::String(const std::string s) {
  _internal = s;
}

  String::String(const char *c) {
    while(*c != '\0') {
      _internal = _internal + *c;
      c++;
    }
  }

  String::String(const unsigned int i) {
    std::stringstream tempStream;
    tempStream << i;
    _internal = tempStream.str();
  }  


  String::String(const long i) {
    std::stringstream tempStream;
    tempStream << i;
    _internal = tempStream.str();
  }  

  String::String(const long long i) {
    std::stringstream tempStream;
    tempStream << i;
    _internal = tempStream.str();
  }  

  String::String(const unsigned long i) {
    std::stringstream tempStream;
    tempStream << i;
    _internal = tempStream.str();
  }  

  String::String(const unsigned long long i) {
    std::stringstream tempStream;
    tempStream << i;
    _internal = tempStream.str();
  }  

String::String(const int i) {
  std::stringstream tempStream;
  tempStream << i;
  _internal = tempStream.str();
}


String::String(const float f) {
  std::stringstream tempStream;
  tempStream << f;
  _internal = tempStream.str();
}

String::String(const double d) {
  std::stringstream tempStream;
  tempStream << d;
  _internal = tempStream.str();
}

String::String(const bool b) {
  std::stringstream tempStream;
  tempStream << b;
  _internal = tempStream.str();
}

  String::String(const char c) {
    _internal = c;
  }


String String::operator+(const String &rhs)  {
  std::string result = _internal + rhs._internal;
  return result;
}

  String  String::operator+=(const String&rhs) {
      _internal = _internal + rhs._internal;
      return *this;
  }

  String String::operator*(const int &a) {
    std::string result = _internal;
    std::string orig = _internal;
    for(int i = 1; i < a; i++) {
      result += orig;
    }
    return result;
  }
  
  String String::operator*=(const int &a) {
    std::string orig = _internal;
    for(int i = 1; i < a; i++) { //already have 1, only need a-1 more
      _internal += orig;
    }
    return *this;
  }





std::ostream& operator<<(std::ostream &out, const String &rhs) {
  out << rhs.str();
  return out;
}


std::istream& operator>>(std::istream &in, String &rhs) {
    std::string s;
    in >> s;
    rhs = s;
    return in;
  }


} //end namespace
