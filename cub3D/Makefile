# ----- Makefile for Cub3D project ------------------------------------------- #

MAKEFLAGS += --no-print-directory

NAME = cub3D
NAME_BNS = cub3D_bonus

# ----- Values --------------------------------------------------------------- #

CC = gcc
RM = rm -rf

# ----- Flags -----------------------------------------------------------------#

FLAGS = -g -Wall -Werror -Wextra -Iinclude #-fsanitize=address
MLX_FLAGS = -ldl -lglfw -pthread -lm

# ----- Librairies ----------------------------------------------------------- #

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
MLX_PATH = ./MLX42/lib
MLX = $(MLX_PATH)/libmlx42.a

# ----- Files ---------------------------------------------------------------- #

FILES =	ft_action \
					ft_calculations \
					ft_check_1 \
					ft_check_2 \
					ft_check_3 \
					ft_check_4 \
					ft_check_5 \
					ft_colors_1 \
					ft_colors_2 \
					ft_errors \
					ft_impact_ray \
					ft_init \
					ft_moves \
					ft_paint \
					ft_parse_1 \
					ft_parse_2 \
					ft_ray \
					ft_remove \
					ft_tools \
					ft_walls \

BNS_FILES = ft_action_bonus \
					ft_animation_bonus \
					ft_calculations_bonus \
					ft_check_1_bonus \
					ft_check_2_bonus \
					ft_check_3_bonus \
					ft_check_4_bonus \
					ft_check_5_bonus \
					ft_colors_1_bonus \
					ft_colors_2_bonus \
					ft_door_bonus \
					ft_errors_bonus \
					ft_impact_ray_bonus \
					ft_init_1_bonus \
					ft_init_2_bonus \
					ft_minimap \
					ft_moves_bonus \
					ft_paint_bonus \
					ft_parse_1_bonus \
					ft_parse_2_bonus \
					ft_ray_bonus \
					ft_remove_bonus \
					ft_tools_bonus \
					ft_walls_bonus \

# ----- Rules ---------------------------------------------------------------- #

$(shell mkdir -p ./src/obj)
$(shell mkdir -p ./src_bonus/obj)

SRCS_DIR = ./src/
OBJS_DIR = ./src/obj/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

BNS_SRC_DIR = ./src_bonus/
BNS_OBJ_DIR = ./src_bonus/obj/
BNS_SRCS = $(addprefix $(BNS_SRC_DIR), $(addsuffix .c, $(BNS_FILES)))
BNS_OBJS = $(addprefix $(BNS_OBJ_DIR), $(addsuffix .o, $(BNS_FILES)))

# ----- Compilation ---------------------------------------------------------- #

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(BNS_OBJ_DIR)%.o: $(BNS_SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(MLX) $(LIBFT) $(FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo " "
	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME} is done!${DEF_COLOR}"
	@echo " "
	@echo "${BLUE}                  █     ${YELLOW}█████ █████"
	@echo "${BLUE}      █████       █     ${YELLOW}    █ █    █"
	@echo "${BLUE}      █     █   █ █████ ${YELLOW}█████ █    █"
	@echo "${BLUE}      █     █   █ █   █ ${YELLOW}    █ █    █"
	@echo "${BLUE}      █████ █████ █████ ${YELLOW}█████ █████"
	@echo " "
	@echo "${DARK_GREEN}	  By: sternero & druiz-ca"
	@echo " "
	@echo "${YELLOW}  🤪 Welcome to the ${NAME} experience! 🤪"
	@echo " "

bonus: $(NAME_BNS)

$(NAME_BNS): $(MLX) $(LIBFT) $(BNS_OBJS)
	@$(CC) $(BNS_OBJS) $(MLX) $(LIBFT) $(FLAGS) $(MLX_FLAGS) -o $(NAME_BNS)
	@echo " "
	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME_BNS} is done!${DEF_COLOR}"
	@echo " "
	@echo "${BLUE}             █     ${YELLOW}█████ █████  ${BROWN}█                        ████"
	@echo "${BLUE} █████       █     ${YELLOW}    █ █    █ ${BROWN}█                       █"
	@echo "${BLUE} █     █   █ █████ ${YELLOW}█████ █    █ ${BROWN}█████ █████ ████  █   █  ███"
	@echo "${BLUE} █     █   █ █   █ ${YELLOW}    █ █    █ ${BROWN}█   █ █   █ █   █ █   █     █"
	@echo "${BLUE} █████ █████ █████ ${YELLOW}█████ █████  ${BROWN}█████ █████ █   █ █████ ████"
	@echo " "
	@echo "${DARK_GREEN}	           By: druiz-ca & sternero"
	@echo " "
	@echo "${YELLOW}        🤪 Welcome to the ${NAME_BNS} experience! 🤪"
	@echo " "

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(MLX):
	@make -C ./MLX42 all

# ----- Clean ---------------------------------------------------------------- #

clean: 
	@$(RM) $(OBJS) $(BNS_OBJS) $(OBJS_DIR)/charge_flag_makefile/charge.flag
	@make -C $(LIBFT_PATH) clean
#@make -C $(MLX_PATH) clean
	@$(RM) $(OBJS_DIR)/charge_flag_makefile/bonus.flag:
	@echo
	@echo "$(RED)🧹 Cleaning Cub3D objects 🧹 $(RESET)"
	$(shell rm -rf ./src/obj)
	$(shell rm -rf ./src_bonus/obj)
	@echo "$(DARK_GREEN)🌪️💥 Cleaned Cub3D objects ✅ $(RESET)"

# ----- Fclean --------------------------------------------------------------- #

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS) 
#$(MLX)
	@make -C $(LIBFT_PATH) fclean
	@echo
	@echo "$(RED)🧹 Cleaning Cub3D executables 🧹$(RESET)"
	@echo "$(DARK_GREEN)🌪️💥 Cleaned Cub3D executables ✅$(RESET)"
	@echo

# ----- Recompilation -------------------------------------------------------- #

re: fclean setup $(NAME)

setup:
	$(shell mkdir -p ./src/obj)
	$(shell mkdir -p ./bonus/src/obj)

# ----- Phony ---------------------------------------------------------------- #

.PHONY: clean fclean re all bonus setup

# ----- Colors --------------------------------------------------------------- #

DARK_GREEN = \033[32;1m
DEF_COLOR = \033[0m
BROWN   = \033[38;2;184;143;29m
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY    = \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD    = \033[1m
RED     = \033[31;1m

# ----- Rule for the charging bar -------------------------------------------- #

$(OBJS_DIR)/charge_flag_makefile/charge.flag:
	@echo
	@echo -n "$(GREEN)Compiling: $(RESET)["
	@for i in $$(seq 1 2); do \
		echo -n "##"; \
		sleep 0.20; \
	done
	@for i in $$(seq 1 6); do \
		echo -n "####"; \
		sleep 0.10; \
	done
	@echo "] $(GREEN)Done!$(RESET)"
	@touch $(OBJS_DIR)/charge_flag_makefile/charge.flag

# ----- Rule for the bonus charging bar -------------------------------------- #

$(OBJS_DIR)/charge_flag_makefile/bonus.flag:
	@echo
	@echo -n "$(YELLOW)Compiling bonus: $(RESET)["
	@for i in $$(seq 1 2); do \
		echo -n "##"; \
		sleep 0.20; \
	done
	@for i in $$(seq 1 6); do \
		echo -n "####"; \
		sleep 0.10; \
	done
	@echo "] $(YELLOW)Done!$(RESET)"
	@touch $(OBJS_DIR)/charge_flag_makefile/bonus.flag

# ----- End of Makefile ------------------------------------------------------ #