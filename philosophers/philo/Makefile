# ***** NAMES ***************************************************************** #

NAME 			= philo

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
RM 				= rm -f

# ***** DIRECTORIES ********************************************************** #

SRCS			= srcs/philo.c \
                	srcs/ft_check.c \
					srcs/ft_tools.c 
                    

# The variable SRCS is used to get all the source files in the SRCS directory.
# The variable SRCS_BONUS is used to get all the source files in the 
# bonus and the SRCS directory. 

OBJS			= $(SRCS:.c=.o)

# .c=.o is used to replace the .c extension with the .o extension.

OBJS_DIR		= ./objs
INCLUDES		= ./includes

# ***** COMPILATION ********************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@echo "${DARK_YELLOW}${BOLD}Compiling my ${NAME}... ${DEF_COLOR}"
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME} is done!${DEF_COLOR}"

philo/%.o: philo/%.c
	@ $(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
	@echo "${BLUE}${BOLD}Compiling $<...${DEF_COLOR}"

# ***** CLEANING ************************************************************* #

clean:
	@${RM} ${OBJS}
	@echo "${RED}${BOLD}Cleaning objects...${DEF_COLOR}"
	@if [ -d "$(OBJS_DIR)" ]; then ${RM} -r $(OBJS_DIR); fi
	@echo "${GREEN}${BOLD}Cleaning objects of ${NAME} is done!${DEF_COLOR}"

fclean: clean
	@${RM} ${NAME}
	@echo "${RED}${BOLD}Cleaning ${NAME}...${DEF_COLOR}"
	@echo "${GREEN}${BOLD}Cleaning all of ${NAME} is done!${DEF_COLOR}"

# clean_screen:
#	@clear
# 	@echo "${DARK_YELLOW}${BOLD}Screen cleaned... let's go there! ${DEF_COLOR}"

re: fclean all
	@echo "${DARK_GREEN}${BOLD}Recompilation is done!${DEF_COLOR}"

.PHONY: all clean fclean re