# ***** NAMES ***************************************************************** #

NAME 			= philo_bonus

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

SRCS			= srcs/ft_check.c \
                	srcs/ft_controller.c \
					srcs/ft_eat_n_think.c \
					srcs/ft_forks.c \
					srcs/ft_free_tools.c \
					srcs/ft_gettering_a.c \
					srcs/ft_gettering_b.c \
					srcs/ft_gettering_c.c \
					srcs/ft_init.c \
					srcs/ft_philo_bonus.c \
					srcs/ft_printing.c \
					srcs/ft_sleep.c \
					srcs/ft_tools_1.c \
					srcs/ft_tools_2.c \
                    

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
	@echo "    ____  __    _ __                       __                     "
	@echo "   / __ \/ /_  (_) /___  _________  ____  / /_  ___  __________   "
	@echo "  / /_/ / __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/   "
	@echo " / ____/ / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  )    "
	@echo "/_/   /_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/     "
	@echo "                                /_/                               "
	@echo " "
	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME} is done! 👌${DEF_COLOR}"
	@echo " "
	@echo "${BDYELLOW}	Remember, 😡 you must enter...${DEF_COLOR}"
	@echo " "
	@echo " "
	@echo "./philo +";
	@echo "number of philosophers (must be a number between 1 and 200) +"
	@echo "time to die (must be a number greater than 60 ms.) +"
	@echo "time to eat (must be a number greater than 60 ms.) +"
	@echo "time to sleep (must be a number greater than 60 ms.) ..."
	@echo " "
	@echo "${DARK_GREEN}😳 Optionally ${DEF_COLOR}: the number of times each phyllo must eat."
	@echo " "
	@echo "${DARK_GREEN}Now let's see an example:	${DEF_COLOR}./philo 4 800 200 200 5"
	@echo " "
	@echo "This will create 4 philosophers," 
	@echo "each with a time to die 😭 of 800 ms,"
	@echo "a time to eat 🤤 of 200 ms, a time to sleep 🥱 of 200 ms,"
	@echo "and each philosopher must eat 5 times."
	@echo " "
	@echo "${BDYELLOW}	😵‍💫 Don't be confused ${DEF_COLOR}... and enjoy the experience. 🤪"
	@echo " "
	@echo " "

@philo/%.o: philo/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
	@echo "${BLUE}${BOLD}Compiling $<...${DEF_COLOR}"

# ***** CLEANING ************************************************************* #

clean:
	@${RM} ${OBJS}
	@echo "${RED}${BOLD}Cleaning objects...${DEF_COLOR}"
	@ if [ -d "$(OBJS_DIR)" ]; then ${RM} -r $(OBJS_DIR); fi
	@echo "${GREEN}${BOLD}Cleaning objects of ${NAME} is done! 💥${DEF_COLOR}"

fclean: clean
	@${RM} ${NAME}
	@echo "${RED}${BOLD}Cleaning ${NAME}...${DEF_COLOR}"
	@echo "${GREEN}${BOLD}Cleaning all of ${NAME} is done! 💥💥${DEF_COLOR}"

# clean_screen:
#	@clear
# 	@echo "${DARK_YELLOW}${BOLD}Screen cleaned... let's go there! ${DEF_COLOR}"

re: fclean all
	@echo "${DARK_GREEN}${BOLD}Recompilation is done! 👌${DEF_COLOR}"

.PHONY: all clean fclean re