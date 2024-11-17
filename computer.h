#ifndef COMPUTER_H
#define COMPUTER_H

#include <QObject>
#include <QQmlEngine>

class Computer : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString cpu READ cpu WRITE setCpu NOTIFY cpuChanged)
    Q_PROPERTY(int ram READ ram WRITE setRam NOTIFY ramChanged)
    Q_PROPERTY(int  position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(int cost READ cost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(int id READ id CONSTANT)
public:
    explicit Computer(QObject *parent = nullptr);

    int ram() const;
    void setRam(int newRam);

    QString cpu() const;
    void setCpu(const QString &newCpu);

    int position() const;
    void setPosition(int newPosition);

    int cost() const;
    void setCost(int newCost);

    int status() const;
    void setStatus(int newStatus);

    int id() const;

signals:
    void ramChanged();
    void cpuChanged();
    void positionChanged();
    void costChanged();
    void statusChanged();

private:
    QString m_cpu;
    int m_id;
    int m_ram;
    int m_position;
    int m_status;
    int m_cost;

    static int computerCount;
};

#endif // COMPUTER_H
