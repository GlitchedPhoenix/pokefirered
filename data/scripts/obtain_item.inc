.set ITEMID, VAR_0x8000
.set AMOUNT, VAR_0x8001
@ Unused, handled by textcolor script cmd
EventScript_SaveTextColor::
	copyvar VAR_PREV_TEXT_COLOR, VAR_TEXT_COLOR
	return

EventScript_RestorePrevTextColor::
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return

Std_ObtainItem::
	copyvar VAR_0x8004, ITEMID
	copyvar VAR_0x8005, AMOUNT
	copyvar VAR_PREV_TEXT_COLOR, VAR_TEXT_COLOR
	textcolor NPC_TEXT_COLOR_NEUTRAL
	additem VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	call_if_eq VAR_0x8007, FALSE, EventScript_TryAddItemToPCObtain
	call EventScript_ObtainItemMessage
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return

EventScript_TryAddItemToPCObtain::
	checkitemtype VAR_0x8004 @ Don't add if it's a key item
	goto_if_eq VAR_RESULT, POCKET_KEY_ITEMS, EventScript_TryAddItemToPCObtainContinue
	addpcitem VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, EventScript_TryAddItemToPCObtainContinue
	setvar VAR_0x8007, 2  @ (0= full, 1= in pocket, 2=in PC) 
	return

EventScript_TryAddItemToPCObtainContinue::
	return

EventScript_ObtainItemMessage::
	bufferitemnameplural STR_VAR_2, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call EventScript_BufferPocketNameTryFanfare
	call_if_ne VAR_0x8007, FALSE, EventScript_ObtainedItem
	call_if_eq VAR_0x8007, FALSE, EventScript_NoRoomForItem
	return

EventScript_BufferPocketNameTryFanfare::
	switch VAR_RESULT
	case POCKET_ITEMS, EventScript_BufferItemsPocket
	case POCKET_KEY_ITEMS, EventScript_BufferKeyItemsPocket
	case POCKET_POKE_BALLS, EventScript_BufferPokeBallsPocket
	case POCKET_TM_CASE, EventScript_BufferTMCase
	case POCKET_BERRY_POUCH, EventScript_BufferBerryPouch
	end

EventScript_BufferItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS_POCKET
	call_if_ne VAR_0x8007, FALSE, EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferKeyItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_KEY_ITEMS_POCKET
	call_if_ne VAR_0x8007, FALSE, EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferPokeBallsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_POKEBALLS_POCKET
	call_if_ne VAR_0x8007, FALSE, EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferTMCase::
	bufferstdstring STR_VAR_3, STDSTRING_TM_CASE
	call_if_ne VAR_0x8007, FALSE, EventScript_PlayFanfareObtainedTMHM
	return

EventScript_BufferBerryPouch::
	bufferstdstring STR_VAR_3, STDSTRING_BERRY_POUCH
	call_if_ne VAR_0x8007, FALSE, EventScript_PlayFanfareObtainedItem
	return

EventScript_ObtainedItem::
	message Text_ObtainedTheX
	waitfanfare
	waitmessage
	call EventScript_PutItemMsg
	setvar VAR_RESULT, 1
	return

EventScript_NoRoomForItem::
	setvar VAR_RESULT, FALSE
	return

EventScript_PlayFanfareObtainedItem::
	playfanfare MUS_LEVEL_UP
	return

EventScript_PlayFanfareObtainedTMHM::
	playfanfare MUS_LEVEL_UP
	return

Std_ObtainDecoration::
	adddecoration VAR_0x8000
	copyvar VAR_0x8007, VAR_RESULT
	call EventScript_ObtainDecorMessage
	return

EventScript_ObtainDecorMessage::
	bufferdecorationname STR_VAR_2, VAR_0x8000
	call_if_eq VAR_0x8007, TRUE, EventScript_ObtainedDecor
	call_if_eq VAR_0x8007, FALSE, EventScript_NoRoomForDecor
	return

EventScript_ObtainedDecor::
	playfanfare MUS_OBTAIN_ITEM
	message Text_ObtainedTheDecor
	waitfanfare
	waitmessage
	msgbox Text_DecorTransferredToPC
	setvar VAR_RESULT, TRUE
	return

EventScript_NoRoomForDecor::
	setvar VAR_RESULT, FALSE
	return

Std_FindItem::
	lock
	faceplayer
	waitse
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_0x8005, VAR_0x8001
	checkitemspace VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	call_if_eq VAR_0x8007, FALSE, EventScript_CheckPCSpace
	bufferitemname STR_VAR_2, VAR_0x8000
	checkitemtype VAR_0x8000																																																									
	call EventScript_BufferPocketNameTryFanfare
	call_if_ne VAR_0x8007, FALSE, EventScript_PickUpItem
	call_if_eq VAR_0x8007, FALSE, EventScript_NoRoomToPickUpItem
	release
	return

