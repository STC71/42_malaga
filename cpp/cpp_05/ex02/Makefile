# ---- MAKEFILE ----------------------------------------------------------------

NAME = forms

TITLE = "🔥 [CPP_05] [EX02] No, you need form 28B, not 28C... 📝"

SRC = AForm.cpp \
		Bureaucrat.cpp \
		main.cpp \
		PresidentialPardonForm.cpp \
		RobotomyRequestForm.cpp \
		ShrubberyCreationForm.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++ 

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 

# ---- rules -------------------------------------------------------------------

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)

	@echo "Compiling $(TITLE) 🛠️"
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo "$(NAME) is ready ✅"
	@echo ""
	./$(NAME)
	@echo ""
	@echo "Cleaning $(TITLE) 🧹"
	@rm -rf $(OBJ)
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