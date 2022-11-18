#!/bin/sh
root_dir=`pwd`
for f in $(find $root_dir -type f -name 'Makefile')
do
	#echo $f
	d=$(dirname $f)
	b=$(basename $d)
	printf "\nInside dir: $b\n"
	cd $d
	make clean
	cd ../
done

