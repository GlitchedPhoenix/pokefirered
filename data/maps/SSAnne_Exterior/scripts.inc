SSAnne_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SSAnne_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SSAnne_Exterior_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAnne_Exterior_OnFrame
	.byte 0

SSAnne_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SSANNE_EXTERIOR
	goto_if_gt VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 1, SSAnne_Exterior_SneakingIn
	end

SSAnne_Exterior_OnLoad::
	call_if_gt VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 1, SSAnne_Exterior_KillWarp
	end

SSAnne_Exterior_KillWarp::
	setmetatile 32, 14, METATILE_General_BrickPath, 0
	return

SSAnne_Exterior_SneakingIn::
	setflag FLAG_HIDE_SS_ANNE
	removeobject LOCALID_SS_ANNE
	end

SSAnne_Exterior_EonTicket::
	lock
	msgbox SSAnne_Exterior_Text_JustATruck
	goto_if_unset FLAG_GOT_EON_TICKET, SSAnne_Exterior_EventScript_GetEonTicket
	release
	end

SSAnne_Exterior_EventScript_GetEonTicket::
	msgbox SSAnne_Exterior_Text_WhatsThis
	giveitem_msg SSAnne_Exterior_Text_GotTicket, ITEM_EON_TICKET, 1, MUS_OBTAIN_KEY_ITEM
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 3
	setflag FLAG_GOT_EON_TICKET
	clearflag FLAG_HIDE_FERRY_SAILOR
	release
	end

SSAnne_Exterior_Text_GotTicket::
	.string "{PLAYER} found an EON TICKET!$"

SSAnne_Exterior_Text_JustATruck::
	.string "Just a simple truck.$"

SSAnne_Exterior_Text_WhatsThis::
	.string "Huh? There's something underneath…$"

SSAnne_Exterior_OnFrame::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 1, SSAnne_Exterior_ExitSSAnne
	.2byte 0

SSAnne_Exterior_ExitSSAnne::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_le VAR_0x8005, 6, SSAnne_Exterior_WalkDown
	call_if_ge VAR_0x8005, 7, SSAnne_Exterior_WalkInPlaceDown
	fadenewbgm MUS_SURF
	delay 50
	special DoSSAnneDepartureCutscene
	waitstate
	removeobject LOCALID_SS_ANNE
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_Exit
	waitmovement 0
	removeitem ITEM_SS_TICKET
	setvar VAR_MAP_SCENE_VERMILION_CITY, 2
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	warp MAP_VERMILION_CITY, 23, 34
	waitstate
	releaseall
	end

SSAnne_Exterior_WalkDown::
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_WalkDown
	waitmovement 0
	return

SSAnne_Exterior_WalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SSAnne_Exterior_Movement_Exit::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SSAnne_Exterior_Movement_WalkDown::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
