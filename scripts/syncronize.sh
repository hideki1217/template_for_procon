#!/bin/bash
#テンプレートを同期
dir_name="$(cd $(dirname $0); pwd)"
dir_name=${dir_name//scripts}

cp $dir_name/field/practice/template.cc $dir_name/field/template/A.cc
cp $dir_name/field/practice/template.cc $dir_name/field/template/B.cc
cp $dir_name/field/practice/template.cc $dir_name/field/template/C.cc
cp $dir_name/field/practice/template.cc $dir_name/field/template/D.cc
cp $dir_name/field/practice/template.cc $dir_name/field/template/E.cc
cp $dir_name/field/practice/template.cc $dir_name/field/template/F.cc
