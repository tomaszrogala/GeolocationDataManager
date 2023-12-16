#include "InputValidator.h"
#include <QRegularExpression>

namespace Helpers
{
    bool InputValidator::IsUrl(const QString& input) const
    {
        //This filter makes sure that IPV4 and IPV6 are definately not provided (Invalid url is allowed)
        QRegularExpression urlRegex(R"(\.[a-zA-Z]+$)");

        return urlRegex.match(input).hasMatch();
    }
}
