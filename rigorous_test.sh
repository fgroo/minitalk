#!/bin/bash

# Rigorous testing script for minitalk

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0

# Function to run a test
run_test() {
    local test_name="$1"
    local message="$2"
    local expected="$3"
    
    echo -e "${YELLOW}Testing: $test_name${NC}"
    
    # Start server in background
    ./server > server_output.txt 2>&1 &
    SERVER_PID=$!
    sleep 0.5
    
    # Get server PID from output
    ACTUAL_SERVER_PID=$(grep "Server PID:" server_output.txt | awk '{print $3}')
    
    if [ -z "$ACTUAL_SERVER_PID" ]; then
        echo -e "${RED}FAILED: Server didn't start properly${NC}"
        kill $SERVER_PID 2>/dev/null
        ((FAILED++))
        return
    fi
    
    # Run client and capture output
    ./client $ACTUAL_SERVER_PID "$message" > client_output.txt 2>&1
    sleep 0.5
    
    # Check server output
    RESULT=$(grep -v "Server PID:" server_output.txt | grep -v "Server is ready")
    
    # Kill server
    kill $ACTUAL_SERVER_PID 2>/dev/null
    wait $ACTUAL_SERVER_PID 2>/dev/null
    
    if [ "$RESULT" == "$expected" ]; then
        echo -e "${GREEN}PASSED${NC}"
        ((PASSED++))
    else
        echo -e "${RED}FAILED${NC}"
        echo "Expected: '$expected'"
        echo "Got:      '$RESULT'"
        ((FAILED++))
    fi
    
    echo ""
}

echo "=== Starting Rigorous Minitalk Tests ==="
echo ""

# Test 1: Single character
run_test "Single character" "a" "a"

# Test 2: Short message
run_test "Short message" "Hello" "Hello"

# Test 3: Message with spaces
run_test "Message with spaces" "Hello World" "Hello World"

# Test 4: Numbers
run_test "Numbers" "123456789" "123456789"

# Test 5: Special characters
run_test "Special characters" "!@#$%^&*()" "!@#$%^&*()"

# Test 6: Longer message
run_test "Longer message" "The quick brown fox jumps over the lazy dog" "The quick brown fox jumps over the lazy dog"

# Test 7: Unicode/Extended ASCII
run_test "Extended ASCII" "café" "café"

# Test 8: Newline character
run_test "Newline" $'Hello\nWorld' $'Hello\nWorld'

# Test 9: Empty string (edge case)
# Note: Client rejects empty strings, so we skip this

# Test 10: Very long message
LONG_MSG="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris."
run_test "Long message" "$LONG_MSG" "$LONG_MSG"

# Test 11: Single character multiple times
for i in {1..5}; do
    run_test "Test $i: Single char 'X'" "X" "X"
done

# Test 12: All printable ASCII
ASCII_MSG=$(printf '%s' {!..~})
run_test "All printable ASCII" "$ASCII_MSG" "$ASCII_MSG"

# Clean up
rm -f server_output.txt client_output.txt

echo "==================================="
echo -e "Tests Passed: ${GREEN}$PASSED${NC}"
echo -e "Tests Failed: ${RED}$FAILED${NC}"
echo "==================================="

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
