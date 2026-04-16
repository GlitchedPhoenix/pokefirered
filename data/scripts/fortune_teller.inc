FortuneTeller_Script_Main::
	lock
	faceplayer
	specialvar VAR_TEMP_3, GetFortuneTellerMap
	call FortuneTeller_Script_CheckFortuneExplanation
	call_if_unset FLAG_FORTUNE_INTRO, FortuneTeller_Script_Intro
	goto FortuneTeller_Script_MailCheck
	end

FortuneTeller_Script_Main2::
#ifdef LEAFGREEN
	call_if_unset FLAG_UNLOCKED_IVY_BAND, FortuneTeller_Script_CheckAllMail
#else
	call_if_unset FLAG_UNLOCKED_FLAME_BROOCH, FortuneTeller_Script_CheckAllMail
#endif
	goto_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_NoUnlocks
	goto FortuneTeller_Script_DoMenu
	end

FortuneTeller_Script_CheckFortuneExplanation::
	goto_if_eq VAR_TEMP_3, 2, FortuneTeller_Script_TwoIsland
	goto_if_eq VAR_TEMP_3, 17, FortuneTeller_Script_Fuchsia
	goto_if_eq VAR_TEMP_3, 5, FortuneTeller_Script_Convenience
	return

FortuneTeller_Script_TwoIsland::
	call_if_ge VAR_FORTUNE_TELLER_STATE, 3, FortuneTeller_Script_GoodDay
	call_if_lt VAR_FORTUNE_TELLER_STATE, 3, FortuneTeller_Script_TwoIslandComment
	return

FortuneTeller_Script_GoodDay::
	msgbox FortuneTeller_Text_GoodDay
	return

FortuneTeller_Script_TwoIslandComment::
	msgbox FortuneTeller_Text_TwoIsland
	setvar VAR_FORTUNE_TELLER_STATE, 3
	return

FortuneTeller_Script_Fuchsia::
	call_if_ge VAR_FORTUNE_TELLER_STATE, 2, FortuneTeller_Script_GoodDay
	call_if_lt VAR_FORTUNE_TELLER_STATE, 2, FortuneTeller_Script_FuchsiaComment
	return


FortuneTeller_Script_MailHintInFortree::
	msgbox FortuneTeller_Text_MailHint
	return

FortuneTeller_Script_MailHintElsewhere::
	msgbox FortuneTeller_Text_MailHint2
	return

FortuneTeller_Script_FuchsiaComment::
	msgbox FortuneTeller_Text_Fuchsia
	setvar VAR_FORTUNE_TELLER_STATE, 2
	return

FortuneTeller_Script_Convenience::
	call_if_ge VAR_FORTUNE_TELLER_STATE, 4, FortuneTeller_Script_GoodDay
	call_if_lt VAR_FORTUNE_TELLER_STATE, 4, FortuneTeller_Script_FortuneTellingIntro
	return

FortuneTeller_Script_FortuneTellingIntro::
	msgbox FortuneTeller_Text_FortuneTelling
	setvar VAR_FORTUNE_TELLER_STATE, 4
	return

FortuneTeller_Script_NoUnlocks::
	goto_if_lt VAR_FORTUNE_TELLER_STATE, 4, FortuneTeller_Script_NoMail
	goto_if_ge VAR_FORTUNE_TELLER_STATE, 4, FortuneTeller_Script_FortuneTellingOnly
	end
	
FortuneTeller_Script_NoMail::
	msgbox FortuneTeller_Text_AnyMail
	msgbox FortuneTeller_Text_NoMail
	release
	end

FortuneTeller_Script_MailCheck::
	setvar VAR_TEMP_2, 0
	specialvar VAR_RESULT, GetFirstHeldItem
	copyvar VAR_0x8007, VAR_RESULT
	switch VAR_RESULT
	case ITEM_RUBY_MAIL, FortuneTeller_RubyMail
	case ITEM_SAPPHIRE_MAIL, FortuneTeller_SapphireMail
	case ITEM_EMERALD_MAIL, FortuneTeller_EmeraldMail
	case ITEM_RED_MAIL, FortuneTeller_FireMail
	case ITEM_GREEN_MAIL, FortuneTeller_LeafMail
	case ITEM_BLUE_MAIL, FortuneTeller_RainMail
	goto FortuneTeller_Script_Main2
	end

