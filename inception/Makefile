COMPOSE_FILE = srcs/docker-compose.yml	# Define la ruta al archivo docker-compose.yml

all: up

up: $(COMPOSE_FILE)	# Para construir y levantar los contenedores
	@ sudo docker-compose -f $(COMPOSE_FILE) up --build -d
	@ touch up
	@ echo >up Inception succesfully up !

down:	# Para detener y eliminar los contenedores
	@ sudo docker-compose -f $(COMPOSE_FILE) down
	@ rm -f up

clean:	# Para limpiar los contenedores y volúmenes
	@ sudo docker-compose -f $(COMPOSE_FILE) down -v --remove-orphans
	@ sudo docker system prune -f --volumes
	@ rm -f up

fclean:	# Para limpiar completamente los contenedores, imágenes, volúmenes y redes
	docker stop $$(docker ps -qa); docker rm $$(docker ps -qa); docker rmi -f $$(docker images -qa); docker volume rm $$(docker volume ls -q); docker network rm $$(docker network ls -q) 2>/dev/null 

re: clean all	# Limpia y reconstruye los contenedores

.PHONY: all down clean re	# Declarar las reglas como "phony" para evitar conflictos con archivos del mismo nombre