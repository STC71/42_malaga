# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: sternero <sternero@student.42.fr>        +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/08/03 00:00:00 by sternero          #+#    #+#             #
#    Updated: 2025/08/03 00:00:00 by sternero         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
BOLD = \033[1m
RESET = \033[0m

# Project configuration
COMPOSE_FILE = srcs/docker-compose.yml
ENV_FILE = .env

# ASCII Art
define INCEPTION_LOGO
$(CYAN)$(BOLD)\
██╗███╗   ██╗ ██████╗███████╗██████╗ ████████╗██╗ ██████╗ ███╗   ██╗\
██║████╗  ██║██╔════╝██╔════╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║\
██║██╔██╗ ██║██║     █████╗  ██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║\
██║██║╚██╗██║██║     ██╔══╝  ██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║\
██║██║ ╚████║╚██████╗███████╗██║        ██║   ██║╚██████╔╝██║ ╚████║\
╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\
$(RESET)
endef

# Default target
all: create_dirs up success

# Display banner (optional - can be called independently)
banner:
	@echo "$(CYAN)$(BOLD)"
	@echo "██╗███╗   ██╗ ██████╗███████╗██████╗ ████████╗██╗ ██████╗ ███╗   ██╗"
	@echo "██║████╗  ██║██╔════╝██╔════╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║"
	@echo "██║██╔██╗ ██║██║     █████╗  ██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║"
	@echo "██║██║╚██╗██║██║     ██╔══╝  ██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║"
	@echo "██║██║ ╚████║╚██████╗███████╗██║        ██║   ██║╚██████╔╝██║ ╚████║"
	@echo "╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝"
	@echo "$(RESET)"
	@echo "$(BLUE)$(BOLD)          🐳 Docker Infrastructure Project - 42 Málaga$(RESET)"
	@echo "$(BLUE)$(BOLD)          ============================================$(RESET)"
	@echo "$(BLUE)$(BOLD)                        - sternero (2025) -$(RESET)"
	@echo ""

# Check if .env file exists and validate
check_env:
	@if [ ! -f $(ENV_FILE) ]; then \
		echo "$(RED)$(BOLD)⚠️  ERROR: .env file not found!$(RESET)"; \
		echo "$(RED)   Configuration file is required to run Inception.$(RESET)"; \
		echo ""; \
		echo "$(CYAN)Would you like to create it now? (y/n):$(RESET)"; \
		read -r response; \
		if [ "$$response" = "y" ] || [ "$$response" = "Y" ]; then \
			echo "$(GREEN)🚀 Launching environment configuration...$(RESET)"; \
			./create_env.sh; \
		else \
			echo "$(RED)❌ Cannot proceed without .env file. Exiting.$(RESET)"; \
			exit 1; \
		fi; \
	fi

# Create data directories
create_dirs: check_env
	@echo "$(YELLOW)📁 Creating data directories...$(RESET)"
	@. ./$(ENV_FILE) && mkdir -p "$$WORDPRESS_DATA_LOCATION" "$$MARIADB_DATA_LOCATION" "$$PORTAINER_DATA_LOCATION"
	@if [ -d "data" ] && [ -w "data" ]; then \
		find data -type d -user $(shell id -u) -exec chmod 755 {} \; 2>/dev/null || true; \
		find data -type f -user $(shell id -u) -exec chmod 644 {} \; 2>/dev/null || true; \
	fi
	@echo "$(GREEN)✅ Data directories created successfully$(RESET)"

# Build Docker images without starting containers
build: check_env $(COMPOSE_FILE)
	@echo "$(YELLOW)🏗️  Building Docker images...$(RESET)"
	@docker-compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE) build --no-cache
	@echo "$(GREEN)✅ Docker images built successfully$(RESET)"

# Build and start containers
up: check_env $(COMPOSE_FILE)
	@echo "$(YELLOW)🏗️  Building Docker images...$(RESET)"
	@docker-compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE) build --no-cache
	@echo "$(YELLOW)🚀 Starting containers...$(RESET)"
	@docker-compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE) up -d
	@echo "$(GREEN)✅ All containers are running$(RESET)"

# Success message with service URLs
success: check_env
	@echo ""
	@echo "$(GREEN)$(BOLD)🎉 INCEPTION SUCCESSFULLY DEPLOYED! 🎉$(RESET)"
	@echo "$(GREEN)=====================================$(RESET)"
	@echo ""
	@echo "$(CYAN)$(BOLD)"
	@echo "██╗███╗   ██╗ ██████╗███████╗██████╗ ████████╗██╗ ██████╗ ███╗   ██╗"
	@echo "██║████╗  ██║██╔════╝██╔════╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║"
	@echo "██║██╔██╗ ██║██║     █████╗  ██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║"
	@echo "██║██║╚██╗██║██║     ██╔══╝  ██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║"
	@echo "██║██║ ╚████║╚██████╗███████╗██║        ██║   ██║╚██████╔╝██║ ╚████║"
	@echo "╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝"
	@echo "$(RESET)"
	@echo "$(BLUE)$(BOLD)          🐳 Docker Infrastructure Project - 42 Málaga$(RESET)"
	@echo "$(BLUE)$(BOLD)          ============================================$(RESET)"
	@echo "$(BLUE)$(BOLD)                        - sternero (2025) -$(RESET)"
	@echo ""
	@echo "$(CYAN)📊 Container Status:$(RESET)"
	@if docker ps -q > /dev/null 2>&1; then \
		echo "$(CYAN)   ╭────────────────┬───────────────┬─────────────────────────╮$(RESET)"; \
		echo "$(CYAN)   │$(RESET) $(WHITE)$(BOLD)Service$(RESET)        $(CYAN)│$(RESET) $(WHITE)$(BOLD)Status$(RESET)        $(CYAN)│$(RESET) $(WHITE)$(BOLD)Uptime$(RESET)                  $(CYAN)│$(RESET)"; \
		echo "$(CYAN)   ├────────────────┼───────────────┼─────────────────────────┤$(RESET)"; \
		for container in nginx wordpress mariadb redis ftp-server adminer website portainer; do \
			if docker ps --format "{{.Names}}" | grep -q "^$$container$$"; then \
				uptime=$$(docker ps --format "{{.Status}}" --filter name=^$$container$$ | sed 's/Up //'); \
				printf "$(CYAN)   │$(RESET) $(GREEN)✅ %-11s$(RESET) $(CYAN)│$(RESET) $(GREEN)%-13s$(RESET) $(CYAN)│$(RESET) $(WHITE)%-23s$(RESET) $(CYAN)│$(RESET)\n" "$$container" "Running" "$$uptime"; \
			else \
				printf "$(CYAN)   │$(RESET) $(RED)❌ %-11s$(RESET) $(CYAN)│$(RESET) $(RED)%-13s$(RESET) $(CYAN)│$(RESET) $(RED)%-23s$(RESET) $(CYAN)│$(RESET)\n" "$$container" "Stopped" "Offline"; \
			fi; \
		done; \
		echo "$(CYAN)   ╰────────────────┴───────────────┴─────────────────────────╯$(RESET)"; \
	else \
		echo "$(RED)   ❌ No containers running$(RESET)"; \
	fi
	@echo ""
	@echo "$(CYAN)📋 Access your services:$(RESET)"
	@. ./$(ENV_FILE) && \
	echo "$(WHITE)   🌐 WordPress:  $(BLUE)https://$$DOMAIN_NAME/$(RESET)"; \
	echo "$(WHITE)   🗄️  Adminer:    $(BLUE)https://$$DOMAIN_NAME/adminer/$(RESET)"; \
	echo "$(WHITE)   💼 Portfolio:  $(BLUE)https://$$DOMAIN_NAME/portfolio/$(RESET)"; \
	echo "$(WHITE)   📁 FTP Server: $(BLUE)ftp://$$DOMAIN_NAME:21$(RESET)"; \
	echo "$(WHITE)   📊 Portainer:  $(BLUE)http://localhost:9000/$(RESET)"
	@echo ""
	@echo "$(YELLOW)⚡ Bonus services included:$(RESET)"
	@echo "$(WHITE)   • Redis cache for WordPress optimization$(RESET)"
	@echo "$(WHITE)   • Adminer for database management$(RESET)"
	@echo "$(WHITE)   • FTP server for file access$(RESET)"
	@echo "$(WHITE)   • Static portfolio website$(RESET)"
	@echo "$(WHITE)   • Portainer for Docker container management$(RESET)"
	@echo ""
	@echo "$(MAGENTA)$(BOLD)🚀 Next Steps & Available Tools:$(RESET)"
	@echo "$(WHITE)   • $(CYAN)./eval_url.sh$(RESET)     - Interactive website demo and evaluation$(RESET)"
	@echo "$(WHITE)   • $(CYAN)./evaluation.sh$(RESET)   - Comprehensive project validation & testing$(RESET)"
	@echo "$(WHITE)   • $(CYAN)./create_env.sh$(RESET)   - Environment configuration wizard & setup$(RESET)"
	@echo "$(WHITE)   • $(CYAN)make status$(RESET)       - Check containers and volumes status$(RESET)"
	@echo "$(WHITE)   • $(CYAN)make logs$(RESET)         - View detailed container logs$(RESET)"
	@echo "$(WHITE)   • $(CYAN)make clean-test$(RESET)   - Remove test files only$(RESET)"
	@echo "$(WHITE)   • $(CYAN)make down$(RESET)         - Stop all containers gracefully$(RESET)"
	@echo "$(WHITE)   • $(CYAN)make help$(RESET)         - Show all available commands$(RESET)"
	@echo ""