FortuneTeller_Script_CheckAllMail::
#ifdef LEAFGREEN
	goto_if_unset FLAG_UNLOCKED_FLAME_BROOCH, EventScript_Return
	goto_if_unset FLAG_UNLOCKED_TEMPEST_PIN, EventScript_Return
#else
	goto_if_unset FLAG_UNLOCKED_TEMPEST_PIN, EventScript_Return
	goto_if_unset FLAG_UNLOCKED_IVY_BAND, EventScript_Return
#endif
	goto_if_unset FLAG_UNLOCKED_MAGMA_BRACER, EventScript_Return
	goto_if_unset FLAG_UNLOCKED_AQUA_NECKLACE, EventScript_Return
	msgbox FortuneTeller_Text_AllMail
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
#ifdef LEAFGREEN
	setvar VAR_0x8007, ITEM_IVY_BAND
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveLeafArtifact
	msgbox FortuneTeller_Text_IvyBand
	setflag FLAG_UNLOCKED_IVY_BAND
#else
	setvar VAR_0x8007, ITEM_FLAME_BROOCH
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveFireArtifact
	msgbox FortuneTeller_Text_FlameBrooch
	setflag FLAG_UNLOCKED_FLAME_BROOCH
#endif
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	return

FortuneTeller_Script_DoMenu::
	msgbox FortuneTeller_Text_WhatCanIDo
	goto_if_ge VAR_FORTUNE_TELLER_STATE, 4, FortuneTeller_Script_ArtifactAndFortuneMenu
	goto_if_lt VAR_FORTUNE_TELLER_STATE, 4, FortuneTeller_Script_ArtifactMenu

FortuneTeller_Script_ArtifactAndFortuneMenu::
	multichoice 0, 0, MULTI_ARTIFACTS_AND_FORTUNES, FALSE
	switch VAR_RESULT
	case 0, FortuneTeller_Script_ObtainArtifacts
	case 1, FortuneTeller_Script_ExplainArtifacts
	case 2, FortuneTeller_Script_ReturnArtifacts
	case 3, FortuneTeller_Script_FortuneTelling
	case 4, FortuneTeller_Script_Cancel
	case SCR_MENU_CANCEL, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_Script_ArtifactMenu::
	multichoice 0, 0, MULTI_ARTIFACTS_ONLY, FALSE
	switch VAR_RESULT
	case 0, FortuneTeller_Script_ObtainArtifacts
	case 1, FortuneTeller_Script_ExplainArtifacts
	case 2, FortuneTeller_Script_ReturnArtifacts
	case 3, FortuneTeller_Script_Cancel
	case SCR_MENU_CANCEL, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_Script_ReturnArtifacts::
	removeitem ITEM_MAGMA_BRACER, 1
	removeitem ITEM_AQUA_NECKLACE, 1
	removeitem ITEM_TEMPEST_PIN, 1
	removeitem ITEM_FLAME_BROOCH, 1
	removeitem ITEM_IVY_BAND, 1
	removeitem ITEM_OCEAN_ANKLET, 1
	clearflag FLAG_MAGMA_BRACER_ACTIVE
	clearflag FLAG_AQUA_NECKLACE_ACTIVE
	clearflag FLAG_TEMPEST_PIN_ACTIVE
	clearflag FLAG_FLAME_BROOCH_ACTIVE
	clearflag FLAG_IVY_BAND_ACTIVE
	clearflag FLAG_OCEAN_ANKLET_ACTIVE
	setvar VAR_ARTIFACTS_OBTAINED, 0
	msgbox FortuneTeller_Text_ThankYouReturn
	multichoicedefault 20, 8, MULTICHOICE_YES_NO, 0, FALSE
	switch VAR_RESULT
	case 0, FortuneTeller_Script_ObtainArtifacts
	case 1, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_Script_ObtainArtifacts::
	msgbox FortuneTeller_Text_WhichWouldYouLike
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	goto_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom2
	special ScriptMenu_CreateArtifactMultichoice
	waitstate
	special GetArtifactSelection
	switch VAR_RESULT
	case 0, FortuneTeller_Script_PickRuby
	case 1, FortuneTeller_Script_PickSapphire
	case 2, FortuneTeller_Script_PickEmerald
	case 3, FortuneTeller_Script_PickFire
	case 4, FortuneTeller_Script_PickLeaf
	case 5, FortuneTeller_Script_PickRain
	case SCR_MENU_CANCEL, FortuneTeller_Script_Cancel
	end

FortuneTeller_Script_AnotherOne::
	msgbox FortuneTeller_Text_AnotherOne
	multichoicedefault 20, 8, MULTICHOICE_YES_NO, 0, FALSE
	switch VAR_RESULT
	case 0, FortuneTeller_Script_ObtainArtifacts
	case 1, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_Script_AlreadyHave::
	msgbox FortuneTeller_Text_YouHaveThis
	release
	end

FortuneTeller_Script_PickRuby::
	goto_if_set FLAG_MAGMA_BRACER_ACTIVE, FortuneTeller_Script_AlreadyHave
	setvar VAR_0x8007, ITEM_MAGMA_BRACER
	setflag FLAG_MAGMA_BRACER_ACTIVE
	call FortuneTeller_Script_GiveArtifact
	call FortuneTeller_Script_TakeGoodCareOfIt
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	goto_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_AnotherOne
	release
	end

FortuneTeller_Script_PickSapphire::
	goto_if_set FLAG_AQUA_NECKLACE_ACTIVE, FortuneTeller_Script_AlreadyHave
	setvar VAR_0x8007, ITEM_AQUA_NECKLACE
	setflag FLAG_AQUA_NECKLACE_ACTIVE
	call FortuneTeller_Script_GiveArtifact
	call FortuneTeller_Script_TakeGoodCareOfIt
	goto_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_AnotherOne
	release
	end

FortuneTeller_Script_PickEmerald::
	goto_if_set FLAG_TEMPEST_PIN_ACTIVE, FortuneTeller_Script_AlreadyHave
	setvar VAR_0x8007, ITEM_TEMPEST_PIN
	setflag FLAG_TEMPEST_PIN_ACTIVE
	call FortuneTeller_Script_GiveArtifact
	call FortuneTeller_Script_TakeGoodCareOfIt
	goto_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_AnotherOne
	release
	end

FortuneTeller_Script_PickFire::
	goto_if_set FLAG_FLAME_BROOCH_ACTIVE, FortuneTeller_Script_AlreadyHave
	setvar VAR_0x8007, ITEM_FLAME_BROOCH
	setflag FLAG_FLAME_BROOCH_ACTIVE
	call FortuneTeller_Script_GiveArtifact
	call FortuneTeller_Script_TakeGoodCareOfIt
	goto_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_AnotherOne
	release
	end

FortuneTeller_Script_PickLeaf::
	goto_if_set FLAG_IVY_BAND_ACTIVE, FortuneTeller_Script_AlreadyHave
	setvar VAR_0x8007, ITEM_IVY_BAND
	setflag FLAG_IVY_BAND_ACTIVE
	call FortuneTeller_Script_GiveArtifact
	call FortuneTeller_Script_TakeGoodCareOfIt
	goto_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_AnotherOne
	release
	end

FortuneTeller_Script_PickRain::
	goto_if_set FLAG_OCEAN_ANKLET_ACTIVE, FortuneTeller_Script_AlreadyHave
	setvar VAR_0x8007, ITEM_OCEAN_ANKLET
	setflag FLAG_OCEAN_ANKLET_ACTIVE
	call FortuneTeller_Script_GiveArtifact
	call FortuneTeller_Script_TakeGoodCareOfIt
	goto_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_AnotherOne
	release
	end

FortuneTeller_Script_ExplainArtifacts::
	special ScriptMenu_CreateArtifactMultichoice
	waitstate
	special GetArtifactSelection
	switch VAR_RESULT
	case 0, FortuneTeller_Script_ExplainRuby
	case 1, FortuneTeller_Script_ExplainSapphire
	case 2, FortuneTeller_Script_ExplainEmerald
	case 3, FortuneTeller_Script_ExplainFire
	case 4, FortuneTeller_Script_ExplainLeaf
	case 5, FortuneTeller_Script_ExplainRain
	case SCR_MENU_CANCEL, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_Script_ExplainRuby::
	msgbox FortuneTeller_Text_MagmaBracer
	goto FortuneTeller_Script_HearMore
	end

FortuneTeller_Script_ExplainSapphire::
	msgbox FortuneTeller_Text_AquaNecklace
	goto FortuneTeller_Script_HearMore
	end

FortuneTeller_Script_ExplainEmerald::
	msgbox FortuneTeller_Text_TempestPin
	goto FortuneTeller_Script_HearMore
	end

FortuneTeller_Script_ExplainFire::
	msgbox FortuneTeller_Text_FlameBrooch
	goto FortuneTeller_Script_HearMore
	end

FortuneTeller_Script_ExplainLeaf::
	msgbox FortuneTeller_Text_IvyBand
	goto FortuneTeller_Script_HearMore
	end

FortuneTeller_Script_ExplainRain::
	msgbox FortuneTeller_Text_OceanAnklet
	goto FortuneTeller_Script_HearMore
	end

FortuneTeller_Script_HearMore::
	msgbox FortuneTeller_Text_HearMore
	multichoicedefault 20, 8, MULTICHOICE_YES_NO, 0, FALSE
	switch VAR_RESULT
	case 0, FortuneTeller_Script_ExplainArtifacts
	case 1, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_Script_Cancel::
	msgbox FortuneTeller_Text_NoMail
	release
	end

FortuneTeller_RubyMail::
	goto_if_unset FLAG_UNLOCKED_MAGMA_BRACER, FortuneTeller_RubyMail_Unlock
	goto FortuneTeller_Script_Main2

FortuneTeller_SapphireMail::
	goto_if_unset FLAG_UNLOCKED_AQUA_NECKLACE, FortuneTeller_SapphireMail_Unlock
	goto FortuneTeller_Script_Main2

FortuneTeller_EmeraldMail::
	goto_if_unset FLAG_UNLOCKED_TEMPEST_PIN, FortuneTeller_EmeraldMail_Unlock
	goto FortuneTeller_Script_Main2

FortuneTeller_FireMail::
#ifdef LEAFGREEN
	goto_if_unset FLAG_UNLOCKED_FLAME_BROOCH, FortuneTeller_FireMail_Unlock
#else
	goto_if_unset FLAG_UNLOCKED_FLAME_BROOCH, FortuneTeller_SameVersion
#endif
	goto FortuneTeller_Script_Main2

FortuneTeller_LeafMail::
#ifdef LEAFGREEN
	goto_if_unset FLAG_UNLOCKED_IVY_BAND, FortuneTeller_SameVersion
#else
	goto_if_unset FLAG_UNLOCKED_IVY_BAND, FortuneTeller_LeafMail_Unlock
#endif
	goto FortuneTeller_Script_Main2

FortuneTeller_RainMail::
	goto_if_unset FLAG_UNLOCKED_OCEAN_ANKLET, FortuneTeller_RainMail_Unlock
	goto FortuneTeller_Script_Main2

FortuneTeller_Script_TradeIn::
	msgbox FortuneTeller_Text_TradeIn
	return

FortuneTeller_RubyMail_Unlock::
	call_if_set FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_RepeatUnlock
	call_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_FirstUnlock
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	setvar VAR_0x8007, ITEM_MAGMA_BRACER
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveRubyArtifact
	msgbox FortuneTeller_Text_MagmaBracer
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	setflag FLAG_UNLOCKED_MAGMA_BRACER
	release
	end

FortuneTeller_SapphireMail_Unlock::
	call_if_set FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_RepeatUnlock
	call_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_FirstUnlock
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	setvar VAR_0x8007, ITEM_AQUA_NECKLACE
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveSapphireArtifact
	msgbox FortuneTeller_Text_AquaNecklace
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	setflag FLAG_UNLOCKED_AQUA_NECKLACE
	release
	end

FortuneTeller_EmeraldMail_Unlock::
	call_if_set FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_RepeatUnlock
	call_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_FirstUnlock
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	setvar VAR_0x8007, ITEM_TEMPEST_PIN
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveEmeraldArtifact
	msgbox FortuneTeller_Text_TempestPin
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	setflag FLAG_UNLOCKED_TEMPEST_PIN
	release
	end

