/*
 * Implementation of a class to get keyboard layout information and change layouts
 *
 * Copyright (C) 2008 by Jay Bromley <jbromley@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 */

#include "XKeyboard.h"
#include "X11Exception.h"
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cstring>


#define assertMsg(expression,msg)                       \
                                                        \
    if(!(expression)){                                  \
                                                        \
        std::ostringstream stream;                      \
                                                        \
        stream << __FILE__    << " : "                  \
               << __LINE__    << " : "                  \
               << "XKeyboard" << " : "                  \
               << msg << "[ " << #expression << "]";    \
                                                        \
        throw std::runtime_error(stream.str());         \
    }


namespace kb {

XKeyboard::XKeyboard()
  : _display(0), _deviceId(XkbUseCoreKbd)
{

  XkbIgnoreExtension(False);

  char* displayName = strdup("");
  int eventCode;
  int errorReturn;
  int major = XkbMajorVersion;
  int minor = XkbMinorVersion;
  int reasonReturn;
  _display = XkbOpenDisplay(displayName, &eventCode, &errorReturn, &major,
      &minor, &reasonReturn);
  switch (reasonReturn) {
    case XkbOD_BadLibraryVersion:
      throw X11Exception("Bad XKB library version.");
      break;
    case XkbOD_ConnectionRefused:
      throw X11Exception("Connection to X server refused.");
      break;
    case XkbOD_BadServerVersion:
      throw X11Exception("Bad X11 server version.");
      break;
    case XkbOD_NonXkbServer:
      throw X11Exception("XKB not present.");
      break;
    case XkbOD_Success:
      break;
  }

  _kbdDescPtr = XkbAllocKeyboard();
  if (_kbdDescPtr == NULL) {
    XCloseDisplay(_display);
    throw X11Exception("Failed to get keyboard description.");
  }

  _kbdDescPtr->dpy = _display;
  if (_deviceId != XkbUseCoreKbd) {
    _kbdDescPtr->device_spec = _deviceId;
  }
}

XKeyboard::~XKeyboard()
{
  if(_kbdDescPtr!=NULL)
    XkbFreeKeyboard(_kbdDescPtr, 0, True);

  XCloseDisplay(_display);
}

std::string XKeyboard::get_kb_string()
{
  XkbGetControls(_display, XkbAllControlsMask, _kbdDescPtr);
  XkbGetNames(_display, XkbSymbolsNameMask, _kbdDescPtr);

  Atom symNameAtom = _kbdDescPtr->names->symbols;

  assertMsg(symNameAtom != None,"Symbol Name is not present");

  char* kbsC = XGetAtomName(_display, symNameAtom);

  assertMsg(kbsC,"Symbol Name pointer is invalid");

  std::string kbs(kbsC);
  XFree(kbsC);

  assertMsg(!kbs.empty(),"Symbol Name is an empty string");

  return kbs;

  /*     StringVector symNames; */
  /*     XkbSymbolParser symParser; */
  /*     symParser.parse(symName, symNames); */
  /*     return symNames; */
}

void XKeyboard::wait_event()
{
  assertMsg(_display != 0,"Display is not present");

  Bool bret = XkbSelectEventDetails(_display, XkbUseCoreKbd, 
      XkbStateNotify, XkbAllStateComponentsMask, XkbGroupStateMask);

  assertMsg(bret==True, "Failed to select event details");

  XEvent event;
  int iret = XNextEvent(_display, &event);

  assertMsg(iret==0,"Failed to retrieve next event with " << iret);
}

void XKeyboard::set_group(int groupNum)
{
  Bool result = XkbLockGroup(_display, _deviceId, groupNum);
  assertMsg(result == True,"Failed to set group to: " << groupNum);
}

int XKeyboard::get_group() const
{
  XkbStateRec xkbState;
  XkbGetState(_display, _deviceId, &xkbState);
  return static_cast<int>(xkbState.group);
}

// returns true if symbol is ok
bool filter(const string_vector& nonsyms, const std::string& symbol)
{
  if(symbol.empty())
    return false;

  // Filter out all prohibited words
  string_vector::const_iterator r = find(nonsyms.begin(), nonsyms.end(), symbol);
  if(r != nonsyms.end())
    return false;

  // Filter out all numbers groups started with number
  if(isdigit(symbol[0]))
    return false;

  return true;
}

string_vector parse1(const std::string& symbols, const string_vector& nonsyms)
{
  bool inSymbol = false;
  std::string sym;
  string_vector symlist;

  for (size_t i = 0; i < symbols.size(); i++) {
    char ch = symbols[i];
    if (ch == '+') {
      if (inSymbol && !sym.empty() && filter(nonsyms, sym)) {
        symlist.push_back(sym);
      }
      inSymbol = true;
      sym.clear();
    }
    else if (inSymbol && ch == '(') {
      inSymbol = false;
    }
    else if (inSymbol && (isalpha(static_cast<int>(ch)) || ch == '_')) {
      sym.append(1, ch);
    }
    else {
      if (inSymbol && !sym.empty() && filter(nonsyms, sym)) {
        symlist.push_back(sym);
      }
      inSymbol = false;
    }
  }

  if (inSymbol && !sym.empty() && filter(nonsyms, sym)) {
    symlist.push_back(sym);
  }

  return symlist;
}

void safe_push_back(string_vector& v, std::string s, std::string /*note*/)
{
  if(s.empty()) return;
#ifdef NOT_TEXSTUDIO
  if(!note.empty()) {
    s += "(" + note + ")";
  }
#endif
  v.push_back(s);
}

bool goodchar(char ch)
{
  return (isdigit(ch) || isalpha(static_cast<int>(ch)) || ch == '_' || ch == '-');
}

string_vector parse2(const std::string& symbols, const string_vector& nonsyms)
{
  enum{ok,skip,broken} state = ok;
  int paren = 0;
  std::string sym;
  // Words between optional '(' ')'
  std::string note;
  string_vector symlist;

  for (size_t i = 0; i < symbols.size(); i++) {
	char ch = symbols[i];

    if (ch == '+') {
      if (state != broken && paren == 0 && filter(nonsyms, sym)) {
        safe_push_back(symlist, sym, note);
      }
      state = ok;
      paren = 0;
      sym.clear();
      note.clear();
    }
    else if (state == ok && ch == '(') {
      paren++;
    }
    else if (state == ok && ch == ')') {
      paren--;
    }
    else if (state == ok && ch == ':') {
      state = skip;
    }
    else if (state == ok && goodchar(ch)) {
      if (paren == 0)
        sym.append(1, ch);
      else
        note.append(1, ch);
    }
    else if(state == ok) {
      state = broken;
    }
  }

  if (state != broken && paren == 0 && filter(nonsyms, sym)) {
    safe_push_back(symlist, sym, note);
  }

  return symlist;
}

string_vector parse3(const std::string& symbols, const string_vector& nonsyms)
{
  enum{ok,skip,broken} state = ok;
  int paren = 0;
  std::string sym;
  // Words between optional '(' ')'
  std::string note;
  string_vector symlist;

  for (size_t i = 0; i < symbols.size(); i++) {
    char ch = symbols[i];

    if (ch == '+' || ch == '_') {
      if(paren == 0) {
        if (state != broken && paren == 0 && filter(nonsyms, sym)) {
          safe_push_back(symlist, sym, note);
        }
        state = ok;
        sym.clear();
        note.clear();
      }
    }
    else if (state == ok && ch == '(') {
      paren++;
    }
    else if (state == ok && ch == ')') {
      paren--;
    }
    else if (state == ok && ch == ':') {
      state = skip;
    }
    else if (state == ok && goodchar(ch)) {
      if (paren == 0)
        sym.append(1, ch);
      else
        note.append(1, ch);
    }
    else if(state == ok) {
      state = broken;
    }
  }

  if (state != broken && paren == 0 && filter(nonsyms, sym)) {
    safe_push_back(symlist, sym, note);
  }

  return symlist;
}

}

#undef assertMsg

