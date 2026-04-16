FourIsland_IcefallCave_Secret_MapScripts::
	.byte 0
	
FourIsland_IcefallCave_Secret_TornScrap2::
	lock
	setflag FLAG_HIDE_TORN_SCRAP_2
	removeobject 1
	giveitem ITEM_TORN_SCRAP_2, 1
	release
	end
