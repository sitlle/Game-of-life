#include<iostream>
#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
struct SQUARE {
    int cnt_of_negh;
    int status;
};
const int WINDOW_H = 1000,WINDOW_W = 1000, square_size = 40;
int mini_window_h = WINDOW_H, mini_window_w = WINDOW_W, font_size = 30, step = square_size;
int cnt_of_V = 0, cnt_of_P = 0;
long double main_time = 60;
long long generation = 0;
sf::RenderWindow window(sf::VideoMode(WINDOW_H, WINDOW_W), "Life");

sf::RectangleShape square(sf::Vector2f(square_size, square_size));
sf::RectangleShape line_stb(sf::Vector2f(2, WINDOW_H));
sf::RectangleShape line_str(sf::Vector2f(WINDOW_W, 2));
sf::Vector2i mouse_position, mouse_position_1;
sf::Time TIME = sf::milliseconds(main_time);

std::vector<std::vector<SQUARE>> Lground(WINDOW_H / step, std::vector<SQUARE> (WINDOW_W / step));
std::vector<std::vector<SQUARE>> Nground(mini_window_h / step, std::vector<SQUARE> (mini_window_w / step));
bool ADD_SQUARE = false, DELETE = false, START_SIM = false, STOP_SIM = false, CLEAR_ALL = false;
bool another_size = false, settings_is_open = false, font_set = true, peaceful_square = true;


void render_shape_at_pos(sf::RectangleShape shape, int x, int y, int a, int b, int c) {
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color(a, b, c));
    window.draw(shape);
}

void Ouput(std::vector<std::vector<SQUARE>>& last_ground) {
    for (long long i = 0; i < Lground.size(); i++) {
        for (long long j = 0; j < Lground.size(); j++) {
            int a = 0, b = 0, c = 0;
            /*a = rand() % 255;
            b = rand() % 225;
            c = rand() % 225;
             */
            if (Lground[i][j].status == 1) {
                sf::RectangleShape square(sf::Vector2f(step, step));
                render_shape_at_pos(square, j * (square_size + (step - square_size)), i * (square_size + (step - square_size)), 255, 255, 255);
            }
            else if(Lground[i][j].status == 2) {
                sf::RectangleShape square(sf::Vector2f(step, step));
                render_shape_at_pos(square, j * (square_size + (step - square_size)), i * (square_size + (step - square_size)), 255, 0, 0);
            }
        }
    }
    if (START_SIM) {
        sleep(TIME);
    }
}

void Checking(std::vector<std::vector<SQUARE>>& Lground, std::vector<std::vector<SQUARE>>& Nground) {
    generation++;
    int cnt = 0, cnt_1 = 0;
    int R = 1 + rand() % 3;
    for (int i = 0; i < std::min(Nground.size(), Lground.size()); i++) {
        for (int j = 0; j < std::min(Nground.size(), Lground.size()); j++) {
            for (int ar = -1; ar < 2; ar++) {
                for (int as = -1; as < 2; as++) {
                    if ((as != 0 || ar != 0) && Lground[(i + ar + Lground.size()) % Lground.size()][(j + as + Lground.size()) % Lground.size()].status == 1) {
                        cnt++;
                    }
                    if ((as != 0 || ar != 0) && Lground[(i + ar + Lground.size()) % Lground.size()][(j + as + Lground.size()) % Lground.size()].status == 2) {
                        cnt_1++;
                    }
                }
            }
            if ((Lground[i][j].status == 0 && cnt == 3) || (Lground[i][j].status == 1 && cnt == 2) || (Lground[i][j].status == 1 && cnt == 3) || cnt_1 >= 6) {
                Nground[i][j].status = 1;
            }
            else if(Lground[i][j].status != 2 || cnt_1 >= 7){
                Nground[i][j].status = 0;
            }
            if(!peaceful_square && Lground[i][j].status > 0 && cnt == 6) {
                Nground[i][j].status = 2;
            }
            if(!peaceful_square && Lground[i][j].status == 2) {
                for (int ar = -1; ar < 2; ar++) {
                    for (int as = -1; as < 2; as++) {
                        int RA = rand() % R;
                        if((as != 0 || ar != 0) && Lground[(i + ar + Lground.size()) % Lground.size()][(j + as + Lground.size()) % Lground.size()].status > 0 && RA != 1) {
                            Nground[(i + ar + Lground.size()) % Lground.size()][(j + as + Lground.size()) % Lground.size()].status = 2;
                        }
                    }
                }
            }
            cnt = 0;
            cnt_1 = 0;
        }
    }
}

