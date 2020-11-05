#!/bin/bash
#コンテスト用にテンプレートをコピー
dir_name="$(cd $(dirname $0); pwd)"
dir_name=${dir_name///scripts}

mkdir $dir_name/field/contests/${1}

cp $dir_name/field/practice/template.cc $dir_name/field/contests/${1}/A.cc
cp $dir_name/field/practice/template.cc $dir_name/field/contests/${1}/B.cc
cp $dir_name/field/practice/template.cc $dir_name/field/contests/${1}/C.cc
cp $dir_name/field/practice/template.cc $dir_name/field/contests/${1}/D.cc
cp $dir_name/field/practice/template.cc $dir_name/field/contests/${1}/E.cc
cp $dir_name/field/practice/template.cc $dir_name/field/contests/${1}/F.cc