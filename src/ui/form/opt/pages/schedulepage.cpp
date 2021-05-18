#include "schedulepage.h"

#include <QCheckBox>
#include <QDate>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QSpinBox>
#include <QTableView>
#include <QVBoxLayout>

#include "../../../conf/firewallconf.h"
#include "../../../task/taskinfo.h"
#include "../../../task/tasklistmodel.h"
#include "../../../task/taskmanager.h"
#include "../../controls/checkspincombo.h"
#include "../../controls/controlutil.h"
#include "../../controls/tableview.h"
#include "../optionscontroller.h"

namespace {

const ValuesList taskIntervalHourValues = { 3, 1, 6, 12, 24, 24 * 7, 24 * 30 };

}

SchedulePage::SchedulePage(OptionsController *ctrl, QWidget *parent) :
    OptBasePage(ctrl, parent), m_taskListModel(new TaskListModel(taskManager(), this))
{
    setupUi();
}

void SchedulePage::setTaskEdited()
{
    if (!m_taskEdited) {
        m_taskEdited = true;
        ctrl()->setIniEdited();
    }
}

void SchedulePage::onAboutToSave()
{
    if (taskEdited()) {
        ini()->setTaskInfoList(taskListModel()->toVariant());
    }
}

void SchedulePage::onEditResetted()
{
    m_taskEdited = false;

    taskListModel()->setupTaskRows();
}

void SchedulePage::onRetranslateUi()
{
    taskListModel()->refresh();

    m_btTaskRun->setText(tr("Run"));
    m_btTaskAbort->setText(tr("Abort"));

    retranslateTaskDetails();
}

void SchedulePage::retranslateTaskDetails()
{
    const QStringList list = { tr("Custom"), tr("Hourly"), tr("Each 6 hours"), tr("Each 12 hours"),
        tr("Daily"), tr("Weekly"), tr("Monthly") };

    m_cscTaskInterval->setNames(list);
    m_cscTaskInterval->spinBox()->setSuffix(tr(" hour(s)"));
}

void SchedulePage::setupUi()
{
    auto layout = new QVBoxLayout();

    // Task Details
    setupTaskDetails();

    // Tasks Table
    setupTableTasks();
    setupTableTasksHeader();

    // Actions on tasks table's current changed
    setupTableTasksChanged();

    layout->addWidget(m_taskDetailsRow);
    layout->addWidget(m_tableTasks, 1);

    this->setLayout(layout);
}

void SchedulePage::setupTableTasks()
{
    m_tableTasks = new TableView();
    m_tableTasks->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableTasks->setSelectionBehavior(QAbstractItemView::SelectItems);

    m_tableTasks->setModel(taskListModel());

    connect(m_tableTasks, &TableView::doubleClicked, this, [&](const QModelIndex &index) {
        const auto taskInfo = taskListModel()->taskInfoAt(index.row());
        emit taskManager()->taskDoubleClicked(taskInfo->type());
    });
}

void SchedulePage::setupTableTasksHeader()
{
    auto header = m_tableTasks->horizontalHeader();

    header->setSectionResizeMode(0, QHeaderView::Fixed);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);
    header->setSectionResizeMode(3, QHeaderView::Stretch);

    const auto refreshTableTasksHeader = [&] {
        auto hh = m_tableTasks->horizontalHeader();
        hh->resizeSection(0, qRound(hh->width() * 0.45));
    };

    refreshTableTasksHeader();

    connect(header, &QHeaderView::geometriesChanged, this, refreshTableTasksHeader);
}

void SchedulePage::setupTaskDetails()
{
    m_taskDetailsRow = new QWidget();

    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    m_taskDetailsRow->setLayout(layout);

    setupTaskInterval();

    m_btTaskRun = ControlUtil::createButton(
            ":/icons/sign-sync.png", [&] { taskManager()->runTask(currentTaskInfo()->type()); });
    m_btTaskAbort = ControlUtil::createButton(
            ":/icons/sign-error.png", [&] { taskManager()->abortTask(currentTaskInfo()->type()); });

    layout->addWidget(m_cscTaskInterval, 1);
    layout->addWidget(m_btTaskRun);
    layout->addWidget(m_btTaskAbort);
}

void SchedulePage::setupTaskInterval()
{
    m_cscTaskInterval = new CheckSpinCombo();
    m_cscTaskInterval->checkBox()->setFont(ControlUtil::fontDemiBold());
    m_cscTaskInterval->spinBox()->setRange(1, 24 * 30 * 12); // ~Year
    m_cscTaskInterval->setValues(taskIntervalHourValues);

    connect(m_cscTaskInterval->checkBox(), &QCheckBox::toggled, this, [&](bool checked) {
        const int taskIndex = currentTaskIndex();
        const auto index = taskListModel()->index(taskIndex, 0);

        taskListModel()->setData(index, checked, TaskListModel::RoleEnabled);
    });
    connect(m_cscTaskInterval->spinBox(), QOverload<int>::of(&QSpinBox::valueChanged), this,
            [&](int value) {
                const int taskIndex = currentTaskIndex();
                const auto index = taskListModel()->index(taskIndex, 1);

                taskListModel()->setData(index, value, TaskListModel::RoleIntervalHours);
            });
}

void SchedulePage::setupTableTasksChanged()
{
    const auto refreshTableTasksChanged = [&] {
        const int taskIndex = currentTaskIndex();
        const bool taskSelected = taskIndex >= 0;

        setCurrentTaskInfo(taskSelected ? taskListModel()->taskInfoAt(taskIndex) : nullptr);
        m_taskDetailsRow->setEnabled(taskSelected);

        if (taskSelected) {
            const auto index = taskListModel()->index(taskIndex, 0);

            m_cscTaskInterval->checkBox()->setChecked(
                    taskListModel()->data(index, TaskListModel::RoleEnabled).toBool());
            m_cscTaskInterval->checkBox()->setText(taskListModel()->data(index).toString());
            m_cscTaskInterval->spinBox()->setValue(
                    taskListModel()->data(index, TaskListModel::RoleIntervalHours).toInt());

            const bool running = currentTaskInfo()->running();
            m_btTaskRun->setEnabled(!running);
            m_btTaskAbort->setEnabled(running);
        } else {
            m_cscTaskInterval->checkBox()->setText(QString());
        }
    };

    refreshTableTasksChanged();

    connect(m_tableTasks, &TableView::currentIndexChanged, this, refreshTableTasksChanged);
    connect(taskListModel(), &TaskListModel::dataChanged, this, refreshTableTasksChanged);

    connect(taskListModel(), &TaskListModel::dataEdited, this, &SchedulePage::setTaskEdited);
}

int SchedulePage::currentTaskIndex() const
{
    return m_tableTasks->currentRow();
}
