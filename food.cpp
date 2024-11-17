#include "food.h"

int Food::foodCount = 1;

Food::Food(QObject *parent)
    : QObject{parent}
{
    m_id = foodCount++;
}

int Food::cost() const
{
    return m_cost;
}

void Food::setCost(int newCost)
{
    if (m_cost == newCost)
        return;
    m_cost = newCost;
    emit costChanged();
}

int Food::remain() const
{
    return m_remain;
}

void Food::setRemain(int newRemain)
{
    if (m_remain == newRemain)
        return;
    m_remain = newRemain;
    emit remainChanged();
}

QString Food::name() const
{
    return m_name;
}

void Food::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int Food::id() const
{
    return m_id;
}

QString Food::imageSource() const
{
    return m_imageSource;
}

void Food::setImageSource(const QString &newImageSource)
{
    if (m_imageSource == newImageSource)
        return;
    m_imageSource = newImageSource;
    emit imageSourceChanged();
}
