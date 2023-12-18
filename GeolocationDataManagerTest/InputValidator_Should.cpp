#include <QtTest>
#include <QCoreApplication>
#include "InputValidator_Should.h"

InputValidator_Should::InputValidator_Should()
{
    mSut = std::make_unique<Helpers::InputValidator>();
}

void InputValidator_Should::initTestCase()
{
    // URL
    mTestDataUrl.push_back("https://www.example.com");
    mTestDataUrl.push_back("http://www.testsite.com");
    mTestDataUrl.push_back("https://subdomain.example.org/path?query=123");
    mTestDataUrl.push_back("https://www.example.com");
    mTestDataUrl.push_back("http://www.testsite.com");
    mTestDataUrl.push_back("https://subdomain.example.org/path?query=123");
    mTestDataUrl.push_back("ftp://ftp.example.com/dir/file.txt");

    // IPv4
    mTestDataIPV4.push_back("192.168.1.1");
    mTestDataIPV4.push_back("10.0.0.1");
    mTestDataIPV4.push_back("172.16.254.1");
    mTestDataIPV4.push_back("192.168.1.1");
    mTestDataIPV4.push_back("10.0.0.1");
    mTestDataIPV4.push_back("172.16.254.1");
    mTestDataIPV4.push_back("255.255.255.255");

    // IPv6
    mTestDataIPV6.push_back("2001:0db8:85a3:0000:0000:8a2e:0370:7334");
    mTestDataIPV6.push_back("::1");
    mTestDataIPV6.push_back("fe80::1ff:fe23:4567:890a");

    // Invalid
    mTestDataInvalid.push_back("");
    mTestDataInvalid.push_back("   ");
    mTestDataInvalid.push_back("http://example.com/<script>");
    mTestDataInvalid.push_back("https://example.com/|pipe");
    mTestDataInvalid.push_back("ftp://example.com/with space");
    mTestDataInvalid.push_back("javascript:alert('XSS')");
}

void InputValidator_Should::ReturnTrue_WhenUrlIsProvidedAsInput()
{

    for(const auto& testData : mTestDataUrl)
    {
        QVERIFY(mSut->IsUrl(testData));
    }

}

void InputValidator_Should::ReturnFalse_WhenIpV4IsProvidedAsInput()
{
    for(const auto& testData : mTestDataIPV4)
    {
        QVERIFY(!mSut->IsUrl(testData));
    }
}

void InputValidator_Should::ReturnFalse_WhenIpV6IsProvidedAsInput()
{
    for(const auto& testData : mTestDataIPV6)
    {
        QVERIFY(!mSut->IsUrl(testData));
    }
}

void InputValidator_Should::ReturnTrue_WhenInputIsInvalid()
{
    for(const auto& testData : mTestDataInvalid)
    {
        QVERIFY(mSut->IsInvalid(testData));
    }
}

void InputValidator_Should::ReturnFalse_WhenInputIsValidalid()
{
    for(const auto& testData : mTestDataUrl)
    {
        QVERIFY(!mSut->IsInvalid(testData));
    }

    for(const auto& testData : mTestDataIPV4)
    {
        QVERIFY(!mSut->IsInvalid(testData));
    }

    for(const auto& testData : mTestDataIPV6)
    {
        QVERIFY(!mSut->IsInvalid(testData));
    }
}


#include "InputValidator_Should.moc"
