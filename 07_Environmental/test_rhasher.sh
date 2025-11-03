#!/bin/bash
echo "Running basic tests..."

actual=$(echo 'MD5 "myawesometest"' | ./rhasher 2>/dev/null | tr -d ' \n')
expected=$(echo -n "myawesometest" | md5sum | cut -d' ' -f1)

if [ "$actual" = "$expected" ]; then
    echo "Test passed"
else
    echo "Test failed"
    echo "Expected: $expected"
    echo "Got: $actual"
fi

echo "abracadabra test" | ./rhasher 2>&1 | grep -q "Error"
if [ $? -eq 0 ]; then
    echo "Error test passed"
else
    echo "Error test failed"
fi
