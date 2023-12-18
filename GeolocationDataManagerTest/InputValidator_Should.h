#pragma once

#include "../GeolocationDataManager/Helpers/InputValidator.h"

class InputValidator_Should : public QObject
{
    Q_OBJECT

public:
    InputValidator_Should();

private slots:
    void initTestCase();

    void ReturnTrue_WhenUrlIsProvidedAsInput();

    void ReturnFalse_WhenIpV4IsProvidedAsInput();

    void ReturnFalse_WhenIpV6IsProvidedAsInput();

    void ReturnTrue_WhenInputIsInvalid();

    void ReturnFalse_WhenInputIsValidalid();

private:
    std::unique_ptr<Helpers::IInputValidator> mSut;
    std::vector<QString> mTestDataUrl;
    std::vector<QString> mTestDataIPV6;
    std::vector<QString> mTestDataIPV4;

    std::vector<QString> mTestDataInvalid;
};
