PokemonTower_4F_MapScripts::
	.byte 0

PokemonTower_4F_EventScript_Paula::
	trainerbattle_single TRAINER_CHANNELER_PAULA, PokemonTower_4F_Text_PaulaIntro, PokemonTower_4F_Text_PaulaDefeat
	msgbox PokemonTower_4F_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_Laurel::
	trainerbattle_single TRAINER_CHANNELER_LAUREL, PokemonTower_4F_Text_LaurelIntro, PokemonTower_4F_Text_LaurelDefeat
	msgbox PokemonTower_4F_Text_LaurelPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_Jody::
	trainerbattle_single TRAINER_CHANNELER_JODY, PokemonTower_4F_Text_JodyIntro, PokemonTower_4F_Text_JodyDefeat
	msgbox PokemonTower_4F_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_FortuneTeller::
	lockall
	faceplayer
	msgbox FortuneTeller_Text_Greetings
	closemessage
	special HealPlayerParty
	trainerbattle_no_intro TRAINER_FORTUNE_TELLER, FortuneTeller_Text_Defeat
	msgbox FortuneTeller_Text_LookInYourEyes
	closemessage
	#ifdef LEAFGREEN
	giveitem ITEM_GREEN_MAIL, 1
	#else
	giveitem ITEM_RED_MAIL, 1
	#endif
	msgbox FortuneTeller_Text_ShowMe
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, PokemonTower_4F_EventScript_FortuneTellerExit
	case DIR_WEST, PokemonTower_4F_EventScript_FortuneTellerExit2
	case DIR_NORTH, PokemonTower_4F_EventScript_FortuneTellerExit
	goto PokemonTower_4F_EventScript_FortuneTellerExit
	end

PokemonTower_4F_EventScript_FortuneTellerExit::
	applymovement LOCALID_FORTUNE_TELLER, FieryPath_FTWalkAwayRight
	waitmovement 0
	removeobject LOCALID_FORTUNE_TELLER
	setflag FLAG_HIDE_TOWER_FT
	clearflag FLAG_HIDE_FUCHSIA_FT
	setvar VAR_FORTUNE_TELLER_STATE, 1
	setvar VAR_ARTIFACT_CAP, 1
	release
	end

PokemonTower_4F_EventScript_FortuneTellerExit2::
	applymovement LOCALID_FORTUNE_TELLER, FieryPath_FTWalkAwayUp
	waitmovement 0
	removeobject LOCALID_FORTUNE_TELLER
	setflag FLAG_HIDE_TOWER_FT
	clearflag FLAG_HIDE_FUCHSIA_FT
	setvar VAR_FORTUNE_TELLER_STATE, 1
	setvar VAR_ARTIFACT_CAP, 1
	release
	end

FortuneTeller_Text_Greetings:
	.string "Oh, hello there.\p"
	.string "Apologies, am I in the way?\p"
	.string "... ... ... ... ...\p"
	.string "Actually, before that...\p"
	.string "I'm sorry to impose, but would you\n"
	.string "indulge me in a short battle?\p"
	.string "Excellent! Onwards!$"

FortuneTeller_Text_LookInYourEyes:
	.string "Thank you very much. Now, could\n"
	.string "I get a good look at your eyes?\p"
	.string "...\p"
	.string "Hm...I see...\p"
#ifdef LEAFGREEN
	.string "Yes, they twinkle with a soothing\n"
	.string "hazel green...\p"
#else
	.string "Yes, they shimmer with a flickering\n"
	.string "scarlet flame...\p"
#endif
	.string "Here, I would like you to have\n"
	.string "this.$"

FortuneTeller_Text_ShowMe:
	.string "There is a theory I wish to\n"
	.string "prove.\p"
	.string "Send this letter out into the world,\n"
	.string "and if you can find one like it,\l"
	.string "bring it to me.\p"
	.string "I may have something special for\n"
	.string "you if you do.\p"
	.string "May our paths cross again, my\n"
	.string "dear!$"

FieryPath_FTWalkAwayUp:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FieryPath_FTWalkAwayRight:
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FortuneTeller_Text_Defeat:
	.string "Yes, I believe you may be\n"
	.string "the right one...$"