FortuneTeller_FireMail_Unlock::
	call_if_set FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_RepeatUnlock
	call_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_FirstUnlock
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	setvar VAR_0x8007, ITEM_FLAME_BROOCH
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveFireArtifact
	msgbox FortuneTeller_Text_FlameBrooch
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	setflag FLAG_UNLOCKED_FLAME_BROOCH
	release
	end

FortuneTeller_LeafMail_Unlock::
	call_if_set FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_RepeatUnlock
	call_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_FirstUnlock
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	setvar VAR_0x8007, ITEM_IVY_BAND
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveLeafArtifact
	msgbox FortuneTeller_Text_IvyBand
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	setflag FLAG_UNLOCKED_IVY_BAND
	release
	end

FortuneTeller_RainMail_Unlock::
	call_if_set FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_RepeatUnlock
	call_if_unset FLAG_FORTUNE_SHOWN_MAIL, FortuneTeller_Script_FirstUnlock
	copyvar VAR_0x8008, VAR_ARTIFACT_CAP
	setvar VAR_0x8007, ITEM_OCEAN_ANKLET
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_NoRoom
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_GiveRainArtifact
	msgbox FortuneTeller_Text_OceanAnklet
	call_if_ge VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TradeIn
	call_if_lt VAR_ARTIFACTS_OBTAINED, VAR_0x8008, FortuneTeller_Script_TakeGoodCareOfIt
	setflag FLAG_UNLOCKED_OCEAN_ANKLET
	release
	end

FortuneTeller_SameVersion::
	msgbox FortuneTeller_Text_SameVersion
	release
	end

FortuneTeller_Script_NoRoom::
	msgbox FortuneTeller_Text_NoRoom
	msgbox FortuneTeller_Text_HoldOntoIt
	return

FortuneTeller_Script_NoRoom2::
	msgbox FortuneTeller_Text_NoRoom
	release
	end

FortuneTeller_Script_GiveArtifact::
	giveitem VAR_0x8007, 1
	return

FortuneTeller_Script_GiveRubyArtifact::
	giveitem VAR_0x8007, 1
	setflag FLAG_MAGMA_BRACER_ACTIVE
	return

FortuneTeller_Script_GiveSapphireArtifact::
	giveitem VAR_0x8007, 1
	setflag FLAG_AQUA_NECKLACE_ACTIVE
	return

FortuneTeller_Script_GiveEmeraldArtifact::
	giveitem VAR_0x8007, 1
	setflag FLAG_TEMPEST_PIN_ACTIVE
	return

FortuneTeller_Script_GiveFireArtifact::
	giveitem VAR_0x8007, 1
	setflag FLAG_FLAME_BROOCH_ACTIVE
	return

FortuneTeller_Script_GiveLeafArtifact::
	giveitem VAR_0x8007, 1
	setflag FLAG_IVY_BAND_ACTIVE
	return

FortuneTeller_Script_GiveRainArtifact::
	giveitem VAR_0x8007, 1
	setflag FLAG_OCEAN_ANKLET_ACTIVE
	return

FortuneTeller_Script_TakeGoodCareOfIt::
	msgbox FortuneTeller_Text_TakeGoodCareOfIt
	addvar VAR_ARTIFACTS_OBTAINED, 1
	return

FortuneTeller_Script_FirstUnlock::
	msgbox FortuneTeller_Text_FirstUnlock
	closemessage
	applymovement VAR_TEMP_3, Common_Movement_FaceAwayPlayer
	waitmovement 0
	delay 48
	msgbox FortuneTeller_Text_Boyfriend
	closemessage
	delay 48
	applymovement VAR_TEMP_3, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortuneTeller_Text_Sorry
	setflag FLAG_FORTUNE_SHOWN_MAIL
	closemessage
	return

FortuneTeller_Script_RepeatUnlock::
	msgbox FortuneTeller_Text_RepeatUnlock
	closemessage
	return

FortuneTeller_Script_Intro::
	msgbox FortuneTeller_Text_Intro
	setflag FLAG_FORTUNE_INTRO
	return

FortuneTeller_Script_FortuneTellingOnly::
	msgbox FortuneTeller_Text_HereToGetFortuneTold
	multichoicedefault 20, 8, MULTICHOICE_YES_NO, 0, FALSE
	switch VAR_RESULT
	case 0, FortuneTeller_Script_FortuneTelling
	case 1, FortuneTeller_Script_Cancel
	release
	end

