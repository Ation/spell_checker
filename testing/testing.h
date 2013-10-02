#ifndef __SPELL_CHECKER_TESTING_H__
#define __SPELL_CHECKER_TESTING_H__

typedef bool (*testFunction)();

typedef struct __test_case {
	typedef bool (*test_function_pointer)();

    const char				*test_name;
	test_function_pointer	test_function;
}TestCase;

void    StartTesting(testFunction *functions, int count);

bool    ExecuteTestCases(TestCase *cases, int count);

#endif // __SPELL_CHECKER_TESTING_H__
