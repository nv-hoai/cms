#include <QFile>
#include <QTextStream>
#include <QDate>
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
    loadRevenues("../../data/revenues.txt");

    systemFiles[0] = "../../data/computer.txt";
    systemFiles[1] = "../../data/customer.txt";
    systemFiles[2] = "../../data/employee.txt";
    systemFiles[3] = "../../data/food.txt";
    systemFiles[4] = "../../data/service.txt";
    systemFiles[5] = "../../data/receipt.txt";
    systemFiles[6] = "../../data/revenues.txt";

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
            if (fields[4].toInt()) {
                Food* food = m_foodModel->getFood(fields[2].toInt());
                food->setRemain(food->remain() - fields[3].toInt());
            }
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

void SystemManager::loadRevenues(const char *path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream in(&file);
    QString lastDay = in.readLine();

    if (lastDay == QDate::currentDate().toString("dd/MM/yyyy"))
        in >> revenues[0];
    else
        revenues[0] = 0;

    for (int i=1; i<7; i++)
        in >> revenues[i];

    oldData = in.readAll();

    file.close();
}

void SystemManager::createReceipt(const int &customerId)
{
    m_receiptModel->add(customerId, m_serviceModel->getServiceList());
}

void SystemManager::payReceipt(const int &receiptIndex)
{
    DoubleLinkedList<Service*>& serviceList = m_receiptModel->serviceList(receiptIndex);
    for(auto it=serviceList.begin(); it!=serviceList.end(); ++it)
        removeService((*it)->id());
    revenues[0] += m_receiptModel->getReceipt(receiptIndex)->totalCharge();
    emit revenuesChanged();
}

void SystemManager::confirmService(const int &serviceId)
{
    Service *service = m_serviceModel->getService(serviceId);
    HireComputer* hc = nullptr;
    OrderFood* of = nullptr;
    if (service->serviceName() == "Hire computer")
        hc = (HireComputer*)service;
    if (service->serviceName() == "Order food")
        of = (OrderFood*)service;


    if (of) {
        if (m_foodModel->getFood(of->food()->id())) {
            Food* food = of->food();
            m_foodModel->setRemain(m_foodModel->getIndexById(food->id()), food->remain()-of->numberOrdered());
        } else {
            removeService(serviceId);
            return;
        }
    }

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
    // OrderFood* of = nullptr;
    if (service->serviceName() == "Hire computer")
        hc = (HireComputer*)service;
    // if (service->serviceName() == "Order food")
    //     of = (OrderFood*)service;

    if (hc) {
        m_computerModel->setStatus(m_computerModel->getIndexById(hc->computer()->id()), 0);
    }

    if (service->status()) {
        m_customerModel->getCustomer(service->customer()->id())->decreaseNumberService();
    }
    m_customerModel->setStatus(m_customerModel->getIndexById(service->customer()->id()), 0);
    m_serviceModel->remove(m_serviceModel->getIndexById(service->id()));
}

int SystemManager::getRevenue(const int &index)
{
    return revenues[index];
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
    m_customerModel->saveCustomerData(systemFiles[1]);
}

void SystemManager::saveEmployeeData()
{
    m_employeeModel->saveEmployeeData(systemFiles[2]);
}

void SystemManager::saveFoodData()
{
    m_foodModel->saveFoodData(systemFiles[3]);
}

void SystemManager::saveServiceData()
{
    m_serviceModel->saveServiceData(systemFiles[4]);
}

void SystemManager::saveReceiptData()
{
    m_receiptModel->saveReceiptData(systemFiles[5]);
}

void SystemManager::saveRevenues()
{

    QFile file(systemFiles[6]);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream out(&file);

    out << QDate::currentDate().toString("dd/MM/yyyy"); Qt::endl(out);

    for (auto e: revenues)
        out << e << " ";

    out << oldData;
}
