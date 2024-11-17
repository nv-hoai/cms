#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QQmlEngine>

class Human : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(bool gender READ gender WRITE setGender NOTIFY genderChanged)
public:
    explicit Human(QObject *parent = nullptr);

    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString lastName() const;
    void setLastName(const QString &newLastName);

    int age() const;
    void setAge(int newAge);

    bool gender() const;
    void setGender(bool newGender);

signals:
    void firstNameChanged();
    void lastNameChanged();
    void ageChanged();
    void genderChanged();

private:
    QString m_firstName;
    QString m_lastName;
    int m_age;
    bool m_gender;
};

#endif // HUMAN_H
