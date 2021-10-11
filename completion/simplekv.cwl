# simplekv package
# Matthew Bertucci 10/11/2021 for v0.2

\setKV[keygroup name]{key1=val1,key2=val2,...}#*
\setKVdefault[keygroup name]{key1=val1,key2=val2,...}#*
\useKV[keygroup]{key%plain}#*
\restoreKV[keygroup]#*
\useKVdefault[keygroup]#*
\ifboolKV[keygroup]{key%plain}{true code}{false code}#*
\showKV[keygroup]{key%plain}#*
\defKV[keygroup]{key1=code1,key2=code2,...}#*
\testboolKV{arg}{true code}{false code}#*
\skvname#S
\skvver#S
\skvdate#S