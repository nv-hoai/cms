#ifndef ORDERFOOD_H
#define ORDERFOOD_H

#include <QObject>
#include <QQmlEngine>
#include "service.h"
#include "food.h"

class OrderFood : public Service
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(Food* food READ food WRITE setFood NOTIFY foodChanged FINAL)
    Q_PROPERTY(int numberOrdered READ numberOrdered WRITE setNumberOrdered NOTIFY numberOrderedChanged)
public:
    explicit OrderFood(QObject *parent = nullptr);

    int numberOrdered() const;
    void setNumberOrdered(int newNumberOrdered);

    Food *food() const;
    void setFood(Food *newFood);

    int totalCost() const override;
signals:
    void numberOrderedChanged();
    void foodChanged();

private:
    int m_foodId;
    int m_numberOrdered;
    Food *m_food;
};

#endif // ORDERFOOD_H
