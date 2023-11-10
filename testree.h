#ifndef TESTREE_H
#define TESTREE_H

#include "printUtils.h"

#ifndef TT_STRCMP
# include <string.h>
# define TT_STRCMP strcmp
#endif // TT_STRCMP

#ifndef TT_MEMCMP
# include <string.h>
# define TT_MEMCMP memcmp
#endif // TT_STRCMP

#ifndef TT_PRINTF
# include <stdio.h>
# define TT_PRINTF printf
#endif

#ifndef TT_FLUSH
# include <stdio.h>
# define TT_FFLUSH fflush
#endif // TT_FFLUSH

#ifndef TT_FILENO
# include <stdio.h>
# define TT_FILENO fileno
#endif // TT_FILENO

#ifndef TT_PIPE2
# ifdef _GNU_SOURCE
#  undef _GNU_SOURCE
# endif // _GNU_SOURCE
# define _GNU_SOURCE
# include <unistd.h>
# include <fcntl.h>
# define TT_PIPE2 pipe2
#endif // TT_PIPE2

#ifndef TT_PIPE
# include <unistd.h>
# define TT_PIPE pipe
#endif // TT_PIPE

#ifndef TT_DUP
# include <unistd.h>
# define TT_DUP dup
#endif // TT_DUP

#ifndef TT_DUP2
# include <unistd.h>
# define TT_DUP2 dup2
#endif // TT_DUP2

#ifndef TT_READ
# include <unistd.h>
# define TT_READ read
#endif // TT_READ

#ifndef TT_CLOSE
# include <unistd.h>
# define TT_CLOSE close
#endif // TT_CLOSE

#ifndef TT_NULL
#define TT_NULL ((void *)0)
#endif // TT_NULL

#ifndef ARRAY_SIZE
# define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif // ARRAY_SIZE

// test utils
#define TT_TEST(name) int name()
#define TT_SUITE(name, ...) TT_Test name[] = {__VA_ARGS__}
#define TT_INIT() int testree_verifyer_of_suites_and_tests_uncolliding_name = 0
#define TT_TEST_SUITE(x) testree_verifyer_of_suites_and_tests_uncolliding_name += TT_makeTests(x, ARRAY_SIZE(x), #x)
#define TT_TEST_SUITE_NAMED(x, name) TT_makeTests(x, ARRAY_SIZE(x), name)
#define TT_RETURN() {if(testree_verifyer_of_suites_and_tests_uncolliding_name>0)TT_PRINTF("%sFailure%s on %d tests suites\n", FORE_RGB(255, 50, 50), FORE_RESET() DECORATION_ITALIC_OFF(), testree_verifyer_of_suites_and_tests_uncolliding_name);else TT_PRINTF("%sSuccess%s on all tests suites\n", FORE_RGB(50, 255, 50), FORE_RESET() DECORATION_ITALIC_OFF());}

// test file pipes
#define TT_PIPE_INIT(file) int testree_pipe_file_descriptor_uncolliding_name[2];FILE *testree_pipe_file_uncolliding_name = file;int testree_pipe_backup_uncollidinig_name = TT_init_pipe(testree_pipe_file_uncolliding_name, testree_pipe_file_descriptor_uncolliding_name)
#define TT_PIPE_READ(buf) TT_FFLUSH(testree_pipe_file_uncolliding_name);TT_read_pipe(buf, testree_pipe_file_descriptor_uncolliding_name[0])
#define TT_PIPE_RESTORE() TT_CLOSE(testree_pipe_file_descriptor_uncolliding_name[1]);TT_restore_pipe(testree_pipe_file_uncolliding_name, testree_pipe_backup_uncollidinig_name);
#define TT_PIPE_RELOAD() TT_PIPE_RESTORE();testree_pipe_file_descriptor_uncolliding_name[0] = -1;testree_pipe_file_descriptor_uncolliding_name[1] = -1;testree_pipe_backup_uncollidinig_name = TT_init_pipe(testree_pipe_file_uncolliding_name, testree_pipe_file_descriptor_uncolliding_name)
#define TT_PIPE_BUFFER(name) static TT_Pipe_Buffer name

