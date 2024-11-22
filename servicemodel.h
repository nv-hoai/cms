#ifndef SERVICEMODEL_H
#define SERVICEMODEL_H

#include <QAbstractListModel>
#include "doublelinkedlist.h"
#include "hirecomputer.h"
#include "orderfood.h"
#include "service.h"
#include "computer.h"
#include "food.h"
#include "customer.h"

class ServiceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole,
        ServiceNameRole,
        CustomerRole,
        ComputerRole,
        TimeUsedRole,
        FoodRole,
        NumberOrderedRole,
        StatusRole,
        CostRole
    };

    explicit ServiceModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void addHireComputer(const QString &serviceName, Customer* customer, Computer* computer, const int &timeUse, const int& status);
    void addOrderFood(const QString &serviceName, Customer* customer, Food* food, const int &numberOredered, const int& status);
    void remove(const int& index);
    void setServiceName(const int& index, const QString& serviceName);
    void setCustomer(const int& index, Customer* customer);
    void setComputer(const int& index, Computer* computer);
    void setTimeUse(const int& index, const int& timeUse);
    void setFood(const int& index, Food* food);
    void setNumberOrdered(const int& index, const int& numberOrdered);
    void setStatus(const int& index, const bool& status);

    DoubleLinkedList<Service*>& getServiceList();
    Service* getService(const int& id);
    int getIndexById(const int& id);

    void saveServiceData(const char* path);
private:
    DoubleLinkedList<Service*> m_serviceList;
};

#endif // SERVICEMODEL_H
