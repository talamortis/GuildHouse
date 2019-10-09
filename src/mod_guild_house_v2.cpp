#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Creature.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "DataMap.h"
#include "GameObject.h"
#include "Transport.h"
#include "Chat.h"
#include "ScriptedGossip.h"
#include "SpellAuraEffects.h"

class GuildData : public DataMap::Base
{
public:
    GuildData() {}
    GuildData(uint32 phase, float posX, float posY, float posZ) : phase(phase), posX(posX), posY(posY), posZ(posZ) {}
    uint32 phase;
    float posX;
    float posY;
    float posZ;
};

class GuildHelper : public GuildScript{

public:

    GuildHelper() : GuildScript("GuildHelper") { }

    void OnCreate(Guild* guild, Player* leader, const std::string& name)
    {
        ChatHandler(leader->GetSession()).PSendSysMessage("You now own a guild. You can purchase a guild house!");
    }

    void OnGuildDisband(Guild* guild)
    {
        if (guild->GetId() != 1)
        {
            WorldDatabase.PQuery("DELETE FROM `creature` WHERE map = 1 AND phaseMask = %u", guild->GetId());
            WorldDatabase.PQuery("DELETE FROM `gameobject WHERE map = 1 and phaseMask = %u", guild->GetId());
        }

        CharacterDatabase.PQuery("DELETE FROM `guild_house` WHERE guild = %u", guild->GetId());
    }
};

class GuildHouseSeller : public CreatureScript {

public:
    GuildHouseSeller() : CreatureScript("GuildHouseSeller") {}

    bool OnGossipHello(Player *player, Creature * creature)
    {
        if (!player->GetGuild())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You are not in a guild");
            return false;
        }

        if (player->GetGuild()->GetLeaderGUID() == player->GetGUID())
        {
            // Only leader of the guild can buy / sell guild house
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "Buy Guild House!", GOSSIP_SENDER_MAIN, 2);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "Sell Guild House!", GOSSIP_SENDER_MAIN, 3, "Are you sure you want to sell your Guild house?", NULL, false);
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "Teleport to Guild House", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Close", GOSSIP_SENDER_MAIN, 5);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature * m_creature, uint32 sender, uint32 action)
    {
        uint32 map;
        float posX;
        float posY;
        float posZ;

        switch (action)
        {
        case 100: // gmsiland
            map = 1;
            posX = 16226.117f;
            posY = 16258.046f;
            posZ = 13.257628f;
            break;
        case 5: // close
            player->CLOSE_GOSSIP_MENU();
            break;
        case 3: // Sell back guild house
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT id, `guild` FROM `guild_house` WHERE guild = %u", player->GetGuildId());

            if (!result)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You do not have a active Guild house!");
                return false;
            }

            CharacterDatabase.PQuery("DELETE FROM `guild_house` WHERE guild = %u", player->GetGuildId());

            if (player->GetGuildId() != 1)
            {
                WorldDatabase.PQuery("DELETE FROM `creature` WHERE `map` = 1 AND phaseMask = %u", player->GetGuildId());
                WorldDatabase.PQuery("DELETE FROM `gameobject` WHERE `map` = 1 and phaseMask = %u", player->GetGuildId());
            }

            ChatHandler(player->GetSession()).PSendSysMessage("You have successfully sold your guild house");
            player->ModifyMoney(+(sConfigMgr->GetIntDefault("CostGuildHouse", 10000000) / 2));

            break;
        }
        case 2: // buy guild house
            BuyGuildHouse(player->GetGuild(), player, m_creature);
            break;
        case 1: // teleport to guild house
            TeleportGuildHouse(player->GetGuild(), player);
            break;
        }

        if (action >= 100)
        {
            CharacterDatabase.PQuery("INSERT INTO `guild_house` (guild, phase, map, positionX, positionY, positionZ) VALUES (%u, %u, %u, %f, %f, %f)", player->GetGuildId(), player->GetGuildId(), map, posX, posY, posZ);
            player->ModifyMoney(-(sConfigMgr->GetIntDefault("CostGuildHouse", 10000000)));
            ChatHandler(player->GetSession()).PSendSysMessage("You have successfully purchased a guild house");
            player->GetGuild()->BroadcastToGuild(player->GetSession(), false, "We have now got a guild house", LANG_UNIVERSAL);
        }
        return true;
    }

    bool BuyGuildHouse(Guild* guild, Player* player, Creature* creature)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT `id`, `guild` FROM guild_house WHERE `guild` = %u", guild->GetId());

        if (result)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You cant buy any more guilds houses!");
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "GM Island", GOSSIP_SENDER_MAIN, 100, "Buy GM island Guildhouse?", sConfigMgr->GetIntDefault("CostGuildHouse", 10000000), false);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " ----- More to Come ----", GOSSIP_SENDER_MAIN, 4);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;

    }

    void TeleportGuildHouse(Guild* guild, Player* player)
    {
        GuildData* guildData = player->CustomData.GetDefault<GuildData>("phase");
        QueryResult result = CharacterDatabase.PQuery("SELECT `id`, `guild`, `phase`, `map`,`positionX`, `positionY`, `positionZ` FROM guild_house WHERE `guild` = %u", guild->GetId());

        if (!result)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Your Guild does not own a guild house");
            return;
        }

        do {

            Field* fields = result->Fetch();
            uint32 id = fields[0].GetUInt32();
            uint32 guild = fields[1].GetUInt32();
            guildData->phase = fields[2].GetUInt32();
            uint32 map = fields[3].GetUInt32();
            guildData->posX = fields[4].GetFloat();
            guildData->posY = fields[5].GetFloat();
            guildData->posZ = fields[6].GetFloat();

            player->TeleportTo(map, guildData->posX, guildData->posY, guildData->posZ, player->GetOrientation());
            player->SetPhaseMask(guildData->phase, true);

        } while (result->NextRow());
    }
};

