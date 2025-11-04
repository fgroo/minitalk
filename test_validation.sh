#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test counters
TESTS_PASSED=0
TESTS_FAILED=0
TESTS_TOTAL=0

# Log file for detailed output
LOG_FILE="test_validation_log.txt"
echo "=== MINITALK VALIDATION TEST LOG ===" > $LOG_FILE
echo "Date: $(date)" >> $LOG_FILE
echo "" >> $LOG_FILE

# Helper functions
print_test() {
    TESTS_TOTAL=$((TESTS_TOTAL + 1))
    printf "${BLUE}[TEST $TESTS_TOTAL]${NC} %s\n" "$1"
    echo "[TEST $TESTS_TOTAL] $1" >> $LOG_FILE
}

log_detail() {
    echo "  DETAIL: $1" >> $LOG_FILE
    echo "  $1"
}

pass_test() {
    TESTS_PASSED=$((TESTS_PASSED + 1))
    printf "${GREEN}✓ PASS${NC}: %s\n" "$1"
    echo "  RESULT: PASS - $1" >> $LOG_FILE
}

fail_test() {
    TESTS_FAILED=$((TESTS_FAILED + 1))
    printf "${RED}✗ FAIL${NC}: %s\n" "$1"
    echo "  RESULT: FAIL - $1" >> $LOG_FILE
    if [[ ! -z "$2" ]]; then
        printf "  Details: %s\n" "$2"
        echo "  DETAILS: $2" >> $LOG_FILE
    fi
}

print_section() {
    printf "\n${YELLOW}========================================${NC}\n"
    printf "${YELLOW}%s${NC}\n" "$1"
    printf "${YELLOW}========================================${NC}\n\n"
    echo "" >> $LOG_FILE
    echo "=== $1 ===" >> $LOG_FILE
}

# Start server with detailed logging
print_section "STARTING SERVER WITH VALIDATION"
./server > /tmp/server_validation.log 2>&1 &
SERVER_PID=$!
sleep 1
echo "Server PID: $SERVER_PID" | tee -a $LOG_FILE

# Verify server started
if ! ps -p $SERVER_PID > /dev/null; then
    echo -e "${RED}FATAL: Server failed to start${NC}"
    echo "FATAL: Server failed to start" >> $LOG_FILE
    exit 1
fi

echo "Server is running" | tee -a $LOG_FILE
sleep 1

# ============================================
# TEST 1: Basic Message Transmission with Validation
# ============================================
print_section "TEST 1: BASIC MESSAGE TRANSMISSION WITH VALIDATION"

