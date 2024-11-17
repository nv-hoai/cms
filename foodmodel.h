#ifndef FOODMODEL_H
#define FOODMODEL_H

#include <QAbstractListModel>
#include "doublelinkedlist.h"
#include "food.h"

class FoodModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole,
        NameRole,
        RemainRole,
        CostRole,
        ImageSourceRole
    };

    explicit FoodModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void add(const QString& name, const int& remain, const int& cost, const QString& imageSource);
    void remove(const int& index);
    void setName(const int& index, const QString& name);
    void setRemain(const int& index, const int& remain);
    void setCost(const int& index, const int& cost);
    void setImageSource(const int& index, const QString& imageSource);

    Food* getFood(const int& id);
    int getIndexById(const int& id);

    void saveFoodData(const char* path);
private:
    DoubleLinkedList<Food*> m_foodList;
};

#endif // FOODMODEL_H
