/***********************************************************************
 * File: menu.h
 * Author: Raymin (B11132009)
 * Create date: 2023/05/11
 * Editor: Raymin (B11132009)
 * Update Date: 2023/05/17
 * Description: Chess GUI menu window header
 * ***********************************************************************/

#pragma once

#include "BoardWindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QString>
#include <QLabel>
#include <QUrl>


class Menu : public QWidget
{
	Q_OBJECT

public:
	Menu(QWidget* parent = Q_NULLPTR);

private slots:
	void on_button_clicked();

private:
	BoardWindow* boardWindow;
	QPushButton* btn;
};


