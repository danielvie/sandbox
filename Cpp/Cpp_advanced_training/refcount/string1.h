#ifndef STRRING1_HXX
#define STRRING1_HXX

#include "MyStr.h"

using namespace std;

class StrCnt
{
private:
    friend class String;

    friend ostream &operator<<(ostream &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator==(const String &, const String &);
    
    MyStr s;
    int count;

    StrCnt(const char *str = "") : s(str), count(1) {}
};


class String
{
    friend ostream &operator<<(ostream &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator==(const String &, const String &);

public:
    String(const char *s = "") { impl = new StrCnt(s); }

    String(const String& s) : impl(s.impl) { impl->count++; }

    ~String() { if (--impl->count == 0) delete impl; }

    String& operator=(const String &s)
    {
        if (this != &s) 
        {
            if (--impl->count == 0)
                delete impl;
            impl = s.impl;
            s.impl->count++; // increment other parties use count
        }
        return *this;
    }

    String& operator=(const char *s)
    {
        if (--impl->count == 0) delete impl; 
        impl = new StrCnt(s);
    }

private:
    StrCnt *impl;
};

inline std::istream& operator>>(std::istream& is, String& tekst)
{
    std::string s;
    is >> s;
    tekst = s.c_str();
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const String &tekst)
{
    os << tekst.impl->s;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const String& tekst)
{
    os << tekst.impl->s;
    return os;
}

inline bool operator>(const String& l, const String& r)
{
    return l.impl->s > r.impl->s;
}

inline bool operator<(const String& l, const String& r)
{
    return l.impl->s < r.impl->s;
}

inline bool operator==(const String& l, const String& r)
{
    return l.impl->s == r.impl->s;
}

#endif