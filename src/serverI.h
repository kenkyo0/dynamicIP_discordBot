#pragma once // prevent for multiple implementation of the header by the compiler
#ifndef HEADER_INCLUDE_
#define HEADER_INCLUDE_

#include <string>

std::string exec_shell_cmd(const std::string cmd);
std::string get_dIP(bool ipv6);
std::string conn_player_num(const std::string port);

#endif // HEADER_INCLUED_
