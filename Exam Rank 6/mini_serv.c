#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>

typedef struct s_client { int id; char msg[370000]; } t_client;

t_client    clients[2048];
fd_set      read_set, write_set, current;
int         max_fd = 0, next_id = 0, server_socket, i, len;
char        send_buffer[400000], recv_buffer[400000];

void    error(char *msg) { write(2, msg ? msg : "Fatal error", msg ? strlen(msg) : 11); write(2, "\n", 1); exit(1); }

void    send_msg(int sender, char *format, ...) {
    bzero(send_buffer, sizeof(send_buffer));
    va_list args; va_start(args, format); vsprintf(send_buffer, format, args); va_end(args);
    for(int fd = 0; fd <= max_fd; fd++)
        if(FD_ISSET(fd, &write_set) && fd != sender)
            if(send(fd, send_buffer, strlen(send_buffer), 0) == -1) { error(NULL); }
}

int     main(int argc, char *argv[]) {
    if(argc != 2) { error("Wrong number of arguments"); }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = htonl(2130706433);
    
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { error(NULL); }
    
    max_fd = server_socket;
    FD_ZERO(&current); FD_ZERO(&write_set); FD_SET(server_socket, &current); bzero(clients, sizeof(clients));

    if(bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == -1 || listen(server_socket, 100) == -1) { error(NULL); }

    while(1) {
        read_set = write_set = current;
        if(select(max_fd + 1, &read_set, &write_set, NULL, NULL) == -1) { continue; }
        for(int fd = 0; fd <= max_fd; fd++){
            if(FD_ISSET(fd, &read_set)){
                if(fd == server_socket){
                    socklen_t addr_len = sizeof(server);
                    int new_client = accept(server_socket, (struct sockaddr*)&server, &addr_len);
                    if(new_client != -1) {
                        if(new_client > max_fd) max_fd = new_client;
                        clients[new_client].id = next_id++;
                        FD_SET(new_client, &current);
                        send_msg(new_client, "server: client %d just arrived\n", clients[new_client].id);
                    }
                } else {
                    int msg_bytes = recv(fd, recv_buffer, sizeof(recv_buffer), 0);
                    if(msg_bytes <= 0){
                        send_msg(fd, "server: client %d just left\n", clients[fd].id);
                        FD_CLR(fd, &current); close(fd); bzero(clients[fd].msg, sizeof(clients[fd].msg));
                        if(fd == max_fd) while(max_fd > 0 && !FD_ISSET(max_fd, &current)) max_fd--;
                    } else {
                        for(i = 0, len = strlen(clients[fd].msg); i < msg_bytes && len < 370000 - 1; i++, len++)
                            if((clients[fd].msg[len] = recv_buffer[i]) == '\n'){
                                clients[fd].msg[len] = '\0';
                                send_msg(fd, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                                bzero(clients[fd].msg, sizeof(clients[fd].msg));
                                len = -1;
                            }
                    }
                }
            }
        }
    }
}