#include "service.h"

int Service::serviceCount = 1;

Service::Service(QObject *parent)
    : QObject{parent}, m_customer(nullptr), m_status(0)
{
    m_id = serviceCount++;
}

QString Service::serviceName() const
{
    return m_serviceName;
}

void Service::setServiceName(const QString &newServiceName)
{
    if (m_serviceName == newServiceName)
        return;
    m_serviceName = newServiceName;
    emit serviceNameChanged();
}

int Service::id() const
{
    return m_id;
}

Customer *Service::customer() const
{
    return m_customer;
}

void Service::setCustomer(Customer *newCustomer)
{
    if (m_customer == newCustomer)
        return;
    m_customer = newCustomer;
    emit customerChanged();
}

int Service::cost() const
{
    return m_cost;
}

void Service::setCost(int newCost)
{
    if (m_cost == newCost)
        return;
    m_cost = newCost;
    emit costChanged();
}

int Service::totalCost() const
{
    return m_cost;
}

bool Service::status() const
{
    return m_status;
}

void Service::setStatus(bool newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}
