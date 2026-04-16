FarawayIsland_Entrance_MapScripts::
	.byte 0

FarawayIsland_Entrance_EventScript_SetCloudsWeather::
	lock
	setweather WEATHER_SUNNY_CLOUDS
	doweather
	release
	end

FarawayIsland_Entrance_EventScript_ClearWeather::
	lock
	resetweather
	doweather
	release
	end

FarawayIsland_Entrance_EventScript_Sailor::
	lock
	faceplayer
	msgbox FarawayIsland_Entrance_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FarawayIsland_Entrance_EventScript_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	goto FarawayIsland_Entrance_EventScript_SailHome
	release
	end

FarawayIsland_Entrance_EventScript_SailHome::
	setvar VAR_0x8004, SEAGALLOP_FARAWAY_ISLAND
	setvar VAR_0x8006, SEAGALLOP_VERMILION_CITY
	goto EventScript_SetSail
	end

FarawayIsland_Entrance_Text_SailorReturn:
	.string "Whew, hope the trip here was\n"
	.string "worth it…\p"
	.string "Do you want to return to VERMILION?$"

FarawayIsland_Entrance_Text_Sign:
	.string "The writing is fading as if it was\n"
	.string "written a long time ago…\p"
	.string "“…ber, 6th day\n"
	.string "If any human…sets foot here…\l"
	.string "again…et it be a kindhearted pers…\l"
	.string "…ith that hope, I depar…”$"

FarawayIsland_Interior_Text_Mew:
	.string "Myuu…$"

FarawayIsland_Entrance_EventScript_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

FarawayIsland_Entrance_EventScript_Sign::
	msgbox FarawayIsland_Entrance_Text_Sign, MSGBOX_SIGN
	end
