########################################
### Makefile for the webserv project ###
########################################

NAME = webserv
CONFIG_FILE = config/default.conf

SRCS = srcs/main.cpp \
       srcs/Server.cpp \
       srcs/Config.cpp \
       srcs/Request.cpp \
       srcs/Response.cpp \
       srcs/CGI.cpp

OBJS = $(SRCS:srcs/%.cpp=obj/%.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -D_GLIBCXX_USE_CXX11_ABI=0

INC = -I include

all: setup-permissions $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)... ⏳"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully! 🎉"
	@echo ""
	@echo "██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗"
	@echo "██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║"
	@echo "██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║"
	@echo "██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝"
	@echo "╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ "
	@echo " ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  "
	@echo ""
	@echo "         🎯 by druiz-ca, rdel-olm & sternero (2025) 🎯"
	@echo ""
	@echo "🚀 HTTP Server ready to serve! Execute with: ./$(NAME) $(CONFIG_FILE)"
	@echo "📋 Ready for evaluation? Try: ./evaluation.sh"
	@echo "🏛️  Need Siege for evaluation? Install and run with: ./siege_test.sh"
	@echo "🔥 Want to stress test? Try: ./stress_tests.sh (destructive tests!)"
	@echo ""

obj/%.o: srcs/%.cpp
	@if [ ! -d obj ]; then mkdir -p obj; echo "Creating object directory obj... 🗂️"; echo "Object directory created. ✅"; fi
	@echo "Compiling $< into $@... 📄"
	@$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@
	@echo "$< compiled into $@ successfully. ✅"

setup-permissions:
	@echo "🔧 Setting up project permissions..."
	@chmod +x *.sh 2>/dev/null || true
	@if [ -f "./chmods.sh" ]; then ./chmods.sh >/dev/null 2>&1; fi
	@echo "✅ Permissions configured!"

clean:
	@echo "Cleaning object files... 🧹"
	@rm -rf obj
	@echo "Object files cleaned! ✅"

fclean: clean
	@echo "Cleaning $(NAME)... 🧹"
	@rm -f $(NAME)
	@echo "$(NAME) cleaned! ✅"
	@echo "Cleaning evaluation log files... 🗂️"
	@rm -f evaluation_results.log server_eval.log valgrind_detailed.log compile.log *.log
	@echo "Evaluation log files cleaned! ✅"
	@echo "Cleaning siege logs directory... 📊"
	@rm -rf logs/
	@echo "Siege logs directory cleaned! ✅"
	@echo "Cleaning siege configuration... ⚙️"
	@rm -f .siegerc
	@echo "Siege configuration cleaned! ✅"
	@echo "Cleaning evaluation status files... 📄"
	@rm -f evaluation_status.md EVALUATION_STATUS.md *.md
	@echo "Evaluation status files cleaned! ✅"

re: fclean all

.PHONY: all setup-permissions clean fclean re