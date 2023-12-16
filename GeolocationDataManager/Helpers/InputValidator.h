#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include "IInputValidator.h"

namespace Helpers
{
    class InputValidator: public IInputValidator
    {
    public:
        InputValidator() = default;

        bool IsUrl(const QString& input) const override;
    };
}
#endif // INPUTVALIDATOR_H
