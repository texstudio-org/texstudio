# GNU extensions for sed are not supported; on Linux, --posix mimics this behaviour
TXS_VERSION=$(sed -ne 's/^#define TXSVERSION "\(.*\)".*$/\1/p' ../src/utilsVersion.h)
echo "TXS_VERSION = ${TXS_VERSION}"

GIT_HASH=$(git show --no-patch --pretty="%h")
echo "GIT_HASH = ${GIT_HASH}"

GIT_DATE=$(git show --no-patch --pretty="%ci")
echo "GIT_DATE = ${GIT_DATE}"

GIT_VERSION=$(git describe --tags --abbrev=0 --always)
echo "GIT_VERSION = ${GIT_VERSION}"

DATE_HASH=$(date -u +"%Y%m%d%H%M")
echo "DATE_HASH = ${DATE_HASH}"
OS_NAME=$(uname)
echo ${OS_NAME}
if [ "${OS_NAME}" = "Darwin" ]; then
	RELEASE_DATE=$(date -ujf "%Y-%m-%d %H:%M:%S %z" "${GIT_DATE}" "+%Y-%m-%dT%H:%M:%S%z")
else
	RELEASE_DATE=$(date -u +"%Y-%m-%dT%H:%M:%S%z" --date="${GIT_DATE}")
fi
echo "RELEASE_DATE = ${RELEASE_DATE}"

VERSION_NAME="${TXS_VERSION}-${DATE_HASH}-git_${GIT_HASH}"
echo "VERSION_NAME = ${VERSION_NAME}"
