/***********************************************************************
 * File: BoardWindow.cpp
 * Author: Raymin (B11132009)
 * Create date: 2023/05/11
 * Editor: Raymin (B11132009)
 * Update Date: 2023/05/17
 * Description: Chess GUI window cpp file for game playing
 * ***********************************************************************/

#include "BoardWindow.h"

// Size
const int BUTTONSIZE = 8;
 
/// Picture URL ///
QUrl pic_bishop = "Picture/bishop.png";
QUrl pic_bishop1 = "Picture/bishop1.png";
QUrl pic_horse = "Picture/horse.png";
QUrl pic_horse1 = "Picture/horse1.png";
QUrl pic_king = "Picture/king.png";
QUrl pic_king1 = "Picture/king1.png";
QUrl pic_pawn = "Picture/pawn.png"; // 小兵
QUrl pic_pawn1 = "Picture/pawn1.png"; 
QUrl pic_queen = "Picture/queen.png";
QUrl pic_queen1 = "Picture/queen1.png";
QUrl pic_rook = "Picture/rook.png";  // 堡壘
QUrl pic_rook1 = "Picture/rook1.png";
QUrl pic_empty = "Picture/Empty.png";

// Intent: BoardWindow Constructor
// Pre: Construct all item in BoardWindow
// Post: Item in BoardWindow is intialized
BoardWindow::BoardWindow(QWidget* parent)
    : QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout(this);

    // Add Banner (0,0)
    bannerLabel = new QLabel("Play Chess Game");
    bannerLabel->setAlignment(Qt::AlignCenter);
    bannerLabel->setFixedHeight(70);
    QFont font("Arial", 16, QFont::Bold);
    bannerLabel->setStyleSheet("background-color:#FFFDD0;");
    bannerLabel->setFont(font);
    gridLayout->addWidget(bannerLabel, 0, 0, 1, BUTTONSIZE); // Added row span and column span

    // Add resign button at (1,0)
    QPushButton* btn_resign = new QPushButton("Resigned");
    btn_resign->setFixedHeight(50);
    btn_resign->setStyleSheet("font-weight:bold;");
    connect(btn_resign, SIGNAL(clicked()), this, SLOT(on_button_surrend()));
    gridLayout->addWidget(btn_resign, 1, 0, 1, 2); // Adjusted row index to accommodate the banner

    ////////////
    // Add clock at (1,8)
    // 创建标签来显示计时器的时间
    timeLabel = new QLabel(this);
    timeLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(timeLabel, 1, 6, 1, 2);

    // 创建计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BoardWindow::updateTime);

    // 设置计时器间隔为1秒
    timer->setInterval(1000);

    // 启动计时器
    timer->start();
    startTime = QDateTime::currentDateTime();
    timeLabel->setStyleSheet("background-color: lightGray; border: 2px solid darkGray; border-radius: 5px; font-weight: bold; font-size: 24px;");
    ///////////////////////////
    
    // Set up the board at (2,0)
    for (int i = 0; i < BUTTONSIZE; i++) {
        for (int j = 0; j < BUTTONSIZE; j++) {
            buttons[i][j] = new QPushButton();

            // Connect click event
            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(on_button_clicked()));

            gridLayout->addWidget(buttons[i][j], i + 2, j); // Adjusted row index to accommodate the banner
        }
    }
    this->setLayout(gridLayout);

    // update the button borad
    this->game.initialGame();

    // set turn
    if (whoFirst == 0) { this->game.setTurns(); }
    BoardUpdate(); 
    game.setTurns();
}

// Intent: Refresh / Update picture on the board
// Pre: gBoard exist 
// Post: window's button is update
void BoardWindow::BoardUpdate() {
    game.update();
    game.refreshCheck();
    game.updateForCheck();// update for check

    // Check gameover
    if (game.gameover()) { closeWindow(); }

    // Banner
    if (game.getTurns() % 2 == 1) bannerLabel->setText("It's Black Turn");
    else bannerLabel->setText("It's White Turn");

    // Select picture for all buttons in 8x8 size
    for (int i = 0; i < BUTTONSIZE; i++) {
        for (int j = 0; j < BUTTONSIZE; j++) {
            // Get url form gBoard[i+1][j+1]
            QUrl url = selectPic(i + 1, j + 1);

            // Set button's icon
            buttons[i][j]->setIcon(QIcon(url.path()));
            buttons[i][j]->setStyleSheet("");
            buttons[i][j]->setStyleSheet("QPushButton:hover{background-color: #C0C0C0;color: yellow;}");
            buttons[i][j]->setIconSize(QSize(50, 50));
        }
    }

    // add color
    for (int i = 0; i < BUTTONSIZE; i++) {
        for (int j = 0; j < BUTTONSIZE; j++) {
            if ((i + j) % 2 == 0) {
                buttons[i][j]->setStyleSheet("background-color:#FDF1EA;");
            }
            else {
                buttons[i][j]->setStyleSheet("background-color: #ffffff;");
            }
        }
    }
}

