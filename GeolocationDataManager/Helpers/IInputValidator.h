#ifndef IINPUTVALIDATOR_H
#define IINPUTVALIDATOR_H
#include <QString>

namespace Helpers
{
    class IInputValidator
    {
    public:
        virtual ~IInputValidator() {}

        virtual bool IsUrl(const QString& input) const = 0;
    };
}
#endif // IINPUTVALIDATOR_H
