VermilionCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VermilionCity_OnFrame
	.byte 0

VermilionCity_OnFrame::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 2, VermilionCity_EventScript_ExitSSAnne
	.2byte 0

VermilionCity_EventScript_ExitSSAnne::
	lockall
	applymovement LOCALID_PLAYER, VermilionCity_Movement_ExitSSAnne
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 3
	releaseall
	end

VermilionCity_Movement_ExitSSAnne::
	walk_up
	walk_up
	step_end

VermilionCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VERMILION_CITY
	call_if_set FLAG_TALKED_TO_OAKS_AIDE_IN_VERMILION, VermilionCity_EventScript_HideOaksAide
	call_if_eq VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 3, VermilionCity_EventScript_SetupSailor
	end

VermilionCity_EventScript_SetupSailor::
	setobjectxyperm LOCALID_VERMILION_FERRY_SAILOR, 32, 28
	return

VermilionCity_EventScript_Weirdo::
	lock
	setobjectxyperm LOCALID_VERMILION_FERRY_SAILOR, 24, 33
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	release
	end

VermilionCity_EventScript_HideOaksAide::
	setflag FLAG_HIDE_VERMILION_CITY_OAKS_AIDE
	return

VermilionCity_EventScript_Woman::
	msgbox VermilionCity_Text_GrimerMultipliesInSludge, MSGBOX_NPC
	end

VermilionCity_EventScript_OldMan1::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, VermilionCity_EventScript_OldMan1SSAnneLeft
	msgbox VermilionCity_Text_DidYouSeeSSAnneInHarbor
	release
	end

VermilionCity_EventScript_OldMan1SSAnneLeft::
	msgbox VermilionCity_Text_SSAnneHasDepartedForYear
	release
	end

VermilionCity_EventScript_FerrySailor::
	lock
	faceplayer
	call_if_set FLAG_SAILOR_THANKFUL, VermilionCity_EventScript_ThankPlayer
	checkitem ITEM_BERRY_PUNCH
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_BerryPunch
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, VermilionCity_EventScript_CheckSeagallopPresent
	msgbox VermilionCity_Text_WelcomeToTheSSAnne
	release
	end

VermilionCity_EventScript_ThankPlayer::
	msgbox VermilionCity_Text_ThankPlayer
	clearflag FLAG_SAILOR_THANKFUL
	return

VermilionCity_EventScript_BerryPunch::
	msgbox VermilionCity_Text_PunchForMe
	closemessage
	applymovement LOCALID_VERMILION_FERRY_SAILOR, VermilionCity_Movement_SailorMove
	waitmovement 0
	removeobject LOCALID_VERMILION_FERRY_SAILOR
	setflag FLAG_HIDE_FERRY_SAILOR
	setflag FLAG_SAILOR_THANKFUL
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 2
	removeitem ITEM_BERRY_PUNCH
	release
	end

VermilionCity_EventScript_ReturnSailor::
	lock
	applymovement LOCALID_VERMILION_FERRY_SAILOR, VermilionCity_Movement_SailorReturn
	waitmovement 0
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	release
	end

VermilionCity_EventScript_ReturnSailor2::
	lock
	applymovement LOCALID_VERMILION_FERRY_SAILOR, VermilionCity_Movement_SailorReturn2
	waitmovement 0
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	release
	end

VermilionCity_Text_PunchForMe::
	.string "Hm?\n"
	.string "BERRY SODA? For me?\p"
	.string "Ha! You're alright, kiddo!\n"
	.string "I'll be back in a few. Gonna share\l"
	.string "some of this with the lads!$"

VermilionCity_Text_ThankPlayer::
	.string "The boys loved the drinks!\n"
	.string "Thanks again, kiddo.\p"
	.string "Now then...$"

VermilionCity_Movement_SailorMove::
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VermilionCity_Movement_SailorReturn::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	face_up
	step_end

VermilionCity_Movement_SailorReturn2::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_right
	face_up
	step_end

