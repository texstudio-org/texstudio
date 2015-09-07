// xkeyboard.h
// Interface for a class to get keyboard layout information and change layouts
// Copyright (C) 2008 by Jay Bromley <jbromley@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// $Id: XKeyboard.h 29 2008-04-09 21:37:44Z jay $

#ifndef XKEYBOARD_H_1C79861A_49B3_4A95_88D6_455C22FEB222
#define XKEYBOARD_H_1C79861A_49B3_4A95_88D6_455C22FEB222

#include <vector>
#include <string>
#include <iostream>
#include <X11/Xlib.h>


typedef std::vector<std::string> StringVector;


// XKeyboard -----------------------------------------------------------

class XKeyboard
{
public:
    XKeyboard();
    ~XKeyboard();
    int groupCount() const;
    StringVector groupNames() const;
    StringVector groupSymbols() const;
    int currentGroupNum() const;
    std::string currentGroupName() const;
    std::string currentGroupSymbol() const;
    bool setGroupByNum(int groupNum);
    bool changeGroup(int increment);

    //friend std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);

private:
    Bool initializeXkb();
    std::string getSymbolNameByResNum(int groupResNum);
    int groupNumResToXkb(int groupNumRes);
    std::string getGroupNameByResNum(int groupResNum);
    int groupLookup(int srcValue, StringVector fromText, StringVector toText, int count);
    void accomodateGroupXkb();

    Display* _display;
    int _groupCount;
    StringVector _groupNames;
    StringVector _symbolNames;
    int _currentGroupNum;

    int _deviceId;
    int _baseEventCode;
    int _baseErrorCode;
};


// XkbSymbolParser -----------------------------------------------------

class XkbSymbolParser
{
public:
    typedef std::vector<std::string>::iterator StringVectorIter;

    XkbSymbolParser();
    ~XkbSymbolParser();
    void parse(const std::string& symbols, std::vector<std::string>& symbolList);
	
private:
    bool isXkbLayoutSymbol(const std::string& symbol);

    StringVector _nonSymbols;
};


// Helper functions ----------------------------------------------------

int compareNoCase(const std::string& s1, const std::string& s2);
// std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);
// std::ostream& operator<<(std::ostream& os, const StringVector& v);

#endif // XKEYBOARD_H_1C79861A_49B3_4A95_88D6_455C22FEB222

// Local Variables:
// mode: c++
// End:
