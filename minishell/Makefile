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
CFLAGS 			= -Wall -Werror -Wextra
AR 				= ar rcs
RM 				= rm -f
MK 				= make -C
MKD				= mkdir -p
MCL 			= make clean -C
MFCL 			= make fclean -C
MK_				= && make

# ***** DIRECTORIES ********************************************************** #

SRCS			= parse/ft_action.c \
				
# The variable SRCS is used to get all the source files in the SRCS directory.

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

$(NAME): clean_screen $(OBJS)
	@echo "${DARK_YELLOW}${BOLD}Compiling my ${NAME}...${DEF_COLOR}"

# The @ symbol is used to hide the command from the terminal.	

	@${MAKE} -C ${LIBFT_DIR} 
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${LIBFT_DIR} -lft -I${INCLUDES}

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

bonus: $(NAME_BONUS)

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
	@echo "${RED}${BOLD}Cleaning objects...${DEF_COLOR}"
	@${MCL} ${LIBFT_DIR}
	@if [ -d "$(OBJS_DIR)" ]; then ${RM} -r $(OBJS_DIR); fi
	@echo "${RED}${BOLD}Cleaning objects is done!${DEF_COLOR}"
	#@${RM} -r ./objs
	#@echo "${RED}${BOLD}Cleaning objects is done!${DEF_COLOR}"

# The clean rule is used to clean the object files.
# ${RM} command is used to remove the object files.
# -r flag is used to remove the directory.
# if [ -d "$(OBJS_DIR)" ]; then ${RM} -r $(OBJS_DIR); fi is used to remove the
# directory if it exists. -d flag is used to check if the directory exists.
# ${MCL} command is used to clean the object files in the libraries.

fclean: clean
	@${RM} ${NAME}
	@echo "${RED}${BOLD}Cleaning ${NAME}...${DEF_COLOR}"
	@${MFCL} $(LIBFT_DIR)
	@echo "${RED}${BOLD}Cleaning ${NAME} is done!${DEF_COLOR}"
# The same of the clean rule but this clean all the files: object files and
# the executable files.

clean_screen:
	@clear

# ***** RECOMPILATION ******************************************************** #

re: fclean all
# The re rule is used to recompile the project from scratch.

.PHONY: all clean fclean re libft
# The .PHONY rule is used to avoid conflicts with the files with the same name.

# ***** THE END ************************************************************** #
