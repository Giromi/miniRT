#! bin/bash

ERROR=( "map/no_file.rt"						\
		"map/empty_file.rt"						\
		"map/error_no_ambient.rt"				\
		"map/error_two_ambient.rt"				\
		"map/error_no_light.rt"					\
		"map/error_no_camera.rt"				\
		"map/error_wrong_ambient_format.rt"		\
		"map/error_wrong_ambient_format2.rt"	\
		)

my_minirt()
{
	echo
	echo "CASE : $i"
	echo ---------------------------
	echo
	./miniRT "$i"
	echo
	echo ---------------------------
	echo
}

for i in "${ERROR[@]}"
do
	my_minirt
done
