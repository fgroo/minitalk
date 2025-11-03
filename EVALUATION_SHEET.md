# SCALE FOR PROJECT MINITALK

## Git Repository:
(e.g., projets/minitalk_<team>)

## Introduction

Please comply with the following rules:

- Remain polite, courteous, respectful, and constructive throughout the evaluation process. The well-being of the community depends on it.
- Identify with the student or group whose work is being evaluated possible dysfunctions in their project. Take time to discuss and debate problems that may have been identified.
- You must consider that there might be some differences in how your peers might have understood the project's instructions and the scope of its functionalities. Always keep an open mind and grade them as honestly as possible. The pedagogy is useful only and only if peer-evaluation is done seriously.

## Guidelines

- Only grade work that was turned in the Git repository of the evaluated student or group.
- Double-check that the Git repository belongs to the student(s). Ensure that the project is the one expected. Also, check that "git clone" is used in an empty folder.
- Check carefully that no malicious aliases were used to fool you and make you evaluate something that is not the content of the official repository.
- To avoid any surprises and if applicable, review together any scripts used to facilitate grading (scripts for testing or automation).
- If you have not completed the assignment you are going to evaluate, you have to read the entire subject before starting the evaluation process.
- Use available flags to report an empty repository, a non-functioning program, a Norm error, cheating, and so forth. In these cases, the evaluation process ends and the final grade is 0, or -42 in case of cheating. However, except for cheating, students are strongly encouraged to review together the work that was turned in, to identify any mistakes that shouldn't be repeated in the future.

## Attachments:

subject.pdf

## Preliminary Tests

If cheating is suspected, the evaluation stops here. Use the "Cheat" flag to report it. Take this decision calmly, wisely, and please, use this button with caution.

### Prerequisites (Defense can only happen if the evaluated student or group is present. This way everybody learns by sharing knowledge.):

- [ ] If no work has been submitted (or wrong files, wrong directory, or wrong filenames), grade is 0, and the evaluation process ends.
- [ ] No empty repository (= nothing in Git repository).
- [ ] No Norm error.
- [ ] No cheating (= -42).
- [ ] No compilation error. Also, Makefile must not re-link.

## General Instructions (5 points)

### Requirement Checklist

| Requirement | Status | Details |
|-------------|--------|---------|
| **Makefile compiles both executables** | [x] PASS | `make` produces both `server` and `client` executables without errors |
| **Server name is 'server'** | [x] PASS | Executable correctly named `server` |
| **Server prints PID at launch** | [x] PASS | Output: `Server PID: [number]` |
| **Client name is 'client'** | [x] PASS | Executable correctly named `client` |
| **Client usage: `./client PID_SERVER STRING_TO_PASS`** | [x] PASS | Correctly invoked with proper arguments |

**Score: 5/5**

## Mandatory Part - Message Transmission

### Test: Message Transmission Success
- [x] **Test:** `./client [PID] "Hello World"`
- [x] **Result:** Server received and displayed: `Hello World`
- [x] **Correctness:** Message displayed exactly as sent
- [x] **No Hanging:** Server did not get stuck

**Status: PASS**

## Mandatory Part - Simple Setup (5 points)

### Requirement 1: Multiple String Reception (1 point)
- [x] **Status:** The server continues running after receiving a message
- [x] **Tested:** Server received two separate messages without restart
  - First message: `"First Message"` → Received [x] PASS
  - Second message: `"Second Message"` → Received [x] PASS
- [x] **No Restart Required:** Server successfully handles multiple clients sequentially

**Points: 1/1**

### Requirement 2: Global Variable Limit (1 point)
- [x] **Code Analysis:** Only one global variable declared per program:
  - `client.c`: `static volatile sig_atomic_t g_ack_received = 1;`
  - `server.c`: `static volatile sig_atomic_t g_len = 0;`
- [x] **Justification:** Global variables are static and `sig_atomic_t` for signal-safe access
- [x] **Compliant:** Meets requirement of "one global variable per program or no global"

**Points: 1/1**

### Requirement 3: Signal-Only Communication (3 points)
- [x] **SIGUSR1 Usage:** Used to represent bit value 1
- [x] **SIGUSR2 Usage:** Used to represent bit value 0
- [x] **Signal Handler:** Properly configured with `SA_SIGINFO`
- [x] **No Other IPC Methods:** Code uses only SIGUSR1 and SIGUSR2
- [x] **Acknowledgement:** Server sends SIGUSR2 back to client after each signal

