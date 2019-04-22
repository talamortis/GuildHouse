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

int cost, GuildHouseInnKeeper, GuildHouseBank, GuildHouseMailBox, GuildHouseAuctioneer, GuildHouseTrainer, GuildHouseVendor, GuildHouseObject, GuildHousePortal, GuildHouseProff;

class GuildHouseSpawner : public CreatureScript {

public:
    GuildHouseSpawner() : CreatureScript("GuildHouseSpawner") { }

    bool OnGossipHello(Player *player, Creature * creature)
    {

        if (player->GetGuild())
        {
            if (player->GetGuild()->GetLeaderGUID() != player->GetGUID())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You are not the guild leader, sorry i cant do business with you");
                return false;
            }
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You are not in a guild!");
            return false;
        }

        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Spawn Innkeeper", GOSSIP_SENDER_MAIN, 18649, "Add a Innkeeper?", GuildHouseInnKeeper, false);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Spawn Mailbox", GOSSIP_SENDER_MAIN, 184137, "Spawn a mailbox?", GuildHouseMailBox, false);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Spawn Class Trainer", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Spawn Vendor", GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Spawn City Portals / Objects", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Spawn Bank", GOSSIP_SENDER_MAIN, 30605, "Spawn banker?", GuildHouseBank, false);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Spawn Auctioneer", GOSSIP_SENDER_MAIN, 6, "Spawn auctioneer", GuildHouseAuctioneer, false);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Primary Profession Trainers", GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Secondry Profession Trainers", GOSSIP_SENDER_MAIN, 8);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature * m_creature, uint32 sender, uint32 action)
    {

        switch (action)
        {
        case 2: // spawn class trainer
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Death Knight", GOSSIP_SENDER_MAIN, 33251, "Spawn Death Knight Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Druid", GOSSIP_SENDER_MAIN, 26324, "Spawn Druid Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Hunter", GOSSIP_SENDER_MAIN, 26325, "Spawn Hunter Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Mage", GOSSIP_SENDER_MAIN, 26326, "Spawn Mage Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Paladin", GOSSIP_SENDER_MAIN, 26327, "Spawn Paladin Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Priest", GOSSIP_SENDER_MAIN, 26328, "Spawn Priest Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Rogue", GOSSIP_SENDER_MAIN, 26329, "Spawn Rogue Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Shaman", GOSSIP_SENDER_MAIN, 26330, "Spawn Shaman Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Warlock", GOSSIP_SENDER_MAIN, 26331, "Spawn Warlock Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Warrior", GOSSIP_SENDER_MAIN, 26332, "Spawn Warrior Trainer?", GuildHouseTrainer, false);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 3: // Vendors
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Trade Supplies", GOSSIP_SENDER_MAIN, 28692, "Spawn Trade Supplies?", GuildHouseVendor, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Tabard Vendor", GOSSIP_SENDER_MAIN, 28776, "Spawn Tabard Vendor?", GuildHouseVendor, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Food & Drink", GOSSIP_SENDER_MAIN, 29715, "Spawn Food & Drink?", GuildHouseVendor, false);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 4: //objects / portals
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Forge", GOSSIP_SENDER_MAIN, 1685, "Add a forge?", GuildHouseObject, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, "Anvil", GOSSIP_SENDER_MAIN, 4087, "Add a Anvil?", GuildHouseObject, false);
            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Stormwind", GOSSIP_SENDER_MAIN, 183325, "Add Stormwind Portal?", GuildHousePortal, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Ironforge", GOSSIP_SENDER_MAIN, 183322, "Add Ironforge Portal?", GuildHousePortal, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Darnassus", GOSSIP_SENDER_MAIN, 183317, "Add Darnassus Portal?", GuildHousePortal, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Exodar", GOSSIP_SENDER_MAIN, 183321, "Add Exodar Portal?", GuildHousePortal, false);
            }
            else
            {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Orgrimmar", GOSSIP_SENDER_MAIN, 183323, "Add Orgrimmar Portal?", GuildHousePortal,  false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Undercity", GOSSIP_SENDER_MAIN, 183327, "Add Undercity Portal?", GuildHousePortal,  false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Thunderbluff", GOSSIP_SENDER_MAIN, 183326, "Add Thunderbuff Portal?", GuildHousePortal,  false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Silvermoon", GOSSIP_SENDER_MAIN, 183324, "Add Silvermoon Portal?", GuildHousePortal,  false);
            }
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Portal: Dalaran", GOSSIP_SENDER_MAIN, 191164, "Add Dalaran Portal?", GuildHousePortal,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Guild Vault", GOSSIP_SENDER_MAIN, 187293, "Add Guild Vault?", GuildHouseObject,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, "Barber Chair", GOSSIP_SENDER_MAIN, 191028, "Add a Barber Chair?", GuildHouseObject,  false);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 6: // Auctioneer
        {
            uint32 auctioneer = 0;
            auctioneer = player->GetTeamId() == TEAM_ALLIANCE ? 8719 : 9856;
            SpawnNPC(auctioneer, player);
            break;
        }
        case 7: // spawn proffession trainers
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Alchemy Trainer", GOSSIP_SENDER_MAIN, 33608, "Spawn Alchemy Trainer?", GuildHouseProff, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Blacksmithing Trainer", GOSSIP_SENDER_MAIN, 33609, "Spawn Blacksmithing Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Enchanting Trainer", GOSSIP_SENDER_MAIN, 33610, "Spawn Enchanting Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Engineering Trainer", GOSSIP_SENDER_MAIN, 33611, "Spawn Engineering Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Tailoring Trainer", GOSSIP_SENDER_MAIN, 33613, "Spawn Tailoring Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Leatherworking Trainer", GOSSIP_SENDER_MAIN, 33612, "Spawn Leatherworking Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Jewlelcrafing Trainer", GOSSIP_SENDER_MAIN, 33614, "Spawn Jewelcrafting Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Inscription Trainer", GOSSIP_SENDER_MAIN, 33615, "Spawn Inscription Trainer?", GuildHouseProff, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Skinning Trainer", GOSSIP_SENDER_MAIN, 33618, "Spawn Skinning Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Mining Trainer", GOSSIP_SENDER_MAIN, 33617, "Spawn Mining Trainer?", GuildHouseProff, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Herbalism Trainer", GOSSIP_SENDER_MAIN, 33616, "Spawn Herbalism Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 8: // secondry proff trainers
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "First Aid Trainer", GOSSIP_SENDER_MAIN, 33621, "Spawn Fist Aid Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Fishing Trainer", GOSSIP_SENDER_MAIN, 33623, "Spawn Fishing Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Cooking Trainer", GOSSIP_SENDER_MAIN, 33619, "Spawn Cooking Trainer?", GuildHouseProff,  false);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 9: // go back!
            OnGossipHello(player, m_creature);
            break;
        case 10: //PVP toggle
            break;
        case 30605: // Banker
            cost = GuildHouseBank;
            SpawnNPC(action, player);
            break;
        case 18649: // Innkeeper
            cost = GuildHouseInnKeeper;
            SpawnNPC(action, player);
            break;
        case 26327: // Paladin
        case 26324: // Druid
        case 26325: // Hunter
        case 26326: // Mage 
        case 26328: // Priest.
        case 26329: // Rogue
        case 26330: // Shaman
        case 26331: // Warlock
        case 26332: // Warrior
        case 33251: // Death Knight
            cost = GuildHouseTrainer;
            SpawnNPC(action, player);
            break;
        case 33609: // Blacksmithing
        case 33617: // Mining
        case 33611: // Engineering
        case 33614: // Jewelcrafting
        case 33610: // Enchanting
        case 33615: // Inscription
        case 33612: // Leatherworking
        case 33618: // Skinning
        case 33608: // Alchemy
        case 33616: // Herbalism
        case 33613: // Tailoring
        case 33619: // Cooking
        case 33623: // Fishing 
        case 33621: // First Aid
            cost = GuildHouseProff;
            SpawnNPC(action, player);
            break;
        case 28692: // Trade supplies
        case 28776: // Tabard Vendor
        case 29715: // Food & Drink
            cost = GuildHouseProff;
            SpawnNPC(action, player);
            break;
        //
        // Objects
        //
        case 184137: // mailbox
            cost = GuildHouseMailBox;
            SpawnObject(action, player);
            break;
        case 1685:  // forge
        case 4087:  // Anvil
        case 187293: // Guild Vault
        case 191028: // Barber Chair
            cost = GuildHouseObject;
            SpawnObject(action, player);
            break;
        case 183325: // Stormwind Portal
        case 183323: // Orgrimmar Portal
        case 183322: // Ironforge Portal
        case 183327: // Undercity Portal
        case 183317: // Darnassus Portal
        case 183326: // Thunder bluff portal
        case 183324: // Silvermoon Portal
        case 183321: // Exodar Portal
        case 191164: // Dalaran Portal
            cost = GuildHousePortal;
            SpawnObject(action, player);
            break;
        }
        return true;
    }

    void SpawnNPC(uint32 entry, Player* player)
    {
        if (player->FindNearestCreature(entry, VISIBILITY_RANGE, true))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You already have this creature!");
            player->CLOSE_GOSSIP_MENU();
            return;
        }

        float posX;
        float posY;
        float posZ;
        float ori;

        QueryResult result = WorldDatabase.PQuery("SELECT `posX`, `posY`, `posZ`, `orientation` FROM `guild_house_spawns` WHERE `entry` = %u", entry);

        if (!result)
            return;

        do
        {
            Field* fields = result->Fetch();
            posX = fields[0].GetFloat();
            posY = fields[1].GetFloat();
            posZ = fields[2].GetFloat();
            ori = fields[3].GetFloat();

        } while (result->NextRow());

        Creature* creature = new Creature();

        if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), player->GetMap(), player->GetPhaseMask(), entry, 0, posX,posY, posZ, ori))
        {
            delete creature;
            return;
        }
        creature->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), player->GetPhaseMask());
        uint32 db_guid = creature->GetDBTableGUIDLow();

        creature->CleanupsBeforeDelete();
        delete creature;
        creature = new Creature();
        if (!creature->LoadCreatureFromDB(db_guid, player->GetMap()))
        {
            delete creature;
            return;
        }

        sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));
        player->ModifyMoney(-cost);
        player->CLOSE_GOSSIP_MENU();
    }

    void SpawnObject(uint32 entry, Player* player)
    {
        float posX;
        float posY;
        float posZ;
        float ori;

        QueryResult result = WorldDatabase.PQuery("SELECT `posX`, `posY`, `posZ`, `orientation` FROM `guild_house_spawns` WHERE `entry` = %u", entry);

        if (!result)
            return;

        do
        {
            Field* fields = result->Fetch();
            posX = fields[0].GetFloat();
            posY = fields[1].GetFloat();
            posZ = fields[2].GetFloat();
            ori = fields[3].GetFloat();

        } while (result->NextRow());

        if (player->FindNearestGameObject(entry, VISIBLE_RANGE))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You already have this object!");
            player->CLOSE_GOSSIP_MENU();
            return;
        }

        uint32 objectId = entry;
        if (!objectId)
            return;

        const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

        if (!objectInfo)
            return;

        if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            return ;

        GameObject* object = sObjectMgr->IsGameObjectStaticTransport(objectInfo->entry) ? new StaticTransport() : new GameObject();
        uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

        if (!object->Create(guidLow, objectInfo->entry, player->GetMap(), player->GetPhaseMask(), posX, posY, posZ, ori, G3D::Quat(), 0, GO_STATE_READY))
        {
            delete object;
            return;
        }

        // fill the gameobject data and save to the db
        object->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), player->GetPhaseMask());
        // delete the old object and do a clean load from DB with a fresh new GameObject instance.
        // this is required to avoid weird behavior and memory leaks
        delete object;

        object = sObjectMgr->IsGameObjectStaticTransport(objectInfo->entry) ? new StaticTransport() : new GameObject();
        // this will generate a new guid if the object is in an instance
        if (!object->LoadGameObjectFromDB(guidLow, player->GetMap()))
        {
            delete object;
            return;
        }

        // TODO: is it really necessary to add both the real and DB table guid here ?
        sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));
        player->ModifyMoney(-cost);
        player->CLOSE_GOSSIP_MENU();
    }    
};

