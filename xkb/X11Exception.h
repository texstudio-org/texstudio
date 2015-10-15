// X11Exception.h
// C++ exception that wraps X11 errors.
// Copyright (C) 2008 Jay Bromley <jbromley@gmail.com>
// 
// $Id: X11Exception.h 26 2008-04-09 08:47:11Z jay $

#ifndef X11EXCEPTION_H_FE39A315_6827_447B_AE62_5FA2C3FD391F
#define X11EXCEPTION_H_FE39A315_6827_447B_AE62_5FA2C3FD391F

#include <exception>

class X11Exception : public std::exception
{
public:
    X11Exception() : _reason("unknown") {}
    X11Exception(const std::string& what) : _reason(what) {}
    virtual ~X11Exception() throw () {};
    virtual const char* what() const throw () { return _reason.c_str(); }

private:
    std::string _reason;
};

#endif // GAMEEXCEPTION_H_FE39A315_6827_447B_AE62_5FA2C3FD391F

// Local Variables:
// mode: c++
// End:

