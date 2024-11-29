#ifndef RECEIPTMODEL_H
#define RECEIPTMODEL_H

#include <QAbstractListModel>
#include "doublelinkedlist.h"
#include "hirecomputer.h"
#include "orderfood.h"
#include "receipt.h"

class ReceiptModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole,
        CreatedTimeRole,
        PaidTimeRole,
        StatusRole,
        TotalChargeRole,
        CustomerRole
    };

    explicit ReceiptModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    DoubleLinkedList<Service*>& serviceList(const int& receiptIndex);
public slots:
    void add(const int& customerId, DoubleLinkedList<Service*> &serviceList);
    void remove(const int& index);

    Service* getService(const int& receiptIndex, const int& serviceIndex);
    HireComputer* toHireComputer(Service* sv);
    OrderFood* toOrderFood(Service* sv);
    Receipt* getReceipt(const int& index);
    int serviceNumber(const int& receiptIndex);

    void saveReceiptData(const char* path);
private:
    DoubleLinkedList<Receipt*> m_receiptList;
};

#endif // RECEIPTMODEL_H
