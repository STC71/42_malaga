# ***** NAMES ***************************************************************** #

NAME 			= minishell

# ***** APARIENCE ************************************************************* #

DEL_LINE 		= \033[2K
ITALIC 			= \033[3m
BOLD 			= \033[1m
DEF_COLOR 		= \033[0;39m
GRAY 			= \033[0;90m
RED 			= \033[0;91m
GREEN 			= \033[0;92m
YELLOW 			= \033[0;93m
BLUE 			= \033[0;94m
MAGENTA 		= \033[0;95m
CYAN 			= \033[0;96m
WHITE 			= \033[0;97m
BLACK 			= \033[0;99m
ORANGE 			= \033[38;5;209m
BROWN 			= \033[38;2;184;143;29m
DARK_GRAY 		= \033[38;5;234m
MID_GRAY 		= \033[38;5;245m
DARK_GREEN 		= \033[38;2;75;179;82m
DARK_YELLOW 	= \033[38;5;143m

# ***** VALUES ************************************************************** #

CC 				= gcc
CFLAGS 			= -g -Wall -Werror -Wextra
AR 				= ar rcs
RM 				= rm -rf
MK 				= make -C
MKD				= mkdir -p
MCL 			= make clean -C
MFCL 			= make fclean -C
MK_				= && make

# ***** DIRECTORIES ********************************************************** #

SRCS			= builtins/cd_errors.c \
					builtins/cd.c \
					builtins/cd_utils.c \
					builtins/delete_env.c \
					builtins/echo.c \
					builtins/exit.c \
					builtins/print_env.c \
					builtins/pwd.c \
					builtins/some_errors.c \
					builtins/update_env_errors.c \
					builtins/update_env_export.c \
					builtins/update_env2.c \
				executor/check_and_exec_builtins.c \
				executor/clean.c \
				executor/execute_ast.c \
				executor/execute_ast_utils.c \
				executor/execute_bin.c \
				executor/execute_bin2.c \
				executor/execute_bin3.c \
				executor/execute_builtins.c \
				executor/heredoc.c \
				executor/redirections.c \
				executor/exec_utils.c \
					parser/ft_action.c \
					parser/ft_action_utils.c \
					parser/ft_checkers_1.c \
					parser/ft_checkers_2.c \
					parser/ft_elements.c \
					parser/ft_envp_tools.c \
					parser/ft_free_utils.c \
					parser/ft_cleanup.c \
					parser/ft_cleanup_utils.c \
				parser/ft_handling_1.c \
				parser/ft_handling_2.c \
				parser/ft_logical_ops.c \
				parser/ft_logical_ops_utils.c \
				parser/ft_logical_extract.c \
				parser/ft_logical_parse.c \
					parser/ft_mem_tools.c \
					parser/ft_parentheses.c \
					parser/ft_parentheses_utils.c \
					parser/ft_quotes_handling.c \
					parser/ft_quotes.c \
					parser/ft_remove.c \
					parser/ft_struct_parse.c \
				parser/ft_tools.c \
				parser/ft_wildcards.c \
				parser/ft_wildcards_helpers.c \
				parser/ft_wildcards_expand.c \
				parser/ft_wildcards_utils.c \
				signals/ft_signals.c# The variable SRCS is used to get all the source files in the SRCS directory.

OBJS			= $(SRCS:.c=.o)

# The variable OBJS is used to get all the object files in the SRCS directory.
# .c=.o is used to replace the .c extension with the .o extension.

OBJS_DIR		= ./objs
LIBFT_DIR		= ./libft
FT_PRINTF_DIR	= ./ft_printf
INCLUDES		= ./includes

# The variable INCLUDES is used to include the header files.

# ***** COMPILATION ********************************************************** #

all: $(NAME) # $(NAME_BONUS)
# The all rule is used to compile the project

$(NAME): $(OBJS)
	@echo "${DARK_YELLOW}${BOLD}Compiling my ${NAME}...${DEF_COLOR}"

# The @ symbol is used to hide the command from the terminal.	

	@${MAKE} -C ${LIBFT_DIR} 
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${LIBFT_DIR} -lft -I${INCLUDES} -lreadline > /dev/null

# To compile the project:
# ${CC} command is used to compile the project.
# ${CFLAGS} variable is used to add the flags to the compilation.
# ${OBJS} variable is used to get the object files.
# ${LIBFT_DIR} variable is used to get the library.
# ${FT_PRINTF_DIR} variable is used to get the library.
# ${INCLUDES} variable is used to include the header files.
# -o flag is used to specify the output file.
# ${NAME} variable is used to specify the output file.

	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME} is done!${DEF_COLOR}"
	@echo " "
	@echo "${BLUE} █   █          █████ ${RED}█   █ █████ █"
	@echo "${BLUE} ██ ██ █ █  █ █ █     ${RED}█   █ █     █     █"
	@echo "${BLUE} █ █ █ █ ██ █ █ █████ ${RED}█████ ████  █     █"
	@echo "${BLUE} █   █ █ █ ██ █     █ ${RED}█   █ █     █     █"
	@echo "${BLUE} █   █ █ █  █ █ █████ ${RED}█   █ █████ █████ █████"
	@echo " "
	@echo "${DARK_GREEN}	  By: druiz-ca & sternero"
	@echo " "
	@echo "${YELLOW}  🤪 Welcome to the ${NAME} experience! 🤪"
	@echo " "
	@echo "${CYAN}  ✨ Bonus features and more included:"
	@echo "${CYAN}     • Wildcards (*) expansion"
	@echo "${CYAN}     • Logical operators (&& and ||)"
	@echo "${CYAN}     • Sequential execution (;)"
	@echo "${CYAN}     • Parentheses for precedence"
	@echo " "

bonus: all
	@echo "${MAGENTA}${BOLD}✓ Bonus features are already compiled in ${NAME}${DEF_COLOR}"

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "${BLUE}${BOLD}Compiling $<...${DEF_COLOR}"

# The %.o: %.c rule is used to compile the object files.
# $< is used to get the first dependency.
# $@ is used to get the target.
# -c flag is used to compile the source files.

# ***** CLEANING ************************************************************* #

clean:
	@${RM} ${OBJS}
	@${RM} parser/*.o
	@echo "${RED}${BOLD}Cleaning objects...${DEF_COLOR}"
	@${MCL} ${LIBFT_DIR}
	@if [ -d "$(OBJS_DIR)" ]; then ${RM} $(OBJS_DIR); fi
	@if [ -f "test_result.md" ]; then ${RM} test_result.md && echo "${RED}${BOLD}Removing test_result.md...${DEF_COLOR}"; fi
	@if [ -f "test_auto_result.md" ]; then ${RM} test_auto_result.md && echo "${RED}${BOLD}Removing test_auto_result.md...${DEF_COLOR}"; fi
	@if [ -f "valgrind_result.md" ]; then ${RM} valgrind_result.md && echo "${RED}${BOLD}Removing valgrind_result.md...${DEF_COLOR}"; fi
	@echo "${RED}${BOLD}Cleaning objects is done!${DEF_COLOR}"
	#@${RM} ./objs
	#@echo "${RED}${BOLD}Cleaning objects is done!${DEF_COLOR}"

# The clean rule is used to clean the object files.
# ${RM} command is used to remove the object files.
# -r flag is used to remove the directory.
# if [ -d "$(OBJS_DIR)" ]; then ${RM} -r $(OBJS_DIR); fi is used to remove the
# directory if it exists. -d flag is used to check if the directory exists.
# ${MCL} command is used to clean the object files in the libraries.

fclean: clean
	@${RM} ${NAME}
	@${RM} parser/*.o
	@echo "${RED}${BOLD}Cleaning ${NAME}...${DEF_COLOR}"
	@${MFCL} $(LIBFT_DIR)
	@if [ -f "test_result.md" ]; then ${RM} test_result.md && echo "${RED}${BOLD}Removing test_result.md...${DEF_COLOR}"; fi
	@if [ -f "test_auto_result.md" ]; then ${RM} test_auto_result.md && echo "${RED}${BOLD}Removing test_auto_result.md...${DEF_COLOR}"; fi
	@if [ -f "valgrind_result.md" ]; then ${RM} valgrind_result.md && echo "${RED}${BOLD}Removing valgrind_result.md...${DEF_COLOR}"; fi
	@echo "${RED}${BOLD}Cleaning ${NAME} is done!${DEF_COLOR}"
# The same of the clean rule but this clean all the files: object files and
# the executable files.

clean_screen:
	@clear

# ***** RECOMPILATION ******************************************************** #

re: fclean all
# The re rule is used to recompile the project from scratch.

# ***** TESTING & VALIDATION ************************************************* #

test: $(NAME)
	@echo "${CYAN}${BOLD}Running interactive test suite...${DEF_COLOR}"
	@echo "${YELLOW}This will run the official evaluation tests${DEF_COLOR}"
	@./test.sh

test_auto: $(NAME)
	@echo "${CYAN}${BOLD}Running automated test suite...${DEF_COLOR}"
	@echo "${YELLOW}This will run 115+ comprehensive tests${DEF_COLOR}"
	@./test_auto.sh

test_fast: $(NAME)
	@echo "${CYAN}${BOLD}Running fast automated tests...${DEF_COLOR}"
	@echo "${YELLOW}Skipping stress tests for quick validation${DEF_COLOR}"
	@./test_auto.sh --fast

valgrind: $(NAME)
	@echo "${MAGENTA}${BOLD}Running Valgrind memory check...${DEF_COLOR}"
	@echo "${YELLOW}Checking for memory leaks...${DEF_COLOR}"
	@if [ -f "valgrind_test_suite.sh" ]; then \
		./valgrind_test_suite.sh; \
	else \
		echo "${RED}Running basic valgrind check...${DEF_COLOR}"; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--suppressions=readline.supp ./$(NAME); \
	fi

# ***** UTILITIES ************************************************************ #

help:
	@echo "${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${DEF_COLOR}"
	@echo "${BOLD}${CYAN}                    MINISHELL MAKEFILE HELP                    ${DEF_COLOR}"
	@echo "${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${DEF_COLOR}"
	@echo ""
	@echo "${BOLD}${GREEN}COMPILATION TARGETS:${DEF_COLOR}"
	@echo "  ${YELLOW}make${DEF_COLOR} or ${YELLOW}make all${DEF_COLOR}      - Compile minishell with all features"
	@echo "  ${YELLOW}make bonus${DEF_COLOR}            - Same as 'all' (bonus already integrated)"
	@echo "  ${YELLOW}make re${DEF_COLOR}               - Clean and recompile everything"
	@echo ""
	@echo "${BOLD}${GREEN}CLEANING TARGETS:${DEF_COLOR}"
	@echo "  ${YELLOW}make clean${DEF_COLOR}            - Remove object files and test results"
	@echo "  ${YELLOW}make fclean${DEF_COLOR}           - Remove objects and executable"
	@echo "  ${YELLOW}make clean_screen${DEF_COLOR}     - Clear the terminal screen"
	@echo ""
	@echo "${BOLD}${GREEN}TESTING TARGETS:${DEF_COLOR}"
	@echo "  ${YELLOW}make test${DEF_COLOR}             - Run interactive evaluation tests (test.sh)"
	@echo "  ${YELLOW}make test_auto${DEF_COLOR}        - Run 115+ automated tests (test_auto.sh)"
	@echo "  ${YELLOW}make test_fast${DEF_COLOR}        - Run quick tests (skip stress tests)"
	@echo ""
	@echo "${BOLD}${GREEN}VALIDATION TARGETS:${DEF_COLOR}"
	@echo "  ${YELLOW}make valgrind${DEF_COLOR}         - Check for memory leaks with Valgrind"
	@echo ""
	@echo "${BOLD}${GREEN}UTILITY TARGETS:${DEF_COLOR}"
	@echo "  ${YELLOW}make help${DEF_COLOR}             - Show this help message"
	@echo ""
	@echo "${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${DEF_COLOR}"
	@echo "${BOLD}${CYAN}FEATURES INCLUDED:${DEF_COLOR}"
	@echo "  ${GREEN}✓${DEF_COLOR} All mandatory built-ins (echo, cd, pwd, export, unset, env, exit)"
	@echo "  ${GREEN}✓${DEF_COLOR} Redirections (<, >, <<, >>)"
	@echo "  ${GREEN}✓${DEF_COLOR} Pipes (|)"
	@echo "  ${GREEN}✓${DEF_COLOR} Environment variables expansion (\$$VAR, \$$?)"
	@echo "  ${GREEN}✓${DEF_COLOR} Signal handling (ctrl-C, ctrl-D, ctrl-\\)"
	@echo "  ${GREEN}✓${DEF_COLOR} Quote handling (' and \")"
	@echo "  ${MAGENTA}✓${DEF_COLOR} ${BOLD}BONUS:${DEF_COLOR} Wildcards (*)"
	@echo "  ${MAGENTA}✓${DEF_COLOR} ${BOLD}BONUS:${DEF_COLOR} Logical operators (&& and ||)"
	@echo "  ${MAGENTA}✓${DEF_COLOR} ${BOLD}BONUS:${DEF_COLOR} Parentheses for precedence"
	@echo ""
	@echo "${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${DEF_COLOR}"
	@echo "${BOLD}${CYAN}AUTHORS:${DEF_COLOR} druiz-ca & sternero"
	@echo "${BOLD}${BLUE}═══════════════════════════════════════════════════════════════${DEF_COLOR}"
	@echo ""

.PHONY: all clean fclean re libft bonus test test_auto test_fast valgrind help clean_screen
# The .PHONY rule is used to avoid conflicts with the files with the same name.

# ***** THE END ************************************************************** #
