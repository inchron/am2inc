#!/usr/bin/env bash

DIR="$(dirname $0)"
DSTFILE="$DIR/gitversion.h"
TMPFILE="$DSTFILE.tmp"


function moveIfChangedOrRemove() {
    local SRC="$1"
    local DST="$2"

    if [[ ! -e "$DST" ]] || ! diff -q "$SRC" "$DST" 2>&1 > /dev/null
    then
        mv "$SRC" "$DST"
    else
        rm "$SRC"
    fi
}


{
    printf "#pragma once\n"
    printf "#define GIT_VERSION \"%s\"\n" "$(git -C "$DIR" describe --always --tags)"
} > "$TMPFILE"

moveIfChangedOrRemove "$TMPFILE" "$DSTFILE"

