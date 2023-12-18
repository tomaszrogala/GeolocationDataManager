#pragma once

#include "IInputValidator.h"

namespace Helpers
{
    class InputValidator: public IInputValidator
    {
    public:
        InputValidator() = default;

        bool IsUrl(const QString& input) const override;
        bool IsInvalid(const QString& input) const override;
    };
}