void Making_Chess_Board() {
    for(int i = 0; i <= WINDOW_H; i += step) {
        render_shape_at_pos(line_str, 0, i, 64, 64, 64);
    }

    for(int i = 0; i <= WINDOW_W; i += step) {
        render_shape_at_pos(line_stb, i, 0, 64, 64, 64);
    }
}

void Window_Clear() {
    for(int i = 0; i < Lground.size(); i++) {
        for(int j = 0; j < Lground.size(); j++) {
            Lground[i][j].status = 0;
        }
    }
    CLEAR_ALL = false;
    generation = 0;
    cnt_of_V = 0;
    cnt_of_P = 0;
}

int main() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                peaceful_square = true;
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                peaceful_square = false;
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                step--;
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                step++;
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                main_time += 2;
                TIME = sf::milliseconds(main_time);
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                main_time -= 2;
                TIME = sf::milliseconds(main_time);
            }
            else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !START_SIM) {
                START_SIM = true;
                STOP_SIM = false;
            }
            else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::P) && START_SIM) {;
                START_SIM = false;
                STOP_SIM = true;
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mouse_position = sf::Mouse::getPosition(window);
                ADD_SQUARE = true;
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                mouse_position = sf::Mouse::getPosition(window);
                DELETE = true;
            }
            else if(event.type == sf::Event::KeyPressed && (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))) {
                CLEAR_ALL = true;
            }
            else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !START_SIM) {
                sf::RenderWindow sol(sf::VideoMode(650,  400), "Help");
                while (sol.isOpen()) {
                    int cnt = 0;
                    sf::Event ev;
                    std::string help_eng = "If you want: \nStart game - click P;\nStop game -  click P second time;\nCreate new square - click LMB;\nDelete square - click Right Button on your\nmouse;\nClear window - click RShift or LShift;\nLeft/Right arrow - speed slower/faster\nDown/Up arrow - smaller/bigger square size\nPeaceful square - white\nVirus square - red\nTo make colony of viruses you can click num2\nand num1 if you want make peaceful colony\n Generation: " +
                            std::to_string(generation) + "\nViruses - " + std::to_string(cnt_of_V) + "\n Peaceful squares - " + std::to_string(cnt_of_P);
                    sf::Text text;
                    sf::Font font;
                    while (sol.pollEvent(ev)) {
                        if (ev.type == sf::Event::Closed || ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                            sol.close();
                        }
                        else if(ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                            font_set = true;
                        }
                        else if(ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                            font_set = false;
                        }
                        else if(ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            font_size++;
                        }
                        else if(ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            font_size--;
                        }
                    }
                    if(font_set) font.loadFromFile("Strange.ttf");
                    else font.loadFromFile("Rubik-Black.ttf");
                    text.setFont(font);
                    text.setCharacterSize(font_size);
                    text.setString(help_eng);
                    sol.clear();
                    sol.draw(text);
                    sol.display();
                }
            }
        }

        std::vector<std::vector<SQUARE>> Nground(mini_window_h / step, std::vector<SQUARE> (mini_window_w / step));

        if (ADD_SQUARE) {
            Lground[(mouse_position.y + step - 1) / step - 1][(mouse_position.x + step - 1) / step - 1].status = 1;
            ADD_SQUARE = false;
        }
        else if(DELETE) {
            Lground[(mouse_position.y + step - 1) / step - 1][(mouse_position.x + step - 1) / step - 1].status = 0;
            DELETE = false;
        }
        else if(CLEAR_ALL) {
            Window_Clear();
        }

        if (START_SIM) {
            Checking(Lground, Nground);
            Lground= Nground;
        }
        window.clear();

        Making_Chess_Board();
        Ouput(Lground);

        window.display();
    }
    return 0;
}
