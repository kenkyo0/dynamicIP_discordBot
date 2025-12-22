/*serverI.cpp
 *
 * This file provides functions to get server informations,
 * such as the current public ip or the number of active clients by a specific port
 * */
#include "serverI.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <sstream>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>


/*This function gets the public ip of the system on which the bot is running on*/
std::string get_dIP(bool ipv6){
    
    // get public ip with a TCP Stream http request
    const char *url = ipv6 ? "ipv6.icanhazip.com" : "ipv4.icanhazip.com";
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

     while((size = recv(sockfd, buf, sizeof(buf), 0)) > 0){
        response.append(buf, size);
     }

     close(sockfd);

     freeaddrinfo(res);
     
     // ignore header 
     std::string ip = strstr(response.c_str(), "\r\n\r\n");
     
     return ip;
}

int conn_player_num(const int port, bool ipv6){

    std::string path= ipv6 ? "/proc/net/tcp6" : "/proc/net/tcp";
    std::ifstream ifs (path);
    if(!ifs.is_open()){
        return 0;
    }

    // reading file
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string content = ss.str();

    // prepare parsing 
    const char *p; 
    int count = 0;
    bool scan = false;
    bool correctp = false;
    int conns = 0;

        // port to hex
    char hexport[5];
    std::stringstream stream;
    //stream << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << port;
    stream << std::uppercase << std::hex << port;
    stream.write(hexport, 4);
    hexport[4] = '\0';

        // defined status : active connection
    const char status[3] = "01"; 
    
    // start parsing
    for(p = content.c_str(); *p != 0; p++){
        // prepare overlapping
        if(count != 0 && *p == '\n'){
            count = 0;
            correctp = false;
        }
        // getting port and status
        if(*p == ':'){
            count++;
        }
        if(count == 2){
            p++;
            if(std::strncmp(p, hexport, 4)){
                correctp = true;
            }
        }

        if((correctp) && (count == 3)){
            p += 6; // skip the dest. port
            if(std::strncmp(p, status, 2)){
                conns++;
            }
            correctp = false;
        }
    }
    
    return conns;
}
