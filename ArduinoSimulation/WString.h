#pragma once


#include <string>
#include <sstream>

class String : public std::string
{
public:
    String() : std::string()
    {

    }

    String(const char * str) : std::string(str)
    {

    }

    String(const std::string & str) : std::string(str)
    {

    }


    bool startsWith(const String & str) const
    {
        return find(str) == 0;
    }

    bool endsWith(const String & str) const
    {
        std::string::size_type i = find(str);
        return i != std::string::npos && i + str.length() == length();
    }

    void trim()
    {
    }

    bool equals(const String & other) const
    {
        return other == *this;
    }

    String substring(size_t offset)
    {
        return String(substr(offset).c_str());
    }

    explicit String(char c);
    explicit String(unsigned char, unsigned char base = 10);
    explicit String(int i, unsigned char base = 10)
    {
        std::stringstream ss;
        ss << i;
        *this = ss.str();
    }
    explicit String(unsigned int u, unsigned char base = 10)
    {
        std::stringstream ss;
        ss << u;
        *this = ss.str();
    }
    explicit String(long, unsigned char base = 10);
    explicit String(unsigned long, unsigned char base = 10);
    explicit String(float, unsigned char decimalPlaces = 2);
    explicit String(double, unsigned char decimalPlaces = 2);

    unsigned char concat(const String &str)
    {
        this->append(str);
        return 1;
    }
    unsigned char concat(const char *cstr)
    {
        this->append(cstr);
        return 1;
    }
    unsigned char concat(char c);
    unsigned char concat(unsigned char c);
    unsigned char concat(int num);
    unsigned char concat(unsigned int num);
    unsigned char concat(long num);
    unsigned char concat(unsigned long num);
    unsigned char concat(float num);
    unsigned char concat(double num);

    // if there's not enough memory for the concatenated value, the string
    // will be left unchanged (but this isn't signalled in any way)
    String & operator += (const String &rhs) { concat(rhs); return (*this); }
    String & operator += (const char *cstr) { concat(cstr); return (*this); }
    String & operator += (char c) { concat(c); return (*this); }
    String & operator += (unsigned char num) { concat(num); return (*this); }
    String & operator += (int num) { concat(num); return (*this); }
    String & operator += (unsigned int num) { concat(num); return (*this); }
    String & operator += (long num) { concat(num); return (*this); }
    String & operator += (unsigned long num) { concat(num); return (*this); }
    String & operator += (float num) { concat(num); return (*this); }
    String & operator += (double num) { concat(num); return (*this); }

};

#define F(str)  String(str)