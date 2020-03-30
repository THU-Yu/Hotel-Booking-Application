#include "room.h"

Room::Room(Room &r)
{
    HotalName = r.getHotalName();
    RoomType = r.getType();
    TotalNum = r.getTotalNum();
    RoomNum = r.getRoomNum();
    Date = r.getDate();
    moneyPerNight = r.getmoneyPerNight();
    next = nullptr;
}
