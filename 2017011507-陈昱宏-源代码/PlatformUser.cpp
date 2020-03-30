#include "platformuser.h"

PlatformUser::PlatformUser(bank_account *b, QString a, QString p, QString number, QString email)
    :bank(b)
{
    change_account(a);
    change_password(p);
    phone_number = number;
    email_address = email;
    UserType = "平台管理";
}