class GuildHouseV2PlayerScript : public PlayerScript
{
public:
    GuildHouseV2PlayerScript() : PlayerScript("GuildHouseV2PlayerScript") { }

    void OnLogin(Player* player)
    {
        CheckPlayer(player);
    }

    void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea)
    {
        if (newZone == 876)
            CheckPlayer(player);
        else
            player->SetPhaseMask(GetNormalPhase(player), true);
    }

    uint32 GetNormalPhase(Player* player) const
    {
        if (player->IsGameMaster())
            return uint32(PHASEMASK_ANYWHERE);

        uint32 phase = PHASEMASK_NORMAL;
        Player::AuraEffectList const& phases = player->GetAuraEffectsByType(SPELL_AURA_PHASE);
        if (!phases.empty())
            phase = phases.front()->GetMiscValue();
        if (uint32 n_phase = phase & ~PHASEMASK_NORMAL)
            return n_phase;

        return PHASEMASK_NORMAL;
    }

    void CheckPlayer(Player* player)
    {
        GuildData* guildData = player->CustomData.GetDefault<GuildData>("phase");
        QueryResult result = CharacterDatabase.PQuery("SELECT `id`, `guild`, `phase`, `map`,`positionX`, `positionY`, `positionZ` FROM guild_house WHERE `guild` = %u", player->GetGuildId());

        if (!result)
            return;

        do {

            Field* fields = result->Fetch();
            uint32 id = fields[0].GetUInt32();
            uint32 guild = fields[1].GetUInt32();
            guildData->phase = fields[2].GetUInt32();
            uint32 map = fields[3].GetUInt32();
            guildData->posX = fields[4].GetFloat();
            guildData->posY = fields[5].GetFloat();
            guildData->posZ = fields[6].GetFloat();

        } while (result->NextRow());

        if (player->GetZoneId() == 876 && player->GetAreaId() == 876) // GM Island
        {
            // If player is not in a guild he doesnt have a guild house teleport away

            if (!result || !player->GetGuild())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Your Guild does not own a guild house");
                teleport(player);
                return;
            }
            player->SetPhaseMask(guildData->phase, true);
        }
        else
            player->SetPhaseMask(GetNormalPhase(player), true);
    }

    void teleport(Player* player)
    {
        if (player->GetTeamId() == TEAM_ALLIANCE)
            player->TeleportTo(0, -8833.379883f, 628.627991f, 94.006599f, 1.0f);
        else
            player->TeleportTo(1, 1486.048340f, -4415.140625f, 24.187496f, 0.13f);
    }
};

