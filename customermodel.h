#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include <QAbstractListModel>
#include "doublelinkedlist.h"
#include "customer.h"

class CustomerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole,
        FirstNameRole,
        LastNameRole,
        AgeRole,
        GenderRole,
        StatusRole
    };

    explicit CustomerModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void add(const QString& firstName, const QString& lastName, const int& age, const bool& gender);
    void remove(const int& index);
    void setCustomerFirstName(const int& index, const QString& firstName);
    void setCustomerLastName(const int& index, const QString& lastName);
    void setCustomerAge(const int& index, const int& age);
    void setCustomerGender(const int& index, const bool& gender);
    void setStatus(const int& index, const int& status);

    Customer* getCustomer(const int& id);
    int getIndexById(const int& id);

    void saveCustomerData(const char* path);
private:
    DoubleLinkedList<Customer*> m_customerList;
};

#endif // CUSTOMERMODEL_H