// test asserts
#define TT_EQ(x, y)                           if(x!=y)                  return __LINE__
#define TT_GR(x, y)                           if(x<=y)                  return __LINE__
#define TT_LE(x, y)                           if(x>=y)                  return __LINE__
#define TT_NEQ(x, y)                          if(x==y)                  return __LINE__
#define TT_GEQ(x, y)                          if(x< y)                  return __LINE__
#define TT_LEQ(x, y)                          if(x> y)                  return __LINE__
#define TT_PTR(x)                             if(x==TT_NULL)            return __LINE__
#define TT_STR_EQ(x, y)                       if(TT_STRCMP(x, y))       return __LINE__
#define TT_ARR_EQ(x, y, size)                 if(TT_MEMCMP(x, y, size)) return __LINE__
#define TT_CUSTOM(x, func)                    if(!func(x))              return __LINE__
#define TT_CODE_EQ(x, y, code)                if(x!=y)                  return code
#define TT_CODE_GR(x, y, code)                if(x<=y)                  return code
#define TT_CODE_LE(x, y, code)                if(x>=y)                  return code
#define TT_CODE_NEQ(x, y, code)               if(x==y)                  return code
#define TT_CODE_GEQ(x, y, code)               if(x< y)                  return code
#define TT_CODE_LEQ(x, y, code)               if(x> y)                  return code
#define TT_CODE_PTR(x, code)                  if(x==TT_NULL)            return code
#define TT_CODE_STR_EQ(x, y, code)            if(TT_STRCMP(x, y))       return code
#define TT_CODE_ARR_EQ(x, y, size, code)      if(TT_MEMCMP(x, y, size)) return code
#define TT_CODE_CUSTOM(x, func, code)         if(!func(x))              return code
#define TT_PIPE_EQ(x, y)                      if(x!=y)                  {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_GR(x, y)                      if(x<=y)                  {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_LE(x, y)                      if(x>=y)                  {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_NEQ(x, y)                     if(x==y)                  {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_GEQ(x, y)                     if(x< y)                  {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_LEQ(x, y)                     if(x> y)                  {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_PTR(x)                        if(x==TT_NULL)            {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_STR_EQ(x, y)                  if(TT_STRCMP(x, y))       {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_ARR_EQ(x, y, size)            if(TT_MEMCMP(x, y, size)) {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_CUSTOM(x, func)               if(!func(x))              {TT_PIPE_RESTORE();return __LINE__;}
#define TT_PIPE_CODE_EQ(x, y, code)           if(x!=y)                  {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_GR(x, y, code)           if(x<=y)                  {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_LE(x, y, code)           if(x>=y)                  {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_NEQ(x, y, code)          if(x==y)                  {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_GEQ(x, y, code)          if(x< y)                  {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_LEQ(x, y, code)          if(x> y)                  {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_PTR(x, code)             if(x==TT_NULL)            {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_STR_EQ(x, y, code)       if(TT_STRCMP(x, y))       {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_ARR_EQ(x, y, size, code) if(TT_MEMCMP(x, y, size)) {TT_PIPE_RESTORE();return code;}
#define TT_PIPE_CODE_CUSTOM(x, func, code)    if(!func(x))              {TT_PIPE_RESTORE();return code;}
#define TT_TEST_END() return 0

// test debug utils
#define TT_LOG(fmt, ...) TT_PRINTF("[DEBUG] -> " fmt "\n", __VA_ARGS__)

// test function and types
typedef int (*TT_Test)();
typedef char TT_Pipe_Buffer[1025];

int  TT_makeTests(TT_Test *tests, int testN, const char *name);
int  TT_init_pipe(FILE *f, int *pipefd);
int  TT_read_pipe(TT_Pipe_Buffer buf, int pipefd);
void TT_restore_pipe(FILE *f, int stdout_bk);

#endif // TESTREE_H

#ifdef TESTREE_IMPLEMENTATION

int TT_makeTests(TT_Test *tests, int testN, const char *name) {
        TT_PRINTF("%s%s[START_OF_TEST] => {%s%s%s%s}%s\n\n", DECORATION_ITALIC(), COLOR_GREY(), FORE_RESET() DECORATION_ITALIC_OFF(), name, DECORATION_ITALIC(), COLOR_GREY(), FORE_RESET() DECORATION_ITALIC_OFF());
        TT_FFLUSH(stdout);
        int errors = 0;
        int errorN[testN];
        for(int i = 0; i < testN; i++) {
                int status = tests[i]();
                TT_PRINTF("TEST[%d] => ", i + 1);
                TT_FFLUSH(stdout);
                if(status == 0) TT_PRINTF("%sSuccess%s", FORE_RGB(50, 255, 50), FORE_RESET() DECORATION_ITALIC_OFF());
                else {
                        TT_PRINTF("%sFailure%s\n\t\tAppened with out : %d (could be a line number or a custom code)", FORE_RGB(255, 50, 50), FORE_RESET() DECORATION_ITALIC_OFF(), status);
                        errorN[errors] = i + 1;
                        errors++;
                }
                TT_PRINTF("\n");
        }
        if(errors == 0) TT_PRINTF("\n%s[INFO]%s -> All tests from %s successfully passed!\n", FORE_RGB(50, 255, 50), FORE_RESET() DECORATION_ITALIC_OFF(), name);
        else if(errors > 0) {
                TT_PRINTF("\n%s[INFO]%s -> Some tests from %s did not pass!\n\t[", FORE_RGB(255, 50, 50), FORE_RESET() DECORATION_ITALIC_OFF(), name);
                for(int i = 0; i < errors - 1; i++) TT_PRINTF("%d, ", errorN[i]);
                TT_PRINTF("%d]\n", errorN[errors - 1]);
        }
        TT_PRINTF("\n%s%s[END_OF_TEST] => {%s%s%s%s}%s\n\n", DECORATION_ITALIC(), COLOR_GREY(),  FORE_RESET() DECORATION_ITALIC_OFF(), name, DECORATION_ITALIC(), COLOR_GREY(), FORE_RESET() DECORATION_ITALIC_OFF());
		if(errors > 0) return 1;
		return 0;
}

int TT_init_pipe(FILE *f, int *pipefd) {
   int  stdout_bk;
   stdout_bk = TT_DUP(TT_FILENO(f));
   TT_PIPE(pipefd);
   TT_DUP2(pipefd[1], TT_FILENO(f));
   return stdout_bk;
}

int  TT_read_pipe(TT_Pipe_Buffer buf, int pipefd) {
   return TT_READ(pipefd, buf, 1024); 
}

void TT_restore_pipe(FILE *f, int stdout_bk) {
   TT_DUP2(stdout_bk, TT_FILENO(f));
}

#endif // TESTREE_IMPLEMENTATION
