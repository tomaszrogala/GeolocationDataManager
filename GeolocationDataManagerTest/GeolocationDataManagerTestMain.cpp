#include <QApplication>
#include <QTest>
#include "IpBasedLocationDataRepository_Should.h"
#include "UrlBasedLocationDataRepository_Should.h"
#include "InputValidator_Should.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    IpBasedLocationDataRepository_Should ipReposytoryTest;
    QTest::qExec(&ipReposytoryTest, argc, argv);

    UrlBasedLocationDataRepository_Should urlReposytoryTest;
    QTest::qExec(&urlReposytoryTest, argc, argv);

    InputValidator_Should inputValidatorTest;
    QTest::qExec(&inputValidatorTest, argc, argv);

    return 0;
}

