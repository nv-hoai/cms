#include "computermodel.h"
#include <QFile>
#include <QTextStream>

ComputerModel::ComputerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ComputerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_computerList.getSize();
}

QVariant ComputerModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_computerList.getSize()) {
        Computer* computer = m_computerList[index.row()];

        switch((Role)role) {
        case IdRole:
            return computer->id();
        case CpuRole:
            return computer->cpu();
        case RamRole:
            return computer->ram();
        case PositionRole:
            return computer->position();
        case StatusRole:
            return computer->status();
        case CostRole:
            return computer->cost();
        }
    }

    return {};
}

bool ComputerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (m_computerList.getSize() == 0)
        return false;

    Computer* computer = m_computerList[index.row()];
    QVariant previousValue;

    switch((Role)role) {
    case IdRole:
        //never happen
        break;
    case CpuRole:
        previousValue = computer->cpu();
        computer->setCpu(value.toString());
        break;
    case RamRole:
        previousValue = computer->ram();
        computer->setRam(value.toInt());
        break;
    case PositionRole:
        previousValue = computer->position();
        computer->setPosition(value.toInt());
        break;
    case StatusRole:
        previousValue = computer->status();
        computer->setStatus(value.toInt());
        break;
    case CostRole:
        previousValue = computer->cost();
        computer->setCost(value.toDouble());
        break;
    }

    if (data(index, role) != previousValue) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ComputerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ComputerModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[IdRole] = "id";
    result[CpuRole] = "cpu";
    result[RamRole] = "ram";
    result[PositionRole] = "position";
    result[StatusRole] = "status";
    result[CostRole] = "cost";

    return result;
}

Computer *ComputerModel::getComputer(const int &id)
{
    for(auto it=m_computerList.begin(); it!=m_computerList.end(); ++it) {
        if (id == (*it)->id())
            return (*it);
    }
    return nullptr;
}

bool ComputerModel::posIsOccupied(const int &position)
{
    for(auto it=m_computerList.begin(); it!=m_computerList.end(); ++it) {
        if ((*it)->position() == position)
            return true;
    }
    return false;
}

int ComputerModel::getIndexById(const int &id)
{
    int index = 0;
    for(auto it=m_computerList.begin(); it!=m_computerList.end(); ++it) {
        if ((*it)->id() == id)
            return index;
        ++index;
    }

    return -1;
}

void ComputerModel::saveComputerData(const char *path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream out(&file);
    for (auto it=m_computerList.begin(); it!=m_computerList.end(); ++it) {
        out << (*it)->cpu() << ";";
        out << (*it)->ram() << ";";
        out << (*it)->position() << ";";
        out << (((*it)->status()!=2)?0:2) << ";";
        out << (*it)->cost(); Qt::endl(out);
    }

    file.close();
}

void ComputerModel::add(const QString &cpu, const int &ram, int position, const int &status, const int &cost)
{
    beginInsertRows(QModelIndex(), m_computerList.getSize(), m_computerList.getSize());
    Computer* computer = new Computer(this);
    if (position == 0)
        position = computer->id();
    computer->setCpu(cpu);
    computer->setCost(cost);
    computer->setRam(ram);
    computer->setPosition(position);
    computer->setStatus(status);
    m_computerList.append(computer);
    endInsertRows();
}

void ComputerModel::remove(const int &index)
{
    if (index >= 0 && index < m_computerList.getSize()) {
        beginRemoveRows(QModelIndex(), index, index);
        Computer* toRemove = m_computerList[index];
        m_computerList.remove(toRemove);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

void ComputerModel::setCpu(const int &index, const QString &cpu)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, cpu, CpuRole);
}

void ComputerModel::setRam(const int &index, const int &ram)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, ram, RamRole);
}

void ComputerModel::setPosition(const int &index, const int &position)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, position, PositionRole);
}

void ComputerModel::setStatus(const int &index, const int &status)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, status, StatusRole);
}

void ComputerModel::setCost(const int &index, const int &cost)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, cost, CostRole);
}
