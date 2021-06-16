/********************************************************************************
** Form generated from reading UI file 'map_preview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP_PREVIEW_H
#define UI_MAP_PREVIEW_H

#include <QtCore/QVariant>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_map_preview
{
public:
    QQuickWidget *quickWidget;

    void setupUi(QWidget *map_preview)
    {
        if (map_preview->objectName().isEmpty())
            map_preview->setObjectName(QStringLiteral("map_preview"));
        map_preview->resize(769, 391);
        quickWidget = new QQuickWidget(map_preview);
        quickWidget->setObjectName(QStringLiteral("quickWidget"));
        quickWidget->setGeometry(QRect(-1, -1, 761, 401));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        retranslateUi(map_preview);

        QMetaObject::connectSlotsByName(map_preview);
    } // setupUi

    void retranslateUi(QWidget *map_preview)
    {
        map_preview->setWindowTitle(QApplication::translate("map_preview", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class map_preview: public Ui_map_preview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP_PREVIEW_H
