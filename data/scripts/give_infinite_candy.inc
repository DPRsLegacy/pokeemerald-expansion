.set ITEM_INFINITE_CANDY, 829

InfiniteCandy_GiveItem::
    giveitem ITEM_INFINITE_CANDY, 1
    msgbox InfiniteCandy_Text_ReceivedItem, MSGBOX_DEFAULT
    release
    end

InfiniteCandy_Text_ReceivedItem:
    .string "Obtained an INFINITE CANDY!\p"
    .string "This special candy will never be\n"
    .string "consumed when used!$"
