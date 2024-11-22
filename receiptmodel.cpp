#include "receiptmodel.h"
#include <QFile>
#include <QTextStream>

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

DoubleLinkedList<Service *> &ReceiptModel::serviceList(const int &receiptIndex)
{
    return m_receiptList[receiptIndex]->serviceList();
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

Receipt *ReceiptModel::getReceipt(const int &index)
{
    return m_receiptList[index];
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
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream out(&file);
    DoubleLinkedList<Service*> *ptServiceList;
    for (auto it=m_receiptList.begin(); it!=m_receiptList.end(); ++it) {
        if ((*it)->status()) {
            out << "ID: " << (*it)->id(); Qt::endl(out);
            out << "Created time: "  << (*it)->createdTime() << " Paid time: " << (*it)->paidTime(); Qt::endl(out);
            out << "Customer's name: " << (*it)->customer()->firstName() + " " + (*it)->customer()->lastName();
            out << " Customer's age: " << (*it)->customer()->age(); Qt::endl(out);
            out << "List of services used: "; Qt::endl(out);
            ptServiceList = &(*it)->serviceList();
            for(auto sv=ptServiceList->begin(); sv!=ptServiceList->end(); ++sv) {
                if ((*sv)->status()) {
                    out << "Service's ID: " << (*sv)->id() << " Service's name: " << (*sv)->serviceName(); Qt::endl(out);
                    if ((*sv)->serviceName() == "Hire computer") {
                        HireComputer* hc = (HireComputer*)(*sv);
                        out << "Computer's ID: " << hc->computer()->id() << " Time used: " << hc->timeUsed() << " Cost per hour: " << hc->cost(); Qt::endl(out);
                    } else {
                        OrderFood* of = (OrderFood*)(*sv);
                        out << "Food's ID: " << of->food()->id() << " Number ordered: " << of->numberOrdered() << " Cost each: " << of->cost(); Qt::endl(out);
                    }
                }
            }
            out << "Total charge: " << (*it)->totalCharge(); Qt::endl(out);
        }
    }

    file.close();
}
