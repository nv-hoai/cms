#ifndef HIRECOMPUTER_H
#define HIRECOMPUTER_H

#include <QObject>
#include <QQmlEngine>
#include "service.h"
#include "computer.h"

class HireComputer : public Service
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(Computer* computer READ computer WRITE setComputer NOTIFY computerChanged)
    Q_PROPERTY(int timeUse READ timeUse WRITE setTimeUse NOTIFY timeUseChanged)
public:
    explicit HireComputer(QObject *parent = nullptr);

    int timeUse() const;
    void setTimeUse(int newTimeUse);

    Computer *computer() const;
    void setComputer(Computer *newComputer);

    int totalCost() const override;

signals:
    void startTimeChanged();
    void timeUseChanged();
    void computerChanged();

private:
    QString m_startTime;
    Computer *m_computer;
    int m_timeUse;
};

#endif // HIRECOMPUTER_H
