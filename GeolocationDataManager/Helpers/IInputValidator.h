#pragma once

#include <QString>

namespace Helpers
{
    class IInputValidator
    {
    public:
        virtual ~IInputValidator() {}

        virtual bool IsUrl(const QString& input) const = 0;
        virtual bool IsInvalid(const QString& input) const = 0;
    };
}
