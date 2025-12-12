# DynamicIP_DiscordBot

This is a light-weight Discord Bot perfect for Game-Servers. The bot updates you about your current public **IPv4** of your Router or your **IPv6** address of your Server,
provided by your isp.
It's a really good alternative, if you don't want to buy a Domain-Name or use third-party services.

## Requirements

Requirements for your server, where your bot should running on.
- dpp libary - [install options](https://dpp.dev/installing.html)
- cmake - install or your package-manager (recommended) or build it from a [download](https://cmake.org/download/)
- build-essential

### Create your Discord Application-Token:
1. go to [https://discord.com/developers/applications]
2. sign in with your Discord Account or create a new one
3. click on the 'New Application' button on the top right (or where ever it is now)
4. create the Bot with a name you want
5. click on the 'Bot' tab, on the left > click 'Add Bot'
6. on your current screen should be now some personal configuration options like name, description, icon ... 
click on 'Reset Token' to create your Bot-Token

***Please don't share this token. You can store NOW the token in a passwort-manager. If you ever somehow compromise your current bot token or see your bot in danger, you can regenerate the token in the panel.*** 

### Get the Bot on your server:
7. go to the [application page](https://discord.com/developers/applications) from Discord of your Bot (click on your Bot under 'My Applications')
8. open the tab 'OAuth2' > 'URL Generator'
9. tick the scope 'bot' and then tick the permissions: Manage Channels, Send Messages, Embed Links
10. Make sure the Integration type is on Guild Install
11. now you can copy and paste the Gnereated URL in your Browser and add it to your Server.

### Get the Bot running:

Execute the following set-up lines on your servers shell.
```bash
git clone https://github.com/kenkyo0/dynamicIP_discordBot.git
cd dynamicIP_ServerBot/build
cmake ..
cd ..
cmake --build build/ -j4
```
now go into the build/ directorie and start the Bot.

If everything went the right way, you should see your Bot online on Discord.
You also should be able to run the discord command /info now, if the command not works restart the bot or if it still doesn't execute the command, check the bot permissions.
