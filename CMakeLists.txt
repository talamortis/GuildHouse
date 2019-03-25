AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod_guild_house_v2.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod_guild_house_npc.cpp")

AC_ADD_SCRIPT_LOADER("GuildHouseV2" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")
AC_ADD_SCRIPT_LOADER("GuildHouseV2NPC" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/mod_guild_house_v2.conf.dist")