# yax package
# Matthew Bertucci 11/6/2021 for v1.03

#include:texapi

\yaxversion#*
\setparameter %<<parameters> : <attributes1>=<value1> <attributes2>=<value2> ...%>#*
\setparameterlist{parameters}{keyvals}#*
\setparameterlist{parameters}[optional macro]{keyvals}#*
\copyparameter %<<parameters> : <parameter><space>%>#*
\gcopyparameter %<<parameters> : <parameter><space>%>#*
\setattribute %<<parameter> : <attribute>=<value> <space>%>#*
\esetattribute %<<parameter> : <attribute>=<value> <space>%>#*
\gsetattribute %<<parameter> : <attribute>=<value> <space>%>#*
\xsetattribute %<<parameter> : <attribute>=<value> <space>%>#*
\deleteattribute %<<parameter> : <attribute>%>#*
\gdeleteattribute %<<parameter> : <attribute>%>#*
\deleteparameter %<<parameters>%>#*
\deleteparameter %<<parameters>%>#*
\nometa%<<command>%>#*
\ifattribute %<<parameter>%>:%<<attribute>%> %<<true>%> %<<false>%>#*
\usevalue %<<parameter>%>:%<<attribute>%>#*
\usevalueor %<<parameter>%>:%<<attribute>%> %<<no value>%>#*
\usevalueand %<<parameter>%>:%<<attribute>%> %<<value exists>%> %<<no value>%>#*
\passvalue%<<code>%> %<<parameter>%>:%<<attribute>%>#*
\passvalueor%<<code>%> %<<parameter>%>:%<<attribute>%> %<<no value>%>#*
\passvalueand%<<code>%> %<<parameter>%>:%<<attribute>%> %<<value exists>%> %<<no value>%>#*
\passvaluenobraces%<<code>%> %<<parameter>%>:%<<attribute>%>#*
\passvaluenobracesor%<<code>%> %<<parameter>%>:%<<attribute>%> %<<no value>%>#*
\passvaluenobracesand%<<code>%> %<<parameter>%>:%<<attribute>%> %<<value exists>%> %<<no value>%>#*
\settovalue%<<dimen or count>%>%<<parameter>%>:%<<attribute>%>#*
\settovalueor%<<dimen or count>%>%<<parameter>%>:%<<attribute>%> %<<no value>%>#*
\settovalueand%<<dimen or count>%>%<<parameter>%>:%<<attribute>%> %<<value exists>%> %<<no value>%>#*
\settovalue%<<dimen or count>%>%<<parameter>%>:%<<attribute>%>#*
\settovalueor%<<dimen or count>%>%<<parameter>%>:%<<attribute>%> %<<no value>%>#*
\settovalueand%<<dimen or count>%>%<<parameter>%>:%<<attribute>%> %<<value exists>%> %<<no value>%>#*
\ifvalue%<<parameter>%>:%<<attribute>%>=%<<value>%> %<<true>%> %<<false>%>#*
\ifcasevalue%<<parameter>%>:%<<attribute>%>#*
\val%<<value>%> %<<code>%>#*
\elseval%<<code>%>#*
\endval#*
\parameterloop %<<list of parameters>%>:%<<code>%>#*
\newsyntax%<<syntax>%>{%<<prefix>%>}#*
\copysyntax%<<prefix1>%>%<<prefix2>%>#*
\letyaxcommand%<<command1>%>%<<command2>%>#*
\letyaxcommand{cmd}#Sd
\restrictparameter %<<list of parameters>%>:%<<list of attributes>%>#*
\restrictattribute %<<parameter>%>:%<<attribute>%> %<<list of values>%>#*
\restrictallattributes %<<attribute>%> %<<list of values>%>#*
\defparameter %<<list of parameters>%>{%<<definition>%>}#*
\executeparameter %<<parameter>%>:#*
\defactiveparameter %<<list of parameters>%>{%<<definition>%>}#*