FortuneTeller_BuyMail::
	lock
	faceplayer
	msgbox FortuneTeller_Text_DusclopsMail, MSGBOX_YESNO
	switch VAR_RESULT
	case 1, FortuneTeller_BoughtMail
	release
	end

FortuneTeller_BoughtMail::
	checkmoney 500
	goto_if_eq VAR_RESULT, 0, FortuneTeller_Poor
	playse SE_SHOP
	removemoney 500
	msgbox FortuneTeller_Text_DusclopsHandsMail
	#ifdef LEAFGREEN
	giveitem ITEM_GREEN_MAIL, 1
	#else
	giveitem ITEM_RED_MAIL, 1
	#endif
	release
	end

FortuneTeller_Poor::
	msgbox FortuneTeller_Text_DusclopsDisappointed
	release
	end

FortuneTeller_Script_FortuneTelling::
	msgbox FortuneTeller_Text_Placeholder
	release
	end


FortuneTeller_Text_DusclopsMail:
#ifdef LEAFGREEN
	.string "The WIGGLYTUFF is holding a green\n"
#else
	.string "The WIGGLYTUFF is holding an orange\n"
#endif
	.string "envelope.\p"
	.string "It looks at you with pleading eyes.\p"
	.string "Put ¥500 in its hand?$"

FortuneTeller_Text_DusclopsDisappointed:
	.string "The WIGGLYTUFF looks at you\n"
	.string "disappointedly...$"

FortuneTeller_Text_DusclopsHandsMail:
	.string "The WIGGLYTUFF happily takes the\n"
	.string "money.\p"
	.string "It hands you a colorful envelope.$"

FortuneTeller_Text_SameVersion:
	.string "Er...\p"
	.string "Not to be rude, but this is just\n"
	.string "the MAIL I gave you, is it not?$"

FortuneTeller_Text_AllMail:
	.string "Say...\p"
	.string "You've put in a lot of work to show\n"
	.string "me a peek of many different worlds,\l"
	.string "have you not?\p"
	.string "Here. I would like you to have\n"
	.string "this.$"

FortuneTeller_Text_HereToGetFortuneTold:
	.string "Are you here to get your fortune\n"
	.string "told?$"

FortuneTeller_Text_Placeholder:
	.string "bepis$"

FortuneTeller_Text_YouHaveThis:
	.string "But don't you already have it?$"

FortuneTeller_Text_ThankYouReturn:
	.string "Thank you.\p"
	.string "Would you like to take any others?$"

FortuneTeller_Text_TwoIsland:
	.string "What a quaint little island...\p"
	.string "Wouldn't you agree?$"

FortuneTeller_Text_Fuchsia:
	.string "What a unique city...\n"
	.string "Quite different from the locales of\n"
	.string "HOENN..."

FortuneTeller_Text_FortuneTelling:
	.string "Oh, good day.\p"
	.string "I believe I will take shelter here\n"
	.string "for the future.\p"
	.string "While I am here, I have a new\n"
	.string "service to provide.\p"
	.string "In exchange for a BIG MUSHROOM, I\n"
	.string "will read your fortune, and\l"
	.string "guide your steps forward.\p"
	.string "Please utilize it at your\n"
	.string "convenience.$"

FortuneTeller_Text_MagmaBracer:
	.string "Rubies represent passion, power,\n"
	.string "and protection.\p"
	.string "If you don the MAGMA CUFF, POKéMON\n"
	.string "you encounter will be drawn to\l"
	.string "your strength and will, and thus\l"
	.string "submit to being caught easier.\p"
	.string "Your allies will also be emboldened,\n"
	.string "and grow faster as a result.$"

FortuneTeller_Text_AquaNecklace:
	.string "Sapphires represent fortune,\n"
	.string "fidelity, and nobility.\p"
	.string "If you hang the AQUA NECKLACE\n"
	.string "from your neck, you will find your\l"
	.string "pockets fuller and your companions\l"
	.string "growing closer to you.$"

FortuneTeller_Text_TempestPin:
	.string "Emeralds represent love, fertility,\n"
	.string "rebirth, wealth, and the banishment\l"
	.string "of illusions.\p"
	.string "If you clip the TEMPEST PIN on,\n"
	.string "POKéMON that shine will be drawn\l"
	.string "close, and you will find yourself\l"
	.string "blessed with EGGs more often.$"

