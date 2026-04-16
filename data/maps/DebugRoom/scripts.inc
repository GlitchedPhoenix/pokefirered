DebugRoom_MapScripts::
	.byte 0

DebugMon::
	lock
	givemon SPECIES_LAPRAS, 100
	release
	end

Debug_RubySapphire::
	lock
	goto_if_set FLAG_RECOVERED_SAPPHIRE, Debug_Emerald
	goto_if_set FLAG_GOT_RUBY, Debug_Sapphire
	setflag FLAG_GOT_RUBY
	giveitem ITEM_RUBY
	release
	end

Debug_EscapeRoom::
	lock
	giveitem ITEM_ESCAPE_ROPE, 20
	giveitem ITEM_MASTER_BALL, 20
	giveitem ITEM_SS_TICKET, 1
	giveitem ITEM_TM01, 1
	giveitem ITEM_TM50, 1
	giveitem ITEM_EXP_SHARE, 1
	giveitem ITEM_LUCKY_EGG, 1
	setflag FLAG_GOT_SS_TICKET
	setvar VAR_ARTIFACT_CAP, 6
	release
	end

Debug_Mail::
	lock
	giveitem ITEM_RUBY_MAIL, 1
	giveitem ITEM_SAPPHIRE_MAIL, 1
	giveitem ITEM_EMERALD_MAIL, 1
	giveitem ITEM_RED_MAIL, 1
	giveitem ITEM_GREEN_MAIL, 1
	giveitem ITEM_BLUE_MAIL, 1
	clearflag FLAG_HIDE_CONVENIENCE_FT
	release
	end

Debug_ItemStacks::
	lock
	giveitem ITEM_RARE_CANDY, 99
	giveitem ITEM_NUGGET, 99
	giveitem ITEM_BIG_PEARL, 99
	giveitem ITEM_HYPER_POTION, 99
	giveitem ITEM_FULL_HEAL, 99
	giveitem ITEM_FULL_RESTORE, 99
	giveitem ITEM_WAVE_MAIL, 99
	giveitem ITEM_ESCAPE_ROPE, 99
	giveitem ITEM_IRON, 99
	giveitem ITEM_CARBOS, 99
	giveitem ITEM_HP_UP, 99
	giveitem ITEM_ZINC, 99
	giveitem ITEM_PROTEIN, 99
	giveitem ITEM_CALCIUM, 99
	giveitem ITEM_MAX_REPEL, 99
	release
	end

Debug_Shiny::
	lock
	goto_if_set FLAG_SHINY_CREATION, Debug_UnShiny
	setflag FLAG_SHINY_CREATION
	release
	end

Debug_UnShiny::
	clearflag FLAG_SHINY_CREATION
	release
	end

Debug_ResetLegendary::
	lock
	call EventScript_ResetLegendaries
	release
	end

Debug_Sapphire::
	lock
	setflag FLAG_RECOVERED_SAPPHIRE
	giveitem ITEM_SAPPHIRE
	release
	end

Debug_Emerald::
	lock
	giveitem ITEM_EMERALD
	release
	end

Debug_HoohLugia::
	lock
	givemon SPECIES_HO_OH, 100
	givemon SPECIES_LUGIA, 100
	giveitem ITEM_HM01, 1
	giveitem ITEM_HM02, 1
	giveitem ITEM_HM03, 1
	giveitem ITEM_HM04, 1
	giveitem ITEM_HM05, 1
	giveitem ITEM_HM06, 1
	giveitem ITEM_HM07, 1
	giveitem ITEM_LEMONADE, 1
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_B_DASH
	release
	end

Debug_Scrap1::
	lock
	giveitem ITEM_TORN_SCRAP_1
	release
	end

Debug_Aurora::
	lock
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	release
	end

Debug_Mystic::
	lock
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	release
	end

Debug_Faraway::
	lock
	giveitem ITEM_NEW_SEA_MAP
	release
	end

Debug_Southern::
	lock
	giveitem ITEM_EON_TICKET
	release
	end

Debug_Scrap2::
	lock
	giveitem ITEM_TORN_SCRAP_2
	release
	end

Debug_Scrap3::
	lock
	giveitem ITEM_TORN_SCRAP_3
	setvar VAR_MAP_SCENE_VERMILION_CITY, 3
	release
	end

Debug_AdvanceOneIsland::
	lock
	addvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1
	setvar VAR_MAP_SCENE_VERMILION_CITY, 3
	release
	end