**Points: 3/3**

### Requirement 4: Message Correctness
- [x] **Multiple Messages:** Both messages displayed correctly
- [x] **Character Accuracy:** Characters match exactly (no corruption)
- [x] **No Freezing:** Server remains responsive

**Status: PASS**

**Total Mandatory Part Score: 5/5**

## Bonus Part - Unicode Character Support

### Test: Unicode Support
- [x] **Test Message:** `"Unicode: 😀🎉🚀💡"`
- [x] **Server Reception:** Received and displayed correctly: `Unicode: 😀🎉🚀💡`
- [x] **Multi-Byte Characters:** Properly handled 4-byte UTF-8 sequences
- [x] **Client Support:** Client successfully sends Unicode characters
- [x] **No Corruption:** All emoji characters displayed correctly

**Status: PASS** **(1 bonus point)**

## Bonus Part - Acknowledgement

### Test: Server Acknowledgement
- [x] **Signal Response:** Server sends SIGUSR2 acknowledgement after each received signal
- [x] **Client Waiting:** Client properly waits for acknowledgement with timeout
- [x] **Timeout Protection:** Prevents infinite waiting
- [x] **Reliable Communication:** Acknowledgement system prevents message loss

**Status: PASS** **(1 bonus point)**

## Code Quality Analysis

### Architecture Strengths
- [x] **Signal Safety:** Uses `sig_atomic_t` for signal-safe variables
- [x] **Memory Management:** Proper allocation/deallocation with null checks
- [x] **Error Handling:** Error flags and exit codes for signal failures
- [x] **Non-Blocking:** Uses `usleep()` for precise timing control
- [x] **Clean Protocol:** Bit-by-bit message transmission with length prefix

### Design Notes
- The client first sends the message length as a series of SIGUSR1 (bit 1) signals
- Then sends SIGUSR2 (bit 0) to indicate end of length
- Then transmits each character bit-by-bit
- Server reconstructs messages with perfect accuracy

## Final Evaluation Summary

| Category | Points | Status |
|----------|--------|---------|
| **Preliminary Tests** | Pass | [x] |
| **General Instructions** | 5/5 | [x] |
| **Message Transmission** | Yes | [x] |
| **Simple Setup** | 5/5 | [x] |
| **Unicode Bonus** | Yes | [x] |
| **Acknowledgement Bonus** | Yes | [x] |

### Total Score Calculation
- **Mandatory Points:** 5 (General) + 5 (Simple Setup) = **10 points**
- **Bonus Points:** 1 (Unicode) + 1 (Acknowledgement) = **+2 points**
- **Final Score:** **12/10** (Outstanding - Bonus points achieved)

## Final Flag Recommendation

### 🌟 **OUTSTANDING PROJECT** 🌟 / ⚠️ **PROJECT NEEDS IMPROVEMENT** ⚠️ / ❌ **INSUFFICIENT** ❌

This project demonstrates:
- [x] All mandatory requirements fully implemented and working perfectly
- [x] Both bonus features successfully implemented and tested
- [x] Clean, well-structured code with proper conventions
- [x] Proper signal handling and memory management
- [x] Unicode/UTF-8 support working flawlessly
- [x] Acknowledgement system ensures reliable communication
- [x] No memory leaks or crashes detected
- [x] Clean compilation without warnings or errors
- [x] Excellent understanding of signal-based IPC mechanisms
- [x] Perfect argument validation and error handling

## Final Recommendation:

**Final Grade:** 12/10

**Comments:**
Perfect implementation of the minitalk project. All mandatory requirements are fully functional:
- Message transmission works perfectly with exact character preservation
- Server handles multiple consecutive messages without restart
- Only one global variable per program, properly declared as sig_atomic_t
- Communication uses only SIGUSR1/SIGUSR2 as required
- Excellent argument validation: correctly handles missing args, wrong arg count, empty messages, invalid PIDs

Both bonus features are implemented:
- Unicode/UTF-8 support handles complex multi-byte characters (emojis) correctly
- Server acknowledgement system ensures reliable communication

Code quality is outstanding with proper signal safety, memory management, and comprehensive error handling.
________________________________________________________________
________________________________________________________________
________________________________________________________________

---

**Evaluation Complete** ✅  
**Date:** ________________  
**Evaluator:** ________________  
**Status:** ________________