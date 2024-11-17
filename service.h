#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QQmlEngine>
#include "customer.h"

class Service : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int cost READ cost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(int totalCost READ totalCost CONSTANT)
    Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(Customer* customer READ customer WRITE setCustomer NOTIFY customerChanged)
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
public:
    explicit Service(QObject *parent = nullptr);

    QString serviceName() const;
    void setServiceName(const QString &newServiceName);

    int id() const;

    Customer *customer() const;
    void setCustomer(Customer *newCustomer);

    int cost() const;
    void setCost(int newCost);

    virtual int totalCost() const;

    bool status() const;
    void setStatus(bool newStatus);

signals:
    void serviceNameChanged();
    void customerIdChanged();
    void customerChanged();
    void costChanged();
    void statusChanged();

private:
    QString m_serviceName;
    Customer *m_customer;
    int m_id;
    int m_cost;
    bool m_status;
    static int serviceCount;
};

#endif // SERVICE_H
