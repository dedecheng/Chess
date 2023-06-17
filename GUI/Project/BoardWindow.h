/***********************************************************************
 * File: BoardWindow.h
 * Author: Raymin (B11132009)
 * Create date: 2023/05/11
 * Editor: Raymin (B11132009)
 * Update Date: 2023/05/17
 * Description: Chess GUI window header for game playing
 * ***********************************************************************/

#pragma once

#include "Variables.h"
#include "Game.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QString>
#include <QLabel>
#include <QUrl>
#include <QTimer>
#include <QDateTime>

class BoardWindow : public QWidget
{
	Q_OBJECT

public:
	BoardWindow(QWidget* parent = Q_NULLPTR);
	void BoardUpdate();
	void printPathBoard(const Position& pos);
	void closeWindow();
	QUrl selectPic(int i, int j);

private slots:
	void on_button_clicked();
	void on_button_surrend();

private:
	QPushButton* buttons[8][8];
	QLabel* bannerLabel;
	Game game;
	int clickTimes = 0;
	Position _before;

// For clock uses
private slots:
	void updateTime();

private:
	QLabel* timeLabel;
	QTimer* timer;
	QDateTime startTime;
};
