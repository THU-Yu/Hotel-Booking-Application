#include "hotalorder.h"

HotalOrder::HotalOrder(HotalOrder &h)
{
    HotalName = h.getHotalName();
    HotalAccount = h.getHotalAccount();
    UserAccount = h.getUserAccount();
    RoomType = h.getRoomType();
    OrderNumber = h.getOrderNumber();
    Totalmoney = h.getTotalmoney();
    Start = h.getStart();
    Final = h.getFinal();
    PayOrNot = h.getPayOrNot();
    SuccessFul = h.getSuccessFul();
    New = h.getNew();
    next = nullptr;
}
