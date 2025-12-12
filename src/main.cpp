#include <iostream>
#include <stdio.h>
#include <dpp/dpp.h>
#include <fstream>
#include "json.hpp"

using namespace std;
ifstream ifs ("../config.json");
using json = nlohmann::json;

int main () {

    if(!ifs){
        cerr << "error at input-stream: config.json";
    }

    json config = json::parse(ifs);
    const string BOT_TOKEN = config["bot_token"].get<string>();
    const dpp::snowflake SERVER_ID = config["server_id"].get<dpp::snowflake>();
    string ip_fpath = config["gameserver"]["ip_file"];
    
    cout << "Bot is starting...\n";
    
    // set up the bot
    dpp::cluster bot(BOT_TOKEN);
    bot.on_log(dpp::utility::cout_logger());
    
    // event trigger
    bot.on_slashcommand([&bot](const dpp::slashcommand_t & event){
        if(event.command.get_command_name() == "mc"){
            dpp::embed mc_info = dpp::embed()
                .set_color(dpp::colors::sti_blue)
                .set_title("mc_flock server ip");

            dpp::message msg(event.command.channel_id, mc_info);
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
                dpp::slashcommand mc_info("mc", "Send a embed with server ip!", bot.me.id);
                bot.guild_command_create(mc_info, SERVER_ID);
	        }
	});

    bot.start(dpp::st_wait);
    return 0;
}
