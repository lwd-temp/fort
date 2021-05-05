#ifndef FIREWALLCONF_H
#define FIREWALLCONF_H

#include <QObject>
#include <QVariant>

class AddressGroup;
class AppGroup;

#define DEFAULT_APP_GROUP_BITS         0xFFFF
#define DEFAULT_MONTH_START            1
#define DEFAULT_TRAF_HOUR_KEEP_DAYS    90 // ~3 months
#define DEFAULT_TRAF_DAY_KEEP_DAYS     365 // ~1 year
#define DEFAULT_TRAF_MONTH_KEEP_MONTHS 36 // ~3 years
#define DEFAULT_LOG_IP_KEEP_COUNT      10000

class FirewallConf : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool filterEnabled READ filterEnabled WRITE setFilterEnabled NOTIFY
                    filterEnabledChanged)
    Q_PROPERTY(bool filterLocals READ filterLocals WRITE setFilterLocals NOTIFY filterLocalsChanged)
    Q_PROPERTY(bool stopTraffic READ stopTraffic WRITE setStopTraffic NOTIFY stopTrafficChanged)
    Q_PROPERTY(bool stopInetTraffic READ stopInetTraffic WRITE setStopInetTraffic NOTIFY
                    stopInetTrafficChanged)
    Q_PROPERTY(bool allowAllNew READ allowAllNew WRITE setAllowAllNew NOTIFY allowAllNewChanged)
    Q_PROPERTY(bool logBlocked READ logBlocked WRITE setLogBlocked NOTIFY logBlockedChanged)
    Q_PROPERTY(bool logStat READ logStat WRITE setLogStat NOTIFY logStatChanged)
    Q_PROPERTY(bool logStatNoFilter READ logStatNoFilter WRITE setLogStatNoFilter NOTIFY
                    logStatNoFilterChanged)
    Q_PROPERTY(bool logAllowedIp READ logAllowedIp WRITE setLogAllowedIp NOTIFY logAllowedIpChanged)
    Q_PROPERTY(bool logBlockedIp READ logBlockedIp WRITE setLogBlockedIp NOTIFY logBlockedIpChanged)
    Q_PROPERTY(bool appBlockAll READ appBlockAll WRITE setAppBlockAll NOTIFY appBlockAllChanged)
    Q_PROPERTY(bool appAllowAll READ appAllowAll WRITE setAppAllowAll NOTIFY appAllowAllChanged)
    Q_PROPERTY(bool activePeriodEnabled READ activePeriodEnabled WRITE setActivePeriodEnabled NOTIFY
                    activePeriodEnabledChanged)

public:
    explicit FirewallConf(QObject *parent = nullptr);

    bool logDebug() const { return m_logDebug; }
    void setLogDebug(bool v) { m_logDebug = v; }

    bool logConsole() const { return m_logConsole; }
    void setLogConsole(bool v) { m_logConsole = v; }

    bool hotKeyEnabled() const { return m_hotKeyEnabled; }
    void setHotKeyEnabled(bool v) { m_hotKeyEnabled = v; }

    bool provBoot() const { return m_provBoot; }
    void setProvBoot(bool provBoot);

    bool filterEnabled() const { return m_filterEnabled; }
    void setFilterEnabled(bool filterEnabled);

    bool filterLocals() const { return m_filterLocals; }
    void setFilterLocals(bool filterLocals);

    bool stopTraffic() const { return m_stopTraffic; }
    void setStopTraffic(bool stopTraffic);

    bool stopInetTraffic() const { return m_stopInetTraffic; }
    void setStopInetTraffic(bool stopInetTraffic);

    bool allowAllNew() const { return m_allowAllNew; }
    void setAllowAllNew(bool allowAllNew);

    bool logBlocked() const { return m_logBlocked; }
    void setLogBlocked(bool logBlocked);

    bool logStat() const { return m_logStat; }
    void setLogStat(bool logStat);

    bool logStatNoFilter() const { return m_logStatNoFilter; }
    void setLogStatNoFilter(bool logStatNoFilter);

    bool logAllowedIp() const { return m_logAllowedIp; }
    void setLogAllowedIp(bool logAllowedIp);

    bool logBlockedIp() const { return m_logBlockedIp; }
    void setLogBlockedIp(bool logBlockedIp);

    bool appBlockAll() const { return m_appBlockAll; }
    void setAppBlockAll(bool appBlockAll);

    bool appAllowAll() const { return m_appAllowAll; }
    void setAppAllowAll(bool appAllowAll);

    bool activePeriodEnabled() const { return m_activePeriodEnabled; }
    void setActivePeriodEnabled(bool activePeriodEnabled);

    QString activePeriodFrom() const { return m_activePeriodFrom; }
    void setActivePeriodFrom(const QString &activePeriodFrom);

    QString activePeriodTo() const { return m_activePeriodTo; }
    void setActivePeriodTo(const QString &activePeriodTo);

    int monthStart() const { return m_monthStart; }
    void setMonthStart(int monthStart);

    int trafHourKeepDays() const { return m_trafHourKeepDays; }
    void setTrafHourKeepDays(int trafHourKeepDays);

    int trafDayKeepDays() const { return m_trafDayKeepDays; }
    void setTrafDayKeepDays(int trafDayKeepDays);

    int trafMonthKeepMonths() const { return m_trafMonthKeepMonths; }
    void setTrafMonthKeepMonths(int trafMonthKeepMonths);

    int trafUnit() const { return m_trafUnit; }
    void setTrafUnit(int trafUnit);

    int allowedIpKeepCount() const { return m_allowedIpKeepCount; }
    void setAllowedIpKeepCount(int allowedIpKeepCount);

    int blockedIpKeepCount() const { return m_blockedIpKeepCount; }
    void setBlockedIpKeepCount(int blockedIpKeepCount);

    quint32 quotaDayMb() const { return m_quotaDayMb; }
    void setQuotaDayMb(quint32 quotaDayMb);

    quint32 quotaMonthMb() const { return m_quotaMonthMb; }
    void setQuotaMonthMb(quint32 quotaMonthMb);

    quint32 appGroupBits() const;
    void setAppGroupBits(quint32 groupBits);

    AddressGroup *inetAddressGroup() const { return m_addressGroups.at(0); }

    const QList<AddressGroup *> &addressGroups() const { return m_addressGroups; }

    Q_INVOKABLE AppGroup *appGroupByName(const QString &name) const;

    const QList<AppGroup *> &appGroups() const { return m_appGroups; }

    const QList<AppGroup *> &removedAppGroupsList() const { return m_removedAppGroups; }
    void clearRemovedAppGroups() const;

    void copyImmediateFlags(const FirewallConf &o);
    void copyFlags(const FirewallConf &o);

    void copy(const FirewallConf &o);

    QVariant toVariant(bool onlyFlags = false) const;
    void fromVariant(const QVariant &v, bool onlyFlags = false);

