# ***** APARIENCE ************************************************************ #

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
DEFAULT = \033[0m

# ***** NAMES **************************************************************** #

NAME = minitalk 
NAME_B = minitalk_bonus

# ***** SOURCES ************************************************************** #

SRC_client = client.c
SRC_server = server.c
NAME_C = client
NAME_S = server
NAME_C_B = client_bonus
NAME_S_B = server_bonus
SRC_cbonus = client_bonus.c
SRC_sbonus = server_bonus.c 

# ***** OBJECTS ************************************************************** #

OBJ_client = $(SRC_client:.c=.o) 
OBJ_server = $(SRC_server:.c=.o)
OBJ_cbonus = $(SRC_cbonus:.c=.o)
OBJ_sbonus = $(SRC_sbonus:.c=.o)

# ***** COMPILATION ********************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make -C
MKD = mkdir -p
MCL = make clean -C
MFCL = make fclean -C

# ***** DIRECTORIES ********************************************************** #

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
FTPRINTF_DIR = ./ft_printf
FTPRINTF_A = $(FTPRINTF_DIR)/libftprintf.a
OBJ_DIR = ./obj
lFLAGS = -L./libft -lft -L./ft_printf -lftprintf

# ***** RULES **************************************************************** #

all: $(NAME) $(NAME_B)

$(NAME): ftlibft ftprintf $(OBJ_client) $(OBJ_server)
	@echo "$(YELLOW)Compiling root ...$(NAME)$(DEFAULT)"
	$(CC) $(CFLAGS) $(OBJ_client) $(lFLAGS) -o $(NAME_C)
	$(CC) $(CFLAGS) $(OBJ_server) $(lFLAGS) -o $(NAME_S)
	@echo "$(GREEN)$(NAME) COMPILED$(DEFAULT)"

$(NAME_B): ftlibft ftprintf $(OBJ_cbonus) $(OBJ_sbonus)
	@echo "$(YELLOW)Compiling bonus ...$(NAME_B)$(DEFAULT)"
	$(CC) $(CFLAGS) $(OBJ_cbonus) $(lFLAGS) -o $(NAME_C_B)
	$(CC) $(CFLAGS) $(OBJ_sbonus) $(lFLAGS) -o $(NAME_S_B)
	@echo "$(GREEN)$(NAME_B) COMPILED$(DEFAULT)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ftlibft:
	@echo "$(YELLOW)Compiling libft ...$(DEFAULT)"
	$(MK) $(LIBFT_DIR)
	@echo "$(GREEN)libft COMPILED$(DEFAULT)"

ftprintf:
	@echo "$(YELLOW)Compiling ft_printf ...$(DEFAULT)"
	$(MK) $(FTPRINTF_DIR)
	@echo "$(GREEN)ft_printf COMPILED$(DEFAULT)"

# ***** CLEANING ************************************************************* #

clean:
	@echo "$(RED)Cleaning ...$(DEFAULT)"
	$(RM) $(OBJ_client) $(OBJ_server) $(OBJ_cbonus) $(OBJ_sbonus)
	$(MCL) $(LIBFT_DIR)
	$(MCL) $(FTPRINTF_DIR)
	@echo "$(GREEN)CLEANED$(DEFAULT)"

fclean: clean
	@echo "$(RED)Full cleaning ...$(DEFAULT)"
	$(RM) $(NAME_C) $(NAME_S) $(NAME_C_B) $(NAME_S_B)
	$(MFCL) $(LIBFT_DIR)
	$(MFCL) $(FTPRINTF_DIR)
	@echo "$(GREEN)FULL CLEANED$(DEFAULT)"

re: fclean all
	@echo "$(YELLOW)Recompiling ...$(DEFAULT)"
	@echo "ReCOMPILED"

# ***** PHONY **************************************************************** #

.PHONY: all bonus ftlibft ftprintf clean fclean re

# ***** THE END ************************************************************** #
