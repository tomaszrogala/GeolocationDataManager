#pragma once

#include <QMainWindow>
#include <QFuture>
#include <QFutureWatcher>
#include "Persistence/Interface\IIpBasedLocationDataRepository.h"
#include "Persistence/Interface\IUrlBasedLocationDataRepository.h"
#include "Persistence/Model\IpBasedLocationData.h"
#include "HttpNetwork/IIpStackClient.h"
#include "Helpers/IInputValidator.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
        std::unique_ptr<Persistence::IIpBasedLocationDataRepository> ipBasedRepository,
        std::unique_ptr<Persistence::IUrlBasedLocationDataRepository> urlBasedRepository,
        std::unique_ptr<HttpNetwork::IIpStackClient> ipStackClient,
        std::unique_ptr<Helpers::IInputValidator> inputValidator);

    ~MainWindow();

private slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onGetDataButtonClicked();
    void onGetAllDataButtonClicked();

    void onGetDataFinished();
    void onGetAllDataFinished();

    void onGetUrlDataFinished();

    void displayErrorMessage(const QString& message);
    void handleLocationData(const QString &locationDataJsonString, const QString& input);

private:
    Ui::MainWindow *mUi;
    std::unique_ptr<Persistence::IIpBasedLocationDataRepository> mIpBasedRepository;
    std::unique_ptr<Persistence::IUrlBasedLocationDataRepository> mUrlBasedRepository;
    std::unique_ptr<HttpNetwork::IIpStackClient> mIpStackClient;
    std::unique_ptr<Helpers::IInputValidator> mInputValidator;

    QFutureWatcher<Persistence::Model::IpBasedLocationData> mGetDataFutureWatcher;
    QFutureWatcher<QString> mGetAllDataFutureWatcher;

    QFutureWatcher<Persistence::Model::UrlBasedLocationData> mUrlBasedGetDataFutureWatcher;
};
