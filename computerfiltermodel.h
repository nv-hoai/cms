#ifndef COMPUTERFILTERMODEL_H
#define COMPUTERFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "ComputerModel.h"

class ComputerFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
public:
    explicit ComputerFilterModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    QString filterText() const;
    void setFilterText(const QString &text);

signals:
    void filterTextChanged();

private:
    QString m_filterText;
};

#endif // COMPUTERFILTERMODEL_H
