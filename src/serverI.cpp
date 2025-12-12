/*serverI.cpp
 *
 * This file provides functions to get server informations,
 * such as the current public ip or the number of active clients by a specific port
 * */
#include "serverI.h"
#include <cstdio>
#include <stdio.h>
#include <cstdlib>
#include <fstream>

std::string exec_shell_cmd(const std::string cmd){
    FILE *fp;
    char buf[128];
    std::string result = "";
    
    if(cmd.find("rm", 0)!=std::string::npos){
        return "config error";
    }

    fp = popen(cmd.c_str(), "r");
    while((fgets(buf, 128, fp)) != NULL){
        result += buf;
    }

    pclose(fp);
    return result;
}


/*This function gets the public ip of the system on which the bot is running on*/
std::string get_dIP(bool ipv6){
    // get public ip with curl
    const std::string cmd = (ipv6) ? "curl -s -6 icanhazip.com" : "curl -s -4 icanhazip.com";
    return exec_shell_cmd(cmd);
}

std::string conn_player_num(const std::string port){
    return exec_shell_cmd("lsof -i :"+port+"| grep -v 'COMMAND' | wc -l");
}