// Intent: Proccess Click event
// Pre: button is connected
// Post: may call other member function, or renew the banner
void BoardWindow::on_button_clicked() {
    if(game.gameover()) { closeWindow(); }

    QPushButton* button = qobject_cast<QPushButton*>(sender()); // 取得被點擊的按鈕
    int i = -1, j = -1;
    if (button) {
        // 在按鈕陣列中尋找按鈕對應的位置
        for (int row = 0; row < BUTTONSIZE; row++) {
            for (int col = 0; col < BUTTONSIZE; col++) {
                if (this->buttons[row][col] == button) {
                    i = row;
                    j = col;
                    break;
                }
            }
            if (i != -1) {
                break;
            }
        }
        // FOR DEBUG
        qDebug() << "You Clicked button at position" << j + 1 << "," << i + 1;
    }

    // 處理資料部分，Notice that the x y position is not same
    Position pos; 
    pos.x = j + 1;
    pos.y = i + 1;

    if ((this->clickTimes) % 2 == 0) {
        if (this->game.isStartValid(pos)) {
            this->clickTimes++;
            this->_before = pos;

            // MORE: PRINT PATH BOARD
            game.printPathBoard(pos);

            // update path board
            printPathBoard(pos);
            cout << endl;
        }
        else {
            cout << "INVALID MOVE" << endl;
        }
        return;
    }
    
    if ((this->clickTimes) % 2 == 1) {
        if (game.isEndValid(this->_before, pos)) {
            this->clickTimes++;
            
            // game
            game.move(this->_before, pos);
            
            // update the button borad
            BoardUpdate();
            game.printBoard();
            game.setTurns();
            cout << endl;
        }
        else {
            cout << "INVALID MOVE" << endl;
        }
        return;
    }
}

// Intent: Proccess Click event
// Pre: button is connected
// Post: call other member function
void BoardWindow::on_button_surrend() {
    // select who surrend
    if (game.getTurns() % 2 == 1) game.whiteSurrender();
    else game.blackSurrender();

    // call gameover to print message
    game.gameover();

    // close window
    closeWindow();
}

// Intent: Refresh / Update picture on the boards
// Pre: gBoard exist 
// Post: window's button is update(show Path)
void BoardWindow::printPathBoard(const Position& pos) {
    // Fetch: getValidMove()
    vector<Position> location;

    // Turn check
    if (game.getTurns() % 2 == 0) {
        location = game.getplayerBlack().findChess(pos).getValidMove();
    }
    else {
        location = game.getplayerWhite().findChess(pos).getValidMove();
    }

    /// Add color into button ///
    for (int i = 0; i < location.size(); i++) {
        buttons[location[i].y - 1][location[i].x - 1]->setStyleSheet("QPushButton { background-color: #FFC8B4; }");
    }
}

// Intent: Close window
// Pre: button is connected, or just pure function calling
// Post: close the window
void BoardWindow::closeWindow() { this->close(); }

// Intent: Return URL from (main) char gBoard[1~9][1~9]
// Pre: i, j is valid position in the board
// Post: Return QUrl
QUrl BoardWindow::selectPic(int i, int j) {
    switch (gBoard[i][j]) {
    case'B':
        return pic_bishop;
    case'b':
        return pic_bishop1;
    case'N':
        return pic_horse;
    case'n':
        return pic_horse1;
    case'K':
        return pic_king;
    case'k':
        return pic_king1;
    case'P':
        return pic_pawn;
    case'p':
        return pic_pawn1;
    case'Q':
        return pic_queen;
    case'q':
        return pic_queen1;
    case'R':
        return pic_rook;
    case'r':
        return pic_rook1;
    default:
        return pic_empty; // TMP
    }
}

// Intent: Update the time
// Pre: signal
// Post: Renew the time in timeLabel
void BoardWindow::updateTime()
{
    // 当前时间
    QDateTime currentTime = QDateTime::currentDateTime();

    // 计算时间差
    qint64 elapsedTime = startTime.msecsTo(currentTime);

    // 将时间差转换为hh:mm:ss格式
    QTime displayTime(0, 0);
    displayTime = displayTime.addMSecs(elapsedTime);
    QString timeString = displayTime.toString("hh:mm:ss");

    // 更新标签上的时间
    timeLabel->setText(timeString);
}