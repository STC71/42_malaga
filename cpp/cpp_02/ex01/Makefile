# ---- MAKEFILE ----------------------------------------------------------------

NAME = fixed

TITLE = "🔥 [CPP_02] [EX01] Towards a more useful fixed-point number class "

# ---- rules -------------------------------------------------------------------

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all:

	@echo "Compiling $(TITLE) 🛠️"
	c++ *.cpp -Wall -Wextra -Werror -std=c++98 -o $(NAME)
	@echo "$(NAME) is ready ✅"
	@echo ""
	./$(NAME)
	@echo ""
	@echo "Cleaning $(TITLE) 🧹"
	@rm -rf $(NAME)
	@echo "$(NAME) is cleaned ✅"

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

# ---- end ---------------------------------------------------------------------