# xt_capts package
# Matthew Bertucci 2022/07/19 for v1.1d

\DeclareCaption{caption%cmd}{language}{definition}#d
\DeclareCaption{caption%cmd}{language}[args]{definition}#d
\DeclareCaption{caption%cmd}{language}[args][default]{definition}#d
\ProvideCaption{caption%cmd}{language}{definition}#d
\ProvideCaption{caption%cmd}{language}[args]{definition}#d
\ProvideCaption{caption%cmd}{language}[args][default]{definition}#d

\UseCaption{language}{caption}

\DeclareCaptionDefault{caption%cmd}{definition}#d
\DeclareCaptionDefault{caption%cmd}[args]{definition}#d
\DeclareCaptionDefault{caption%cmd}[args][default]{definition}#d
\ProvideCaptionDefault{caption%cmd}{definition}#d
\ProvideCaptionDefault{caption%cmd}[args]{definition}#d
\ProvideCaptionDefault{caption%cmd}[args][default]{definition}#d

\BeforeAtBeginDocument{code}#*
\AfterAtBeginDocument{code}#*
\BeforeAtEndDocument{code}#*