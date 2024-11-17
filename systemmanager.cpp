#include <QFile>
#include <QTextStream>
#include <QDir>
#include "systemmanager.h"

using namespace std;

SystemManager::SystemManager(QObject *parent)
    : QObject{parent}
    , m_computerModel(new ComputerModel(this))
    , m_customerModel(new CustomerModel(this))
    , m_employeeModel(new EmployeeModel(this))
    , m_foodModel(new FoodModel(this))
    , m_serviceModel(new ServiceModel(this))
    , m_receiptModel(new ReceiptModel(this))
    , m_computerFilterModel(new ComputerFilterModel(this))
    , m_customerFilterModel(new CustomerFilterModel(this))
    , m_employeeFilterModel(new EmployeeFilterModel(this))
    , m_foodFilterModel(new FoodFilterModel(this))
    , m_serviceFilterModel(new ServiceFilterModel(this))
{
    loadComputerData("../../data/computer.txt");
    loadCustomerData("../../data/customer.txt");
    loadEmployeeData("../../data/employee.txt");
    loadFoodData("../../data/food.txt");
    loadServiceData("../../data/service.txt");

    m_computerFilterModel->setSourceModel(m_computerModel);
    m_customerFilterModel->setSourceModel(m_customerModel);
    m_employeeFilterModel->setSourceModel(m_employeeModel);
    m_foodFilterModel->setSourceModel(m_foodModel);
    m_serviceFilterModel->setSourceModel(m_serviceModel);
}

ComputerModel* SystemManager::computerModel() const
{
    return m_computerModel;
}

CustomerModel* SystemManager::customerModel() const
{
    return m_customerModel;
}

EmployeeModel* SystemManager::employeeModel() const
{
    return m_employeeModel;
}

FoodModel* SystemManager::foodModel() const
{
    return m_foodModel;
}

ServiceModel* SystemManager::serviceModel() const
{
    return m_serviceModel;
}

ReceiptModel* SystemManager::receiptModel() const
{
    return m_receiptModel;
}

void SystemManager::loadComputerData(const char* path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    systemFiles[0] = path;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() != 5) {
            std::cerr << "Invalid line format: " << line.toStdString() << std::endl;
            continue;
        }

        m_computerModel->add(fields[0], fields[1].toInt(), fields[2].toInt(), fields[3].toInt(), fields[4].toDouble());
    }

    file.close();
}

void SystemManager::loadCustomerData(const char* path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    systemFiles[1] = path;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() != 4) {
            std::cerr << "Invalid line format: " << line.toStdString() << std::endl;
            continue;
        }

        m_customerModel->add(fields[0], fields[1], fields[2].toInt(), fields[3].toInt());
    }

    file.close();
}

void SystemManager::loadEmployeeData(const char* path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    systemFiles[2] = path;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() != 8) {
            std::cerr << "Invalid line format: " << line.toStdString() << std::endl;
            continue;
        }

        m_employeeModel->add(fields[0], fields[1], fields[2].toInt(), fields[3].toInt(),
                             fields[4], fields[5].toInt(), fields[6], fields[7].toDouble());
    }

    file.close();
}

void SystemManager::loadFoodData(const char* path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    systemFiles[3] = path;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() != 4) {
            std::cerr << "Invalid line format: " << line.toStdString() << std::endl;
            continue;
        }

        m_foodModel->add(fields[0], fields[1].toInt(), fields[2].toDouble(), fields[3]);
    }

    file.close();
}

