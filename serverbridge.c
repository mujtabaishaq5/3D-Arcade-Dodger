#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// C calls ELPL, which in turn calls Assembly
extern char* handle_elpl_request(char* request_buffer);

void start_bare_metal_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) exit(1);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) exit(1);
    if (listen(server_fd, 3) < 0) exit(1);

    printf("[C-NET] Server listening on http://localhost:8080 ...\n");

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) continue;

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        // 1. C triggers ELPL -> ELPL calls Assembly -> Returns raw badge string pointer
        char* asm_badge = handle_elpl_request(buffer);
        if (asm_badge == NULL) {
            asm_badge = " [Fallback Badge]";
        }

        // 2. Build HTML incorporating the data routed through ELPL
        char body[1024];
        snprintf(body, sizeof(body),
            "<html><body style='font-family: sans-serif; text-align: center; margin-top: 50px;'>"
            "<h1>ELPL + Assembly + C Web Server</h1>"
            "<p style='color: green; font-weight: bold;'>Data Flow: C &rarr; ELPL &rarr; Assembly &rarr; ELPL &rarr; C</p>"
            "<hr style='width: 50%%;'>"
            "<p>Assembly Badge fetched via ELPL: <code>%s</code></p>"
            "</body></html>",
            asm_badge
        );

        char header[256];
        snprintf(header, sizeof(header), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n", strlen(body));

        write(new_socket, header, strlen(header));
        write(new_socket, body, strlen(body));

        shutdown(new_socket, SHUT_WR);
        close(new_socket);
    }
}