VermilionCity_EventScript_CheckHasMysticTicket::
	goto_if_unset FLAG_ENABLE_SHIP_NAVEL_ROCK, EventScript_SetResultFalse
	checkitem ITEM_MYSTIC_TICKET
	goto_if_eq VAR_RESULT, FALSE, EventScript_SetResultFalse
	goto EventScript_SetResultTrue
	end

VermilionCity_EventScript_CheckHasAuroraTicket::
	goto_if_unset FLAG_ENABLE_SHIP_BIRTH_ISLAND, EventScript_SetResultFalse
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, EventScript_SetResultFalse
	goto EventScript_SetResultTrue
	end

VermilionCity_EventScript_CheckSeagallopPresent::
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, VermilionCity_EventScript_TicketCheck
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1, VermilionCity_EventScript_ChooseSeagallopDestTriPass
	msgbox VermilionCity_Text_TheShipSetSail
	release
	end

VermilionCity_EventScript_TicketCheck::
	clearflag FLAG_EVENTS_READY
	setvar VAR_NEW_TICKETS, 0
	setvar VAR_TICKET_SHOWN, 0
	call VermilionCity_EventScript_TicketCheck2
	call_if_gt VAR_NEW_TICKETS, 1, VermilionCity_EventScript_NewTicketsPlural
	call_if_eq VAR_NEW_TICKETS, 1, VermilionCity_EventScript_NewTicketsSingle
	goto_if_set FLAG_EVENTS_READY, VermilionCity_EventScript_EventIslandMulti
	goto VermilionCity_EventScript_ChooseSeagallopDestRainbowPass
	end

VermilionCity_EventScript_ChooseSeagallopDestRainbowPass::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	message VermilionCity_Text_BoardSeagallopRainbowPass
	waitmessage
	goto EventScript_SeviiDestinationsPage1
	end

VermilionCity_EventScript_TicketCheck2::
	checkitem ITEM_MYSTIC_TICKET
	call_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_TicketCheck_Mystic
	checkitem ITEM_AURORA_TICKET
	call_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_TicketCheck_Aurora
	checkitem ITEM_EON_TICKET
	call_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_TicketCheck_Eon
	checkitem ITEM_NEW_SEA_MAP
	call_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_TicketCheck_Faraway
	return

VermilionCity_EventScript_TicketCheck_Mystic::
	setflag FLAG_EVENTS_READY
	setvar VAR_0x8003, ITEM_MYSTIC_TICKET
	call_if_unset FLAG_SHOWN_MYSTIC_TICKET, VermilionCity_EventScript_TicketCheck_New
	setflag FLAG_SHOWN_MYSTIC_TICKET
	return

VermilionCity_EventScript_TicketCheck_Aurora::
	setflag FLAG_EVENTS_READY
	setvar VAR_0x8003, ITEM_AURORA_TICKET
	call_if_unset FLAG_SHOWN_AURORA_TICKET, VermilionCity_EventScript_TicketCheck_New
	setflag FLAG_SHOWN_AURORA_TICKET
	return

VermilionCity_EventScript_TicketCheck_Eon::
	setflag FLAG_EVENTS_READY
	setvar VAR_0x8003, ITEM_EON_TICKET
	call_if_unset FLAG_SHOWN_EON_TICKET, VermilionCity_EventScript_TicketCheck_New
	setflag FLAG_SHOWN_EON_TICKET
	return

VermilionCity_EventScript_TicketCheck_Faraway::
	setflag FLAG_EVENTS_READY
	return

VermilionCity_EventScript_TicketCheck_New::
	addvar VAR_NEW_TICKETS, 1
	copyvar VAR_TICKET_SHOWN, VAR_0x8003
	return

VermilionCity_EventScript_NewTicketsPlural::
	msgbox VermilionCity_Text_MultipleTickets
	return