class GuildHouseNPCConf : public WorldScript
{
public:
    GuildHouseNPCConf() : WorldScript("GuildHouseNPCConf") {}

    void OnBeforeConfigLoad(bool reload) override
    {
        GuildHouseInnKeeper = sConfigMgr->GetIntDefault("GuildHouseInnKeeper", 1000000);
        GuildHouseBank = sConfigMgr->GetIntDefault("GuildHouseBank", 1000000);
        GuildHouseMailBox = sConfigMgr->GetIntDefault("GuildHouseMailbox", 500000);
        GuildHouseAuctioneer = sConfigMgr->GetIntDefault("GuildHouseAuctioneer", 500000);
        GuildHouseTrainer = sConfigMgr->GetIntDefault("GuildHouseTrainerCost", 1000000);
        GuildHouseVendor = sConfigMgr->GetIntDefault("GuildHouseVendor", 500000);
        GuildHouseObject = sConfigMgr->GetIntDefault("GuildHouseObject", 500000);
        GuildHousePortal = sConfigMgr->GetIntDefault("GuildHousePortal", 500000);
        GuildHouseProff = sConfigMgr->GetIntDefault("GuildHouseProff", 500000);
    }
};

void AddGuildHouseV2NPCScripts()
{
    new GuildHouseSpawner();
    new GuildHouseNPCConf();
}
