#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QVector>

#include "../util/model/tableitemmodel.h"
#include "taskeditinfo.h"

class TaskInfo;
class TaskManager;

class TaskListModel : public TableItemModel
{
    Q_OBJECT

public:
    enum Roles { RoleEnabled = Qt::UserRole, RoleIntervalHours, RoleRunning };
    Q_ENUM(Roles)

    explicit TaskListModel(TaskManager *taskManager, QObject *parent = nullptr);

    TaskManager *taskManager() const { return m_taskManager; }

    const QList<TaskInfo *> &taskInfoList() const;
    TaskInfo *taskInfoAt(int row) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(
            int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void setupTaskRows();

    QVariant toVariant() const;

signals:
    void dataEdited();

private:
    QVariant dataDisplay(const QModelIndex &index) const;
    QVariant dataCheckState(const QModelIndex &index) const;

    bool taskEnabled(int row) const;
    void setTaskEnabled(const QModelIndex &index, bool v);

    int taskIntervalHours(int row) const;
    void setTaskIntervalHours(const QModelIndex &index, int v);

    TaskEditInfo &taskRowAt(int row) { return m_taskRows[row]; }
    const TaskEditInfo &taskRowAt(int row) const { return m_taskRows[row]; }

    static QString formatDateTime(const QDateTime &dateTime);

private:
    TaskManager *m_taskManager = nullptr;

    QVector<TaskEditInfo> m_taskRows;
};

#endif // TASKLISTMODEL_H
