#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "computerfiltermodel.h"
#include "customerfiltermodel.h"
#include "employeefiltermodel.h"
#include "foodfiltermodel.h"
#include "servicefiltermodel.h"
#include "receiptmodel.h"

class SystemManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(ComputerFilterModel* computerFilterModel READ computerFilterModel CONSTANT)
    Q_PROPERTY(CustomerFilterModel* customerFilterModel READ customerFilterModel CONSTANT)
    Q_PROPERTY(EmployeeFilterModel* employeeFilterModel READ employeeFilterModel CONSTANT)
    Q_PROPERTY(FoodFilterModel* foodFilterModel READ foodFilterModel CONSTANT)
    Q_PROPERTY(ServiceFilterModel* serviceFilterModel READ serviceFilterModel CONSTANT)
    Q_PROPERTY(ComputerModel* computerModel READ computerModel CONSTANT)
    Q_PROPERTY(CustomerModel* customerModel READ customerModel  CONSTANT)
    Q_PROPERTY(EmployeeModel* employeeModel READ employeeModel CONSTANT)
    Q_PROPERTY(FoodModel* foodModel READ foodModel CONSTANT)
    Q_PROPERTY(ServiceModel* serviceModel READ serviceModel CONSTANT)
    Q_PROPERTY(ReceiptModel* receiptModel READ receiptModel CONSTANT)
public:
    explicit SystemManager(QObject *parent = nullptr);

    ComputerModel* computerModel() const;
    CustomerModel* customerModel() const;
    EmployeeModel* employeeModel() const;
    FoodModel* foodModel() const;
    ServiceModel* serviceModel() const;
    ReceiptModel* receiptModel() const;

    void loadComputerData(const char* path);
    void loadCustomerData(const char* path);
    void loadEmployeeData(const char* path);
    void loadFoodData(const char* path);
    void loadServiceData(const char* path);
    void loadRevenues(const char* path);

    ComputerFilterModel *computerFilterModel() const;
    CustomerFilterModel *customerFilterModel() const;
    EmployeeFilterModel *employeeFilterModel() const;
    FoodFilterModel *foodFilterModel() const;
    ServiceFilterModel *serviceFilterModel() const;

signals:
    void revenuesChanged();
public slots:
    void saveComputerData();
    void saveCustomerData();
    void saveEmployeeData();
    void saveFoodData();
    void saveServiceData();
    void saveReceiptData();
    void saveRevenues();
    void createReceipt(const int& customerId);
    void payReceipt(const int& receiptIndex);
    void confirmService(const int& serviceId);
    void removeService(const int& serviceId);

    int getRevenue(const int& index);
private:
    ComputerModel* m_computerModel;
    CustomerModel* m_customerModel;
    EmployeeModel* m_employeeModel;
    FoodModel* m_foodModel;
    ServiceModel* m_serviceModel;
    ReceiptModel* m_receiptModel;
    ComputerFilterModel *m_computerFilterModel;
    CustomerFilterModel *m_customerFilterModel;
    EmployeeFilterModel *m_employeeFilterModel;
    FoodFilterModel *m_foodFilterModel;
    ServiceFilterModel *m_serviceFilterModel;

    int revenues[7];
    QString oldData;
    const char* systemFiles[7];
};

#endif // SYSTEMMANAGER_H