print_test "Simple ASCII message - VALIDATING SERVER OUTPUT"
truncate -s 0 /tmp/server_validation.log  # Clear log before test
OUTPUT=$(./client $SERVER_PID "Hello World" 2>&1)
CLIENT_EXIT_CODE=$?
sleep 0.5
SERVER_LOG=$(cat /tmp/server_validation.log | tr -d '\0')
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Client output: $OUTPUT"
log_detail "Server received: '$SERVER_LOG'"
if [[ "$SERVER_LOG" == "Hello World" ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Simple ASCII message with server validation"
else
    fail_test "Simple ASCII message" "Expected 'Hello World', got '$SERVER_LOG', exit code: $CLIENT_EXIT_CODE"
fi

print_test "Single character - VALIDATING SERVER OUTPUT"
truncate -s 0 /tmp/server_validation.log  # Clear log before test
OUTPUT=$(./client $SERVER_PID "A" 2>&1)
CLIENT_EXIT_CODE=$?
sleep 0.5
SERVER_LOG=$(cat /tmp/server_validation.log | tr -d '\0')
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Server received: '$SERVER_LOG'"
if [[ "$SERVER_LOG" == "A" ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Single character with server validation"
else
    fail_test "Single character" "Expected 'A', got '$SERVER_LOG', exit code: $CLIENT_EXIT_CODE"
fi

print_test "Numbers only - VALIDATING SERVER OUTPUT"
truncate -s 0 /tmp/server_validation.log  # Clear log before test
OUTPUT=$(./client $SERVER_PID "1234567890" 2>&1)
CLIENT_EXIT_CODE=$?
sleep 0.5
SERVER_LOG=$(cat /tmp/server_validation.log | tr -d '\0')
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Server received: '$SERVER_LOG'"
if [[ "$SERVER_LOG" == "1234567890" ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Numbers only with server validation"
else
    fail_test "Numbers only" "Expected '1234567890', got '$SERVER_LOG', exit code: $CLIENT_EXIT_CODE"
fi

# ============================================
# TEST 2: Unicode Support with Validation
# ============================================
print_section "TEST 2: UNICODE SUPPORT WITH VALIDATION"

print_test "Emojis 😀🎉 - VALIDATING SERVER OUTPUT"
truncate -s 0 /tmp/server_validation.log  # Clear log before test
OUTPUT=$(./client $SERVER_PID "😀🎉" 2>&1)
CLIENT_EXIT_CODE=$?
sleep 0.5
SERVER_LOG=$(cat /tmp/server_validation.log | tr -d '\0')
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Server received: '$SERVER_LOG'"
if [[ "$SERVER_LOG" == "😀🎉" ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Emojis with server validation"
else
    fail_test "Emojis" "Expected '😀🎉', got '$SERVER_LOG', exit code: $CLIENT_EXIT_CODE"
fi

print_test "Mixed text and Unicode - VALIDATING SERVER OUTPUT"
truncate -s 0 /tmp/server_validation.log  # Clear log before test
OUTPUT=$(./client $SERVER_PID "Hello 🚀 World" 2>&1)
CLIENT_EXIT_CODE=$?
sleep 0.5
SERVER_LOG=$(cat /tmp/server_validation.log | tr -d '\0')
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Server received: '$SERVER_LOG'"
if [[ "$SERVER_LOG" == "Hello 🚀 World" ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Mixed text and Unicode with server validation"
else
    fail_test "Mixed text and Unicode" "Expected 'Hello 🚀 World', got '$SERVER_LOG', exit code: $CLIENT_EXIT_CODE"
fi

# ============================================
# TEST 3: Error Handling - CRITICAL VALIDATION
# ============================================
print_section "TEST 3: ERROR HANDLING - CRITICAL VALIDATION"

print_test "Missing arguments - SHOULD SHOW USAGE"
echo "Testing: ./client (no arguments)" >> $LOG_FILE
timeout 5 ./client 2>&1 > /tmp/client_no_args.log 2>&1
CLIENT_EXIT_CODE=$?
OUTPUT=$(cat /tmp/client_no_args.log)
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Client output: '$OUTPUT'"
if [[ $CLIENT_EXIT_CODE -ne 0 ]] && [[ "$OUTPUT" == *"Usage"* ]]; then
    pass_test "Missing arguments shows usage"
else
    fail_test "Missing arguments" "Expected usage message and non-zero exit, got exit code: $CLIENT_EXIT_CODE, output: '$OUTPUT'"
fi

print_test "Wrong number of arguments - SHOULD SHOW USAGE"
echo "Testing: ./client 123 msg extra" >> $LOG_FILE
timeout 5 ./client 123 "msg" "extra" 2>&1 > /tmp/client_wrong_args.log 2>&1
CLIENT_EXIT_CODE=$?
OUTPUT=$(cat /tmp/client_wrong_args.log)
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Client output: '$OUTPUT'"
if [[ $CLIENT_EXIT_CODE -ne 0 ]] && [[ "$OUTPUT" == *"Usage"* ]]; then
    pass_test "Wrong number of arguments shows usage"
else
    fail_test "Wrong number of arguments" "Expected usage message and non-zero exit, got exit code: $CLIENT_EXIT_CODE, output: '$OUTPUT'"
fi

print_test "Invalid PID (0) - SHOULD REJECT"
echo "Testing: ./client 0 test" >> $LOG_FILE
timeout 5 ./client 0 "test" 2>&1 > /tmp/client_invalid_pid.log 2>&1
CLIENT_EXIT_CODE=$?
OUTPUT=$(cat /tmp/client_invalid_pid.log)
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Client output: '$OUTPUT'"
if [[ $CLIENT_EXIT_CODE -ne 0 ]] && [[ "$OUTPUT" == *"Invalid"* ]]; then
    pass_test "Invalid PID (0) rejection"
else
    fail_test "Invalid PID (0)" "Expected rejection and non-zero exit, got exit code: $CLIENT_EXIT_CODE, output: '$OUTPUT'"
fi

# ============================================
# TEST 4: Client Output Validation
# ============================================
print_section "TEST 4: CLIENT OUTPUT VALIDATION"

print_test "Client prints PID - VALIDATING OUTPUT"
echo "Testing client PID output" >> $LOG_FILE
OUTPUT=$(./client $SERVER_PID "test" 2>&1)
CLIENT_EXIT_CODE=$?
log_detail "Client exit code: $CLIENT_EXIT_CODE"
log_detail "Client output: '$OUTPUT'"
if [[ "$OUTPUT" == *"Client PID:"* ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Client prints PID"
else
    fail_test "Client prints PID" "Expected 'Client PID:' in output, got: '$OUTPUT', exit code: $CLIENT_EXIT_CODE"
fi

print_test "Client prints success message - VALIDATING OUTPUT"
if [[ "$OUTPUT" == *"successfully"* ]] && [[ $CLIENT_EXIT_CODE -eq 0 ]]; then
    pass_test "Client prints success message"
else
    fail_test "Client prints success message" "Expected 'successfully' in output, got: '$OUTPUT', exit code: $CLIENT_EXIT_CODE"
fi

# ============================================
# TEST 5: Memory Validation with ACTUAL Valgrind
# ============================================
print_section "TEST 5: MEMORY VALIDATION WITH ACTUAL VALGRIND"

print_test "Valgrind - ACTUAL MEMORY LEAK CHECK"
echo "Running: valgrind --leak-check=full ./client $SERVER_PID valgrind_test" >> $LOG_FILE
timeout 10 valgrind --leak-check=full --show-leak-kinds=all ./client $SERVER_PID "valgrind_test" 2>&1 > /tmp/valgrind_output.log 2>&1
VALGRIND_EXIT_CODE=$?
VALGRIND_OUTPUT=$(cat /tmp/valgrind_output.log)
log_detail "Valgrind exit code: $VALGRIND_EXIT_CODE"
echo "$VALGRIND_OUTPUT" >> $LOG_FILE

# Check for actual memory leaks - handle both possible outputs
if echo "$VALGRIND_OUTPUT" | grep -q "All heap blocks were freed -- no leaks are possible" || \
   (echo "$VALGRIND_OUTPUT" | grep -q "definitely lost: 0 bytes" && echo "$VALGRIND_OUTPUT" | grep -q "indirectly lost: 0 bytes"); then
    pass_test "Valgrind - no memory leaks detected"
else
    fail_test "Valgrind - memory leaks detected" "Check valgrind output in log file"
fi

# ============================================
# TEST 6: Server Stability
# ============================================
print_section "TEST 6: SERVER STABILITY"

print_test "Server still running after tests"
if ps -p $SERVER_PID > /dev/null; then
    pass_test "Server still running"
else
    fail_test "Server crashed" "Server process not found"
fi

print_test "Server responsive after multiple messages"
truncate -s 0 /tmp/server_validation.log  # Clear log before test
OUTPUT=$(./client $SERVER_PID "final_test" 2>&1)
CLIENT_EXIT_CODE=$?
sleep 0.5
SERVER_LOG=$(cat /tmp/server_validation.log | tr -d '\0')
if [[ $CLIENT_EXIT_CODE -eq 0 ]] && [[ "$SERVER_LOG" == "final_test" ]]; then
    pass_test "Server responsive with validation"
else
    fail_test "Server responsive" "Server did not respond correctly, exit code: $CLIENT_EXIT_CODE, server got: '$SERVER_LOG'"
fi

# ============================================
# CLEANUP
# ============================================
print_section "CLEANUP"
kill $SERVER_PID 2>/dev/null
wait $SERVER_PID 2>/dev/null
echo "Server stopped" | tee -a $LOG_FILE

# ============================================
# COMPARISON WITH REPORTED RESULTS
# ============================================
print_section "COMPARISON WITH REPORTED RESULTS"

echo "=== COMPARISON WITH REPORTED TEST RESULTS ===" >> $LOG_FILE
echo "Actual tests run: $TESTS_TOTAL" >> $LOG_FILE
echo "Actual passed: $TESTS_PASSED" >> $LOG_FILE
echo "Actual failed: $TESTS_FAILED" >> $LOG_FILE
echo "Actual pass rate: $(( TESTS_PASSED * 100 / TESTS_TOTAL ))%" >> $LOG_FILE
echo "" >> $LOG_FILE

echo "Reported in TEST_RESULTS.md: 51/51 tests passed (100%)" >> $LOG_FILE
echo "Reported in COMPREHENSIVE_TEST_REPORT.md: 51/51 tests passed (100%)" >> $LOG_FILE
echo "Reported in TEST_REPORT.md: 24/24 tests passed (100%)" >> $LOG_FILE
echo "" >> $LOG_FILE

if [[ $TESTS_FAILED -gt 0 ]]; then
    echo "DISCREPANCY DETECTED: Reports claim 100% pass rate, but actual validation shows failures" >> $LOG_FILE
    printf "${RED}DISCREPANCY: Reports claim 100%% pass rate, but validation shows $TESTS_FAILED failures${NC}\n"
else
    echo "PASS RATES MATCH: Both reports and validation show 100% pass rate" >> $LOG_FILE
    printf "${GREEN}PASS RATES MATCH: Both reports and validation show 100%% pass rate${NC}\n"
fi

# ============================================
# SUMMARY
# ============================================
print_section "VALIDATION SUMMARY"
TESTS_FAILED=$((TESTS_TOTAL - TESTS_PASSED))
printf "${BLUE}Total Tests:${NC} $TESTS_TOTAL\n"
printf "${GREEN}Passed:${NC} $TESTS_PASSED\n"
printf "${RED}Failed:${NC} $TESTS_FAILED\n"
printf "\n"

echo "=== VALIDATION SUMMARY ===" >> $LOG_FILE
echo "Total Tests: $TESTS_TOTAL" >> $LOG_FILE
echo "Passed: $TESTS_PASSED" >> $LOG_FILE
echo "Failed: $TESTS_FAILED" >> $LOG_FILE
echo "Pass Rate: $(( TESTS_PASSED * 100 / TESTS_TOTAL ))%" >> $LOG_FILE

if [[ $TESTS_FAILED -eq 0 ]]; then
    printf "${GREEN}✓ ALL VALIDATION TESTS PASSED${NC}\n"
    echo "CONCLUSION: All validation tests passed" >> $LOG_FILE
    exit 0
else
    printf "${RED}✗ SOME VALIDATION TESTS FAILED${NC}\n"
    echo "CONCLUSION: Some validation tests failed - test reports may be inaccurate" >> $LOG_FILE
    exit 1
fi