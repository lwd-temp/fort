#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QFrame>

QT_FORWARD_DECLARE_CLASS(QCheckBox)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QPushButton)

QT_FORWARD_DECLARE_CLASS(DriverManager)
QT_FORWARD_DECLARE_CLASS(FirewallConf)
QT_FORWARD_DECLARE_CLASS(FortManager)
QT_FORWARD_DECLARE_CLASS(FortSettings)
QT_FORWARD_DECLARE_CLASS(OptionsController)
QT_FORWARD_DECLARE_CLASS(TaskManager)
QT_FORWARD_DECLARE_CLASS(TranslationManager)

class BasePage : public QFrame
{
    Q_OBJECT

public:
    explicit BasePage(OptionsController *ctrl,
                      QWidget *parent = nullptr);

protected:
    OptionsController *ctrl() const { return m_ctrl; }
    FortManager *fortManager() const;
    FortSettings *settings() const;
    FirewallConf *conf() const;
    DriverManager *driverManager() const;
    TranslationManager *translationManager() const;
    TaskManager *taskManager() const;

protected slots:
    virtual void onEditResetted() {}
    virtual void onAboutToSave() {}
    virtual void onSaved() {}

    virtual void onRetranslateUi() {}

private:
    void setupController();

private:
    OptionsController *m_ctrl = nullptr;
};

#endif // BASEPAGE_H
