file range

set $counter = 0

break range.c:23 if ++$counter >= 28 && $counter <= 35
commands 1
    printf "@@@ start = %d\n", start
    printf "@@@ end   = %d\n", end
    printf "@@@ step  = %d\n", step
    printf "@@@ i     = %d\n", i
    continue
end

run -100 100 3 1>/dev/null

quit
