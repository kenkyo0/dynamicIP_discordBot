/*serverI.cpp
 *
 * This file provides functions to get server informations,
 * such as the current public ip or the number of active clients by a specific port
 * */
#include "serverI.h"
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>


/*This function gets the public ip of the system on which the bot is running on*/
std::string get_dIP(bool ipv6){
    
    // get public ip with a TCP Stream http request
    const char *url = ipv6 ? "ipv6.icanhayip.com" : "ipv4.icanhazip.com";
    const char *port = "80";

    addrinfo info{}, *res; // from netdb.h include
    info.ai_family = ipv6 ? AF_INET6 : AF_INET;
    info.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(url, port, &info, &res) != 0){
        return  "dns error";
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sockfd == -1){
        return "error on socket creation";
    }
    if(connect(sockfd, res->ai_addr, res->ai_addrlen) < 0){
        return "error on connection to icanhazip.com";
        close(sockfd);
    }

     std::string req =
        "GET / HTTP/1.1\r\n"
        "Host: " + std::string(url) + "\r\n"
        "Connection: close\r\n\r\n";

     send(sockfd, req.c_str(), req.size(), 0);
    
     char buf[128];
     std::string response;
     ssize_t size;

     while((size = recv(sockfd, buf, sizeof(buf), 0)) < 0){
        response.append(buf, size);
     }

     close(sockfd);

     freeaddrinfo(res);
     
     // ignore header 
     std::string ip = strstr(response.c_str(), "\r\n\r\n");
     
     return ip;
}

std::string conn_player_num(const std::string port){
    return exec_shell_cmd("lsof -i :"+port+"| grep -v 'COMMAND' | wc -l");
}
