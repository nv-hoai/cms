#include "receiptmodel.h"

ReceiptModel::ReceiptModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ReceiptModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_receiptList.getSize();
}

QVariant ReceiptModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_receiptList.getSize()) {
        Receipt* receipt = m_receiptList[index.row()];

        switch((Role)role) {
        case IdRole:
            return receipt->id();
        case CreatedTimeRole:
            return receipt->createdTime();
        case PaidTimeRole:
            return receipt->paidTime();
        case StatusRole:
            return receipt->status();
        case TotalChargeRole:
            return receipt->totalCharge();
        case CustomerRole:
            return QVariant::fromValue(receipt->customer());
        }
    }

    return {};
}

bool ReceiptModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (m_receiptList.getSize() == 0)
        return false;

    Receipt* receipt = m_receiptList[index.row()];
    QVariant previousValue;

    switch((Role)role) {
    case StatusRole:
        previousValue = receipt->status();
        receipt->setStatus(value.toBool());
        break;
    case PaidTimeRole:
        previousValue = receipt->paidTime();
        receipt->setPaidTime(QTime::currentTime().toString());
        break;
    }

    if (data(index, role) != previousValue) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ReceiptModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ReceiptModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[IdRole] = "id";
    result[CreatedTimeRole] = "createdTime";
    result[PaidTimeRole] = "paidTime";
    result[StatusRole] = "status";
    result[TotalChargeRole] = "totalCharge";
    result[CustomerRole] = "customer";

    return result;
}

void ReceiptModel::add(const int& customerId, DoubleLinkedList<Service*> &serviceList)
{
    beginInsertRows(QModelIndex(), m_receiptList.getSize(), m_receiptList.getSize());
    Receipt* receipt = new Receipt(this);
    receipt->receiveServiceList(customerId, serviceList);
    m_receiptList.append(receipt);
    endInsertRows();
}

void ReceiptModel::remove(const int &index)
{
    if (index >= 0 && index < m_receiptList.getSize()) {
        beginRemoveRows(QModelIndex(), index, index);
        Receipt* toRemove = m_receiptList[index];
        m_receiptList.remove(toRemove);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

Service *ReceiptModel::getService(const int &receiptIndex, const int &serviceIndex)
{
    if (receiptIndex >= 0 && receiptIndex < m_receiptList.getSize()) {
        Receipt* receipt = m_receiptList[receiptIndex];
        return receipt->getService(serviceIndex);
    }
    return nullptr;
}

int ReceiptModel::serviceNumber(const int &receiptIndex)
{
    if (receiptIndex >= 0 && receiptIndex < m_receiptList.getSize()) {
        Receipt* receipt = m_receiptList[receiptIndex];
        return receipt->serviceNumber();
    }
    return 0;
}

void ReceiptModel::saveReceiptData(const char *path)
{

}
