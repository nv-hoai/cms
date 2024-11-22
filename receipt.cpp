#include "receipt.h"

int Receipt::receiptCount = 1;

Receipt::Receipt(QObject *parent)
    : QObject{parent}, m_status(0)
{
    m_id = receiptCount++;
    m_createdTime = QTime::currentTime().toString();
}

int Receipt::id() const
{
    return m_id;
}

QString Receipt::createdTime() const
{
    return m_createdTime;
}

bool Receipt::status() const
{
    return m_status;
}

void Receipt::setStatus(bool newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

int Receipt::totalCharge() const
{
    int sum = 0;
    for(int i=0; i<map.getSize(); ++i) {
        sum += m_serviceList[map[i]]->totalCost();
    }
    return sum;
}

void Receipt::receiveServiceList(const int& customerId, DoubleLinkedList<Service *> &serviceList)
{
    for(auto it=serviceList.begin(); it!=serviceList.end(); ++it) {
        if ((*it)->customer()->id() == customerId) {
            m_serviceList.append((*it));
            if ((*it)->status() == 1)
                map.append(m_serviceList.getSize()-1);
        }
    }
}

DoubleLinkedList<Service *> &Receipt::serviceList()
{
    return m_serviceList;
}

Customer *Receipt::customer() const
{
    return m_serviceList[0]->customer();
}

Service *Receipt::getService(const int &index)
{
    if (index >= 0 && index < m_serviceList.getSize())
        return m_serviceList[map[index]];
    return nullptr;
}

int Receipt::serviceNumber()
{
    return map.getSize();
}

QString Receipt::paidTime() const {
    return m_paidTime;
}

void Receipt::setPaidTime(const QString &newPaidTime)
{
    if (m_paidTime == newPaidTime)
        return;
    m_paidTime = newPaidTime;
    emit paidTimeChanged();
}
