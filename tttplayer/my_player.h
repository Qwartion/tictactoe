#pragma once
#include <ostream>
#include <iomanip>
#include "player.h"

extern int winX;
extern int winO;
extern int draw;

/////////// MY PLAYER:
/////Для работы нужен Random.h и Random.cpp


class GameField {   //вспомогательный класс в котром будут храниться веса ходов
    Boundary b;
    int _win_len;
    int rows, cols;
    int** Field = nullptr;
    Mark my_mark;
    float _ratio = 1;
    void Analyze_Line(const MoveEvent& move_data, const Point* check_line, const int LenghtOfLine);
public:
    GameField(){}
    void FieldAnalysis(const MoveEvent& move_data);
    ~GameField();
    friend class MyPlayer;
};

class MyPlayer : public Player {
    std::string _name;
    GameField _my_field;
public:
    MyPlayer(const std::string& name) : _name(name) {}
    std::string get_name() const override { return _name; }
    Point play(const GameView& game) override;
    void assign_mark(Mark player_mark) override;
    void notify(const GameView&, const Event&) override;
};

//////////////////////



