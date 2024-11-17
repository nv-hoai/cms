#ifndef RECEIPT_H
#define RECEIPT_H

#include <QObject>
#include <QQmlEngine>
#include "customer.h"
#include "service.h"
#include "doublelinkedlist.h"

class Receipt : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(Customer* customer READ customer CONSTANT)
    Q_PROPERTY(QString createdTime READ createdTime CONSTANT)
    Q_PROPERTY(QString paidTime READ paidTime WRITE setPaidTime NOTIFY paidTimeChanged)
    Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int totalCharge READ totalCharge CONSTANT)
public:
    explicit Receipt(QObject *parent = nullptr);

    int id() const;

    Customer* customer() const;

    QString createdTime() const;

    bool status() const;
    void setStatus(bool newStatus);

    int totalCharge() const;

    QString paidTime() const;
    void setPaidTime(const QString &newPaidTime);

    void receiveServiceList(const int& customerId, DoubleLinkedList<Service*> &serviceList);
signals:
    void statusChanged();
    void totalChargeChanged();
    void paidTimeChanged();

public slots:
    Service* getService(const int& index);
    int serviceNumber();
private:
    QString m_createdTime;
    QString m_paidTime;
    int m_id;
    bool m_status;

    DoubleLinkedList<Service*> m_serviceList;
    static int receiptCount;

};

#endif // RECEIPT_H
