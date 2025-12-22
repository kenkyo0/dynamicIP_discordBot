#pragma once // prevent for multiple implementation of the header by the compiler
#ifndef HEADER_INCLUDE_
#define HEADER_INCLUDE_

#include <string>

std::string get_dIP(bool ipv6);
int conn_player_num(const int port, bool ipv6);

#endif // HEADER_INCLUED_
