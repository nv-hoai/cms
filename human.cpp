#include "human.h"

Human::Human(QObject *parent)
    : QObject{parent}
{}

QString Human::firstName() const
{
    return m_firstName;
}

void Human::setFirstName(const QString &newFirstName)
{
    if (m_firstName == newFirstName)
        return;
    m_firstName = newFirstName;
    emit firstNameChanged();
}

QString Human::lastName() const
{
    return m_lastName;
}

void Human::setLastName(const QString &newLastName)
{
    if (m_lastName == newLastName)
        return;
    m_lastName = newLastName;
    emit lastNameChanged();
}

int Human::age() const
{
    return m_age;
}

void Human::setAge(int newAge)
{
    if (m_age == newAge)
        return;
    m_age = newAge;
    emit ageChanged();
}

bool Human::gender() const
{
    return m_gender;
}

void Human::setGender(bool newGender)
{
    if (m_gender == newGender)
        return;
    m_gender = newGender;
    emit genderChanged();
}
