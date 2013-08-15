/********************************************************************************
** Form generated from reading UI file 'TortoiseDialog.ui'
**
** Created: Thu Aug 15 14:53:00 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TORTOISEDIALOG_H
#define UI_TORTOISEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TortoiseDialog
{
public:
    QLabel *label;

    void setupUi(QWidget *TortoiseDialog)
    {
        if (TortoiseDialog->objectName().isEmpty())
            TortoiseDialog->setObjectName(QString::fromUtf8("TortoiseDialog"));
        TortoiseDialog->resize(400, 300);
        label = new QLabel(TortoiseDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 130, 161, 31));
        QFont font;
        font.setPointSize(17);
        label->setFont(font);

        retranslateUi(TortoiseDialog);

        QMetaObject::connectSlotsByName(TortoiseDialog);
    } // setupUi

    void retranslateUi(QWidget *TortoiseDialog)
    {
        TortoiseDialog->setWindowTitle(QApplication::translate("TortoiseDialog", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TortoiseDialog", "Hello World", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TortoiseDialog: public Ui_TortoiseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TORTOISEDIALOG_H
