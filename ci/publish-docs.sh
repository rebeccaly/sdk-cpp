#!/bin/bash
#
# Copyright (C) 2015 Virgil Security Inc.
#
# Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     (1) Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#     (2) Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#
#     (3) Neither the name of the copyright holder nor the names of its
#     contributors may be used to endorse or promote products derived from
#     this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

set -ev

if [ "${PUBLISH_DOCS}" != "ON" ] || if [ "${TRAVIS_BRANCH}" != "${DOC_BRANCH}" ]; then exit; fi

# Settings
REPO_PATH=git@github.com:VirgilSecurity/virgil-cpp.git
HTML_PATH_DST="${TRAVIS_BUILD_DIR}/${BUILD_DIR_NAME}/docs/html"
COMMIT_USER="Travis CI documentation builder."
COMMIT_EMAIL="sergey.seroshtan@gmail.com"
CHANGESET=$(git rev-parse --verify HEAD)

# Get a clean version of the HTML documentation repo.
rm -rf ${HTML_PATH_DST}
mkdir -p ${HTML_PATH_DST}
git clone -b gh-pages "${REPO_PATH}" --single-branch ${HTML_PATH_DST}

# Generate the HTML documentation.
cd "${TRAVIS_BUILD_DIR}/${BUILD_DIR_NAME}" && make doc-sdk-public-keys doc-sdk-private-keys
cd -

# Define SDK versions
PUBLIC_KEYS_SDK_VERSION=`cat ${TRAVIS_BUILD_DIR}/virgil.sdk.keys/VERSION | awk -F"." '{ printf "v%d.%d",$1,$2 }'`
PRIVATE_KEYS_SDK_VERSION=`cat ${TRAVIS_BUILD_DIR}/virgil.sdk.private-keys/VERSION | awk -F"." '{ printf "v%d.%d",$1,$2 }'`

PUBLIC_KEYS_SDK_HTML_PATH_DST="${HTML_PATH_DST}/sdk-keys/${PUBLIC_KEYS_SDK_VERSION}"
PRIVATE_KEYS_SDK_HTML_PATH_DST="${HTML_PATH_DST}/sdk-private-keys/${PRIVATE_KEYS_SDK_VERSION}"

# Prepare destination folders
rm -fr "${PUBLIC_KEYS_SDK_HTML_PATH_DST}" && mkdir -p "${PUBLIC_KEYS_SDK_HTML_PATH_DST}"
rm -fr "${PRIVATE_KEYS_SDK_HTML_PATH_DST}" && mkdir -p "${PRIVATE_KEYS_SDK_HTML_PATH_DST}"

# Copy new documentation
cp -af "${TRAVIS_BUILD_DIR}/virgil.sdk.keys/docs/html/." "${PUBLIC_KEYS_SDK_HTML_PATH_DST}"
cp -af "${TRAVIS_BUILD_DIR}/virgil.sdk.private-keys/docs/html/." "${PRIVATE_KEYS_SDK_HTML_PATH_DST}"

# Fix source file names
function fix_html_source_file_names {
    cd "${1}"
    for f in _*.html; do
        old_name=$f
        new_name=${f/${f:0:1}/}
        mv $old_name $new_name
        sed -i"" "s/$old_name/$new_name/g" *.html
    done
    cd -
}

fix_html_source_file_names "${PUBLIC_KEYS_SDK_HTML_PATH_DST}"
fix_html_source_file_names "${PRIVATE_KEYS_SDK_HTML_PATH_DST}"

# Generate root HTML file
function get_dir_names {
    local DIRS=`find -type d -maxdepth 1 -name "$1" "$2"`
    local DIR_NAMES=()
    for dir in ${DIRS}; do
        DIR_NAMES+=("${dir#${1}/}")
    done
    echo ${DIR_NAMES[*]}
}

cat >"${HTML_PATH_DST}/index.html" <<EOL
<!DOCTYPE HTML>
<html>
   <head>
        <meta charset="utf-8">
        <title>Virgil SDK Documentation</title>
   </head>
   <body>
        Virgil Public Keys SDK
        <ul>
EOL

for dir in `get_dir_names "${PUBLIC_KEYS_SDK_HTML_PATH_DST}/.." "v*"`; do
    echo "<li><p><a href=\"sdk-keys/${dir}/index.html\">${dir}</a></p></li>" >> "${HTML_PATH_DST}/index.html"
done

cat >>"${HTML_PATH_DST}/index.html" <<EOL
        </ul>
        Virgil Private Keys SDK
        <ul>
EOL

for dir in `get_dir_names "${PRIVATE_KEYS_SDK_HTML_PATH_DST}/.." "v*"`; do
    echo "<li><p><a href=\"sdk-private-keys/${dir}/index.html\">${dir}</a></p></li>" >> "${HTML_PATH_DST}/index.html"
done

cat >>"${HTML_PATH_DST}/index.html" <<EOL
        </ul>
   </body>
</html>
EOL

# Create and commit the documentation repo.
cd ${HTML_PATH_DST}
git add .
git config user.name "${COMMIT_USER}"
git config user.email "${COMMIT_EMAIL}"
git commit -m "Automated documentation build for changeset ${CHANGESET}."
git push origin gh-pages
cd -
