#include "rulespage.h"

RulesPage::RulesPage(OptionsController *ctrl, QWidget *parent) : OptBasePage(ctrl, parent)
{
    setupUi();
}

void RulesPage::onSaveWindowState(IniUser * /*ini*/) { }

void RulesPage::onRestoreWindowState(IniUser * /*ini*/) { }

void RulesPage::onRetranslateUi() { }

void RulesPage::setupUi() { }
