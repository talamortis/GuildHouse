
# Guild House Module


## Description

This is a phased guild house system for Azerothcore, it allows players to from the same guild to visit their guild house.
All guilds will get their own phasing system which then the guild master will have to purchase NPC's creatures and other stuff to complete the creation.

### Purchasables

* Class Trainers (all available in Wrath)
* Primary Profession Trainers (all available in Wrath)
* Secondary Profession Trainers (all available in Wrath)
* Vendors: Reagents, Food & Water and Trade Goods
* Portals to Neutral, Horde and Alliance cities
* Spirit Healer
* Guild Bank and Personal Bank access
* Auctioneer

## How to use ingame
1) As GM: .npc add 70101 -> somewhere public and accessible by other players.
2) Purchase a guild house from the added NPC, then either teleport to the guildhouse via the NPC or chat: `.guildhouse tele`
3) Once the player is in the location of the guild house the guild master has a command .guildhouse spawnnpc this will load the Guild House Assistant.
4) Speak with the Guild House Assistant to begin purchasing objects.

## Requirements

- AzerothCore v1.0.1+

## Installation

```
1) Simply place the module under the `modules` directory of your AzerothCore source. 
2) Import the SQL manually to the right Database (auth, world or characters)
3) Apply the guildhouse.patch to your source 
4) Re-run cmake and launch a clean build of AzerothCore.
```
## Patch Information (guildhouse.patch)

The patch basically turns the selected area from a bitmask to a uint, this fixes the issues with the phasing

Before Patch :
Guild 1 Can see phase 1
Guild 2 Can see phase 2
Guild 3 Can See Guild 1 & 2

After Patch: 
All guilds will now have a seperate phase for the area 876 (GM Island)

## Edit module configuration (optional)

If you need to change the module configuration, go to your server configuration folder (where your `worldserver` or `worldserver.exe` is), copy `mod_guild_house_v2.conf.dist` to `mod_guild_house_v2.conf` and edit that new file.

## Credits

* [Talamortis](https://github.com/talamortis) (Original author of the module)
* [Rochet2](https://github.com/Rochet2/): Thanks for the help with the phasing situation & General support
* [Anhanga](https://github.com/rbedfordpro)

AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/64FH6Y8)
