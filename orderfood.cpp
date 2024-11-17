#include "orderfood.h"

OrderFood::OrderFood(QObject *parent)
    : Service{parent}, m_food(nullptr)
{}

int OrderFood::numberOrdered() const
{
    return m_numberOrdered;
}

void OrderFood::setNumberOrdered(int newNumberOrdered)
{
    if (m_numberOrdered == newNumberOrdered)
        return;
    m_numberOrdered = newNumberOrdered;
    emit numberOrderedChanged();
}

Food *OrderFood::food() const
{
    return m_food;
}

void OrderFood::setFood(Food *newFood)
{
    if (m_food == newFood)
        return;
    m_food = newFood;
    emit foodChanged();
}

int OrderFood::totalCost() const
{
    return (cost()*m_numberOrdered);
}