# Stop containers
down: check_env
	@echo "$(YELLOW)🛑 Stopping containers...$(RESET)"
	@docker-compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE) down
	@echo "$(GREEN)✅ All containers stopped$(RESET)"

# Clean containers and volumes
clean:
	@echo "$(YELLOW)🧹 Cleaning containers and volumes...$(RESET)"
	@docker-compose -f $(COMPOSE_FILE) down -v --remove-orphans 2>/dev/null || true
	@docker system prune -f --volumes
	@echo "$(CYAN)🗑️  Removing test files...$(RESET)"
	@rm -f test_upload.txt downloaded_from_ftp.txt .env.backup 2>/dev/null || true
	@if docker ps --format "{{.Names}}" | grep -q "^wordpress$$"; then \
		echo "$(CYAN)🗑️  Removing FTP test files from WordPress volume...$(RESET)"; \
		docker exec wordpress sh -c 'rm -f /var/www/html/test_download.txt /var/www/html/uploaded_via_ftp.txt' 2>/dev/null || true; \
	fi
	@echo "$(GREEN)✅ Cleanup completed$(RESET)"

# Force clean all Docker resources
fclean:
	@echo "$(RED)$(BOLD)💥 NUCLEAR CLEANUP - Removing ALL Docker resources$(RESET)"
	@echo "$(RED)⚠️  This will delete ALL containers, images, volumes, networks AND .env file!$(RESET)"
	@echo "$(YELLOW)Are you sure? (y/N):$(RESET)"
	@read -r response; \
	if [ "$$response" = "y" ] || [ "$$response" = "Y" ]; then \
		echo "$(CYAN)🗑️  Removing all test and temporary files...$(RESET)"; \
		rm -f test_upload.txt downloaded_from_ftp.txt .env.backup 2>/dev/null || true; \
		rm -f *.tmp *.log *_test.* *_temp.* 2>/dev/null || true; \
		docker stop $$(docker ps -qa) 2>/dev/null || true; \
		docker rm $$(docker ps -qa) 2>/dev/null || true; \
		docker rmi -f $$(docker images -qa) 2>/dev/null || true; \
		docker volume rm $$(docker volume ls -q) 2>/dev/null || true; \
		docker network rm $$(docker network ls -q) 2>/dev/null || true; \
		rm -rf data/ 2>/dev/null || true; \
		rm -f .env 2>/dev/null || true; \
		echo "$(GREEN)✅ Nuclear cleanup completed - everything removed!$(RESET)"; \
	else \
		echo "$(CYAN)Operation cancelled$(RESET)"; \
	fi

# Clean only test files (keep containers running)
clean-test:
	@echo "$(CYAN)🗑️  Removing FTP and evaluation test files...$(RESET)"
	@rm -f test_upload.txt downloaded_from_ftp.txt .env.backup 2>/dev/null || true
	@rm -f *.tmp *.log *_test.* *_temp.* 2>/dev/null || true
	@if docker ps --format "{{.Names}}" | grep -q "^wordpress$$"; then \
		echo "$(CYAN)🗑️  Removing test files from WordPress volume...$(RESET)"; \
		docker exec wordpress sh -c 'rm -f /var/www/html/test_download.txt /var/www/html/uploaded_via_ftp.txt /var/www/html/*_test.* /var/www/html/*_temp.*' 2>/dev/null || true; \
	fi
	@echo "$(GREEN)✅ Test files cleanup completed$(RESET)"

