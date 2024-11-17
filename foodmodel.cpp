#include <QFile>
#include <QTextStream>
#include "foodmodel.h"

FoodModel::FoodModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int FoodModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_foodList.getSize();
}

QVariant FoodModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_foodList.getSize()) {
        Food* food = m_foodList[index.row()];

        switch((Role)role) {
        case IdRole:
            return food->id();
        case NameRole:
            return food->name();
        case RemainRole:
            return food->remain();
        case CostRole:
            return food->cost();
        case ImageSourceRole:
            return food->imageSource();
        }
    }

    return {};
}

bool FoodModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (m_foodList.getSize() == 0)
        return false;

    Food* food = m_foodList[index.row()];
    QVariant previousValue;

    switch((Role)role) {
    case IdRole:
        //never happen
        break;
    case NameRole:
        previousValue = food->name();
        food->setName(value.toString());
        break;
    case RemainRole:
        previousValue = food->remain();
        food->setRemain(value.toInt());
        break;
    case CostRole:
        previousValue = food->cost();
        food->setCost(value.toDouble());
        break;
    case ImageSourceRole:
        previousValue = food->imageSource();
        food->setImageSource(value.toString());
    }

    if (data(index, role) != previousValue) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags FoodModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> FoodModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[IdRole] = "id";
    result[NameRole] = "name";
    result[RemainRole] = "remain";
    result[CostRole] = "cost";
    result[ImageSourceRole] = "imageSource";

    return result;
}

Food *FoodModel::getFood(const int &id)
{
    for(auto it=m_foodList.begin(); it!=m_foodList.end(); ++it) {
        if (id == (*it)->id())
            return (*it);
    }
    return nullptr;
}

int FoodModel::getIndexById(const int &id)
{
    int index = 0;
    for(auto it=m_foodList.begin(); it!=m_foodList.end(); ++it) {
        if ((*it)->id() == id)
            return index;
        ++index;
    }

    return -1;
}

void FoodModel::saveFoodData(const char *path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream out(&file);
    for (auto it=m_foodList.begin(); it!=m_foodList.end(); ++it) {
        out << (*it)->name() << ";";
        out << (*it)->remain() << ";";
        out << (*it)->cost() << ";";
        out << (*it)->imageSource(); Qt::endl(out);
    }

    file.close();
}

void FoodModel::add(const QString &name, const int &remain, const int &cost, const QString& imageSource)
{
    beginInsertRows(QModelIndex(), m_foodList.getSize(), m_foodList.getSize());
    Food* food = new Food(this);
    food->setName(name);
    food->setRemain(remain);
    food->setCost(cost);
    food->setImageSource(imageSource);
    m_foodList.append(food);
    endInsertRows();
}

void FoodModel::remove(const int &index)
{
    if (index >= 0 && index < m_foodList.getSize()) {
        beginRemoveRows(QModelIndex(), index, index);
        Food* toRemove = m_foodList[index];
        m_foodList.remove(toRemove);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

void FoodModel::setName(const int &index, const QString &name)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, name, NameRole);
}

void FoodModel::setRemain(const int &index, const int &remain)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, remain, RemainRole);
}

void FoodModel::setCost(const int &index, const int &cost)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, cost, CostRole);
}

void FoodModel::setImageSource(const int &index, const QString &imageSource)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, imageSource, ImageSourceRole);
}


