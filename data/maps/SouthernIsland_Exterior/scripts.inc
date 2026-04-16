SouthernIsland_Exterior_MapScripts::
	.byte 0

SouthernIsland_Exterior_EventScript_Sailor::
	lock
	faceplayer
	msgbox SouthernIsland_Exterior_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FarawayIsland_Entrance_EventScript_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	goto SouthernIsland_Exterior_EventScript_SailHome
	release
	end

SouthernIsland_Exterior_EventScript_SailHome::
	setvar VAR_0x8004, SEAGALLOP_SOUTHERN_ISLAND
	setvar VAR_0x8006, SEAGALLOP_VERMILION_CITY
	goto EventScript_SetSail
	end

SouthernIsland_Exterior_EventScript_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

Ferry_EventScript_DepartIslandSouth::
	applymovement LOCALID_PLAYER, Ferry_Movement_DepartIslandBoardSouth
	waitmovement 0
	return

Ferry_EventScript_DepartIslandWest::
	applymovement LOCALID_PLAYER, Ferry_Movement_DepartIslandBoardWest
	waitmovement 0
	return

Ferry_Movement_DepartIslandBoardSouth::
	walk_down
	step_end

Ferry_Movement_DepartIslandBoardWest::
	walk_left
	walk_in_place_faster_down
	step_end

SouthernIsland_Exterior_EventScript_Sign::
	msgbox SouthernIsland_Exterior_Text_Sign, MSGBOX_SIGN
	end

EventTicket_Text_ShowEonTicket::
	.string "Aye, mate, are you the one who brought\n"
	.string "that mighty odd PASS?\p"
	.string "I'll tell you, you're trying to reach a\n"
	.string "tiny spit of an island far in the south.\p"
	.string "There's no telling what we'll encounter\n"
	.string "once we reach there, aye.\l"
	.string "That shivers my timbers!\p"
	.string "All aboard!$"

SouthernIsland_Exterior_Text_SailorReturn::
	.string "Aye, mate, there's nothing here to\n"
	.string "see or do all the way out here.\p"
	.string "What say we sail back to VERMILION?$"

EventTicket_Text_SailHome::
	.string "Aye, right, then!\n"
	.string "Sail home we will!$"

EventTicket_Text_AsYouLike::
	.string "Aye, right, as you like, then.$"

SouthernIsland_Interior_Text_Sign::
	.string "“All dreams are but another reality.\n"
	.string "Never forget…”$"

SouthernIsland_Exterior_Text_Sign::
	.string "“Those whose memories fade seek to\n"
	.string "carve them in their hearts…”$"


