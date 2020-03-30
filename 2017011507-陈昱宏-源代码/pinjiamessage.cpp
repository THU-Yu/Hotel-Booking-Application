#include "PinJiaMessage.h"

PinJiaMessage::PinJiaMessage(PinJiaMessage &p)
{
    PinJia = p.getPinJia();
    User = p.getUser();
    HotalName = p.getHotalName();
    message = p.getmessage();
    next = nullptr;
}

void PinJiaMessage::addMessage(Message *m)
{
    if (message == nullptr)
    {
        message = m;
    }
    else
    {
        Message *ptr;
        for (ptr = message;ptr->getnext() != nullptr;ptr = ptr->getnext()){}
        ptr->changenext(m);
    }
}
