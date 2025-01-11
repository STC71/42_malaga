# ---- MAKEFILE ----------------------------------------------------------------

# ---- compiler and flags ------------------------------------------------------

NAME = megaphone

SRC = megaphone.cpp

CXX = c++ 

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 

# ---- rules -------------------------------------------------------------------

all: $(NAME) 

$(NAME): $(SRC)
	@echo "$(RED)Compiling $(NAME) 🛠️ $(RESET)"
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)
	@echo "$(GREEN)$(NAME) is ready ✅$(RESET)"

clean: 
	@echo "$(RED)Cleaning $(NAME) 🧹 $(RESET)"
	@rm -rf megaphone
	@echo "$(GREEN)$(NAME) is cleaned ✅$(RESET)"

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

re: clean all

# ---- phony -------------------------------------------------------------------

.PHONY: all clean re

# ---- end ---------------------------------------------------------------------