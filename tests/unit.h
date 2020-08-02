/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static inline void Describe(char* desc, void (^lambda)());
static inline void It(char* desc, void (^lambda)());
static inline int Summary(void);

static inline int TestCountInc();
static inline int TestFailInc();
static inline int TestPassInc();

static int first_time = 1;

#define Log(x) printf("%s\n", x)
/**
 *  MACRO __FILENAME__
 *      extracts the filename from the path
 */
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/**
 *  MACRO Expect
 *      this is done as a macro so we can display the
 *      actual source file location for each failure.
 *  
 *      'test' must be an expression that resolves to true or false
 */
#define Expect(test)                                                    \
({                                                                      \
    if (!(test)) {                                                      \
        fprintf(stdout , " failed (%s:%i) ", __FILENAME__, __LINE__);   \
	    TestFailInc();                                                  \
    } else {                                                            \
        fprintf(stdout , " passed ");                                   \
	    TestPassInc();                                                  \
    }                                                                   \
    TestCountInc();                                                     \
})

/**
 * DarkUnit TDD
 * 
 */
static inline void sighandler(int signum);
static inline void resethandlers();
typedef struct test_stats {
    int total;
    int failed;
    int passed;
	int verbosity;
} test_stats;
test_stats tests = { 0, 0, 0, 1};

static inline int TestCountInc() { return tests.total++; }
static inline int TestFailInc()  { return tests.failed++; }
static inline int TestPassInc()  { return tests.passed++; }

/**
 * Describe
 * @param desc title of section
 * @lambda the section code
 * 
 * print a section title & execute
 */
static inline void Describe(char* desc, void (^lambda)()) {
	// fprintf(stdout , "\n");
	fprintf(stdout , "\n\n%s\n======================================", desc);
	lambda();
}

/**
 * It
 * @param desc title of test
 * @lambda the test code
 * 
 * print a test title & execute
 */
static inline void It(char* desc, void (^lambda)()) {
	fprintf(stdout, "\n");
	lambda();
    fprintf(stdout , "[%s]", desc);
	fflush(stdout);
	// lambda();
}

/**
 * print summary info
 */
static inline int Summary(void) {
	if (tests.verbosity > 1) {
		fprintf(stdout , "Tests run: %d\n", tests.total);
		fprintf(stdout , "Tests passed: %d\n", tests.passed);
		fprintf(stdout , "Tests failed: %d\n", tests.failed);
	}
	return tests.failed;
}


/**
 * Handle fatal errors
 */
static inline void resethandlers() {
	signal(SIGABRT, sighandler);
	signal(SIGFPE, sighandler);
	signal(SIGILL, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sighandler);
	signal(SIGTERM, sighandler);
}
/**
 * Handled fatal error
 */
static inline void sighandler(int signum) {
	switch(signum) {
	case SIGABRT: 	
		fprintf(stderr , "Program Aborted\n");		
		break;
	case SIGFPE: 	
		fprintf(stderr , "Division by Zero\n");		
		break;
	case SIGILL: 	
		fprintf(stderr , "Illegal Instruction\n"); 	
		break;
	case SIGINT: 	
		fprintf(stderr , "Program Interrupted\n"); 	
		break;
	case SIGSEGV: 	
		fprintf(stderr , "Segmentation fault\n"); 	
		break;
	case SIGTERM:	
		fprintf(stderr , "Program Terminated\n"); 	
		break;
	default:
		fprintf(stderr , "Unknown Signal %x\n", signum); 	
		break;
	}
	resethandlers();
	exit(-1);
}
/**
 * Set some fatal error traps
 */
static inline void __attribute__((constructor)) DarkUnit() {
	resethandlers();
}
