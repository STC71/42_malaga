# ***** NAMES ***************************************************************** #

NAME 			= so_long
BONUS_NAME		= so_long_bonus

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
MLX42 			= ./MLX42
LIBFT 			= ./libft
FT_PRINTF 		= ./ft_printf
INCLUDES 		= -I$(MLX42)/include -I$(LIBFT)/include -I$(FT_PRINTF)/include -Iincludes
LIBS 			= -L$(MLX42)/lib -lmlx42 -lglfw -ldl -lm -lpthread -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf

# ***** DIRECTORIES ********************************************************* #

SRC_DIR 		= ./srcs
SRC_BONUS_DIR 	= ./srcs_bonus
OBJ_DIR 		= ./obj
OBJ_BONUS_DIR 	= ./obj_bonus

# ***** FILES *************************************************************** #

SRC_FILES 		= so_long.c \
					ft_tools.c \
					ft_moves.c \
					ft_materials.c \
					ft_mlx_init.c \
					ft_initialize.c \
					ft_free_tools.c \
					ft_drawing_tools.c \
					ft_drawing_moves.c \
					ft_check_game.c \
					ft_cells.c \
					ft_check_tools.c 
SRC_BONUS_FILES = so_long_bonus.c \
					ft_tools_bonus.c \
					ft_moves_bonus.c \
					ft_materials_bonus.c \
					ft_mlx_init_bonus.c \
					ft_initialize_bonus.c \
					ft_free_tools_bonus.c \
					ft_drawing_tools_bonus.c \
					ft_drawing_moves_bonus.c \
					ft_check_game_bonus.c \
					ft_cells_bonus.c \
					ft_check_tools_bonus.c 

OBJS 			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJS_BONUS 		= $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_BONUS_FILES:.c=.o))

# ***** RULES *************************************************************** #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(CYAN)Compiling:$(DEF_COLOR) $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled:$(DEF_COLOR) $<"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@echo "$(CYAN)Compiling:$(DEF_COLOR) $<"
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled:$(DEF_COLOR) $<"

$(NAME): $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a $(OBJS)
	@echo "$(CYAN)Linking:$(DEF_COLOR) $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)Linked:$(DEF_COLOR) $(NAME)"

$(BONUS_NAME): $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a $(OBJS_BONUS)
	@echo "$(CYAN)Linking:$(DEF_COLOR) $(BONUS_NAME)"
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS) $(LIBS)
	@echo "$(GREEN)Linked:$(DEF_COLOR) $(BONUS_NAME)"

# ***** DEPENDENCIES ******************************************************** #

$(LIBFT)/libft.a:
	@echo "$(CYAN)Compiling:$(DEF_COLOR) $(LIBFT)"
	@$(MAKE) -C $(LIBFT)
	@echo "$(GREEN)Compiled:$(DEF_COLOR) $(LIBFT)"

$(FT_PRINTF)/libftprintf.a:
	@echo "$(CYAN)Compiling:$(DEF_COLOR) $(FT_PRINTF)"
	@$(MAKE) -C $(FT_PRINTF)
	@echo "$(GREEN)Compiled:$(DEF_COLOR) $(FT_PRINTF)"

# ***** PRINCIPAL RULES ***************************************************** #

all: 	$(NAME) $(BONUS_NAME)
bonus: 	$(BONUS_NAME)

# ***** CLEANING RULES ****************************************************** #

clean:
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(OBJ_DIR)"
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(OBJ_BONUS_DIR)"
	@$(MAKE) -C $(FT_PRINTF) clean
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(OBJ_DIR)"
	@$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "$(GREEN)Cleaned:$(DEF_COLOR) $(OBJ_DIR) $(OBJ_BONUS_DIR)"

# ***** FCLEANING RULES ***************************************************** #

fclean: clean
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(NAME)"
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(BONUS_NAME)"
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(LIBFT)/libft.a"
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(FT_PRINTF)/libftprintf.a"
	@echo "$(RED)Cleaning:$(DEF_COLOR) $(MLX42)/lib/libmlx42.a"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(GREEN)Cleaned:$(DEF_COLOR) $(NAME) $(BONUS_NAME) $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a $(MLX42)/lib/libmlx42.a"

# ***** RE RULES *********************************************************** #

re: fclean all
	@echo "$(GREEN)Recompiled:$(DEF_COLOR) $(NAME) $(BONUS_NAME)"

# ***** PHONY *************************************************************** #

.PHONY: all clean fclean re

# ***** THE END ************************************************************** #
