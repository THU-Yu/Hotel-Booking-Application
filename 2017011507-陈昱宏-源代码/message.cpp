#include "message.h"

Message::Message(Message &m)
{
    sendUser = m.getsendUser();
    receiveUser = m.getreceiveUser();
    message = m.getmessage();
    date = m.getdate();
    New = m.getNew();
    next = nullptr;
}