EventScript_CheckPCSpace::
	checkitemtype VAR_0x8004 @ Don't add if it's a key item
	goto_if_eq VAR_RESULT, POCKET_KEY_ITEMS, EventScript_CheckPCSpaceContinue
	checkpcspace VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, EventScript_CheckPCSpaceContinue
	setvar VAR_0x8007, 2  @ (0= full, 1= in pocket, 2=in PC)
	return
	
EventScript_CheckPCSpaceContinue::
	return

EventScript_PickUpItem::
	removeobject VAR_LAST_TALKED
	goto_if_eq VAR_0x8007, 2, EventScript_PickUpItemPCAdd
	additem VAR_0x8004, VAR_0x8005
	goto EventScript_PickUpItemContinueAdd
EventScript_PickUpItemPCAdd::
	addpcitem VAR_0x8004, VAR_0x8005
EventScript_PickUpItemContinueAdd::
	specialvar VAR_RESULT, BufferTMHMMoveName
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, TRUE, EventScript_FoundTMHM
	call_if_eq VAR_0x8008, FALSE, EventScript_FoundItem
	waitfanfare
	waitmessage
	call EventScript_PutItemMsg
	return

EventScript_TryAddItemToPCHidden::
	checkitemtype VAR_0x8005 @ Don't add if it's a key item
	goto_if_eq VAR_RESULT, POCKET_KEY_ITEMS, EventScript_TryAddHiddenItemToPCContinue
	addpcitem VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, EventScript_TryAddHiddenItemToPCContinue
	setvar VAR_0x8007, 2  @ (0= full, 1= in pocket, 2=in PC) 
EventScript_TryAddHiddenItemToPCContinue::
	return

EventScript_FoundTMHM::
	message Text_FoundTMHMContainsMove
	return

EventScript_FoundItem::
	message Text_FoundOneItem
	return

EventScript_NoRoomToPickUpItem::
	msgbox Text_ObtainedTheX
	msgbox Text_TooBadBagFull
	setvar VAR_RESULT, FALSE
	return

EventScript_HiddenItemScript::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	waitse
	goto_if_eq VAR_0x8005, 0, EventScript_TryPickUpHiddenCoins
	call EventScript_TryPickUpHiddenItem
	goto_if_eq VAR_0x8007, TRUE, EventScript_PickedUpHiddenItem
	goto_if_eq VAR_0x8007, FALSE, EventScript_NoRoomForHiddenItem
	end

EventScript_TryPickUpHiddenItem::
	additem VAR_0x8005, VAR_0x8006
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemname STR_VAR_2, VAR_0x8005
	checkitemtype VAR_0x8005
	call EventScript_BufferPocketNameTryFanfare
	return

EventScript_PickedUpHiddenItem::
	call_if_eq VAR_0x8006, 1, EventScript_FoundSingleItem
	call_if_ne VAR_0x8006, 1, EventScript_FoundMultipleItems
	waitfanfare
	waitmessage
	call EventScript_PutItemMsg
	special SetHiddenItemFlag
	releaseall
	end

EventScript_PutItemMsg::
	goto_if_eq VAR_0x8007, 2, EventScript_PutItemPCMsg
	msgbox Text_PutItemAway, MSGBOX_DEFAULT
	goto EventScript_PutItemContinueMsg
EventScript_PutItemPCMsg::
	msgbox gText_PutItemInPC, MSGBOX_DEFAULT
EventScript_PutItemContinueMsg::
	return

EventScript_FoundSingleItem::
	message Text_FoundOneItem
	return

EventScript_FoundCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXCoins
	return

EventScript_FoundMultipleItems::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXItems
	return

EventScript_NoRoomForHiddenItem::
	msgbox Text_FoundOneItem
	msgbox gText_TooBadBagAndPCAreFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	releaseall
	end

gText_PutItemInPC::
	.string "{PLAYER} sent the {STR_VAR_2}\n"
	.string "to the PC.$"

gText_TooBadBagAndPCAreFull::
	.string "Too bad!\n"
	.string "The BAG and PC are full…$"

EventScript_TryPickUpHiddenCoins::
	goto_if_unset FLAG_GOT_COIN_CASE, EventScript_NoCaseForHiddenCoins
	checkcoins VAR_RESULT
	specialvar VAR_RESULT, CheckAddCoins
	goto_if_eq VAR_RESULT, FALSE, EventScript_HiddenCoinsButCaseIsFull
	addcoins VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	call EventScript_PlayFanfareObtainedItem
	call EventScript_FoundCoins
	waitfanfare
	waitmessage
	msgbox Text_PutCoinsAwayInCoinCase
	special SetHiddenItemFlag
	releaseall
	end

EventScript_HiddenCoinsButCaseIsFull::
	buffernumberstring STR_VAR_1, VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	msgbox Text_FoundXCoins
	msgbox Text_CoinCaseIsFull
	setvar VAR_RESULT, 0
	releaseall
	end

EventScript_NoCaseForHiddenCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	msgbox Text_FoundXCoins
	msgbox Text_NothingToPutThemIn
	setvar VAR_RESULT, 0
	releaseall
	end
