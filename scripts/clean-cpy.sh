find ./ -name "* - コピー" -print0 | \
while read -r -d '' file
do newname=$(echo $file | sed 's/ - コピー//g')
    mv "$file" "$newname"; 
done
