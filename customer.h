#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QQmlEngine>
#include "human.h"

class Customer : public Human
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
public:
    explicit Customer(QObject *parent = nullptr);

    int id() const;

    int status() const;
    void setStatus(int newStatus);

    int numberServiceUsing() const;
    void increaseNumberService();
    void decreaseNumberService();

signals:
    void statusChanged();

private:
    int m_id;
    int m_status;
    int m_numberServiceUsing;

    static int customerCount;

};

#endif // CUSTOMER_H
