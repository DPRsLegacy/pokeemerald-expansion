#include "data/scripts/give_infinite_candy.inc"

TestInfiniteCandy_Event::
    lock
    faceplayer
    msgbox TestInfiniteCandy_Text_Intro, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq TestInfiniteCandy_GiveItem
    msgbox TestInfiniteCandy_Text_Declined, MSGBOX_DEFAULT
    release
    end

TestInfiniteCandy_GiveItem:
    goto InfiniteCandy_GiveItem

TestInfiniteCandy_Text_Intro:
    .string "Would you like to test the\n"
    .string "INFINITE CANDY item?$"

TestInfiniteCandy_Text_Declined:
    .string "Come back if you want to try it!$"
