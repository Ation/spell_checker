#ifndef __SPELL_CHECKER_TESTING_H__
#define __SPELL_CHECKER_TESTING_H__


typedef struct __test_case {
	typedef bool (*test_function_pointer)();

    const char				*test_name;
	test_function_pointer	test_function;
}TestCase;

#endif // __SPELL_CHECKER_TESTING_H__
