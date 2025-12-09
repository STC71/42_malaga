# =============================================================================
#                         🎮 TRANSCENDENCE PONG 🎮
#                    Advanced Multiplayer Game Platform
#                            42 Málaga - 2025
# =============================================================================

# Project Configuration
NAME = transcendence
COMPOSE_FILE = docker-compose.yml
COMPOSE := $(shell command -v docker-compose >/dev/null 2>&1 && echo "docker-compose" || echo "docker compose")
DATA_DIR = /home/${USER}/data

# Color Definitions
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m

# Colors
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

# Background Colors
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN = \033[46m

# Emojis
ROCKET = 🚀
GEAR = ⚙️
CLEAN = 🧹
CHECK = ✅
CROSS = ❌
INFO = 💡
GAME = 🎮
CHART = 📊
SHIELD = 🛡️
FIRE = 🔥

# =============================================================================
#                               MAIN COMMANDS
# =============================================================================

all:
	@echo "$(CYAN)$(BOLD)================================================================$(RESET)"
	@echo "$(CYAN)$(BOLD) $(ROCKET) $(BOLD)Starting $(NAME) - Full Build & Deploy$(RESET)"
	@echo "$(CYAN)$(BOLD)================================================================$(RESET)"
	@echo "$(YELLOW)$(GEAR) Setting up data directories...$(RESET)"
	@mkdir -p $(DATA_DIR) $(DATA_DIR)/backend $(DATA_DIR)/frontend
	@echo "$(GREEN)$(CHECK) Directories created successfully$(RESET)"
	@echo "$(YELLOW)$(GEAR) Building and starting containers...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) up -d --build
	@echo ""
	@echo "$(GREEN)$(BOLD)$(FIRE) TRANSCENDENCE IS READY! $(FIRE)$(RESET)"
	@echo "$(CYAN)Access the game at: $(WHITE)$(BOLD)https://localhost:8443$(RESET)"
	@echo ""

build:
	@echo "$(BLUE)$(BOLD)$(GEAR) Building $(NAME) containers...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) build
	@echo "$(GREEN)$(CHECK) Build completed successfully!$(RESET)"

down:
	@echo "$(YELLOW)Stopping $(NAME) containers...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) down
	@echo "$(GREEN)$(CHECK) Containers stopped$(RESET)"

up:
	@echo "$(GREEN)$(ROCKET) Starting $(NAME) containers...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) up -d
	@echo "$(GREEN)$(CHECK) Containers are running!$(RESET)"

clean: down
	@echo "$(YELLOW)$(CLEAN) Cleaning Docker system...$(RESET)"
	@docker system prune -a
	@if [ -f "test_result.md" ]; then rm -f test_result.md && echo "$(GREEN)✓$(RESET) test_result.md removed"; fi
	@if [ -f "test_evaluation_result.md" ]; then rm -f test_evaluation_result.md && echo "$(GREEN)✓$(RESET) test_evaluation_result.md removed"; fi
	@echo "$(GREEN)$(CHECK) Cleanup completed$(RESET)"

fclean:
	@echo "$(RED)$(BOLD)============================================================$(RESET)"
	@echo "$(RED)$(BOLD) $(CLEAN) $(BOLD)DEEP CLEAN - Removing ALL Docker resources$(RESET)"
	@echo "$(RED)$(BOLD)============================================================$(RESET)"
	@echo "$(YELLOW)Stopping all containers...$(RESET)"
	@if [ -n "$$(docker ps -qa)" ]; then docker stop $$(docker ps -qa); fi
	@echo "$(YELLOW)Pruning system resources...$(RESET)"
	@docker system prune --all --force --volumes
	@docker network prune --force
	@docker volume prune --force
	@docker image prune --all --force
	@docker container prune --force
	@docker builder prune --all --force
	@if [ -n "$$(docker volume ls -q)" ]; then docker volume rm $$(docker volume ls -q); fi
	@echo "$(YELLOW)Removing host data directory...$(RESET)"
	@if [ -d "$(DATA_DIR)" ]; then rm -rf $(DATA_DIR); fi
	@echo "$(YELLOW)Removing test reports...$(RESET)"
	@if [ -f "test_result.md" ]; then rm -f test_result.md && echo "$(GREEN)✓$(RESET) test_result.md removed"; fi
	@if [ -f "test_evaluation_result.md" ]; then rm -f test_evaluation_result.md && echo "$(GREEN)✓$(RESET) test_evaluation_result.md removed"; fi
	@echo "$(GREEN)$(BOLD)$(CHECK) Deep clean completed! System is pristine.$(RESET)"

re: fclean all

logs:
	@echo "$(CYAN)$(CHART) Following logs for $(NAME)...$(RESET)"
	@echo "$(DIM)Press Ctrl+C to stop$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) logs -f

status:
	@echo "$(BLUE)$(INFO) $(BOLD)Container Status Report$(RESET)"
	@echo "$(DIM)-------------------------------------$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) ps

restart:
	@echo "$(YELLOW)$(GEAR) Restarting $(NAME) containers...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) restart
	@echo "$(GREEN)$(CHECK) Restart completed$(RESET)"

# =============================================================================
#                           DEVELOPMENT COMMANDS
# =============================================================================
dev:
	@echo "$(MAGENTA)$(BOLD)$(ROCKET) Development Mode$(RESET)"
	@echo "$(CYAN)Live reload enabled - Code changes will auto-update$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) up --build

backend-logs:
	@echo "$(BLUE)$(CHART) Backend Logs - $(NAME)$(RESET)"
	@echo "$(DIM)Monitoring server activity...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) logs -f backend

frontend-logs:
	@echo "$(GREEN)$(CHART) Frontend Logs - $(NAME)$(RESET)"
	@echo "$(DIM)Monitoring client activity...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) logs -f frontend

game-debug:
	@echo "$(RED)$(BOLD)🐛 Game Server Debug$(RESET)"
	@echo "$(CYAN)Showing last 50 log entries...$(RESET)"
	@$(COMPOSE) -f $(COMPOSE_FILE) logs --tail=50 backend

# =============================================================================
#                              TESTING COMMANDS
# =============================================================================

test:
	@echo "$(MAGENTA)$(BOLD)🧪 Running Project Validation...$(RESET)"
	@echo "$(CYAN)This validates all modules according to en.subject.pdf$(RESET)"
	@echo "$(DIM)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@bash test_auto.sh
	@if [ -f test_result.md ]; then \
		echo "$(GREEN)$(CHECK) Report generated: $(BOLD)test_result.md$(RESET)"; \
	fi

evaluation:
	@echo "$(BLUE)$(BOLD)📋 Running Evaluation Criteria Check...$(RESET)"
	@echo "$(CYAN)This validates all criteria from evaluation_ft_transcendence.pdf$(RESET)"
	@echo "$(DIM)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@bash test_evaluation.sh
	@if [ -f test_evaluation_result.md ]; then \
		echo "$(GREEN)$(CHECK) Evaluation report generated: $(BOLD)test_evaluation_result.md$(RESET)"; \
		echo "$(CYAN)$(INFO) Open with: $(WHITE)cat test_evaluation_result.md$(RESET)"; \
	fi

test-all:
	@echo "$(MAGENTA)$(BOLD)🔬 Running Complete Test Suite...$(RESET)"
	@echo "$(CYAN)Testing both subject modules and evaluation criteria$(RESET)"
	@echo "$(DIM)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@make test
	@echo ""
	@make evaluation
	@echo ""
	@echo "$(GREEN)$(BOLD)$(CHECK) Complete test suite finished!$(RESET)"
	@echo "$(CYAN)Reports available:$(RESET)"
	@echo "  • $(BOLD)test_result.md$(RESET) - Subject modules validation"
	@echo "  • $(BOLD)test_evaluation_result.md$(RESET) - Evaluation criteria check"

# =============================================================================
#                           MAINTENANCE COMMANDS
# =============================================================================
backup-db:
	@echo "$(CYAN)$(SHIELD) Creating database backup...$(RESET)"
	@mkdir -p ./backups
	@BACKUP_NAME="db-backup-$$(date +%Y%m%d-%H%M%S)"; \
	 docker cp transcendence-backend:/app/data ./backups/$$BACKUP_NAME 2>/dev/null && \
	 echo "$(GREEN)$(CHECK) Backup created: ./backups/$$BACKUP_NAME$(RESET)" || \
	 echo "$(YELLOW)⚠️  Warning: Container not running, backup skipped$(RESET)"

restore-db:
	@echo "$(BLUE)$(INFO) $(BOLD)Database Restore Instructions$(RESET)"
	@echo "$(DIM)---------------------------------------$(RESET)"
	@echo "$(CYAN)1.$(RESET) Copy backup to ./backups/ directory"
	@echo "$(CYAN)2.$(RESET) Run: $(WHITE)$(BOLD)docker cp ./backups/[backup-name] transcendence-backend:/app/data$(RESET)"
	@echo "$(CYAN)3.$(RESET) Run: $(WHITE)$(BOLD)make restart$(RESET)"
	@echo "$(DIM)---------------------------------------$(RESET)"

# =============================================================================
#                         TESTING & PERFORMANCE
# =============================================================================

test-game:
	@echo "$(MAGENTA)$(BOLD)🧪 System Health Check$(RESET)"
	@echo "$(DIM)-----------------------------------$(RESET)"
	@echo "$(CYAN)Testing backend health...$(RESET)"
	@curl -f http://localhost:3000/health 2>/dev/null && \
	 echo "$(GREEN)$(CHECK) Backend: $(BOLD)HEALTHY$(RESET)" || \
	 echo "$(RED)$(CROSS) Backend: $(BOLD)NOT RESPONDING$(RESET)"
	@echo "$(CYAN)Testing frontend...$(RESET)"
	@curl -f http://localhost:2323 2>/dev/null && \
	 echo "$(GREEN)$(CHECK) Frontend: $(BOLD)HEALTHY$(RESET)" || \
	 echo "$(RED)$(CROSS) Frontend: $(BOLD)NOT RESPONDING$(RESET)"
	@echo "$(DIM)-----------------------------------$(RESET)"

monitor:
	@echo "$(YELLOW)$(CHART) $(BOLD)Resource Monitor$(RESET)"
	@echo "$(CYAN)Monitoring $(NAME) containers - Press Ctrl+C to stop$(RESET)"
	@echo "$(DIM)------------------------------------------------------$(RESET)"
	@docker stats transcendence-backend transcendence-frontend

# =============================================================================
#                           INFORMATION COMMANDS
# =============================================================================
info:
	@echo ""
	@echo "$(CYAN)$(BOLD)=============================================================================$(RESET)"
	@echo "$(CYAN)$(BOLD)                       $(GAME) $(BOLD)TRANSCENDENCE PONG $(GAME)$(RESET)"
	@echo "$(CYAN)$(BOLD)                    Advanced Multiplayer Game Platform$(RESET)"
	@echo "$(CYAN)$(BOLD)=============================================================================$(RESET)"
	@echo ""
	@echo " $(ROCKET) $(BOLD)URLs:$(RESET)"
	@echo "    $(CYAN)Access the game at: $(WHITE)$(BOLD)https://localhost:8443$(RESET)"
	@echo ""
	@echo " $(FIRE) $(BOLD)Features:$(RESET)"
	@echo "   • AI with Spin Detection  • Physics Engine  • Particle Effects"
	@echo "   • Procedural Audio        • Replay System   • Real-time Stats"
	@echo ""
	@echo " $(INFO) $(BOLD)Documentation:$(RESET) $(WHITE)S_IMPLEMENTACIONES.md$(RESET)"
	@echo ""
	@echo "$(CYAN)$(BOLD)=============================================================================$(RESET)"
	@echo " $(GEAR) $(BOLD)AVAILABLE COMMANDS$(RESET)"
	@echo ""
	@echo " $(GREEN)Main Commands:$(RESET)"
	@echo "   make all        $(DIM)Full build and deploy$(RESET)"
	@echo "   make build      $(DIM)Build containers only$(RESET)"
	@echo "   make up         $(DIM)Start existing containers$(RESET)"
	@echo "   make down       $(DIM)Stop all containers$(RESET)"
	@echo ""
	@echo " $(MAGENTA)Development:$(RESET)"
	@echo "   make dev         $(DIM)Development mode with live reload$(RESET)"
	@echo "   make game-debug  $(DIM)Show recent game server logs$(RESET)"
	@echo "   make monitor     $(DIM)Resource usage monitoring$(RESET)"
	@echo ""
	@echo " $(YELLOW)Maintenance:$(RESET)"
	@echo "   make backup-db   $(DIM)Backup game database$(RESET)"
	@echo "   make test-game   $(DIM)Health check endpoints$(RESET)"
	@echo "   make clean       $(DIM)Clean Docker resources$(RESET)"
	@echo "   make fclean      $(DIM)Deep clean everything$(RESET)"
	@echo ""
	@echo " $(MAGENTA)Testing:$(RESET)"
	@echo "   make test        $(DIM)Complete project validation (subject requirements)$(RESET)"
	@echo "   make evaluation  $(DIM)Evaluation PDF criteria check (defense preparation)$(RESET)"
	@echo "$(CYAN)$(BOLD)=============================================================================$(RESET)"
	@echo ""

# =============================================================================
#                              QUICK COMMANDS
# =============================================================================
quick-restart:
	@echo "$(YELLOW)⚡ Quick restart (backend only)...$(RESET)"
	@$(COMPOSE) restart backend
	@echo "$(GREEN)$(CHECK) Backend restarted$(RESET)"

rebuild-backend:
	@echo "$(BLUE)$(GEAR) Rebuilding backend...$(RESET)"
	@$(COMPOSE) build backend
	@$(COMPOSE) up -d backend
	@echo "$(GREEN)$(CHECK) Backend rebuilt and started$(RESET)"

rebuild-frontend:
	@echo "$(GREEN)$(GEAR) Rebuilding frontend...$(RESET)"
	@$(COMPOSE) build frontend
	@$(COMPOSE) up -d frontend
	@echo "$(GREEN)$(CHECK) Frontend rebuilt and started$(RESET)"

# =============================================================================
#                           SELECTIVE CLEANUP
# =============================================================================

clean-logs:
	@echo "$(YELLOW)$(CLEAN) Cleaning container logs and unused volumes...$(RESET)"
	@docker system prune --volumes --force
	@echo "$(GREEN)$(CHECK) Logs and volumes cleaned$(RESET)"

# =============================================================================
#                                 VAULT RESET
# =============================================================================
vault-reset:
	@printf "\n Resetting Vault configuration...\n"
	@$(COMPOSE) -f $(COMPOSE_FILE) down
	@docker volume rm ${NAME}_vault_file ${NAME}_vault_secrets 2>/dev/null || true
	@rm -f srcs/secrets/vault/root_token srcs/secrets/vault/unseal_key srcs/secrets/vault/init.txt
	@$(COMPOSE) -f $(COMPOSE_FILE) up -d vault
	@printf "Esperando a que Vault esté listo...\n\n"
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do \
		docker compose exec -T vault vault status >/dev/null 2>&1 && break; \
		sleep 2; \
	done
	@docker compose exec -T vault vault operator init -key-shares=1 -key-threshold=1 > srcs/secrets/vault/init.txt
	@grep 'Unseal Key 1:' srcs/secrets/vault/init.txt | awk -F': ' '{print $$2}' > srcs/secrets/vault/unseal_key
	@grep 'Initial Root Token:' srcs/secrets/vault/init.txt | awk -F': ' '{print $$2}' > srcs/secrets/vault/root_token
	@printf "$(GREEN)Vault reset complete. Archivos generados: init.txt, root_token, unseal_key.$(RESET)\n"
	@printf "$(CYAN)Ejecuta 'bash srcs/scripts/01.init_waf_and_vault.sh' para continuar.$(RESET)\n\n"


# =============================================================================
#                                 PHONY
# =============================================================================

.PHONY: all build down clean fclean re logs status restart \
        dev backend-logs frontend-logs game-debug \
        backup-db restore-db test test-game monitor info \
        quick-restart rebuild-backend rebuild-frontend clean-logs vault-reset \
        evaluation test-all

# =============================================================================
#   🎮 TRANSCENDENCE - Advanced Pong Game Platform
#   Created by: 42 Málaga Students
#   Year: 2025
#   Features: AI, Physics, Particles, Audio, Replay System
# =============================================================================