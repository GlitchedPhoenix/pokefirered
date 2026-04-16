SixIsland_AlteringCave_Secret_MapScripts::
	.byte 0

SixIsland_AlteringCave_Secret_EventScript_TriggerGiovanni::
	lockall
	applymovement LOCALID_GIOVANNI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 32
	playse SE_PIN
	applymovement LOCALID_GIOVANNI, AlteringCaveSecret_ApproachMiddle
	waitmovement 0
	goto SixIsland_AlteringCave_Secret_EventScript_Giovanni
	end

SixIsland_AlteringCave_Secret_EventScript_TriggerGiovanniLeft::
	lockall
	applymovement LOCALID_GIOVANNI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 32
	playse SE_PIN
	applymovement LOCALID_GIOVANNI, AlteringCaveSecret_ApproachLeft
	waitmovement 0
	goto SixIsland_AlteringCave_Secret_EventScript_Giovanni
	end

SixIsland_AlteringCave_Secret_EventScript_TriggerGiovanniRight::
	lockall
	applymovement LOCALID_GIOVANNI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 32
	playse SE_PIN
	applymovement LOCALID_GIOVANNI, AlteringCaveSecret_ApproachRight
	waitmovement 0
	goto SixIsland_AlteringCave_Secret_EventScript_Giovanni
	end

SixIsland_AlteringCave_Secret_EventScript_Giovanni::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox AlteringCaveSecret_Text_SoYouFoundMe
	closemessage
	trainerbattle_no_intro TRAINER_VAGABOND_GIOVANNI, AlteringCaveSecret_Text_GiovanniDefeat
	msgbox AlteringCaveSecret_Text_PostBattle
	closemessage
	textcolor 3
	msgbox AlteringCaveSecret_Text_GiovanniUsedFlash, MSGBOX_SIGN
	closemessage
	playse SE_M_LEER
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_GIOVANNI
	setflag FLAG_HIDE_ALTERING_CAVE_GIOVANNI
	setvar VAR_GIOVANNI_ALTERING_CAVE, 1
	delay 32
	playse SE_DOOR
	delay 64
	fadescreen FADE_FROM_WHITE
	releaseall
	end

SixIsland_AlteringCave_Secret_EventScript_AuroraTicket::
	lock
	setflag FLAG_HIDE_AURORA_TICKET
	removeobject 2
	giveitem_msg AlteringCaveSecret_Text_FoundTicket, ITEM_AURORA_TICKET, 1, MUS_OBTAIN_KEY_ITEM
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	release
	end

AlteringCaveSecret_Text_FoundTicket::
	.string "{PLAYER} found an AURORATICKET!$"

AlteringCaveSecret_Text_SoYouFoundMe::
	.string "So, you found me.\p"
	.string "I had hoped my subordinates would\n"
	.string "find my message before somebody\l"
	.string "else did.\p"
	.string "But of all the people...\p"
	.string "{PLAYER}. Face me in battle once\n"
	.string "again.\p"
	.string "I need to know if I am able to\n"
	.string "face my team.\p"
	.string "No holding back!$"

AlteringCaveSecret_Text_GiovanniDefeat::
	.string "It seems I still have a long way\n"
	.string "to go...$"

AlteringCaveSecret_Text_PostBattle::
	.string "{PLAYER}, you truly are a constant\n"
	.string "thorn in my side.\p"
	.string "You are a truly terrifying TRAINER.\n"
	.string "Regardless, I will now be taking\l"
	.string "my leave.\p"
	.string "Goodbye, {PLAYER}. We will not see\n"
	.string "one another again.$"

AlteringCaveSecret_Text_GiovanniUsedFlash::
	.string "MURKROW used FLASH!$"

AlteringCaveSecret_ApproachLeft::
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	walk_left
	walk_down
	step_end

AlteringCaveSecret_ApproachMiddle::
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	step_end

AlteringCaveSecret_ApproachRight::
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	walk_right
	walk_down
	step_end
