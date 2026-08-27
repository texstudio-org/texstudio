# robotkarol.cwl — Autovervollständigung für robotkarol.sty v3.6
#include:tikz
#include:listings
#include:struktex
#include:graphicx
#include:fontspec

#keyvals:\karolsetup#c
feldbreite=%<Länge%>
bodenfarbe=%<Farbe%>
ziegelfarbe=%<Farbe%>
ziegelkoerperfarbe=%<Farbe%>
ziegelkantenfarbe=%<Farbe%>
markenfarbe=%<Farbe%>
quaderfarbe=%<Farbe%>
gitterfarbe=%<Farbe%>
hervorfarbe=%<Farbe%>
figur=#karol,emma
schrift=#karol,dokument
textschrift=%<Schriftumschaltung%>
codeschrift=%<Schriftumschaltung%>
befehlfarbe=%<Farbe%>
schleifenfarbe=%<Farbe%>
verzweigungfarbe=%<Farbe%>
bedingungfarbe=%<Farbe%>
anweisungfarbe=%<Farbe%>
kommentarfarbe=%<Farbe%>
hutfarbe=%<Farbe%>
#endkeyvals

\karolsetup{keyvals}
# Figur der Welten: karol (Vorgabe) oder emma (langes Haar + Blume)
\karolfigur{%<karol,emma%>}

# --- Schriften (v3.6) ---
# Vorgabe: Noto Sans + Hack wie in Robot Karol Online.  Mit der
# Paketoption schrift=dokument benutzt das Paket \sffamily und \ttfamily.
#keyvals:\usepackage/robotkarol#c
schrift=#karol,dokument
#endkeyvals
\karolschrift
\karolcodeschrift

#keyvals:\karolzeile#c,\karolgitter#c,\karolpaar#c
skalierung=%<Faktor%>
nummern=#true,false
hinweis=%<Text%>
titel=%<Text%>
hervorheben=%<Feldliste%>
rahmen=#true,false
hoehe=%<Ziegellagen%>
#endkeyvals

# Weltzeichen: > < ^ v Karol | . leer | Z Ziegel | 1–9 Stapel | M Marke
# Q Quader | {…} mehrere Objekte auf einem Feld, z. B. {M>} {2M} {3>}
\karolzeile{%<Weltstring%>}
\karolzeile[keyvals]{%<Weltstring%>}
\karolgitter{%<Feldanzahl%>}
\karolgitter[keyvals]{%<Feldanzahl%>}
\karolpaar{%<vorher%>}{%<nachher%>}
\karolpaar[keyvals]{%<vorher%>}{%<nachher%>}
\karolpaar[keyvals][keyvals]{%<vorher%>}{%<nachher%>}
\karollegende
\karollegendenitem{%<Weltstring%>}{%<Beschriftung%>}
\karollegendentrenner

#keyvals:\begin{karolbloecke}#c
skalierung=%<Faktor%>
#endkeyvals

\begin{karolbloecke}
\end{karolbloecke}
\begin{karolbloecke}[keyvals]
\end{karolbloecke}

\bbefehl{%<Befehl%>}
\bbefehl[%<Anzahl%>]{%<Befehl%>}
\bwiederholemal{%<Anzahl%>}{%<Blöcke%>}
\bwiederholesolange{%<Bedingung%>}{%<Blöcke%>}
\bwiederholeimmer{%<Blöcke%>}
\bwenndann{%<Bedingung%>}{%<Blöcke%>}
\bwenndannsonst{%<Bedingung%>}{%<dann-Blöcke%>}{%<sonst-Blöcke%>}
\bluecke
\bluecke[%<Breite%>]
\bbedingung{%<Bedingung%>}
# Himmelsrichtungen mit Auswahlmenü (Norden/Süden/Osten/Westen)
\bist{%<Richtung%>}
\bnichtist{%<Richtung%>}
\bkommentar{%<Text%>}
\baufruf{%<Name%>}
\baufruf[%<Anzahl%>]{%<Name%>}
\banweisung{%<Name%>}{%<Blöcke%>}
\bhauptprogramm

# --- Inline-Blöcke für den Fließtext (v3.0) ---
# Setzen genau einen Block in die laufende Zeile: Schriftgröße und
# Grundlinie wie der umgebende Text.  Schleifen und Verzweigungen
# erscheinen inline nur mit ihrem Kopf.
\ibefehl{%<Befehl%>}
\ibefehl[%<Anzahl%>]{%<Befehl%>}
\iaufruf{%<Name%>}
\iaufruf[%<Anzahl%>]{%<Name%>}
\ianweisung{%<Name%>}
\ikommentar{%<Text%>}
\ihauptprogramm
\iwiederholemal{%<Anzahl%>}
\iwiederholesolange{%<Bedingung%>}
\iwiederholeimmer
\iwenndann{%<Bedingung%>}
\isonst
\ibedingung{%<Bedingung%>}
\iist{%<Richtung%>}
\inichtist{%<Richtung%>}
\iluecke
\iluecke[%<Breite%>]

# Das optionale Argument nimmt listings-Schlüssel (\lstset), z. B.
# \begin{karolcode}[numbers=left]
\begin{karolcode}
\end{karolcode}
\begin{karolcode}[options%keyvals]
\end{karolcode}
\kb{%<Bezeichner%>}#*
\kw{%<Schlüsselwort%>}#*
\leeranweisung
\stklucke
\stklucke[%<Breite%>]

# --- karolwelt-Umgebung (v3.0) ---
\begin{karolwelt}
\end{karolwelt}
\begin{karolwelt}[keyvals]
\end{karolwelt}
#keyvals:\begin{karolwelt}
breite=%<Spalten%>
laenge=%<Zeilen%>
hoehe=%<Ziegellagen%>
ansicht=#3d,2d
skalierung=%<Faktor%>
titel=%<Text%>
hinweis=%<Text%>
#endkeyvals
\karol[keyvals]
\ziegel[keyvals]
\marke[keyvals]
\quader[keyvals]
\wand[keyvals]
#keyvals:\karol,\ziegel,\marke,\quader,\wand
x=%<Spalte%>
y=%<Zeile%>
richtung=#osten,westen,norden,sueden,rechts,links,vorn,vorne,unten,hinten,oben
anzahl=%<Ziegel%>
farbe=%<Farbe%>
bisx=%<Spalte%>
bisy=%<Zeile%>
bisX=%<Spalte%>
bisY=%<Zeile%>
#endkeyvals
