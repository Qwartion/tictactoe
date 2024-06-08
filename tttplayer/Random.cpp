#include "Random.h"
#include <cstdlib>

static field_index_t rand_int(field_index_t min, field_index_t max) {
    return min + rand() % (max - min + 1);
}

Point RandomPlayer::play(const GameView& game) {
    Boundary b = game.get_settings().field_size;
    Point result;
    do {
        result = {
            .x = rand_int(b.min.x, b.max.x),
            .y = rand_int(b.min.y, b.max.y),
        };
    } while (game.get_state().field->get_value(result) != Mark::None);
    return result;
}


void BasicObserver::notify(const GameView& game, const Event& event) {
    if (event.get_type() == MoveEvent::TYPE) {
        auto& data = get_data<MoveEvent>(event);
        /*_out << "Move:\tx = " << data.point.x
            << ",\ty = " << data.point.y << ":\t";
        _print_mark(data.mark) << '\n';*/
        Point last_move = { .x = data.point.x, .y = data.point.y };
        //_print_field(game, last_move);
        return;
    }
    if (event.get_type() == PlayerJoinedEvent::TYPE) {
        auto& data = get_data<PlayerJoinedEvent>(event);
        _out << "Player '" << data.name << "' joined as ";
        _print_mark(data.mark) << '\n';
        return;
    }
    if (event.get_type() == GameStartedEvent::TYPE) {
        _out << "Game started\n";
        return;
    }
    if (event.get_type() == WinEvent::TYPE) {
        auto& data = get_data<WinEvent>(event);
        _out << "Player playing ";
        _print_mark(data.winner_mark) << " has won\n";
        if (isO(data.winner_mark) == 0) winO++;
        if (isO(data.winner_mark) == 1) winX++;
        return;
    }
    if (event.get_type() == DrawEvent::TYPE) {
        auto& data = get_data<DrawEvent>(event);
        _out << "Draw happened, reason: '" << data.reason << "'\n";
        draw++;
        return;
    }
    if (event.get_type() == DisqualificationEvent::TYPE) {
        auto& data = get_data<DisqualificationEvent>(event);
        _out << "Player playing ";
        _print_mark(data.player_mark) << " was disqualified, reason: '"
            << data.reason << "'\n";
        return;
    }
}

std::ostream& BasicObserver::_print_mark(Mark m) {
    if (m == Mark::Cross) return _out << "X";
    if (m == Mark::Zero) return _out << "O";
    return _out << "?";
}

int BasicObserver::isO(Mark m) {
    if (m == Mark::Zero) return 0;
    if (m == Mark::Cross) return 1;
    return 2;
}

void BasicObserver::_print_field(const GameView& game, const Point& last_move) {
    const auto& field = game.get_state().field;
    const Point& min = game.get_settings().field_size.min;
    const Point& max = game.get_settings().field_size.max;
    const int width = 3;

    _out << std::setw(width) << std::left << ' ';
    for (int x = min.x; x <= max.x; x++) {
        _out << std::setw(width) << std::left << x;
    }
    _out << '\n';

    for (int y = max.y; y >= min.y; y--) {
        _out << std::setw(width) << std::left << y;

        for (int x = min.x; x <= max.x; x++) {
            Point p = { .x = x, .y = y };
            Mark mark = field->get_value(p);
            if (p.x == last_move.x and p.y == last_move.y) {
                _out << "\033[31m";
            }
            if (mark == Mark::None) {
                _out << std::setw(width) << std::left << '.';
            }
            else {
                _print_mark(mark);
                _out << std::setw(width - 1) << std::left << ' ';
            }
            _out << "\033[0m";
        }
        _out << '\n';
    }
    _out << '\n';
}
