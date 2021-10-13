#!/usr/bin/env bash

. .github/scripts/get-version.sh > /dev/null
RELEASE_OPENING_TAG="<release date=\"$RELEASE_DATE\" version=\"$TXS_VERSION\">"
DESCRIPTION_OPENING_TAG="<description>"
LIST_OPENING_TAG="<ul>"
CHANGELOG=$(sed '/^[[:space:]]*$/d' utilities/manual/CHANGELOG.txt | tail -n +2 | awk 'NR==2,/TeXstudio/' | head -n -1 | sed -e 's|-|<li>|g' | sed -e 's|$|</li>|g' | sed -e 's|<li>\s\{1,\}|<li>|g' )
CHANGELOG="${CHANGELOG//
/\\n}"
LIST_CLOSING_TAG="</ul>"
DESCRIPTION_CLOSING_TAG="</description>"
RELEASE_CLOSING_TAG="</release>"

sed -i '/releases/,/releases/{//!d}' utilities/texstudio.metainfo.xml

if [ "$CHANGELOG" != "<li></li>" ]; then
	RELEASE_TAG=$RELEASE_OPENING_TAG$DESCRIPTION_OPENING_TAG$LIST_OPENING_TAG$CHANGELOG$LIST_CLOSING_TAG$DESCRIPTION_CLOSING_TAG$RELEASE_CLOSING_TAG
else
	RELEASE_TAG=$RELEASE_OPENING_TAG$RELEASE_CLOSING_TAG
fi

sed -e "s|<releases>|<releases>$RELEASE_TAG|g" -i utilities/texstudio.metainfo.xml
echo $RELEASE_TAG
cp utilities/texstudio.metainfo.xml utilities/texstudio.metainfo.xml.bak
xmllint --format utilities/texstudio.metainfo.xml.bak > utilities/texstudio.metainfo.xml && \
rm utilities/texstudio.metainfo.xml.bak
appstream-util validate-relax utilities/texstudio.metainfo.xml