class GuildHouseCommand : public CommandScript
{
public:
    GuildHouseCommand() : CommandScript("GuildHouseCommand") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> GuildHouseCommandTable =
        {
            // View Command
            { "Teleport", SEC_PLAYER, false, &HandleGuildHouseTeleCommand, "" },
            // Set Command
            { "SpawnNpc", SEC_PLAYER, false, &HandleSpawnNPCCommand, "" },
        };

        static std::vector<ChatCommand> GuildHouseCommandBaseTable =
        {
            { "Guildhouse", SEC_PLAYER, false, nullptr, "", GuildHouseCommandTable }
        };

        return GuildHouseCommandBaseTable;
    }

    static bool HandleSpawnNPCCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->GetAreaId() != 876)
            return false;

        if (player->GetGuild()->GetLeaderGUID() != player->GetGUID())
            return false;

        if (player->FindNearestCreature(70102, VISIBLE_RANGE, true))
            return false;

        float posX = 16202.185547f;
        float posY = 16255.916992f;
        float posZ = 21.160221f;
        float ori = 6.195375f;

        Creature* creature = new Creature();

        if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), player->GetMap(), player->GetPhaseMask(), 70102, 0, posX, posY, posZ, ori))
        {
            delete creature;
            return false;
        }
        creature->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), player->GetPhaseMask());
        uint32 db_guid = creature->GetDBTableGUIDLow();

        creature->CleanupsBeforeDelete();
        delete creature;
        creature = new Creature();
        if (!creature->LoadCreatureFromDB(db_guid, player->GetMap()))
        {
            delete creature;
            return false;
        }

        sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));
        return true;
    }

    static bool HandleGuildHouseTeleCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player || player->IsInCombat())
            return false;

        GuildData* guildData = player->CustomData.GetDefault<GuildData>("phase");
        QueryResult result = CharacterDatabase.PQuery("SELECT `id`, `guild`, `phase`, `map`,`positionX`, `positionY`, `positionZ` FROM guild_house WHERE `guild` = %u", player->GetGuildId());

        if (!result)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Your Guild does not own a guild house");
            return false;
        }

        do {

            Field* fields = result->Fetch();
            uint32 id = fields[0].GetUInt32();
            uint32 guild = fields[1].GetUInt32();
            guildData->phase = fields[2].GetUInt32();
            uint32 map = fields[3].GetUInt32();
            guildData->posX = fields[4].GetFloat();
            guildData->posY = fields[5].GetFloat();
            guildData->posZ = fields[6].GetFloat();

            player->TeleportTo(map, guildData->posX, guildData->posY, guildData->posZ, player->GetOrientation());
            player->SetPhaseMask(guildData->phase, true);

        } while (result->NextRow());

        return true;
    }
};

class GuildHouseConf : public WorldScript
{
public:
    GuildHouseConf() : WorldScript("GuildHouseConf") {}

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/mod_guild_house_v2.conf";

#ifdef WIN32
            cfg_file = "mod_guild_house_v2.conf";
#endif

            std::string cfg_def_file = cfg_file + ".dist";
            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddGuildHouseV2Scripts() {
    new GuildHelper();
    new GuildHouseSeller();
    new GuildHouseV2PlayerScript();
    new GuildHouseCommand();
}

