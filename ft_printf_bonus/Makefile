# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 12:00:00 by sternero          #+#    #+#              #
#    Updated: 2024/11/13 12:00:00 by sternero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

# Mandatory Part
SRCS		= ft_printf.c \
			  ft_utils.c \
			  ft_putnbr.c \
			  ft_putptr.c

# Bonus Part  
SRCS_BONUS	= ft_printf_bonus.c \
			  ft_parse_bonus.c \
			  ft_dispatch_bonus.c \
			  ft_utils_bonus.c \
			  ft_numlen_bonus.c \
			  ft_putnbr_bonus.c \
			  ft_putunsigned_bonus.c \
			  ft_putptr_bonus.c

OBJS_DIR	= obj/
OBJS		= $(SRCS:%.c=$(OBJS_DIR)%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=$(OBJS_DIR)%.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f
MKDIR		= mkdir -p

RESET		= \033[0m
GREEN		= \033[38;5;46m
CYAN		= \033[38;5;51m
YELLOW		= \033[38;5;226m
MAGENTA		= \033[38;5;201m
PURPLE		= \033[38;5;141m
BOLD		= \033[1m

.PHONY: all bonus clean fclean re test help

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@printf "\n$(CYAN)$(BOLD)"
	@printf "     ███████╗████████╗     ██████╗ ██████╗ ██╗███╗   ██╗████████╗███████╗\n"
	@printf "     ██╔════╝╚══██╔══╝     ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝██╔════╝\n"
	@printf "     █████╗     ██║        ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   █████╗  \n"
	@printf "     ██╔══╝     ██║        ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ██╔══╝  \n"
	@printf "     ██║        ██║███████╗██║     ██║  ██║██║██║ ╚████║   ██║   ██║     \n"
	@printf "     ╚═╝        ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     \n"
	@printf "$(RESET)\n"
	@printf "    $(PURPLE)════════════════════════════════════════════════════════════════════$(RESET)\n"
	@printf "    \n"
	@printf "         $(YELLOW)Proyecto:$(RESET) ft_printf                $(YELLOW)Autor:$(RESET) sternero\n"
	@printf "         $(YELLOW)Escuela:$(RESET) 42 Málaga                 $(YELLOW)Versión:$(RESET) Mandatory\n"
	@printf "         \n"
	@printf "         $(CYAN)\"Versión básica - Sin flags ni modificadores\"$(RESET)\n"
	@printf "         \n"
	@printf "    $(PURPLE)════════════════════════════════════════════════════════════════════$(RESET)\n\n"
	@printf "    $(CYAN)🔨 Compilando archivos fuente...$(RESET)\n"
	@$(AR) $(NAME) $(OBJS)
	@printf "    $(CYAN)📦 Creando biblioteca libftprintf.a...$(RESET)\n"
	@printf "    $(GREEN)$(BOLD)✅ ¡libftprintf.a creado exitosamente!$(RESET)\n"
	@printf "    \n"
	@printf "    $(YELLOW)💡 Tip: Usa $(CYAN)make bonus$(YELLOW) para compilar con todas las características$(RESET)\n"
	@printf "    $(YELLOW)    o $(CYAN)make help$(YELLOW) para ver todas las opciones$(RESET)\n\n"

bonus: $(OBJS_DIR) $(OBJS_BONUS)
	@printf "\n$(CYAN)$(BOLD)"
	@printf "     ███████╗████████╗     ██████╗ ██████╗ ██╗███╗   ██╗████████╗███████╗\n"
	@printf "     ██╔════╝╚══██╔══╝     ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝██╔════╝\n"
	@printf "     █████╗     ██║        ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   █████╗  \n"
	@printf "     ██╔══╝     ██║        ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ██╔══╝  \n"
	@printf "     ██║        ██║███████╗██║     ██║  ██║██║██║ ╚████║   ██║   ██║     \n"
	@printf "     ╚═╝        ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     \n"
	@printf "$(RESET)\n"
	@printf "    $(PURPLE)════════════════════════════════════════════════════════════════════$(RESET)\n"
	@printf "    \n"
	@printf "         $(YELLOW)Proyecto:$(RESET) ft_printf                $(YELLOW)Autor:$(RESET) sternero\n"
	@printf "         $(YELLOW)Escuela:$(RESET) 42 Málaga                 $(YELLOW)Objetivo:$(RESET) 125%%\n"
	@printf "         \n"
	@printf "         $(MAGENTA)\"Porque ft_putnbr() y ft_putstr() no son suficientes...\"$(RESET)\n"
	@printf "         \n"
	@printf "    $(PURPLE)════════════════════════════════════════════════════════════════════$(RESET)\n\n"
	@printf "    $(CYAN)🔨 Compilando archivos fuente...$(RESET)\n"
	@$(RM) $(NAME)
	@$(AR) $(NAME) $(OBJS_BONUS)
	@printf "    $(CYAN)📦 Creando biblioteca libftprintf.a...$(RESET)\n"
	@printf "    $(GREEN)$(BOLD)✅ ¡libftprintf.a creado exitosamente!$(RESET)\n"
	@printf "    \n"
	@printf "    $(GREEN)$(BOLD)🎉 Compilación completada - Listo para evaluación 125%%$(RESET)\n\n"

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c
	@printf "$(CYAN)  🔨 Compiling: %-30s$(RESET) " "$<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)✓$(RESET)\n"

clean:
	@printf "\n$(YELLOW)$(BOLD)🧹 Cleaning object files...$(RESET)\n"
	@$(RM) -r $(OBJS_DIR)
	@printf "$(GREEN)$(BOLD)✅ Object files removed!$(RESET)\n\n"

fclean: clean
	@printf "$(YELLOW)$(BOLD)🗑️  Removing $(NAME) and test binary...$(RESET)\n"
	@$(RM) $(NAME) ft_test
	@printf "$(GREEN)$(BOLD)✅ Full cleanup completed!$(RESET)\n\n"

re: fclean bonus

# Test
test: all bonus
	@printf "\n$(PURPLE)$(BOLD)🧪 Compiling full test suite...$(RESET)\n"
	@$(CC) $(CFLAGS) ft_test.c $(NAME) -o ft_test
	@printf "$(GREEN)$(BOLD)✅ Test compiled$(RESET)\n"
	@printf "\n$(PURPLE)$(BOLD)▶️  Running complete test battery (mandatory + bonus)...$(RESET)\n\n"
	@./ft_test

# Help
help:
	@printf "\n$(CYAN)$(BOLD)╔══════════════════════════════════════════════════════════════╗$(RESET)\n"
	@printf "$(CYAN)$(BOLD)║              FT_PRINTF - BUILD SYSTEM                        ║$(RESET)\n"
	@printf "$(CYAN)$(BOLD)╚══════════════════════════════════════════════════════════════╝$(RESET)\n\n"
	@printf "$(GREEN)$(BOLD)Available targets:$(RESET)\n\n"
	@printf "  $(YELLOW)make$(RESET) or $(YELLOW)make all$(RESET)\n"
	@printf "      Compiles mandatory part only\n"
	@printf "      Generates: $(CYAN)libftprintf.a$(RESET) (without flags)\n\n"
	@printf "  $(MAGENTA)make bonus$(RESET)\n"
	@printf "      Compiles with all bonus features\n"
	@printf "      Supported flags: $(CYAN)- 0 . # + space *$(RESET)\n"
	@printf "      Generates: $(CYAN)libftprintf.a$(RESET) (full version)\n\n"
	@printf "  $(PURPLE)make test$(RESET)\n"
	@printf "      Compiles BOTH versions (mandatory + bonus)\n"
	@printf "      Then runs complete test suite\n"
	@printf "      Executes: $(CYAN)54 tests$(RESET) (mandatory + bonus)\n\n"
	@printf "  $(YELLOW)make clean$(RESET)\n"
	@printf "      Removes object files (*.o)\n"
	@printf "      Keeps: $(CYAN)libftprintf.a$(RESET)\n\n"
	@printf "  $(YELLOW)make fclean$(RESET)\n"
	@printf "      Full cleanup (objects + library + test)\n"
	@printf "      Removes: everything except source code\n\n"
	@printf "  $(GREEN)make re$(RESET)\n"
	@printf "      Complete recompilation (fclean + bonus)\n"
	@printf "      Useful after modifying .h files\n\n"
	@printf "  $(CYAN)make help$(RESET)\n"
	@printf "      Shows this help\n\n"
	@printf "$(GREEN)$(BOLD)Typical usage:$(RESET)\n\n"
	@printf "  $(CYAN)1.$(RESET) make bonus          $(GREEN)# Compile full version$(RESET)\n"
	@printf "  $(CYAN)2.$(RESET) make test           $(GREEN)# Verify functionality$(RESET)\n"
	@printf "  $(CYAN)3.$(RESET) make fclean         $(GREEN)# Clean before submission$(RESET)\n\n"
	@printf "$(PURPLE)$(BOLD)Generated files:$(RESET)\n"
	@printf "  • $(CYAN)libftprintf.a$(RESET)       - Static library\n"
	@printf "  • $(CYAN)obj/*.o$(RESET)             - Object files\n"
	@printf "  • $(CYAN)ft_test$(RESET)             - Test executable\n\n"
	@printf "$(YELLOW)For more info: cat README.md$(RESET)\n\n"
