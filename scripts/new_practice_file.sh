#!/bin/bash
#new を作って、サンプルを消去
dir_name="$(cd $(dirname $0); pwd)"
dir_name=${dir_name//scripts}

cp $dir_name/field/practice/template.cc $dir_name/field/practice/new.cc
if [ -e $dir_name/tmp/_new ]; then 
    rm $dir_name/tmp/_new
fi
