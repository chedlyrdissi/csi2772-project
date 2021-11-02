for i in 'Blue' 'Chili' 'Stink' 'Green' 'Soy' 'Black' 'Red' 'Garden'
do
	echo "class $i {" > "$i.h"
	echo "" >> "$i.h"
	echo "}" >> "$i.h"
	echo "" >> "$i.h"
	echo "#pragma once" >> "$i.h"
	echo "" >> "$i.h"
done