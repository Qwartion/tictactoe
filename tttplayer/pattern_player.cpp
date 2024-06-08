#include "my_player.h"
#include <cstdlib>

int winX = 0;
int winO = 0;
int draw = 0;


///////////////////////// MY PLAYER:
//GameField:
const char* patterns[] = {
    "OOOO",     // 0
    "O.OOO",    // 1
    "OO.OO",    // 2
    "OOO.O",    // 3
    "OOO",      // 4
    "O.OO",     // 5
    "OO.O",     // 6
    "OO",       // 7
    "O.O",      // 8
};


void GameField::Analyze_Line(const MoveEvent& move_data, const Point* check_line, const int LenghtOfLine) {
    int MarkOfThisMove = (move_data.mark == my_mark) ? -1 : -2;     //-1 - моя марка, -2 - марка врага
    int MarkOfEnemyMove = (MarkOfThisMove == -1) ? -2 : -1;
    
    Field[move_data.point.y - b.min.y][move_data.point.x - b.min.x] = MarkOfThisMove;
    //if (_ratio < 1.1)
    
        _ratio = 1.1;
        for (int i = move_data.point.y - 1; i <= move_data.point.y + 1; i++)
        {
            for (int j = move_data.point.x - 1; j <= move_data.point.x + 1; j++)
            {
                if (i>=b.min.y and i<=b.max.y and j>=b.min.x and j<=b.max.x and (this->Field[i-b.min.y][j-b.min.x] >= 0))
                {
                    Field[i - b.min.y][j - b.min.x] += std::rand()%2;
                }
            }
        }
    
    std::string ValuesOfLine;
    bool isBlock = false;
    int countTHISmark = 0, countNONEmark = 0;
    for (int i = 0; i < LenghtOfLine; i++)
    {
        int tmpVal;
        char tmpChar;
        tmpVal = (Field[check_line[i].y - b.min.y][check_line[i].x - b.min.x]);
        if (tmpVal == MarkOfThisMove) { 
            tmpChar = 'O';
            countTHISmark++;
        }
        else if (tmpVal == MarkOfEnemyMove) tmpChar = 'X';
        else tmpChar = '.', countNONEmark++;
        ValuesOfLine += tmpChar;
    }
    if (countNONEmark+countTHISmark < 5) return;
    int PatternLen = 0;
    switch (countTHISmark)
    {
    default:
    case 4:
        PatternLen = 4;
        for (int i = 0; i < LenghtOfLine-PatternLen; i++)
        {
            std::string StrForCMP = ValuesOfLine.substr(i, PatternLen);
            if (StrForCMP == patterns[0])
            {
                if (i>0 and ValuesOfLine[i-1] == '.')
                {
                    Field[check_line[i-1].y - b.min.y][check_line[i-1].x - b.min.x] += (MarkOfThisMove == -1) ? 100000 * _ratio : 100000;
                }
                if (i+PatternLen<LenghtOfLine and ValuesOfLine[i+PatternLen] == '.')
                {
                    Field[check_line[i+PatternLen].y - b.min.y][check_line[i+PatternLen].x - b.min.x] += (MarkOfThisMove == -1) ? 100000 * _ratio : 100000;
                }
            }
        }
        PatternLen = 5;
        for (int i = 0; i < LenghtOfLine - PatternLen; i++)
        {
            std::string StrForCMP = ValuesOfLine.substr(i, PatternLen);
            if (StrForCMP == patterns[1] or StrForCMP == patterns[2] or StrForCMP == patterns[3])
            {
                for (int j = (i>0?i-1:i); j < (i+PatternLen+1<LenghtOfLine?i+PatternLen+1:i+PatternLen); j++)
                {
                    if (ValuesOfLine[j] == '.')
                    {
                        Field[check_line[j].y - b.min.y][check_line[j].x - b.min.x] += (MarkOfThisMove == -1) ? 90000 * _ratio : 9000;
                    }
                }
            }
        }
    case 3:
        PatternLen = 3;
        for (int i = 0; i < LenghtOfLine - PatternLen; i++)
        {
            std::string StrForCMP = ValuesOfLine.substr(i, PatternLen);
            if (StrForCMP == patterns[4])
            {
                if (i > 0 and ValuesOfLine[i - 1] == '.')
                {
                    Field[check_line[i - 1].y - b.min.y][check_line[i - 1].x - b.min.x] += (MarkOfThisMove == -1) ? 4000 * _ratio : 4000;
                }
                if (i + PatternLen < LenghtOfLine and ValuesOfLine[i + PatternLen] == '.')
                {
                    Field[check_line[i + PatternLen].y - b.min.y][check_line[i + PatternLen].x - b.min.x] += (MarkOfThisMove == -1) ? 4000 * _ratio : 4000;
                }
            }
        }
        PatternLen = 4;
        for (int i = 0; i < LenghtOfLine - PatternLen; i++)
        {
            std::string StrForCMP = ValuesOfLine.substr(i, PatternLen);
            if (StrForCMP == patterns[5] or StrForCMP == patterns[6])
            {
                for (int j = (i > 0 ? i - 1 : i); j < (i + PatternLen + 1 < LenghtOfLine ? i + PatternLen + 1 : i + PatternLen); j++)
                {
                    if (ValuesOfLine[j] == '.')
                    {
                        Field[check_line[j].y - b.min.y][check_line[j].x - b.min.x] += (MarkOfThisMove == -1) ? 7000 * _ratio : 7000;
                    }
                }
            }
        }
    case 2:
        PatternLen = 2;
        for (int i = 0; i < LenghtOfLine - PatternLen; i++)
        {
            std::string StrForCMP = ValuesOfLine.substr(i, PatternLen);
            if (StrForCMP == patterns[7])
            {
                if (i > 0 and ValuesOfLine[i - 1] == '.')
                {
                    Field[check_line[i - 1].y - b.min.y][check_line[i - 1].x - b.min.x] += (MarkOfThisMove == -1) ? 7000 * _ratio : 7000;
                }
                if (i + PatternLen < LenghtOfLine and ValuesOfLine[i + PatternLen] == '.')
                {
                    Field[check_line[i + PatternLen].y - b.min.y][check_line[i + PatternLen].x - b.min.x] += (MarkOfThisMove == -1) ? 7000 * _ratio : 7000;
                }
            }
        }
        PatternLen = 3;
        for (int i = 0; i < LenghtOfLine - PatternLen; i++)
        {
            std::string StrForCMP = ValuesOfLine.substr(i, PatternLen);
            if (StrForCMP == patterns[8])
            {
                for (int j = (i > 0 ? i - 1 : i); j < (i + PatternLen + 1 < LenghtOfLine ? i + PatternLen + 1 : i + PatternLen); j++)
                {
                    if (ValuesOfLine[j] == '.')
                    {
                        Field[check_line[j].y - b.min.y][check_line[j].x - b.min.x] += (MarkOfThisMove == -1) ? 1500 * _ratio : 1500;
                    }
                }
            }
        }
    case 1:
    case 0:
        break;
    }
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
        for (int sq = -1; sq < 2; sq++)
        {
            int DeltaX = sq * dx, DeltaY = sq * dy;

            /*Point p_start = move_data.point;
            Point p_end = move_data.point;*/
            Point p_start = Point{ .x = move_data.point.x + dx * _win_len + DeltaX, .y = move_data.point.y + dy * _win_len +DeltaY };
            Point p_end = Point{ .x = move_data.point.x - dx * _win_len + DeltaX, .y = move_data.point.y - dy * _win_len +DeltaY };
            //Point tmpP = { .x = move_data.point.x, .y = move_data.point.y };  //доработка
            //for (int i = 1; i < _win_len+1; i++)
            //{
            //    tmpP = { .x = tmpP.x + dx, .y = tmpP.y + dy };
            //    if (b.is_within(tmpP) and this->Field[tmpP.y - b.min.y][tmpP.x - b.min.x] != -2)
            //    {
            //        p_start = tmpP;
            //    }
            //    else break;
            //}
            //
            //tmpP = { .x = move_data.point.x, .y = move_data.point.y };
            //for (int i = 1; i < _win_len + 1; i++)
            //{
            //    tmpP = { .x = tmpP.x - dx, .y = tmpP.y - dy };
            //    if (b.is_within(tmpP) and this->Field[tmpP.y - b.min.y][tmpP.x - b.min.x] != -2)
            //    {
            //        p_end = tmpP;
            //    }
            //    else break;
            //}
            //   //

            while (!b.is_within(p_start))
            {
                p_start = { p_start.x - dx, p_start.y - dy };
            }
            while (!b.is_within(p_end))
            {
                p_end = { p_end.x + dx, p_end.y + dy };
            }
            Point p = p_start;
            int LenghtOfLine = abs(p_end.x - p_start.x) + 1, j = 0;
            if (LenghtOfLine < 5)continue;
            Point* check_line = new Point[LenghtOfLine];
            for (int j = 0; j < LenghtOfLine; j++) {
                check_line[j] = p;
                p = { p.x - dx, p.y - dy };
            }
            Analyze_Line(move_data, check_line, LenghtOfLine);
            delete[] check_line;
        }
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
        /*return Point{
            .x = rand_int(_my_field.b.min.x, _my_field.b.max.x),
            .y = rand_int(_my_field.b.min.y, _my_field.b.max.y),
        };*/
        return Point {
            .x = (_my_field.b.min.x + _my_field.b.max.x) / 2,
            .y = (_my_field.b.min.y + _my_field.b.max.y) / 2,
        };
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
        /*for (int i = _my_field.rows-2; i >= 0; i--)
        {
            for (int j = 0; j < _my_field.cols; j++)
            {
                printf("%d ", _my_field.Field[i][j]);
            }
            printf("\n");
        }*/
    }
}
//
////////////////////////////////////