signals:
    void provBootChanged();
    void filterEnabledChanged();
    void filterLocalsChanged();
    void stopTrafficChanged();
    void stopInetTrafficChanged();
    void allowAllNewChanged();
    void logBlockedChanged();
    void logStatChanged();
    void logStatNoFilterChanged();
    void logAllowedIpChanged();
    void logBlockedIpChanged();
    void appBlockAllChanged();
    void appAllowAllChanged();
    void activePeriodEnabledChanged();
    void activePeriodFromChanged();
    void activePeriodToChanged();
    void monthStartChanged();
    void trafHourKeepDaysChanged();
    void trafDayKeepDaysChanged();
    void trafMonthKeepMonthsChanged();
    void trafUnitChanged();
    void allowedIpKeepCountChanged();
    void blockedIpKeepCountChanged();
    void quotaDayMbChanged();
    void quotaMonthMbChanged();
    void addressGroupsChanged();
    void appGroupsChanged();

public slots:
    void addAppGroup(AppGroup *appGroup, int to = -1);
    AppGroup *addAppGroupByName(const QString &name);
    void moveAppGroup(int from, int to);
    void removeAppGroup(int from, int to);
    void addDefaultAppGroup();

    void setupDefaultAddressGroups();

private:
    void setupAddressGroups();

    QVariant immediateFlagsToVariant() const;
    void immediateFlagsFromVariant(const QVariant &v);

    QVariant flagsToVariant() const;
    void flagsFromVariant(const QVariant &v);

    QVariant addressesToVariant() const;
    void addressesFromVariant(const QVariant &v);

    QVariant appGroupsToVariant() const;
    void appGroupsFromVariant(const QVariant &v);

private:
    bool m_logDebug : 1;
    bool m_logConsole : 1;
    bool m_hotKeyEnabled : 1;

    bool m_provBoot : 1;
    bool m_filterEnabled : 1;
    bool m_filterLocals : 1;
    bool m_stopTraffic : 1;
    bool m_stopInetTraffic : 1;
    bool m_allowAllNew : 1;

    bool m_logBlocked : 1;
    bool m_logStat : 1;
    bool m_logStatNoFilter : 1;

    bool m_logAllowedIp : 1;
    bool m_logBlockedIp : 1;

    bool m_appBlockAll : 1;
    bool m_appAllowAll : 1;

    bool m_activePeriodEnabled : 1;

    int m_monthStart = DEFAULT_MONTH_START;

    int m_trafHourKeepDays = DEFAULT_TRAF_HOUR_KEEP_DAYS;
    int m_trafDayKeepDays = DEFAULT_TRAF_DAY_KEEP_DAYS;
    int m_trafMonthKeepMonths = DEFAULT_TRAF_MONTH_KEEP_MONTHS;

    int m_trafUnit = 0;

    int m_allowedIpKeepCount = DEFAULT_LOG_IP_KEEP_COUNT;
    int m_blockedIpKeepCount = DEFAULT_LOG_IP_KEEP_COUNT;

    quint32 m_quotaDayMb = 0;
    quint32 m_quotaMonthMb = 0;

    QString m_activePeriodFrom;
    QString m_activePeriodTo;

    QList<AddressGroup *> m_addressGroups;
    QList<AppGroup *> m_appGroups;
    mutable QList<AppGroup *> m_removedAppGroups;
};

#endif // FIREWALLCONF_H
