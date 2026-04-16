FiveIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FiveIsland_OnTransition
	.byte 0

FiveIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FIVE_ISLAND
	end

FiveIsland_EventScript_IslandSign::
	msgbox FiveIsland_Text_IslandSign, MSGBOX_SIGN
	end

FiveIsland_EventScript_BugCatcher::
	msgbox FiveIsland_Text_WeirdBuildingInMeadow, MSGBOX_NPC
	end

FiveIsland_EventScript_Fisher::
	msgbox FiveIsland_Text_BeenGettingBusierAroundHere, MSGBOX_NPC
	end

FiveIsland_EventScript_DottedHole::
	msgbox FiveIsland_Text_IHeardARumor, MSGBOX_NPC
	end

FiveIsland_Text_IHeardARumor::
	.string "I heard a rumor about DOTTED HOLE\n"
	.string "on SIX ISLAND.\p"
	.string "They say you'll find buried treasure\n"
	.string "if you go a certain way.\p"
	.string "But there's something even greater\n"
	.string "if you find your own way!$"
