/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit_W;
    QTextEdit *textEdit_E;
    QTextEdit *textEdit_N;
    QTextEdit *textEdit_S;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *textEdit_zoom;
    QLabel *label_5;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textEdit_W = new QTextEdit(centralwidget);
        textEdit_W->setObjectName(QStringLiteral("textEdit_W"));
        textEdit_W->setGeometry(QRect(60, 100, 141, 71));
        textEdit_E = new QTextEdit(centralwidget);
        textEdit_E->setObjectName(QStringLiteral("textEdit_E"));
        textEdit_E->setGeometry(QRect(410, 100, 141, 71));
        textEdit_N = new QTextEdit(centralwidget);
        textEdit_N->setObjectName(QStringLiteral("textEdit_N"));
        textEdit_N->setGeometry(QRect(240, 10, 141, 71));
        textEdit_S = new QTextEdit(centralwidget);
        textEdit_S->setObjectName(QStringLiteral("textEdit_S"));
        textEdit_S->setGeometry(QRect(240, 210, 141, 71));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 170, 81, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(460, 170, 81, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(280, 80, 81, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(290, 280, 81, 31));
        textEdit_zoom = new QTextEdit(centralwidget);
        textEdit_zoom->setObjectName(QStringLiteral("textEdit_zoom"));
        textEdit_zoom->setGeometry(QRect(240, 310, 141, 71));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(290, 380, 54, 12));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 410, 561, 61));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(250, 490, 182, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\245\277\347\273\217\357\274\210\350\264\237\346\225\260\357\274\211", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\344\270\234\347\273\217", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\214\227\347\272\254", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\215\227\347\272\254\357\274\210\350\264\237\346\225\260\357\274\211", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Zoom", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "stop", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "start", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "clear", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "preview", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
