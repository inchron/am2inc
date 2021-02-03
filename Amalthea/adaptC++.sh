#!/bin/sh
#
# Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
#
# SPDX-License-Identifier: EPL-2.0
#
set -e

acore=$1
if [ ! -f "$acore" ] ; then
    echo "$acore not found, exiting with error"
    exit 2
fi

bcore=$(mktemp)
cp $acore $bcore

# dos2unix $bcore
sed -i 's/\r//' $bcore

sed -i 's|ecore.ecore#//|http://www.eclipse.org/emf/2002/Ecore#//|g' $bcore

sed -i 's/"0f"/"0.f"/g' $bcore

sed -i 's/eLiterals name="default"/eLiterals name="_default_" literal="default"/g' $bcore
sed -i 's/eLiterals name="explicit"/eLiterals name="_explicit_" literal="explicit"/g' $bcore


set +e
# copy-if-changed
diff -q "$acore" "$bcore" 2>&1 > /dev/null
status=$?

if [ "$status" -eq 1 ] ; then
    echo "Adapted $acore"
    cp $bcore $acore
fi

rm -f $bcore

if [ "$status" -eq 2 ] ; then
    exit 2
fi

exit 0
