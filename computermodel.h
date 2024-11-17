#ifndef COMPUTERMODEL_H
#define COMPUTERMODEL_H

#include <QAbstractListModel>
#include "doublelinkedlist.h"
#include "computer.h"

class ComputerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole,
        CpuRole,
        RamRole,
        PositionRole,
        StatusRole,
        CostRole
    };

    explicit ComputerModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void add(const QString& cpu, const int& ram, int position, const int& status, const int& cost);
    void remove(const int& index);
    void setCpu(const int& index, const QString& cpu);
    void setRam(const int& index, const int& ram);
    void setPosition(const int& index, const int& position);
    void setStatus(const int& index, const int& status);
    void setCost(const int& index, const int& cost);

    Computer* getComputer(const int& id);
    bool posIsOccupied(const int& position);
    int getIndexById(const int& id);

    void saveComputerData(const char* path);
private:
    DoubleLinkedList<Computer*> m_computerList;
};

#endif // COMPUTERMODEL_H
