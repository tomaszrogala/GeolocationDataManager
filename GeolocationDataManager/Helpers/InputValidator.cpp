#include "InputValidator.h"
#include <QRegularExpression>

namespace Helpers
{
    bool InputValidator::IsUrl(const QString& input) const
    {
        //This filter makes sure that IPV4 and IPV6 are definately not provided (Invalid url is allowed)

        QRegularExpression urlRegex(R"((\.[a-zA-Z]+)|^(?=.*[a-zA-Z]).{5}$)");

        return urlRegex.match(input).hasMatch();
    }

    bool InputValidator::IsInvalid(const QString& input) const
    {
        if (input.trimmed().isEmpty()) {
            return true;
        }

        QRegularExpression invalidCharsRegex("[<|>|#|(|)|{|}|,| |;]");
        if (invalidCharsRegex.match(input).hasMatch()) {
            return true;
        }

        if (input.length() < 3 || input.length() > 2048) {
            return true;
        }

        return false;
    }

}
