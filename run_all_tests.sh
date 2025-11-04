#!/bin/bash

# Master test runner for minitalk
# Runs all test suites and provides a comprehensive report

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Test results tracking
TOTAL_SUITES=0
PASSED_SUITES=0
FAILED_SUITES=0

# Function to print header
print_header() {
    echo ""
    echo -e "${CYAN}╔══════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║${NC}${BOLD}          MINITALK - COMPREHENSIVE TEST SUITE${NC}              ${CYAN}║${NC}"
    echo -e "${CYAN}║${NC}              Running All Tests - $(date +%Y-%m-%d)              ${CYAN}║${NC}"
    echo -e "${CYAN}╚══════════════════════════════════════════════════════════════╝${NC}"
    echo ""
}

# Function to print section
print_section() {
    echo ""
    echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}${BOLD} $1${NC}"
    echo -e "${YELLOW}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
}

# Function to run a test suite
run_test_suite() {
    local test_name="$1"
    local test_script="$2"
    local test_number="$3"
    
    TOTAL_SUITES=$((TOTAL_SUITES + 1))
    
    echo -e "${BLUE}[${test_number}/3]${NC} ${BOLD}Running: ${test_name}${NC}"
    echo -e "${CYAN}Script: ${test_script}${NC}"
    echo ""
    
    # Run the test and capture output
    if bash "$test_script" > "/tmp/${test_script}.log" 2>&1; then
        EXIT_CODE=0
    else
        EXIT_CODE=$?
    fi
    
    # Display the output
    cat "/tmp/${test_script}.log"
    
    echo ""
    
    # Check result
    if [ $EXIT_CODE -eq 0 ]; then
        echo -e "${GREEN}✓ ${test_name} PASSED${NC}"
        PASSED_SUITES=$((PASSED_SUITES + 1))
        return 0
    else
        echo -e "${RED}✗ ${test_name} FAILED (Exit code: $EXIT_CODE)${NC}"
        FAILED_SUITES=$((FAILED_SUITES + 1))
        return 1
    fi
}

# Function to print final summary
print_summary() {
    echo ""
    echo -e "${CYAN}╔══════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║${NC}${BOLD}                    FINAL TEST SUMMARY${NC}                       ${CYAN}║${NC}"
    echo -e "${CYAN}╚══════════════════════════════════════════════════════════════╝${NC}"
    echo ""
    echo -e "${BLUE}Total Test Suites Run:${NC} ${BOLD}${TOTAL_SUITES}${NC}"
    echo -e "${GREEN}Suites Passed:${NC}         ${BOLD}${PASSED_SUITES}${NC}"
    echo -e "${RED}Suites Failed:${NC}         ${BOLD}${FAILED_SUITES}${NC}"
    
    if [ $FAILED_SUITES -eq 0 ]; then
        echo ""
        echo -e "${GREEN}${BOLD}╔════════════════════════════════════════╗${NC}"
        echo -e "${GREEN}${BOLD}║  🎉 ALL TEST SUITES PASSED! 🎉        ║${NC}"
        echo -e "${GREEN}${BOLD}╚════════════════════════════════════════╝${NC}"
        echo ""
        echo -e "${GREEN}Your minitalk implementation is ready for evaluation!${NC}"
    else
        echo ""
        echo -e "${RED}${BOLD}╔════════════════════════════════════════╗${NC}"
        echo -e "${RED}${BOLD}║  ⚠️  SOME TEST SUITES FAILED  ⚠️       ║${NC}"
        echo -e "${RED}${BOLD}╚════════════════════════════════════════╝${NC}"
        echo ""
        echo -e "${YELLOW}Please review the failed test logs above.${NC}"
    fi
    echo ""
}

# Main execution
clear
print_header

# Check if test scripts exist
if [ ! -f "test_validation.sh" ] || [ ! -f "rigorous_test.sh" ] || [ ! -f "stress_test.sh" ]; then
    echo -e "${RED}Error: One or more test scripts not found!${NC}"
    echo "Required files: test_validation.sh, rigorous_test.sh, stress_test.sh"
    exit 1
fi

# Make sure test scripts are executable
chmod +x test_validation.sh rigorous_test.sh stress_test.sh

echo -e "${MAGENTA}${BOLD}Preparing to run 3 comprehensive test suites...${NC}"
echo ""
sleep 1

# Run Test Suite 1: Validation Tests
print_section "TEST SUITE 1: VALIDATION TESTS"
echo -e "${CYAN}This suite validates basic functionality, Unicode support, error handling,${NC}"
echo -e "${CYAN}client output, memory leaks (Valgrind), and server stability.${NC}"
echo ""
sleep 1
run_test_suite "Validation Tests" "test_validation.sh" "1"
VALIDATION_RESULT=$?

# Wait between tests
sleep 2

# Run Test Suite 2: Rigorous Tests
print_section "TEST SUITE 2: RIGOROUS TESTS"
echo -e "${CYAN}This suite runs rigorous message transmission tests with various${NC}"
echo -e "${CYAN}message types, sizes, and character sets.${NC}"
echo ""
sleep 1
run_test_suite "Rigorous Tests" "rigorous_test.sh" "2"
RIGOROUS_RESULT=$?

# Wait between tests
sleep 2

# Run Test Suite 3: Stress Tests
print_section "TEST SUITE 3: STRESS TESTS"
echo -e "${CYAN}This suite performs stress testing with multiple consecutive messages,${NC}"
echo -e "${CYAN}very long messages, rapid fire transmissions, and special sequences.${NC}"
echo ""
sleep 1
run_test_suite "Stress Tests" "stress_test.sh" "3"
STRESS_RESULT=$?

# Print final summary
print_section "COMPLETE TEST RESULTS"
print_summary

# Generate detailed report file
REPORT_FILE="test_run_$(date +%Y%m%d_%H%M%S).log"
{
    echo "=== MINITALK COMPREHENSIVE TEST RUN ==="
    echo "Date: $(date)"
    echo ""
    echo "Test Suites Run: $TOTAL_SUITES"
    echo "Passed: $PASSED_SUITES"
    echo "Failed: $FAILED_SUITES"
    echo ""
    echo "Individual Results:"
    echo "-------------------"
    [ $VALIDATION_RESULT -eq 0 ] && echo "✓ Validation Tests: PASSED" || echo "✗ Validation Tests: FAILED"
    [ $RIGOROUS_RESULT -eq 0 ] && echo "✓ Rigorous Tests: PASSED" || echo "✗ Rigorous Tests: FAILED"
    [ $STRESS_RESULT -eq 0 ] && echo "✓ Stress Tests: PASSED" || echo "✗ Stress Tests: FAILED"
    echo ""
    echo "Detailed logs available in /tmp/*.log"
} > "$REPORT_FILE"

echo -e "${BLUE}Detailed report saved to: ${BOLD}${REPORT_FILE}${NC}"
echo ""

# Cleanup temp logs
rm -f /tmp/test_validation.sh.log /tmp/rigorous_test.sh.log /tmp/stress_test.sh.log

# Exit with appropriate code
if [ $FAILED_SUITES -eq 0 ]; then
    exit 0
else
    exit 1
fi