VermilionCity_EventScript_NewTicketsSingle::
	call_if_eq VAR_TICKET_SHOWN, ITEM_AURORA_TICKET, VermilionCity_EventScript_ShowAuroraTicket
	call_if_eq VAR_TICKET_SHOWN, ITEM_MYSTIC_TICKET, VermilionCity_EventScript_ShowMysticTicket
	call_if_eq VAR_TICKET_SHOWN, ITEM_EON_TICKET, VermilionCity_EventScript_ShowEonTicket
	return

VermilionCity_EventScript_HasMysticTicket::
	call VermilionCity_EventScript_CheckHasAuroraTicket
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_HasMysticAndAuroraTickets
	call_if_unset FLAG_SHOWN_MYSTIC_TICKET, VermilionCity_EventScript_ShowMysticTicket
	goto VermilionCity_EventScript_EventIslandMulti
	multichoice 17, 6, MULTICHOICE_SEVII_NAVEL, FALSE
	switch VAR_RESULT
	case 0, EventScript_SeviiDestinationsPage1
	case 1, EventScript_SailToNavelRock
	case 2, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

VermilionCity_EventScript_EventIslandMulti::
	message VermilionCity_Text_BoardSeagallopFerry
	waitmessage
	special ScriptMenu_CreateEventIslandMultichoice
	waitstate
	special GetSeagallopSelection
	switch VAR_RESULT
	case 1, EventScript_SeviiDestinationsPage1
	case 2, EventScript_SailToNavelRock
	case 3, EventScript_SailToBirthIsland
	case 4, EventScript_SailToSouthernIsland
	case 5, EventScript_SailToFarawayIsland
	case 6, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

VermilionCity_EventScript_ShowMysticTicket::
	msgbox VermilionCity_Text_OhMysticTicketTakeYouToNavelRock
	return

VermilionCity_EventScript_HasAuroraTicket::
	call_if_unset FLAG_SHOWN_AURORA_TICKET, VermilionCity_EventScript_ShowAuroraTicket
	message VermilionCity_Text_BoardSeagallopFerry
	waitmessage
	goto VermilionCity_EventScript_EventIslandMulti
	multichoice 13, 6, MULTICHOICE_SEVII_BIRTH, FALSE
	switch VAR_RESULT
	case 0, EventScript_SeviiDestinationsPage1
	case 1, EventScript_SailToBirthIsland
	case 2, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

VermilionCity_EventScript_ShowAuroraTicket::
	msgbox VermilionCity_Text_OhAuroraTicketTakeYouToBirthIsland
	return
	
VermilionCity_EventScript_ShowEonTicket::
	msgbox VermilionCity_Text_OhEonTicketTakeYouToSouthernIsland
	return

VermilionCity_EventScript_HasMysticAndAuroraTickets::
	call_if_unset FLAG_SHOWN_MYSTIC_TICKET, VermilionCity_EventScript_ShowMysticTicket
	call_if_unset FLAG_SHOWN_AURORA_TICKET, VermilionCity_EventScript_ShowAuroraTicket
	message VermilionCity_Text_BoardSeagallopFerry
	waitmessage
	goto VermilionCity_EventScript_EventIslandMulti
	multichoice 13, 5, MULTICHOICE_SEVII_NAVEL_BIRTH, FALSE
	switch VAR_RESULT
	case 0, EventScript_SeviiDestinationsPage1
	case 1, EventScript_SailToNavelRock
	case 2, EventScript_SailToBirthIsland
	case 3, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

EventScript_SailToNavelRock::
	msgbox VermilionCity_Text_Seagallop10Departing
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	setvar VAR_0x8006, SEAGALLOP_NAVEL_ROCK
	goto EventScript_SetSail
	end

EventScript_SailToBirthIsland::
	msgbox VermilionCity_Text_Seagallop12Departing
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	setvar VAR_0x8006, SEAGALLOP_BIRTH_ISLAND
	goto EventScript_SetSail
	end

EventScript_SailToSouthernIsland::
	msgbox VermilionCity_Text_Seagallop15Departing
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	setvar VAR_0x8006, SEAGALLOP_SOUTHERN_ISLAND
	goto EventScript_SetSail
	end

