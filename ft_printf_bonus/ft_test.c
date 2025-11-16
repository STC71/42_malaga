/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 00:00:00 by sternero          #+#    #+#             */
/*   Updated: 2024-11-12 00:00:00 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf_bonus.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

static int	g_test_count = 0;
static int	g_pass_count = 0;
static int	g_fail_count = 0;

#define TEST_COMPARE(name, example, format, ...) \
	do { \
		int ret1, ret2; \
		g_test_count++; \
		printf(CYAN "\nTest %d: %s" RESET "\n", g_test_count, name); \
		if (example) \
			printf(MAGENTA "Example:   %s" RESET "\n", example); \
		printf("Format:    \"%s\"\n", format); \
		printf("Printf:    "); \
		fflush(stdout); \
		ret1 = printf(format, ##__VA_ARGS__); \
		printf("\n"); \
		printf("Ft_printf: "); \
		fflush(stdout); \
		ret2 = ft_printf(format, ##__VA_ARGS__); \
		printf("\n"); \
		if (ret1 == ret2) { \
			printf(GREEN "✓ PASS - Return values match: %d" RESET "\n", ret1); \
			g_pass_count++; \
		} else { \
			printf(RED "✗ FAIL - Return values differ: printf=%d, ft_printf=%d" RESET "\n", ret1, ret2); \
			g_fail_count++; \
		} \
	} while (0)

#define TEST_COMPARE_EXT(name, example, explain, format, ...) \
	do { \
		int ret1, ret2; \
		g_test_count++; \
		printf(CYAN "\nTest %d: %s" RESET "\n", g_test_count, name); \
		if (example) \
			printf(MAGENTA "Example:   %s" RESET "\n", example); \
		if (explain) \
			printf(BLUE "%s" RESET "\n", explain); \
		printf("Format:    \"%s\"\n", format); \
		printf("Printf:    "); \
		fflush(stdout); \
		ret1 = printf(format, ##__VA_ARGS__); \
		printf("\n"); \
		printf("Ft_printf: "); \
		fflush(stdout); \
		ret2 = ft_printf(format, ##__VA_ARGS__); \
		printf("\n"); \
		if (ret1 == ret2) { \
			printf(GREEN "✓ PASS - Return values match: %d" RESET "\n", ret1); \
			g_pass_count++; \
		} else { \
			printf(RED "✗ FAIL - Return values differ: printf=%d, ft_printf=%d" RESET "\n", ret1, ret2); \
			g_fail_count++; \
		} \
	} while (0)

void	test_mandatory(void)
{
	printf(YELLOW "\n=== MANDATORY TESTS ===" RESET "\n");
	printf(BLUE "Basic conversions without flags:\n" RESET);
	printf("  %%c → print a character        (example: 'A' → A)\n");
	printf("  %%s → print a string           (example: \"Hi\" → Hi)\n");
	printf("  %%d → print decimal number     (example: 42 → 42)\n");
	printf("  %%u → print unsigned number    (example: 42 → 42)\n");
	printf("  %%x → print hex lowercase      (example: 255 → ff)\n");
	printf("  %%X → print hex uppercase      (example: 255 → FF)\n");
	printf("  %%p → print memory address     (example: 0x7fff...)\n");
	printf("  %%%% → print %% symbol           (example: %%%% → %%)\n\n");
	TEST_COMPARE("Basic char", "printf(\"%c\", 'A')", "%c", 'A');
	TEST_COMPARE("Basic string", "printf(\"%s\", \"Hello\")", "%s", "Hello");
	TEST_COMPARE("NULL string", "printf(\"%s\", NULL)", "%s", (char *)NULL);
	TEST_COMPARE("Empty string", "printf(\"%s\", \"\")", "%s", "");
	TEST_COMPARE("Basic int", "printf(\"%d\", 42)", "%d", 42);
	TEST_COMPARE("Negative int", "printf(\"%d\", -42)", "%d", -42);
	TEST_COMPARE("Zero", "printf(\"%d\", 0)", "%d", 0);
	TEST_COMPARE("INT_MIN", "printf(\"%d\", INT_MIN)", "%d", INT_MIN);
	TEST_COMPARE("INT_MAX", "printf(\"%d\", INT_MAX)", "%d", INT_MAX);
	TEST_COMPARE("Basic unsigned", "printf(\"%u\", 42)", "%u", 42);
	TEST_COMPARE("Zero unsigned", "printf(\"%u\", 0)", "%u", 0);
	TEST_COMPARE("UINT_MAX", "printf(\"%u\", UINT_MAX)", "%u", UINT_MAX);
	TEST_COMPARE("Hex lowercase", "printf(\"%x\", 255)", "%x", 255);
	TEST_COMPARE("Hex uppercase", "printf(\"%X\", 255)", "%X", 255);
	TEST_COMPARE("Hex zero", "printf(\"%x\", 0)", "%x", 0);
	TEST_COMPARE("Pointer", "printf(\"%p\", ptr)", "%p", (void *)0x12345678);
	TEST_COMPARE("NULL pointer", "printf(\"%p\", NULL)", "%p", (void *)NULL);
	TEST_COMPARE("Percent sign", "printf(\"100%%\")", "%%");
	TEST_COMPARE("Multiple conversions", "printf(\"%d %s %c\", 42, \"test\", 'X')", "%d %s %c", 42, "test", 'X');
	TEST_COMPARE("Mixed text and conversions", "printf(\"Number: %d, String: %s\", 123, \"example\")", "Number: %d, String: %s", 123,
		"example");
}

void	test_bonus_flags(void)
{
	printf(YELLOW "\n=== BONUS: BASIC FLAGS ===" RESET "\n");
	printf(BLUE "Alignment, padding and precision:\n" RESET);
	printf("  - (minus)  → left align, add spaces on right\n");
	printf("               %%-10d with 42 → \"42        \" (8 spaces after)\n");
	printf("  0 (zero)   → pad with zeros instead of spaces\n");
	printf("               %%010d with 42 → \"0000000042\"\n");
	printf("  . (dot)    → set precision (min digits for numbers)\n");
	printf("               %%.5d with 42 → \"00042\" (5 digits total)\n");
	printf("               %%.3s with \"Hello\" → \"Hel\" (only 3 chars)\n\n");
	TEST_COMPARE_EXT("Left align", "printf(\"%-10d\", 42)", 
		"  -       → left align\n  10      → min width 10", 
		"%-10d", 42);
	TEST_COMPARE_EXT("Left align string", "printf(\"%-10s\", \"test\")", 
		"  -       → left align\n  10      → min width 10", 
		"%-10s", "test");
	TEST_COMPARE_EXT("Left align INT_MIN", "printf(\"%-10d\", INT_MIN)", 
		"  -       → left align\n  10      → min width 10", 
		"%-10d", INT_MIN);
	TEST_COMPARE_EXT("Zero padding", "printf(\"%010d\", 42)", 
		"  0       → zero padding\n  10      → min width 10", 
		"%010d", 42);
	TEST_COMPARE_EXT("Zero negative", "printf(\"%010d\", -42)", 
		"  0       → zero padding\n  10      → min width 10", 
		"%010d", -42);
	TEST_COMPARE_EXT("Zero INT_MIN", "printf(\"%010d\", INT_MIN)", 
		"  0       → zero padding\n  10      → min width 10", 
		"%010d", INT_MIN);
	TEST_COMPARE_EXT("Precision int", "printf(\"%.5d\", 42)", 
		"  .5      → precision 5 (min 5 digits)", 
		"%.5d", 42);
	TEST_COMPARE_EXT("Precision negative", "printf(\"%.5d\", -42)", 
		"  .5      → precision 5 (min 5 digits)", 
		"%.5d", -42);
	TEST_COMPARE_EXT("Precision zero", "printf(\"%.0d\", 0)", 
		"  .0      → precision 0 (prints nothing for 0)", 
		"%.0d", 0);
	TEST_COMPARE_EXT("Precision string", "printf(\"%.3s\", \"Hello\")", 
		"  .3      → precision 3 (max 3 chars)", 
		"%.3s", "Hello");
	TEST_COMPARE_EXT("Precision unsigned", "printf(\"%.5u\", 42)", 
		"  .5      → precision 5 (min 5 digits)", 
		"%.5u", 42);
	TEST_COMPARE_EXT("Precision hex", "printf(\"%.5x\", 255)", 
		"  .5      → precision 5 (min 5 digits)", 
		"%.5x", 255);
}

void	test_bonus_advanced(void)
{
	printf(YELLOW "\n=== BONUS: ADVANCED FLAGS ===" RESET "\n");
	printf(BLUE "Alternative format and sign display:\n" RESET);
	printf("  # (hash)   → add prefix for hex numbers\n");
	printf("               %%#x with 255 → \"0xff\" (adds 0x)\n");
	printf("               %%#X with 255 → \"0XFF\" (adds 0X)\n");
	printf("  + (plus)   → always show sign (+ or -)\n");
	printf("               %%+d with 42 → \"+42\" (shows + for positive)\n");
	printf("               %%+d with -5 → \"-5\" (shows - for negative)\n");
	printf("  (space)    → add space before positive numbers\n");
	printf("               %% d with 42 → \" 42\" (space before number)\n\n");
	TEST_COMPARE_EXT("Hash hex", "printf(\"%#x\", 255)", 
		"  #       → alt form (adds 0x prefix)", 
		"%#x", 255);
	TEST_COMPARE_EXT("Hash hex zero", "printf(\"%#x\", 0)", 
		"  #       → alt form (no prefix for 0)", 
		"%#x", 0);
	TEST_COMPARE_EXT("Hash uppercase", "printf(\"%#X\", 255)", 
		"  #       → alt form (adds 0X prefix)\n  X       → uppercase hex", 
		"%#X", 255);
	TEST_COMPARE_EXT("Force sign positive", "printf(\"%+d\", 42)", 
		"  +       → force sign (shows +)", 
		"%+d", 42);
	TEST_COMPARE_EXT("Force sign negative", "printf(\"%+d\", -42)", 
		"  +       → force sign (shows -)", 
		"%+d", -42);
	TEST_COMPARE_EXT("Force sign zero", "printf(\"%+d\", 0)", 
		"  +       → force sign (shows + even for 0)", 
		"%+d", 0);
	TEST_COMPARE_EXT("Space sign positive", "printf(\"% d\", 42)", 
		"  (space) → add space if no sign", 
		"% d", 42);
	TEST_COMPARE_EXT("Space sign negative", "printf(\"% d\", -42)", 
		"  (space) → ignored (already has - sign)", 
		"% d", -42);
	TEST_COMPARE_EXT("Space sign zero", "printf(\"% d\", 0)", 
		"  (space) → add space before 0", 
		"% d", 0);
}

void	test_bonus_combinations(void)
{
	printf(YELLOW "\n=== BONUS: FLAG COMBINATIONS ===" RESET "\n");
	printf(BLUE "Multiple flags working together:\n" RESET);
	printf("  %%-10.5d with 42    → \"00042     \" (left + width + precision)\n");
	printf("  %%+010d with 42     → \"+000000042\" (sign + zero padding)\n");
	printf("  %%#10.5x with 255   → \"  0x000ff\" (hash + width + precision)\n");
	printf("  %% #8x with 255     → \"    0xff\" (space + hash + width)\n");
	printf("\n  Note: Some combinations override others (- cancels 0)\n\n");
	TEST_COMPARE_EXT("Width + precision", "printf(\"%10.5d\", 42)", 
		"  10      → min width 10\n  .5      → precision 5 digits", 
		"%10.5d", 42);
	TEST_COMPARE_EXT("Left + width + precision", "printf(\"%-10.5d\", 42)", 
		"  -       → left align\n  10      → min width 10\n  .5      → precision 5", 
		"%-10.5d", 42);
	TEST_COMPARE_EXT("Zero + width", "printf(\"%010d\", 42)", 
		"  0       → zero padding\n  10      → min width 10", 
		"%010d", 42);
	TEST_COMPARE_EXT("Width + precision + sign", "printf(\"%+10.5d\", 42)", 
		"  %+      → force sign (+)\n  10      → min width 10\n  .5      → precision 5 digits", 
		"%+10.5d", 42);
	TEST_COMPARE_EXT("All flags", "printf(\"%+010.5d\", 42)", 
		"  +       → force sign\n  0       → zero padding (ignored with precision)\n  10      → min width 10\n  .5      → precision 5", 
		"%+010.5d", 42);
	TEST_COMPARE_EXT("Hash + width + precision", "printf(\"%#10.5x\", 255)", 
		"  #       → alt form (0x prefix)\n  10      → min width 10\n  .5      → precision 5 digits", 
		"%#10.5x", 255);
	TEST_COMPARE_EXT("Multiple complex", "printf(\"%+010d %#x %-10s\", 42, 255, \"test\")", 
		"  %+010d  → sign + zero pad + width 10\n  %#x     → alt hex (0x prefix)\n  %-10s   → left align + width 10", 
		"%+010d %#x %-10s", 42, 255, "test");
}

void	test_edge_cases(void)
{
	printf(YELLOW "\n=== EDGE CASES ===" RESET "\n");
	printf(BLUE "Special and extreme test cases:\n" RESET);
	printf("  • Multiple conversions in one call\n");
	printf("  • Very long strings (buffer handling)\n");
	printf("  • Limit values (INT_MIN, INT_MAX, NULL)\n");
	printf("  • Zero with zero precision: %%.0d with 0 → \"\" (empty!)\n");
	printf("  • Negative precision (should be ignored)\n");
	printf("  • Consecutive %%%% symbols\n\n");
	TEST_COMPARE("Consecutive percent", "printf(\"100%%\")", "%%%%");
	TEST_COMPARE("Many conversions", "printf(\"%d%d%d%d%d\", 1, 2, 3, 4, 5)", "%d%d%d%d%d", 1, 2, 3, 4, 5);
	TEST_COMPARE("Long string", "printf(\"%s\", long_str)",  "%s",
		"This is a very long string to test buffer handling");
	TEST_COMPARE("Negative width effect", "printf(\"%-d\", 42)", "%-d", 42);
	TEST_COMPARE("Zero precision zero value", "printf(\"%.0d\", 0)", "%.0d", 0);
	TEST_COMPARE("Negative precision via *", "printf(\"%.*d\", -5, 42)", "%.*d", -5, 42);
}

int	main(void)
{
	printf(MAGENTA "\n╔════════════════════════════════════════════════════╗\n"
		RESET);
	printf(MAGENTA "║     " CYAN "FT_PRINTF COMPREHENSIVE TEST SUITE (125%%)" MAGENTA
		"      ║\n" RESET);
	printf(MAGENTA "╚════════════════════════════════════════════════════╝\n"
		RESET);
	test_mandatory();
	test_bonus_flags();
	test_bonus_advanced();
	test_bonus_combinations();
	test_edge_cases();
	printf(MAGENTA "\n╔════════════════════════════════════════════════════╗\n"
		RESET);
	printf(MAGENTA "║  " RESET "FINAL RESULTS:" MAGENTA
		"                                    ║\n" RESET);
	printf(MAGENTA "║  " GREEN "✓ Passed: %3d" MAGENTA
		"                                     ║\n" RESET, g_pass_count);
	printf(MAGENTA "║  " RED "✗ Failed: %3d" MAGENTA
		"                                     ║\n" RESET, g_fail_count);
	printf(MAGENTA "║  " BLUE "Total:    %3d" MAGENTA
		"                                     ║\n" RESET, g_test_count);
	printf(MAGENTA "╚════════════════════════════════════════════════════╝\n"
		RESET);
	if (g_fail_count == 0)
		printf(GREEN "\n🎉 ALL TESTS PASSED! Ready for 125%% evaluation!\n"
			RESET);
	else
		printf(RED "\n⚠️  Some tests failed. Please review.\n" RESET);
	return (g_fail_count > 0);
}


