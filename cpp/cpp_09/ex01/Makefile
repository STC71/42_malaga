# ---- MAKEFILE ----------------------------------------------------------------

# ---- compiler and flags ------------------------------------------------------

NAME = RPN

TITLE = "🔥 [CPP_09] [EX01] Reverse Polish Notation"

SRC = main.cpp \
		RPN.cpp
		

CXX = c++ 

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address

# ---- rules -------------------------------------------------------------------

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME) 

$(NAME): $(SRC)
	@echo "$(RED)Compiling $(TITLE) 🛠️ $(RESET)"
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)
	@echo "$(GREEN)$(NAME) is ready ✅$(RESET)"

	@echo "$(BLUE) ____  ____  _   _ "
	@echo "|  _ \|  _ \| \ | |"
	@echo "| |_) | |_) |  \| |"
	@echo "|  _ <|  __/| |\  |"
	@echo "|_| \_\_|   |_| \_|"
	@echo "$(YELLOW) Reverse Polish Notation "
	@echo "$(RESET)"
	@echo " Usage:$(BLUE) ./RPN ''operations''"
	@echo "$(RESET)"

clean: 
	@echo "$(RED)Cleaning $(TITLE) 🧹 $(RESET)"
	@rm -rf $(NAME)
	@echo "$(GREEN)$(NAME) is cleaned ✅$(RESET)"

fclean: clean
	@echo "$(RED)Full cleaning $(TITLE) 🧹 $(RESET)"
	@rm -rf $(NAME)
	@echo "$(GREEN)$(NAME) is fully cleaned ✅$(RESET)"

# ---- colors ------------------------------------------------------------------

DEF_COLOR = \033[0m

BROWN   = \033[33;1m
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
DARK_GREEN = \033[32;1m
WHITE   = \033[37;1m
GRAY    = \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD    = \033[1m
RED     = \033[31;1m

RESET   = \033[0m

# ---- recompilation -----------------------------------------------------------

re: fclean all

# ---- phony -------------------------------------------------------------------

.PHONY: all clean fclean re

# ---- end ---------------------------------------------------------------------