# Rebuild everything
re: clean all

# Show status
status:
	@echo "$(CYAN)$(BOLD)📊 INCEPTION STATUS$(RESET)"
	@echo "$(CYAN)==================$(RESET)"
	@echo ""
	@echo "$(YELLOW)🐳 Docker Containers:$(RESET)"
	@docker ps --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}" 2>/dev/null || echo "$(RED)No containers running$(RESET)"
	@echo ""
	@echo "$(YELLOW)💾 Docker Volumes:$(RESET)"
	@docker volume ls --format "table {{.Name}}\t{{.Driver}}" 2>/dev/null || echo "$(RED)No volumes found$(RESET)"

# Show logs
logs: check_env
	@echo "$(YELLOW)📋 Showing container logs...$(RESET)"
	@docker-compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE) logs --tail=50

# Help
help:
	@echo "$(CYAN)$(BOLD)"
	@echo "██╗███╗   ██╗ ██████╗███████╗██████╗ ████████╗██╗ ██████╗ ███╗   ██╗"
	@echo "██║████╗  ██║██╔════╝██╔════╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║"
	@echo "██║██╔██╗ ██║██║     █████╗  ██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║"
	@echo "██║██║╚██╗██║██║     ██╔══╝  ██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║"
	@echo "██║██║ ╚████║╚██████╗███████╗██║        ██║   ██║╚██████╔╝██║ ╚████║"
	@echo "╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝"
	@echo "$(RESET)"
	@echo "$(BLUE)$(BOLD)          🐳 Docker Infrastructure Project - 42 Málaga$(RESET)"
	@echo "$(BLUE)$(BOLD)          ============================================$(RESET)"
	@echo "$(BLUE)$(BOLD)                        - sternero (2025) -$(RESET)"
	@echo ""
	@echo "$(BLUE)$(BOLD)Available commands:$(RESET)"
	@echo ""
	@echo "$(GREEN)  all$(RESET)      - 🚀 Complete setup: check env, create dirs, build and start"
	@echo "$(GREEN)  up$(RESET)       - 🏗️  Build and start containers"
	@echo "$(GREEN)  down$(RESET)     - 🛑 Stop all containers"
	@echo "$(GREEN)  clean$(RESET)    - 🧹 Stop containers, remove volumes and test files"
	@echo "$(GREEN)  clean-test$(RESET) - 🗑️  Remove only test files (keep containers running)"
	@echo "$(GREEN)  fclean$(RESET)   - 💥 Nuclear cleanup (removes EVERYTHING including .env)"
	@echo "$(GREEN)  re$(RESET)       - 🔄 Clean and rebuild everything"
	@echo "$(GREEN)  env$(RESET)      - 🔧 Create/recreate .env configuration file"
	@echo "$(GREEN)  status$(RESET)   - 📊 Show containers and volumes status"
	@echo "$(GREEN)  logs$(RESET)     - 📋 Show container logs"
	@echo "$(GREEN)  help$(RESET)     - ❓ Show this help message"
	@echo ""
	@echo "$(YELLOW)First time setup:$(RESET)"
	@echo "$(WHITE)  1. make env        $(CYAN)# Configure environment$(RESET)"
	@echo "$(WHITE)  2. make all        $(CYAN)# Build and start everything$(RESET)"
	@echo ""
	@echo "$(MAGENTA)$(BOLD)🚀 Additional Tools:$(RESET)"
	@echo "$(WHITE)  • $(CYAN)./eval_url.sh$(RESET)     - Interactive demo for evaluation$(RESET)"
	@echo "$(WHITE)  • $(CYAN)./create_env.sh$(RESET)   - Environment configuration wizard$(RESET)"

.PHONY: all banner check_env create_dirs up success down clean clean-test fclean re env status logs help 
	# Total clean, like an atomic bomb

re: clean all	# Rebuild everything by cleaning and then starting up again

# Configure environment variables
env:
	@echo "$(YELLOW)🔧 Configurando archivo .env...$(RESET)"
	@./create_env.sh

.PHONY: all down clean re	# Declare targets as phony to avoid conflicts with files of the same name
