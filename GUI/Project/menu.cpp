/***********************************************************************
 * File: menu.cpp
 * Author: Raymin (B11132009)
 * Create date: 2023/05/11
 * Editor: Raymin (B11132009)
 * Update Date: 2023/05/17
 * Description: Chess GUI window cpp file for menu
 * ***********************************************************************/

#include "menu.h"

 // Intent: Menu Constructor
 // Pre: Construct all item in window
 // Post: Item in window is intialized
Menu::Menu(QWidget* parent)
	: QWidget(parent)
{
	QGridLayout* gridLayout = new QGridLayout(this);
	btn = new QPushButton("Clicked to start the game", this);
	btn->setStyleSheet("QPushButton { background-color: blue; color: white; }"
		"QPushButton:hover { background-color: red; }"
		"QPushButton:pressed { background-color: green; }");
	connect(btn, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	gridLayout->addWidget(btn, 0, 0);

	/// Button ///
	QHBoxLayout* hLoadLayout = new QHBoxLayout;
	QPushButton* btn1 = new QPushButton("White First", this);
	QPushButton* btn2 = new QPushButton("Black First", this);

	connect(btn1, &QPushButton::clicked, []() {whoFirst = 1; qDebug() << "You Choose White First";}); // 0->white, 1->black
	connect(btn2, &QPushButton::clicked, []() {whoFirst = 0; qDebug() << "You Choose Black First"; });

	// 设置按钮的样式
	// 将按钮添加到布局中
	hLoadLayout->addWidget(btn1);
	hLoadLayout->addWidget(btn2);

	gridLayout->addLayout(hLoadLayout, 1 ,0);

	/// Picture ///
	QPixmap pixmap("Picture/animate.png");
	QLabel* label = new QLabel;
	label->setPixmap(pixmap);
	label->setFixedSize(300, 200); // 设置宽度和高度
	label->setScaledContents(true);
	gridLayout->addWidget(label, 2, 0);
}

// Intent: Proccess Click event
// Pre: button is connected
// Post: Show boardWindow, and hide Menu
void Menu::on_button_clicked() {
	boardWindow = new BoardWindow();
	boardWindow->show();
	this->hide();
}