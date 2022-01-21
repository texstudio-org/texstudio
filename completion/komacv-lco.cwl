# komacv-lco package
# Matthew Bertucci 1/20/2022 for v0.9b

#include:etoolbox
#include:fontawesome
#include:marvosym
#include:scrkbase

\newkomavar{name}
\newkomavar[description]{name}
\newkomavar*{name}
\newkomavar*[description]{name}
\setkomavar{name%keyvals}{content}
\setkomavar{name%keyvals}[description]{content}
\setkomavar*{name%keyvals}{content}
\usekomavar{name%keyvals}
\usekomavar[command]{name%keyvals}
\usekomavar*{name%keyvals}
\usekomavar*[command]{name%keyvals}
\ifkomavarempty{name%keyvals}{true code}{false code}
\ifkomavarempty*{name%keyvals}{true code}{false code}
\ifkomavar{name%keyvals}{true code}{false code}
\ifkomavar*{name%keyvals}{true code}{false code}
\LoadLetterOption{file}#i
\LoadLetterOptions{file list}#i
\ifkomavarenabled{name%keyvals}{true code}{false code}
\emaillink{URL}#U
\emaillink[link text]{URL}#U
\httplink{URL}#U
\httplink[link text]{URL}#U
\httpslink{URL}#U
\httpslink[link text]{URL}#U

#keyvals:\setkomavar#c,\setkomavar*#c,\usekomavar#c,\usekomavar*#c,\ifkomavarempty#c,\ifkomavarempty*#c,\ifkomavar#c,\ifkomavar*#c,\ifkomavarenabled#c
fromacadtitle
fromaddress
fromaddresscity
fromaddressstreet
fromemail
fromextrainfo
fromfax
fromfacebook
fromfamilyname
fromfirstname
fromgithub
fromlinkedin
frommobilephone
fromname
fromphone
fromtwitter
fromurl
location
place
#endkeyvals