void SystemManager::loadServiceData(const char* path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    systemFiles[4] = path;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() != 5) {
            std::cerr << "Invalid line format: " << line.toStdString() << std::endl;
            continue;
        }

        if (fields[0] == "Hire computer") {
            m_serviceModel->addHireComputer(fields[0], m_customerModel->getCustomer(fields[1].toInt()),
                                            m_computerModel->getComputer(fields[2].toInt()), fields[3].toInt(), fields[4].toInt());
            if (fields[4].toInt())
                m_computerModel->getComputer(fields[2].toInt())->setStatus(1);
            else
                m_computerModel->getComputer(fields[2].toInt())->setStatus(2);
        }
        if (fields[0] == "Order food") {
            m_serviceModel->addOrderFood(fields[0], m_customerModel->getCustomer(fields[1].toInt()),
                                         m_foodModel->getFood(fields[2].toInt()), fields[3].toInt(), fields[4].toInt());
            Food* food = m_foodModel->getFood(fields[2].toInt());
            food->setRemain(food->remain() - fields[3].toInt());
        }
        if (fields[4].toInt()) {
            m_customerModel->getCustomer(fields[1].toInt())->increaseNumberService();
            m_customerModel->getCustomer(fields[1].toInt())->setStatus(1);
        } else {
            m_customerModel->getCustomer(fields[1].toInt())->setStatus(2);
        }
    }

    file.close();
}

void SystemManager::createReceipt(const int &customerId)
{
    m_receiptModel->add(customerId, m_serviceModel->getServiceList());
}

void SystemManager::removeReceipt(const int &receiptIndex, const bool& status)
{
    if (status) {
        Service* service = nullptr;
        int numberService = m_receiptModel->serviceNumber(receiptIndex);
        for(int i=0; i<numberService; i++) {
            service = m_receiptModel->getService(receiptIndex, i);
            removeService(service->id());
        }
    }
    m_receiptModel->remove(receiptIndex);
}

void SystemManager::confirmService(const int &serviceId)
{
    Service *service = m_serviceModel->getService(serviceId);
    HireComputer* hc = nullptr;
    // OrderFood* of = nullptr;
    if (service->serviceName() == "Hire computer")
        hc = (HireComputer*)service;
    // if (service->serviceName() == "Order food")
    //     of = (OrderFood*)service;

    Customer* customer = m_customerModel->getCustomer(service->customer()->id());
    customer->increaseNumberService();
    m_customerModel->setStatus(m_customerModel->getIndexById(customer->id()), 1);

    if (hc) {
        m_computerModel->setStatus(m_computerModel->getIndexById(hc->computer()->id()), 1);
    }
    m_serviceModel->setStatus(m_serviceModel->getIndexById(service->id()), 1);
}

void SystemManager::removeService(const int &serviceId)
{
    Service *service = m_serviceModel->getService(serviceId);
    HireComputer* hc = nullptr;
    OrderFood* of = nullptr;
    if (service->serviceName() == "Hire computer")
        hc = (HireComputer*)service;
    if (service->serviceName() == "Order food")
        of = (OrderFood*)service;

    if (hc) {
        m_computerModel->setStatus(m_computerModel->getIndexById(hc->computer()->id()), 0);
    }

    if (!service->status()) {
        if (of) {
            Food* food = m_foodModel->getFood(of->food()->id());
            m_foodModel->setRemain(m_foodModel->getIndexById(food->id()), food->remain() + of->numberOrdered());
        }
    }

    if (service->status()) {
        m_customerModel->getCustomer(service->customer()->id())->decreaseNumberService();
    }
    m_customerModel->setStatus(m_customerModel->getIndexById(service->customer()->id()), 0);
    m_serviceModel->remove(m_serviceModel->getIndexById(service->id()));
}

ComputerFilterModel *SystemManager::computerFilterModel() const
{
    return m_computerFilterModel;
}

CustomerFilterModel *SystemManager::customerFilterModel() const
{
    return m_customerFilterModel;
}

EmployeeFilterModel *SystemManager::employeeFilterModel() const
{
    return m_employeeFilterModel;
}

FoodFilterModel *SystemManager::foodFilterModel() const
{
    return m_foodFilterModel;
}

ServiceFilterModel *SystemManager::serviceFilterModel() const
{
    return m_serviceFilterModel;
}

void SystemManager::saveComputerData()
{
    m_computerModel->saveComputerData(systemFiles[0]);
}

void SystemManager::saveCustomerData()
{

}

void SystemManager::saveEmployeeData()
{

}

void SystemManager::saveFoodData()
{

}

void SystemManager::saveServiceData()
{

}
