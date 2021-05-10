#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

namespace Control {

enum Command : qint8 {
    CommandNone = 0,
    Conf,
    Prog,
    Rpc_Result_Ok,
    Rpc_Result_Error,
    Rpc_RpcManager_initClient,
    Rpc_AppInfoManager_lookupAppInfo,
    Rpc_AppInfoManager_checkLookupFinished,
    Rpc_ConfManager_onConfChanged,
    Rpc_ConfManager_save,
    Rpc_ConfManager_saveResult,
    Rpc_DriverManager_updateState,
    Rpc_DriverManager_reinstallDriver,
    Rpc_DriverManager_uninstallDriver,
    Rpc_QuotaManager_alert,
    Rpc_StatManager_appCreated,
    Rpc_StatManager_trafficAdded,
    Rpc_TaskManager_taskStarted,
    Rpc_TaskManager_taskFinished,
    Rpc_TaskManager_runTask,
    Rpc_TaskManager_abortTask,
};

}

#endif // CONTROL_H
