#ifndef STRING_H_RAMSEY_14
#define STRING_H_RAMSEY_14

#include <string>
#include <iostream>


namespace Ramsey {
class String {
 private:
    std::string _internal;    
 public:
    //constructors
    std::string str() const { return _internal; }
    String() { };// default is fine
    String(const char *);
    String(const std::string s);
    //    String(const String &s); //default is fine // copy constructor
    String(const int i);
    String(const float f);
    String(const double d);
    String(const bool b);
    String(const char c);
    String(const unsigned int);
    String(const unsigned long);
    String(const unsigned long long);
    String(const long);
    String(const long long);


    //~String() { }; //empty destructor - _internal is destructed on its own
    //String& operator=(const String&rhs); //copyassignment - not special nothing dynamic

    String operator+(const String &rhs);

    String operator+=(const String&rhs);

    String operator*(const int &a);

    String operator*=(const int &a);
    

    friend std::ostream& operator<< (std::ostream &out, const String &rhs); //overload output.
    friend std::istream& operator>> (std::istream &in, String &rhs); //eventually overload input?


    //wrapper functions to expose base string functionality - much is implemented here but not everything just yet.
    //in addition, most of this is currently untested and needs virgous runs to test debugging
    
    char& operator[] (size_t pos)  { return _internal[pos]; }
    const char & operator[] (size_t pos) const  { return _internal[pos]; }

    inline bool operator==(const String&rhs) { return _internal == rhs._internal; }


    String& append(const String& rhs) { _internal.append(rhs.str()); return *this; }
    String& assign(const String& rhs) { _internal.assign(rhs.str()); return *this; }
    size_t size() const { return _internal.size(); }
    size_t length() const { return _internal.length(); }
    void resize(size_t n ) { _internal.resize(n); }
    void resize(size_t n, char c) { _internal.resize(n,c); }
    size_t capacity() const { return _internal.capacity(); }
    void clear() { _internal.clear(); }
    bool empty() const { return _internal.empty(); }
    char& at(size_t n) { return _internal.at(n); } 
    const char& at(size_t n) const { return _internal.at(n); } 
    //string manipulators/operations
    const char *c_str() { return _internal.c_str(); } //these functions are way safer in C++11
    const char *data() { return _internal.data(); } 
    size_t copy(char* s, size_t len, size_t pos = 0) const { return _internal.copy(s,len,pos); }


    size_t find(const String& str, size_t pos = 0 ) const { return _internal.find(str.str(), pos); }
    //really need to do some testing on find/rfind and these funtions to see if only one the above function is needed
    size_t find(const std::string&str, size_t pos = 0) const { return _internal.find(str, pos); }
    size_t find(const char* s, size_t pos = 0) const { return _internal.find(s,pos); }
    size_t find(const char* s, size_t pos, size_t n) const { return _internal.find(s,pos,n); }
    size_t find(char c, size_t pos) { return _internal.find(c,pos); }

    size_t rfind(const String& str, size_t pos = 0 ) const { return _internal.rfind(str.str(), pos); }
    size_t rfind(const std::string&str, size_t pos = 0) const { return _internal.rfind(str, pos); }
    size_t rfind(const char* s, size_t pos = 0) const { return _internal.rfind(s,pos); }
    size_t rfind(const char* s, size_t pos, size_t n) const { return _internal.rfind(s,pos,n); }
    size_t rfind(char c, size_t pos) { return _internal.rfind(c,pos); }


    size_t find_first_of(const String& str, size_t pos = 0 ) const { return _internal.find_first_of(str.str(), pos); }
    size_t find_first_of(const std::string&str, size_t pos = 0) const { return _internal.find_first_of(str, pos); }
    size_t find_first_of(const char* s, size_t pos = 0) const { return _internal.find_first_of(s,pos); }
    size_t find_first_of(const char* s, size_t pos, size_t n) const { return _internal.find_first_of(s,pos,n); }
    size_t find_first_of(char c, size_t pos) { return _internal.find_first_of(c,pos); }

    size_t find_last_of(const String& str, size_t pos = 0 ) const { return _internal.find_last_of(str.str(), pos); }
    size_t find_last_of(const std::string&str, size_t pos = 0) const { return _internal.find_last_of(str, pos); }
    size_t find_last_of(const char* s, size_t pos = 0) const { return _internal.find_last_of(s,pos); }
    size_t find_last_of(const char* s, size_t pos, size_t n) const { return _internal.find_last_of(s,pos,n); }
    size_t find_last_of(char c, size_t pos) { return _internal.find_last_of(c,pos); }

    size_t find_first_not_of(const String& str, size_t pos = 0 ) const { return _internal.find_first_not_of(str.str(), pos); }
    size_t find_first_not_of(const std::string&str, size_t pos = 0) const { return _internal.find_first_not_of(str, pos); }
    size_t find_first_not_of(const char* s, size_t pos = 0) const { return _internal.find_first_not_of(s,pos); }
    size_t find_first_not_of(const char* s, size_t pos, size_t n) const { return _internal.find_first_not_of(s,pos,n); }
    size_t find_first_not_of(char c, size_t pos) { return _internal.find_first_not_of(c,pos); }

    size_t find_last_not_of(const String& str, size_t pos = 0 ) const { return _internal.find_last_not_of(str.str(), pos); }
    size_t find_last_not_of(const std::string&str, size_t pos = 0) const { return _internal.find_last_not_of(str, pos); }
    size_t find_last_not_of(const char* s, size_t pos = 0) const { return _internal.find_last_not_of(s,pos); }
    size_t find_last_not_of(const char* s, size_t pos, size_t n) const { return _internal.find_last_not_of(s,pos,n); }
    size_t find_last_not_of(char c, size_t pos) { return _internal.find_last_not_of(c,pos); }

    //-1 here is for npos - the largest possible value for len. This is a bit of a hack
    String substr(size_t pos = 0, size_t len = std::string::npos) const { std::string s = _internal.substr(pos,len); return String(s); }

    int compare(const String& str) const { return _internal.compare(str.str()); }
    int compare(size_t pos, size_t len, const String &str) const { return _internal.compare(pos,len,str.str()); }
    int compare(size_t pos, size_t len, const String &str, size_t subpos, size_t sublen) const { return _internal.compare(pos,len,str.str(),subpos,sublen); }

  };


}


#endif
