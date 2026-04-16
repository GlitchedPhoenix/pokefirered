NavelRock_Summit_MapScripts::
	.byte 0

Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	step_end

Movement_CameraPanDown:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	step_end
