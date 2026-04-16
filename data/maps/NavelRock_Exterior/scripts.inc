NavelRock_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NavelRock_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, NavelRock_Exterior_OnResume
	.byte 0

NavelRock_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_NAVEL_ROCK_EXTERIOR
	goto_if_eq VAR_NAVEL_ROCK_PROGRESS, 1, NavelRock_Exterior_ChangeGear
	goto_if_eq VAR_NAVEL_ROCK_PROGRESS, 2, NavelRock_Exterior_ChangeGear
	setdynamicwarp MAP_NAVEL_ROCK_1F, 1
	end

NavelRock_Exterior_OnResume::
	goto_if_eq VAR_NAVEL_ROCK_PROGRESS, 1, NavelRock_Exterior_ChangeGear
	goto_if_eq VAR_NAVEL_ROCK_PROGRESS, 2, NavelRock_Exterior_ChangeGear
	setdynamicwarp MAP_NAVEL_ROCK_1F, 1
	end

NavelRock_Exterior_ChangeGear::
	setdynamicwarp MAP_NAVEL_ROCK_1F_SPECIAL, 1
	setweather WEATHER_RAIN
	end

NavelRock_Exterior_CheckHoohLugia::
	lock
	specialvar VAR_RESULT, CheckHoohLugia
	goto_if_eq VAR_RESULT, TRUE, NavelRock_Exterior_Quake
	release
	end

NavelRock_Exterior_Quake::
	lock
	setweather WEATHER_RAIN
	doweather
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 10
	setvar VAR_0x8007, 3
	special ShakeScreen
	playse SE_THUNDER
	delay 10
	playse SE_ICE_BREAK
	waitse
	playse SE_ICE_BREAK
	waitse
	playse SE_ICE_BREAK
	waitse
	delay 30
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 3
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 2
	special ShakeScreen
	delay 60
	playse SE_MUGSHOT
	msgbox NavelRock_Exterior_Text_Question
	setdynamicwarp MAP_NAVEL_ROCK_1F_SPECIAL, 1
	setvar VAR_NAVEL_ROCK_PROGRESS, 1
	release
	end

NavelRock_Exterior_Revert::
	lock
	resetweather
	doweather
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 10
	setvar VAR_0x8007, 3
	special ShakeScreen
	playse SE_THUNDER
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 3
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 2
	special ShakeScreen
	delay 60
	playse SE_MUGSHOT
	setdynamicwarp MAP_NAVEL_ROCK_1F, 1
	setvar VAR_NAVEL_ROCK_PROGRESS, 3
	release
	end

NavelRock_Exterior_Text_Question::
	.string "...?$"
