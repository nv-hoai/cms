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
    Q_PROPERTY(int timeUsed READ timeUsed WRITE setTimeUsed NOTIFY timeUsedChanged)
public:
    explicit HireComputer(QObject *parent = nullptr);

    int timeUsed() const;
    void setTimeUsed(int newTimeUsed);

    Computer *computer() const;
    void setComputer(Computer *newComputer);

    int totalCost() const override;
signals:
    void timeUsedChanged();
    void computerChanged();

private:
    Computer *m_computer;
    int m_timeUsed;
};

#endif // HIRECOMPUTER_H