FortuneTeller_Text_FlameBrooch:
	.string "Fire agate represents creativity,\n"
	.string "strength, and healing.\p"
	.string "If you pin the FLAME BROOCH on\n"
	.string "your chest, POKéMON that seldom\l"
	.string "show themselves will begin to\l"
	.string "appear more often, and certain\l"
	.string "ailments will mend in resting.$"

FortuneTeller_Text_IvyBand:
	.string "Peridot represents growth,\n"
	.string "temperance, and protection against\l"
	.string "evil spirits.\p"
	.string "If you bear the IVY BAND on your\n"
	.string "finger, you will be blessed with\l"
	.string "high potential POKéMON that lead\l"
	.string "the pack in battle.\p"
	.string "Though their rarity will also\n"
	.string "make for emptier fields.$"

FortuneTeller_Text_OceanAnklet:
	.string "Turquoise represents wisdom,\n"
	.string "hope, and prosperity.\p"
	.string "If you bear the OCEAN ANKLET, you\n"
	.string "will be blessed with luck in\l"
	.string "commerce, and all other ARTIFACTs\l"
	.string "will be bolstered.$"

FortuneTeller_Text_NoRoom:
	.string "Oh, my apologies.\n"
	.string "You're already holding too many\l"
	.string "ARTIFACTs.$"

FortuneTeller_Text_HoldOntoIt:
	.string "Well, I will hold onto it until\n"
	.string "you're ready, then.$"

FortuneTeller_Text_TakeGoodCareOfIt:
	.string "Please take good care of it.$"

FortuneTeller_Text_TradeIn:
	.string "Once you're ready, trade the\n"
	.string "ARTIFACTs you have back to me and\l"
	.string "you can take it.$"

FortuneTeller_Text_FirstUnlock:
	.string "Oh?\p"
	.string "That MAIL your POKéMON is holding...\n"
	.string "May I see it?\p"
	.string "...!\p"
	.string "Hee hee... Hahahaha!!\p"
	.string "I knew it!\n"
	.string "Other worlds do exist!$"

FortuneTeller_Text_Boyfriend:
	.string "Hee hee... I wonder if I should have\n"
	.string "them ask if I have a boyfriend in\l"
	.string "the other world...$"

FortuneTeller_Text_Sorry:
	.string "E-excuse me, I'm getting ahead of\n"
	.string "myself.\p"
	.string "Thank you for your assistance.\p"
	.string "Please accept this as my thanks.$"

FortuneTeller_Text_RepeatUnlock:
	.string "Oh? You have a new piece of mail?\p"
	.string "...\p"
	.string "Fascinating... truly fascinating...\p"
	.string "Thank you, my friend.\n"
	.string "Here, take this.$"

FortuneTeller_Text_GoodDay:
	.string "Oh, good day.$"

FortuneTeller_Text_Intro:
	.string "You were the one I gave MAIL to,\n"
	.string "yes?\p"
	.string "You may call me the FORTUNE\n"
	.string "TELLER.\p"
	.string "If your POKéMON happen to be holding\n"
	.string "any peculiar MAIL, I would very\l"
	.string "much like to see it.$"

FortuneTeller_Text_AnyMail:
	.string "Tell me.\n"
	.string "Do you have any new MAIL to show?$"

FortuneTeller_Text_NoMail:
	.string "No? That's a shame.$"

FortuneTeller_Text_WhatCanIDo:
	.string "What can I do for you?$"

FortuneTeller_Text_HearMore:
	.string "Would you like to hear more?$"

FortuneTeller_Text_WhichWouldYouLike:
	.string "Which one would you like?$"

FortuneTeller_Text_AnotherOne:
	.string "Would you like to take another?$"

FortuneTeller_Text_MailHint:
	.string "...I see you no longer hold the\n"
	.string "MAIL in your BAG.\p"
	.string "Well, if you ever require more,\n"
	.string "I have supplied the MART here with\l"
	.string "copies.$"

FortuneTeller_Text_MailHint2:
	.string "...I see you no longer hold the\n"
	.string "MAIL in your BAG.\p"
	.string "Well, if you ever require more,\n"
	.string "I have supplied the MART in\l"
	.string "FORTREE with copies.$"