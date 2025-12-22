#include "serverI.h"
#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <dpp/dpp.h>
#include "json.hpp"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using json = nlohmann::json;

int main () {
    
    cout << "Bot is starting...\n";

    // read config.json 
    ifstream ifs ("../config.json");
    if(!ifs){
        cerr << "error at input-stream: config.json";
    }

    json config = json::parse(ifs);
    const std::string BOT_TOKEN = config["bot_token"].get<string>();
    const dpp::snowflake SERVER_ID = config["server_id"].get<dpp::snowflake>();
    bool ipv6b = config["gameserver"]["ipv6"].get<bool>();
    const int port = config["gameserver"]["port"].get<int>;


    // set up the bot
    dpp::cluster bot(BOT_TOKEN);
    bot.on_log(dpp::utility::cout_logger());
    
    // event trigger
    bot.on_slashcommand([&bot, ipv6b, port](const dpp::slashcommand_t & event){

        if(event.command.get_command_name() == "info"){

            string ip = get_dIP(ipv6b);
            int player_num = conn_player_num(port, true);

            dpp::embed info = dpp::embed()
                .set_color(0x58D68D) // Mint-Grün
                .set_title("welcome in the flock of joy :)")
                .set_description("follow the link, before you join")
                .add_field(
                        "vibe-check link:",
                        "https://youtu.be/cIMKJ43TFLs?si=ru75W1TJV08EvrhC",
                        true
                )
                .add_field(
                        "IP:",
                        ip
                )
                .add_field(
                        "Player Online:",
                        player_num
                );

            dpp::message msg(event.command.channel_id, info);
            event.reply(msg);
        }
    });

    bot.on_ready([&bot, SERVER_ID](const dpp::ready_t & event) {

            if (dpp::run_once<struct clear_bot_commands>()) {
	            /* clear our commands */
	            /* This one requires a guild id, otherwise it won't know what guild's commands it needs to wipe! */
	            bot.guild_bulk_command_delete(SERVER_ID);
	        }

	        if (dpp::run_once<struct register_bot_commands>()) {
                /* Create and register a command when the bot is ready */
                dpp::slashcommand info("info", "Send a embed with server informations!", bot.me.id);
                bot.guild_command_create(info, SERVER_ID);
	        }
	});

    bot.start(dpp::st_wait);
    return 0;
}
