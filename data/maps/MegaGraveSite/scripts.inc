MegaGraveSite_MapScripts::
	.byte 0

MegaGraveSite_EventScript_ExitToRoute103::
	lockall
	warpteleport MAP_ROUTE103, 3, 18
	waitstate
	releaseall
	end

MegaGraveSite_EventScript_GraveSign::
	lockall
	msgbox MegaGraveSite_Text_Grave, MSGBOX_DEFAULT
	goto_if_set FLAG_RECEIVED_MEGA_RING, MegaGraveSite_EventScript_GraveSignEnd
	giveitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, MegaGraveSite_EventScript_BagFull
	setflag FLAG_RECEIVED_MEGA_RING
MegaGraveSite_EventScript_GraveSignEnd::
	releaseall
	end

MegaGraveSite_EventScript_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	releaseall
	end

MegaGraveSite_Text_Grave:
	.string "Smitty Werben Man Jensen\n"
	.string "He was No. 1$"
