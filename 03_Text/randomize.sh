#!/bin/dash

delay=${1:-0.05}

# initialisation
tput setab 0

lines_count=$(tput lines)

char_coord=$(mktemp)
shuf_idx=$(mktemp)

inp=$(cat)

char_y=0

# write characters and their coodrinates in `char_coord` file
echo "$inp" | while IFS= read -r string; do
	char_x=0

	echo "$string" | sed 's/./&\n/g' | while IFS= read -r char; do
		if [ -n "$char" ] && [ "$char" != " " ]; then
            echo "$char:$char_x:$char_y" >> "$char_coord"
        fi

        char_x=$((char_x + 1))
	done

	char_y=$(($char_y + 1))
done

# enumerate all characters and write their shuffled indexes in `shuf_idx` file
char_count=$(wc -l < "$char_coord")
seq 0 $((char_count - 1)) | shuf > "$shuf_idx"

# animation
tput clear
tput setab 0
tput setaf 7
tput home

while IFS= read -r idx; do
    line_num=$((idx + 1))
    line=$(sed -n "${line_num}p" "$char_coord" 2>/dev/null)

    if [ -n "$line" ]; then
        char=$(echo "$line" | cut -d: -f1)
        x=$(echo "$line" | cut -d: -f2)
        y=$(echo "$line" | cut -d: -f3)

        tput cup $y $x
        sleep $delay
        printf "%s" "$char"
    fi
done < "$shuf_idx"

tput cup $lines_count 0
tput sgr0

rm -f "$char_coord" "$shuf_idx"
