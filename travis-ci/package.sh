#!/usr/bin/env sh

# Exit on errors
set -e

cd "${TRAVIS_BUILD_DIR}"

. travis-ci/defs.sh

if [ "${TRAVIS_PULL_REQUEST}" != "false" ]; then
	print_warning "Not packaging pull-requests for deployment"
	exit 0
fi

print_headline "Packaging ${QT} for deployment"

POPPLERDATA_VERSION="0.4.8"
POPPLERDATA_SUBDIR="poppler-data-${POPPLERDATA_VERSION}"
POPPLERDATA_FILE="poppler-data-${POPPLERDATA_VERSION}.tar.gz"
POPPLERDATA_URL="https://poppler.freedesktop.org/${POPPLERDATA_FILE}"
POPPLERDATA_SHA256="1096a18161f263cccdc6d8a2eb5548c41ff8fcf9a3609243f1b6296abdf72872"

# Gather information

# GNU extensions for sed are not supported; on Linux, --posix mimicks this behaviour
TXS_VERSION=$(sed -ne 's/^#define TXSVERSION "\(.*\)".*$/\1/p' utilsVersion.h)
echo "TXS_VERSION = ${TXS_VERSION}"

GIT_HASH=$(git --git-dir=".git" show --no-patch --pretty="%h")
echo "GIT_HASH = ${GIT_HASH}"

GIT_DATE=$(git --git-dir=".git" show --no-patch --pretty="%ci")
echo "GIT_DATE = ${GIT_DATE}"

DATE_HASH=$(date -u +"%Y%m%d%H%M")
echo "DATE_HASH = ${DATE_HASH}"

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
	RELEASE_DATE=$(date -u +"%Y-%m-%dT%H:%M:%S%z" --date="${GIT_DATE}")
elif [ "${TRAVIS_OS_NAME}" = "osx" ]; then
	RELEASE_DATE=$(date -ujf "%Y-%m-%d %H:%M:%S %z" "${GIT_DATE}" "+%Y-%m-%dT%H:%M:%S%z")
else
	print_error "Unsupported operating system '${TRAVIS_OS_NAME}'"
	exit 1
fi
echo "RELEASE_DATE = ${RELEASE_DATE}"

VERSION_NAME="${TXS_VERSION}-${DATE_HASH}-git_${GIT_HASH}"
echo "VERSION_NAME = ${VERSION_NAME}"


if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
	print_info "Running macdeployqt"
	/usr/local/opt/qt/bin/macdeployqt texstudio.app -dmg	

	print_info "Renaming .dmg"
	mv "${TRAVIS_BUILD_DIR}/"texstudio.dmg "${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_OS_NAME}-${VERSION_NAME}.dmg"

	print_info "Preparing bintray.json"
	cat > "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json" <<EOF
	{
		"package": {
			"name": "texstudio",
			"repo": "texstudio",
			"subject": "sunderme"
		},

		"version": {
			"name": "${VERSION_NAME}",
			"released": "${RELEASE_DATE}",
			"gpgSign": false
		},
		"files":
		[
			{"includePattern": "${TRAVIS_BUILD_DIR}/texstudio-${TRAVIS_OS_NAME}-${VERSION_NAME}.dmg", "uploadPattern": "texstudio-${TRAVIS_OS_NAME}-${VERSION_NAME}.dmg"}
		],
		"publish": true
	}
EOF

cat "${TRAVIS_BUILD_DIR}/travis-ci/bintray.json"
fi

cd "${TRAVIS_BUILD_DIR}"

print_info "Deployment preparation successful"
