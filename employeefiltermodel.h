#ifndef EMPLOYEEFILTERMODEL_H
#define EMPLOYEEFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "EmployeeModel.h"

class EmployeeFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
public:
    explicit EmployeeFilterModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    QString filterText() const;
    void setFilterText(const QString &text);

signals:
    void filterTextChanged();

private:
    QString m_filterText;
};

#endif // EMPLOYEEFILTERMODEL_H
