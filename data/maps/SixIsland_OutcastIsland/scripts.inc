SixIsland_OutcastIsland_MapScripts::
	.byte 0

SixIsland_OutcastIsland_EventScript_Rocket::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_46, SixIsland_OutcastIsland_Text_RocketIntro, SixIsland_OutcastIsland_Text_RocketDefeat
	goto_if_set FLAG_HIDE_OUTCAST_ROCKET, SixIsland_OutcastIsland_EventScript_RocketGivenUp
	msgbox SixIsland_OutcastIsland_Text_RocketPostBattle, MSGBOX_AUTOCLOSE
	goto_if_gt VAR_EMAIL_HINT, 1, SixIsland_OutcastIsland_EventScript_Rocket2
	release
	end

SixIsland_OutcastIsland_EventScript_RocketGivenUp::
	msgbox SixIsland_OutcastIsland_Text_Ellipses
	release
	end

SixIsland_OutcastIsland_EventScript_Rocket2::
	lock
	msgbox SixIsland_OutcastIsland_Text_WarehouseGone
	closemessage
	delay 32
	playse SE_PIN
	applymovement 1, SixIsland_OutcastIsland_Movement_Contemplate
	waitmovement 0
	delay 64
	msgbox SixIsland_OutcastIsland_Text_HideoutHint
	closemessage
	setflag FLAG_HIDE_OUTCAST_ROCKET
	release
	end

SixIsland_OutcastIsland_Movement_Contemplate::
	emote_dots
	step_end

SixIsland_OutcastIsland_Text_WarehouseGone::
	.string "A cipher? I got no idea what\n"
	.string "you're on about, man.\p"
	.string "Huh? The WAREHOUSE was abandoned?\n"
	.string "Ha! Don't make me laugh!$"

SixIsland_OutcastIsland_Text_HideoutHint::
	.string "Tch. You're serious, aren't you?\n"
	.string "So no one's coming for me, eh?\p"
	.string "...Fine. I don't know the cipher,\n"
	.string "that stuff was always above my\l"
	.string "pay grade.\p"
	.string "But if you look somewhere the\n"
	.string "BOSS was at, there might be\l"
	.string "something written down.\p"
	.string "Now leave me alone, I gotta\n"
	.string "figure some things out...$"

SixIsland_OutcastIsland_Text_Ellipses::
	.string "...$"

