#include "my_player.h"
#include <cstdlib>

int winX = 0;
int winO = 0;
int draw = 0;

static field_index_t rand_int(field_index_t min, field_index_t max) {
    return min + rand() % (max - min + 1);
}


///////////////////////// MY PLAYER:
//GameField:

void GameField::Analyze_Line(const MoveEvent& move_data, const Point* check_line, const int LenghtOfLine) {
    int MarkOfThisMove = (move_data.mark == my_mark) ? -1 : -2;     //-1 - моя марка, -2 - марка врага
    int MarkOfEnemyMove = (MarkOfThisMove == -1) ? -2 : -1;
    Field[move_data.point.y - b.min.y][move_data.point.x - b.min.x] = MarkOfThisMove;
    if (_ratio < 1.1)
    {
        _ratio = 1.5;
        for (int i = move_data.point.y - 1; i <= move_data.point.y + 1; i++)
        {
            for (int j = move_data.point.x - 1; j <= move_data.point.x + 1; j++)
            {
                if (i>=b.min.y and i<=b.max.y and j>=b.min.x and j<=b.max.x and (this->Field[i-b.min.y][j-b.min.x] >= 0))
                {
                    Field[i - b.min.y][j - b.min.x] += 1;
                }
            }
        }
    }
    int* ValuesOfLine = new int[LenghtOfLine];
    for (int i = 0; i < LenghtOfLine; i++)
    {
        ValuesOfLine[i] = (Field[check_line[i].y - b.min.y][check_line[i].x - b.min.x]);
    }
    for (int i = 0; i < LenghtOfLine; i++)
    {
        int countTHISmark = 0, countNONEmark = 0, countENEMYmark = 0;
        int j = i;
        while (j<=i+5 and j<LenghtOfLine)
        {
            if (ValuesOfLine[j] == MarkOfThisMove)countTHISmark++;
            else if (ValuesOfLine[j] < 0)countENEMYmark++;
            else countNONEmark++;
            j++;
            if (j == LenghtOfLine)
                break;
        }
        j--;
        switch (countTHISmark)
        {
        case 4:
            if (ValuesOfLine[i]>=0 and ValuesOfLine[j]>=0)
            {
                ValuesOfLine[i] = (MarkOfThisMove == -1) ? 999999 * _ratio : 999999;   //открытая четверка
                ValuesOfLine[j] = (MarkOfThisMove == -1) ? 999999 * _ratio : 999999;
            }
            else if (ValuesOfLine[i] == MarkOfEnemyMove and ValuesOfLine[j] >= 0)
            {
                ValuesOfLine[j] = (MarkOfThisMove == -1) ? 8000 * _ratio : 8000; //четверка закрыта слева
            }
            else if (ValuesOfLine[j] == MarkOfEnemyMove and ValuesOfLine[i] >= 0)
            {
                ValuesOfLine[i] = (MarkOfThisMove == -1) ? 8000 * _ratio : 8000; //четверка закрыта справа
            }
            else if (countENEMYmark == 0 or (countENEMYmark == 1 and (ValuesOfLine[i] == MarkOfEnemyMove or ValuesOfLine[j] == MarkOfEnemyMove)))
            {
                for (int k = 0; k <= 3; k++)
                {
                    if (ValuesOfLine[i+k] == MarkOfThisMove and ValuesOfLine[i+1+k] >= 0)
                    {
                        ValuesOfLine[i + 1 + k] = (MarkOfThisMove == -1) ? 4000 * _ratio : 4000; 
                        //четверка с дыркой внутри
                    }
                }
            }
            break;
        case 3:
            if (countENEMYmark == 0) {
                if (ValuesOfLine[i] >= 0 and ValuesOfLine[j] >= 0) {
                    ValuesOfLine[i] = (MarkOfThisMove == -1) ? 5000 * _ratio : 5000; // открытая тройка
                    ValuesOfLine[j] = (MarkOfThisMove == -1) ? 5000 * _ratio : 5000;
                }
            }
            else if (countENEMYmark == 1 and (ValuesOfLine[i] == MarkOfEnemyMove or ValuesOfLine[j] == MarkOfEnemyMove)) {
                if (ValuesOfLine[i] == MarkOfEnemyMove) {
                    if (ValuesOfLine[j] >= 0) {
                        ValuesOfLine[j] = (MarkOfThisMove == -1) ? 2500 * _ratio : 2500; // тройка закрыта слева
                    }
                }
                else if (ValuesOfLine[j] == MarkOfEnemyMove) {
                    if (ValuesOfLine[i] >= 0) {
                        ValuesOfLine[i] = (MarkOfThisMove == -1) ? 2500 * _ratio : 2500; // тройка закрыта справа
                    }
                }
                for (int k = 0; k <= 2; k++) {
                    if (ValuesOfLine[i + k] == MarkOfThisMove and ValuesOfLine[i + 1 + k] >= 0 and ValuesOfLine[i + 2 + k] == MarkOfThisMove) {
                        ValuesOfLine[i + 1 + k] = (MarkOfThisMove == -1) ? 1500 * _ratio : 1500; // тройка с дыркой внутри
                    }
                }
            }
            break;
        case 2:
            if (countENEMYmark == 0) {
                for (int k = 0; k <= 1; k++) {
                    if (ValuesOfLine[i + k] == MarkOfThisMove and ValuesOfLine[i + 1 + k] >= 0) {
                        ValuesOfLine[i + 1 + k] = (MarkOfThisMove == -1) ? 500 * _ratio : 500; // двойка открытая
                    }
                }
            }
            else if (countENEMYmark == 1 and (ValuesOfLine[i] == MarkOfEnemyMove or ValuesOfLine[j] == MarkOfEnemyMove)) {
                for (int k = 0; k <= 1; k++) {
                    if (ValuesOfLine[i + k] == MarkOfThisMove and ValuesOfLine[i + 1 + k] >= 0) {
                        ValuesOfLine[i + 1 + k] = (MarkOfThisMove == -1) ? 100 * _ratio : 100; // двойка с одной закрытой стороной
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < LenghtOfLine; i++) {
        Field[check_line[i].y - b.min.y][check_line[i].x - b.min.x] = ValuesOfLine[i];
    }
    delete[] ValuesOfLine;
}

void GameField::FieldAnalysis(const MoveEvent& move_data) {
    struct
    {
        int dx, dy;
    }lines[] = { {1,0}, {0,1}, {1,1}, {1,-1} };
    for (int i = 0; i < 4; i++)
    {
        int dx = lines[i].dx;
        int dy = lines[i].dy;
        Point p_start = Point{ .x = move_data.point.x + dx * _win_len, .y = move_data.point.y + dy * _win_len };
        Point p_end = Point{ .x = move_data.point.x - dx * _win_len, .y = move_data.point.y - dy * _win_len };
        while (!b.is_within(p_start))
        {
            p_start = { p_start.x - dx, p_start.y - dy };
        }
        while (!b.is_within(p_end))
        {
            p_end = { p_end.x + dx, p_end.y + dy };
        }
        Point p = p_start;
        int LenghtOfLine = abs(p_end.x - p_start.x)+1, j=0;
        Point* check_line = new Point[LenghtOfLine];
        for (int j = 0; j < LenghtOfLine; j++) {
            check_line[j] = p;
            p = { p.x - dx, p.y - dy };
        }
        Analyze_Line(move_data, check_line, LenghtOfLine);
        delete[] check_line;
    }
}

GameField::~GameField() {
    if (this->Field != nullptr)
    {
        for (int i = 0; i < this->rows; i++)
        {
            delete[] this->Field[i];
        }
        delete[] this->Field;
        this->rows = 0;
        this->cols = 0;
    }
}
//
////////
//Player:
void MyPlayer::assign_mark(Mark player_mark) { _my_field.my_mark = player_mark; }

Point MyPlayer::play(const GameView& game) {
    const bool is_first_move = game.get_state().number_of_moves == 0;
    
    if (is_first_move) {
        return Point{
            .x = rand_int(_my_field.b.min.x, _my_field.b.max.x),
            .y = rand_int(_my_field.b.min.y, _my_field.b.max.y),
        };
        /*return Point {
            .x = (_my_field.b.min.x + _my_field.b.max.x) / 2,
            .y = (_my_field.b.min.y + _my_field.b.max.y) / 2,
        };*/
    }
    else
    {
        int max_i = 0, max_j = 0, max_val = 0;
        for (int i = 0; i < _my_field.rows; i++)
        {
            for (int j = 0; j < _my_field.cols; j++)
            {
                if (_my_field.Field[i][j] >= max_val)
                {
                    max_val = _my_field.Field[i][j];
                    max_i = i;
                    max_j = j;
                }
            }
        }
        return Point{
            .x = max_j + _my_field.b.min.x,
            .y = max_i + _my_field.b.min.y,
        };
    }
}

void MyPlayer::notify(const GameView& view, const Event& event) {
    const bool is_support_field_NOTexist = _my_field.Field == nullptr;
    if (is_support_field_NOTexist)
    {
        _my_field.b = view.get_settings().field_size;
        _my_field._win_len = view.get_settings().win_length;
        _my_field.rows = _my_field.b.max.y - _my_field.b.min.y + 1;
        _my_field.cols = _my_field.b.max.x - _my_field.b.min.x + 1;
        _my_field.Field = new int* [_my_field.rows];
        for (int i = 0; i < _my_field.rows; i++)
        {
            _my_field.Field[i] = new int[_my_field.cols];
            for (int j = 0; j < _my_field.cols; j++)
            {
                _my_field.Field[i][j] = 0;
            }
        }
    }
    if (event.get_type() == MoveEvent::TYPE) {
        auto& data = get_data<MoveEvent>(event);
        _my_field.FieldAnalysis(data);
    }
}
//
////////////////////////////////////

