file range

break range.c:23 if i % 5 == 0
commands 1
    printf "@@@ start = %d\n", start
    printf "@@@ end   = %d\n", end
    printf "@@@ step  = %d\n", step
    printf "@@@ i     = %d\n", i
    continue
end

run 1 12 1>/dev/null

quit
