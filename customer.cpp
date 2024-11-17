#include "customer.h"

int Customer::customerCount = 1;

Customer::Customer(QObject *parent)
    : Human(parent), m_status(0), m_numberServiceUsing(0)
{
    m_id = customerCount++;
}

int Customer::id() const
{
    return m_id;
}

int Customer::status() const
{
    return m_status;
}

void Customer::setStatus(int newStatus)
{
    if (newStatus != 1 && m_numberServiceUsing != 0)
        return;
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

int Customer::numberServiceUsing() const
{
    return m_numberServiceUsing;
}

void Customer::increaseNumberService()
{
    m_numberServiceUsing++;
}

void Customer::decreaseNumberService()
{
    m_numberServiceUsing--;
}