EventScript_SailToFarawayIsland::
	call_if_unset FLAG_SHOWN_NEW_SEA_MAP, VermilionCity_EventScript_ShowNewSeaMap
	msgbox VermilionCity_Text_Seagallop20Departing
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	setvar VAR_0x8006, SEAGALLOP_FARAWAY_ISLAND
	goto EventScript_SetSail
	end

VermilionCity_EventScript_ShowNewSeaMap::
	setflag FLAG_SHOWN_NEW_SEA_MAP
	msgbox VermilionCity_Text_ShowNewSeaMap
	return

VermilionCity_EventScript_ChooseSeagallopDestTriPass::
	message VermilionCity_Text_BoardSeagallopTriPass
	waitmessage
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	multichoice 19, 5, MULTICHOICE_SEAGALLOP_123, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToOneIsland2
	case 1, EventScript_SailToTwoIsland2
	case 2, EventScript_SailToThreeIsland2
	case 3, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

@ Unreachable
Vermilion_EventScript_Unused::
	release
	end

VermilionCity_EventScript_CheckTicketLeft::
	lockall
	goto VermilionCity_EventScript_CheckTicket
	end

VermilionCity_EventScript_CheckTicketRight::
	lockall
	goto VermilionCity_EventScript_CheckTicket
	end

VermilionCity_EventScript_ExitedTicketCheck::
	lockall
	goto_if_eq VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 3, VermilionCity_EventScript_ReturnSailor
	goto_if_eq VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 2, VermilionCity_EventScript_ExitCancel
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	releaseall
	end

VermilionCity_EventScript_ExitCancel::
	releaseall
	end

VermilionCity_EventScript_CheckTicket::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_VERMILION_FERRY_SAILOR, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, VermilionCity_EventScript_CheckSeagallopPresentTrigger
	msgbox VermilionCity_Text_DoYouHaveATicket
	goto_if_unset FLAG_GOT_SS_TICKET, VermilionCity_EventScript_DontHaveSSTicket
	msgbox VermilionCity_Text_FlashedSSTicket
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 1
	releaseall
	end

VermilionCity_EventScript_DontHaveSSTicket::
	msgbox VermilionCity_Text_DontHaveNeededSSTicket
	closemessage
	goto VermilionCity_EventScript_WalkUpPier
	end

VermilionCity_EventScript_CheckSeagallopPresentTrigger::
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, VermilionCity_EventScript_TicketCheck
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1, VermilionCity_EventScript_ChooseSeagallopDestTriPass
	msgbox VermilionCity_Text_TheShipSetSail
	closemessage
	goto VermilionCity_EventScript_WalkUpPier
	end

VermilionCity_EventScript_Sailor::
	msgbox VermilionCity_Text_SSAnneVisitsOnceAYear, MSGBOX_NPC
	end

VermilionCity_EventScript_OaksAide::
	lock
	faceplayer
	setflag FLAG_TALKED_TO_OAKS_AIDE_IN_VERMILION
	msgbox VermilionCity_Text_Route2AideHasPackageForYou
	release
	end

VermilionCity_EventScript_OldMan2::
	msgbox VermilionCity_Text_BuildingOnThisLand, MSGBOX_NPC
	end

VermilionCity_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, CRY_MODE_NORMAL
	msgbox VermilionCity_Text_Machop
	waitmoncry
	msgbox VermilionCity_Text_MachopStompingLandFlat
	release
	end

VermilionCity_EventScript_CitySign::
	msgbox VermilionCity_Text_CitySign, MSGBOX_SIGN
	end

VermilionCity_EventScript_SnorlaxNotice::
	msgbox VermilionCity_Text_SnorlaxBlockingRoute12, MSGBOX_SIGN
	end

VermilionCity_EventScript_PokemonFanClubSign::
	msgbox VermilionCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

VermilionCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_LTSURGE, 0
	msgbox VermilionCity_Text_GymSign
	releaseall
	end

VermilionCity_EventScript_HarborSign::
	msgbox VermilionCity_Text_VermilionHarbor, MSGBOX_SIGN
	end
