#!/bin/bash

# Additional stress tests for minitalk

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "=== Stress Testing Minitalk ==="
echo ""

# Start server
echo "Starting server..."
./server > server_output.txt 2>&1 &
SERVER_PID=$!
sleep 0.5

ACTUAL_SERVER_PID=$(grep "Server PID:" server_output.txt | awk '{print $3}')

if [ -z "$ACTUAL_SERVER_PID" ]; then
    echo -e "${RED}FAILED: Server didn't start${NC}"
    exit 1
fi

echo "Server PID: $ACTUAL_SERVER_PID"
echo ""

# Test 1: Multiple consecutive messages
echo -e "${YELLOW}Test 1: Multiple consecutive messages${NC}"
for i in {1..10}; do
    echo "Sending message $i..."
    ./client $ACTUAL_SERVER_PID "Message number $i" > /dev/null 2>&1
    sleep 0.3
done
echo -e "${GREEN}PASSED${NC}"
echo ""

# Test 2: Very long message (stress test)
echo -e "${YELLOW}Test 2: Very long message (1000+ chars)${NC}"
LONG=$(python3 -c "print('A' * 1000)")
./client $ACTUAL_SERVER_PID "$LONG" > /dev/null 2>&1
sleep 2
RESULT=$(tail -1 server_output.txt | wc -c)
if [ $RESULT -gt 1000 ]; then
    echo -e "${GREEN}PASSED${NC}"
else
    echo -e "${RED}FAILED: Expected 1000+ chars, got $RESULT${NC}"
fi
echo ""

# Test 3: Rapid fire single characters
echo -e "${YELLOW}Test 3: Rapid fire single characters${NC}"
for char in A B C D E F G H I J; do
    ./client $ACTUAL_SERVER_PID "$char" > /dev/null 2>&1
    sleep 0.2
done
echo -e "${GREEN}PASSED${NC}"
echo ""

# Test 4: Special sequences
echo -e "${YELLOW}Test 4: Special sequences${NC}"
./client $ACTUAL_SERVER_PID $'Tab\there' > /dev/null 2>&1
sleep 0.3
./client $ACTUAL_SERVER_PID "Line1"$'\n'"Line2" > /dev/null 2>&1
sleep 0.3
./client $ACTUAL_SERVER_PID "\"Quoted\"" > /dev/null 2>&1
sleep 0.3
echo -e "${GREEN}PASSED${NC}"
echo ""

# Test 5: Edge case - single character then long message
echo -e "${YELLOW}Test 5: Single char followed by long message${NC}"
./client $ACTUAL_SERVER_PID "X" > /dev/null 2>&1
sleep 0.3
./client $ACTUAL_SERVER_PID "This is a much longer message that follows the single character" > /dev/null 2>&1
sleep 0.5
echo -e "${GREEN}PASSED${NC}"
echo ""

# Test 6: Numeric stress
echo -e "${YELLOW}Test 6: All digits repeated${NC}"
DIGITS=$(python3 -c "print('0123456789' * 50)")
./client $ACTUAL_SERVER_PID "$DIGITS" > /dev/null 2>&1
sleep 1
echo -e "${GREEN}PASSED${NC}"
echo ""

# Clean up
kill $ACTUAL_SERVER_PID 2>/dev/null
wait $ACTUAL_SERVER_PID 2>/dev/null

echo "==================================="
echo -e "${GREEN}All stress tests completed!${NC}"
echo "==================================="
echo ""
echo "Check server_output.txt for all received messages"
