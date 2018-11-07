#pragma once

#include <vector>
#include <set>

namespace pmines {
    namespace model {
        class GameState {
        public:
            enum TileState {
                HIDDEN,
                REVEALED,
                FLAGGED
            };

            GameState(int width, int height, int mines, unsigned seed, int x, int y);
            int get_width();
            int get_height();
            bool is_mine(int x, int y);
            int get_neighbouring_mines(int x, int y);
            bool is_revealed(int x, int y);
            bool is_flagged(int x, int y);
            bool is_hidden(int x, int y);
            void reveal(int x, int y);
            void flag(int x, int y);
            void unflag(int x, int y);
        protected:
            int m_width;
            int m_height;

            static std::set<int> _get_reserved(int width, int height, int x, int y);
            static std::vector<std::vector<bool>> _random_minefield(int width, int height, int mines, unsigned seed, const std::set<int>& reserved);

            std::vector<std::vector<bool>> m_mines;
            std::vector<std::vector<TileState>> m_tile_state;
        };
    }
}