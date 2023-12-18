#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Persistence/Interface\IIpBasedLocationDataRepository.h"
#include "Persistence/Interface\IUrlBasedLocationDataRepository.h"
#include "HttpNetwork/IIpStackClient.h"
#include "Helpers/IInputValidator.h"
#include <QtConcurrent>
#include <QMessageBox>

MainWindow::MainWindow(
    std::unique_ptr<Persistence::IIpBasedLocationDataRepository> ipBasedRepository,
    std::unique_ptr<Persistence::IUrlBasedLocationDataRepository> urlBasedRepository,
    std::unique_ptr<HttpNetwork::IIpStackClient> ipStackClient,
    std::unique_ptr<Helpers::IInputValidator> inputValidator)
    : QMainWindow(nullptr)
    , mUi(new Ui::MainWindow)
    , mIpBasedRepository(std::move(ipBasedRepository))
    , mUrlBasedRepository(std::move(urlBasedRepository))
    , mIpStackClient(std::move(ipStackClient))
    , mInputValidator(std::move(inputValidator))
{
    mUi->setupUi(this);

    if(!mIpBasedRepository->Initialize())
    {
        displayErrorMessage("Location table creation failed! Application will not work properly. Please check the database file and run again.");
    }

    if(!mUrlBasedRepository->Initialize())
    {
        displayErrorMessage("Location table creation failed! Application will not work properly. Please check the database file and run again.");
    }

    connect(mUi->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(mUi->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(mUi->getDataButton, &QPushButton::clicked, this, &MainWindow::onGetDataButtonClicked);
    connect(mUi->getAllButton, &QPushButton::clicked, this, &MainWindow::onGetAllDataButtonClicked);

    connect(&mGetAllDataFutureWatcher, &QFutureWatcher<QString>::finished, this, &MainWindow::onGetAllDataFinished);
    connect(&mGetDataFutureWatcher, &QFutureWatcher<Persistence::Model::IpBasedLocationData>::finished, this, &MainWindow::onGetDataFinished);

    connect(&mUrlBasedGetDataFutureWatcher, &QFutureWatcher<Persistence::Model::UrlBasedLocationData>::finished, this, &MainWindow::onGetUrlDataFinished);

    QObject* ipStackClientAsQObject = dynamic_cast<QObject*>(mIpStackClient.get());
    if(ipStackClientAsQObject)
    {
        connect(ipStackClientAsQObject, SIGNAL(GetLocationDataResponse(QString, QString)), this, SLOT(handleLocationData(QString, QString)), Qt::AutoConnection);
    }
    else
    {
        qDebug() << "IpStackClient is not a QObject.";
    }

    QObject* ipRepositoryAsQObject = dynamic_cast<QObject*>(mIpBasedRepository.get());
    if(ipRepositoryAsQObject)
    {
        connect(ipRepositoryAsQObject, SIGNAL(errorOccurred(QString)), this, SLOT(displayErrorMessage(QString)));
    }
    else
    {
        qDebug() << "Ip Repository is not a QObject.";
    }

    QObject* urlRepositoryAsQObject = dynamic_cast<QObject*>(mUrlBasedRepository.get());
    if(urlRepositoryAsQObject)
    {
        connect(urlRepositoryAsQObject, SIGNAL(errorOccurred(QString)), this, SLOT(displayErrorMessage(QString)));
    }
    else
    {
        qDebug() << "Url Repository is not a QObject.";
    }
}

MainWindow::~MainWindow()
{
    delete mUi;
}

void MainWindow::displayErrorMessage(const QString& message)
{
    QMessageBox::warning(this, "Error", message);
}

void MainWindow::handleLocationData(const QString &locationDataJsonString, const QString& input)
{
    qDebug() << locationDataJsonString;
    if(locationDataJsonString.isNull())
    {
        displayErrorMessage("Input is invalid!");
        return;
    }

    if(mInputValidator->IsInvalid(input))
    {
        displayErrorMessage("Input is invalid!");
        return;
    }

    if(mInputValidator->IsUrl(input))
    {
        Persistence::Model::UrlBasedLocationData urlLocationData;
        try
        {
            urlLocationData.FromJson(locationDataJsonString);
        }
        catch (const std::exception& e)
        {
            qDebug() << QString("Parsing Data failed with exception: ").arg(e.what());
            displayErrorMessage(QString("Parsing Data failed with exception: ").arg(e.what()));
        }

        urlLocationData.url = input;

        QtConcurrent::run([this, urlLocationData](){ mUrlBasedRepository->Add(urlLocationData); });
        return;
    }

    Persistence::Model::IpBasedLocationData ipLocationData;
    ipLocationData.FromJson(locationDataJsonString);

    QtConcurrent::run([this, ipLocationData](){ mIpBasedRepository->Add(ipLocationData); });
}

void MainWindow::onAddButtonClicked()
{
    qDebug() << "Add button clicked";

    auto input = mUi->lineEdit->text();

    if(input.isNull() || input.isEmpty())
    {
        displayErrorMessage("Input data are empty. Please provide ip or url.");
        return;
    }

    if(mInputValidator->IsInvalid(input))
    {
        displayErrorMessage("Input is invalid!");
        return;
    }

    try
    {
        mIpStackClient->GetLocationDataRequest(input);
    }
    catch (const std::exception& e) {
        qDebug() << QString("Get location data request failed with exception: ").arg(e.what());
        displayErrorMessage(QString("Get location data request failed with exception: ").arg(e.what()));
    }

}

void MainWindow::onDeleteButtonClicked()
{
    qDebug() << "Delete button clicked";

    auto input = mUi->lineEdit->text();

    if(input.isNull() || input.isEmpty())
    {
        displayErrorMessage("Input data are empty. Please provide ip or url.");
        return;
    }

    if(mInputValidator->IsInvalid(input))
    {
        displayErrorMessage("Input is invalid!");
        return;
    }

    if(mInputValidator->IsUrl(input))
    {
        auto data = mUrlBasedRepository->GetByUrl(input);

        if(data.url.isNull() || data.url.isEmpty())
        {
            emit displayErrorMessage("Not Found.");
            return;
        }

        QtConcurrent::run([this, input](){ mUrlBasedRepository->DeleteByUrl(input); });
    }
    else
    {
        auto data = mIpBasedRepository->GetByIp(input);

        if(data.ip.isNull() || data.ip.isEmpty())
        {
            emit displayErrorMessage("Not Found.");
            return;
        }

        QtConcurrent::run([this, input](){ mIpBasedRepository->DeleteByIp(input); });
    }

}

void MainWindow::onGetDataButtonClicked()
{
    qDebug() << "Get All Data button clicked";

    mGetDataFutureWatcher.cancel();
    mGetDataFutureWatcher.waitForFinished();

    mUrlBasedGetDataFutureWatcher.cancel();
    mUrlBasedGetDataFutureWatcher.waitForFinished();

    auto input = mUi->lineEdit->text();
    if(input.isNull() || input.isEmpty())
    {
        displayErrorMessage("Input data are empty. Please provide ip or url.");
        return;
    }

    if(mInputValidator->IsInvalid(input))
    {
        displayErrorMessage("Input is invalid!");
        return;
    }

    if(mInputValidator->IsUrl(input))
    {
        QFuture<Persistence::Model::UrlBasedLocationData> future = QtConcurrent::run([this, input] {
            return mUrlBasedRepository->GetByUrl(input);
        });
        mUrlBasedGetDataFutureWatcher.setFuture(future);
        return;
    }

    QFuture<Persistence::Model::IpBasedLocationData> future = QtConcurrent::run([this, input] {
        return mIpBasedRepository->GetByIp(input);
    });

    mGetDataFutureWatcher.setFuture(future);
}

void MainWindow::onGetDataFinished()
{
    auto data = mGetDataFutureWatcher.future().result();

    if(data.ip.isNull() || data.ip.isEmpty())
    {
        displayErrorMessage("Not Found.");
        return;
    }

    QString displayText;

    displayText += data.Str() + "\n";

    mUi->resultsLabel->setText(displayText);
}

void MainWindow::onGetUrlDataFinished()
{
    auto data = mUrlBasedGetDataFutureWatcher.future().result();

    if(data.ip.isNull() || data.ip.isEmpty())
    {
        displayErrorMessage("Not Found.");
        return;
    }

    QString displayText;

    displayText += data.Str() + "\n";

    mUi->resultsLabel->setText(displayText);
}

void MainWindow::onGetAllDataButtonClicked()
{
    qDebug() << "Get All Data button clicked";

    mGetAllDataFutureWatcher.cancel();
    mGetAllDataFutureWatcher.waitForFinished();


    QFuture<QString> future = QtConcurrent::run([this] {

       auto data = mIpBasedRepository->GetAll();
        QString displayText;

        for (const auto& item : data) {
            displayText += item.Str() + "\n\n";
        }

        auto urlData = mUrlBasedRepository->GetAll();

        for (const auto& item : urlData) {
            displayText += item.Str() + "\n\n";
        }

        return displayText;
    });


    mGetAllDataFutureWatcher.setFuture(future);
}

void MainWindow::onGetAllDataFinished()
{
    auto displayText = mGetAllDataFutureWatcher.future().result();

    mUi->resultsLabel->setText(displayText);
}

