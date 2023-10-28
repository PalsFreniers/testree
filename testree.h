#ifndef TESTREE_H
#define TESTREE_H

#include "printUtils.h"

#ifndef TT_STRCMP
# include <string.h>
# define TT_STRCMP strcmp
#endif // TT_STRCMP

#ifndef TT_PRINTF
# include <stdio.h>
# define TT_PRINTF printf
#endif

#ifndef ARRAY_SIZE
# define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif // ARRAY_SIZE

#define TT_TEST(name) int name()
#define TT_SUITE(name, ...) TT_Test name[] {__VA_ARGS__}
#define TT_TEST_SUITE(x) TT_makeTests(x, ARRAY_SIZE(x), #x)
#define TT_TEST_SUITE_NAMED(x, name) TT_makeTests(x, ARRAY_SIZE(x), name)

#define TT_EQ(x, y) if(x!=y)return __LINE__
#define TT_NEQ(x, y) if(x==y)return __LINE__
#define TT_GR(x, y) if(x<=y)return __LINE__
#define TT_LE(x, y) if(x>=y)return __LINE__
#define TT_GEQ(x, y) if(x<y)return __LINE__
#define TT_LEQ(x, y) if(x>y)return __LINE__
#define TT_STR_EQ(x, y) if(TT_STRCMP(x, y))return __LINE__
#define TT_ARR_EQ(x, y) if(TT_STRCMP(x, y))return __LINE__
#define TT_CUSTOM(x, func) if(!func(x))return __LINE__
#define TT_TEST_END() return 0

typedef int (*TT_Test)();

void TT_makeTests(TT_Test *tests, int testN, const char *name);

#endif // TESTREE_H

#ifdef TESTREE_IMPLEMENTATION

void TT_makeTests(TT_Test *tests, int testN, const char *name) {
        TT_PRINTF("%s%s[START_OF_TEST] => {%s%s%s%s}%s\n\n", DECORATION_ITALIC(), COLOR_GREY(), FORE_RESET() DECORATION_ITALIC_OFF(), name, DECORATION_ITALIC(), COLOR_GREY(), FORE_RESET() DECORATION_ITALIC_OFF());
        int errors = 0;
        int errorN[testN];
        for(int i = 0; i < testN; i++) {
                TT_PRINTF("TEST[%d] => ", i + 1);
                int status = tests[i]();
                if(status == 0) TT_PRINTF("%sSuccess%s", FORE_RGB(50, 255, 50), FORE_RESET() DECORATION_ITALIC_OFF());
                else {
                        TT_PRINTF("%sFailure%s\n\t\tAppened on line : %d", FORE_RGB(255, 50, 50), FORE_RESET() DECORATION_ITALIC_OFF(), status);
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

}

#endif // TESTREE_IMPLEMENTATION
