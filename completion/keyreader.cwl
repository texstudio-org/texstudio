# keyreader package
# Matthew Bertucci 2022/06/24 for v0.5b

#include:xkeyval
#include:pdftexcmds

\krddefinekeys{kfamily}{keylist%plain}#*
\krddefinekeys{kfamily}[mprefix]{keylist%plain}#*
\krddefinekeys[kprefix]{kfamily}{keylist%plain}#*
\krddefinekeys[kprefix]{kfamily}[mprefix]{keylist%plain}#*
\krddefinekeys*{kfamily}{keylist%plain}#*
\krddefinekeys*{kfamily}[mprefix]{keylist%plain}#*
\krddefinekeys*[kprefix]{kfamily}{keylist%plain}#*
\krddefinekeys*[kprefix]{kfamily}[mprefix]{keylist%plain}#*
\krdsetkeys{families}{keyvals}#*
\krdsetkeys[kprefix]{families}[ignored keys]{keyvals}#*
\krdsetkeys*{families}{keyvals}#*
\krdsetkeys*[kprefix]{families}[ignored keys]{keyvals}#*
\krdsetkeys+{families}{keyvals}#*
\krdsetkeys+[kprefix]{families}[ignored keys]{keyvals}#*
\krdsetkeys*+{families}{keyvals}#*
\krdsetkeys*+[kprefix]{families}[ignored keys]{keyvals}#*
\krdsetrmkeys{families}#*
\krdsetrmkeys[prefix]{families}[ignored keys]#*
\krdsetrmkeys*{families}#*
\krdsetrmkeys*[prefix]{families}[ignored keys]#*
\krdsetrmkeys+{families}#*
\krdsetrmkeys+[prefix]{families}[ignored keys]#*
\krdsetrmkeys*+{families}#*
\krdsetrmkeys*+[prefix]{families}[ignored keys]#*
\krdpresetkeys{family}{head keys}#*
\krdpresetkeys[prefix]{family}{head keys}#*
\krdpostsetkeys{family}{tail keys}#*
\krdpostsetkeys[prefix]{family}{tail keys}#*
\krddisablekeys{family}{keys}#*
\krddisablekeys[prefix]{family}{keys}#*
\krdDeclareOption{key%plain}{function}#*
\krdDeclareOption[prefix]<family>{key%plain}[default]{function}#*
\krdDeclareOption*{function}#*
\krdExecuteOptions{keyvals}#*
\krdExecuteOptions[prefix]<families>[ignored keys]{keyvals}#*
\krdProcessOptions#*
\krdProcessOptions[prefix]<families>[ignored keys]#*
\krdProcessOptions*#*
\krdProcessOptions*[prefix]<families>[ignored keys]#*
\savevaluekeys{family}{keyvals}#*
\savevaluekeys[prefix]{family}{keyvals}#*

# not documented
\ifkrdindef#S
\krdaddtolist#S
\krdAfterEndPackage{code}#S
\krdaftergr{arg1}#S
\krdcommaloop#S
\krdcsvnormalize#S
\krdecommaloop#S
\krdexpandarg{arg1}{arg2}#S
\krdexpandargonce{arg1}{arg2}#S
\krdexpanded{arg1}#S
\krdexpandonce{arg1}#S
\krdexpandsecond{arg1}{arg2}#S
\krdexpandsecondonce{arg1}{arg2}#S
\krdfor{arg1}#S
\krdforeach#S
\krdgaddtolist#S
\krdifblank{arg1}#S
\krdifbool{arg1}#S
\krdifbraced{arg1}#S
\krdifcond{arg1}#S
\krdifcsdef{arg1}#S
\krdifdef{arg1}#S
\krdifescaped{arg1}#S
\krdifledbyspace{arg1}#S
\krdifstrcmp{arg1}{arg2}#S
\krdifswitch{arg1}#S
\krdifx{arg1}{arg2}#S
\krdindeffalse#S
\krdindeftrue#S
\krdkvnormalize{arg1}#S
\krdncsname#S
\krdnewlet{cmd}#Sd 
\krdnoexpandcs{arg1}#S
\krdorder#S
\krdoxdetok{arg1}#S
\krdstripouterbraces{arg1}{arg2}#S
\krdswap{arg1}{arg2}#S
\krdtrimspace{arg1}#S
\krdusearg{arg1}{arg2}#S
\krduserinput#S
\krdzapspace{arg1}#S
\stopforeach#S
