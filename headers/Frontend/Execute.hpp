#pragma once
#include <Pattern.hpp>
#include <vector>

struct Process
{
    float x, y;
    Frontend::CircleNode *Cur;
    Frontend::Arrow *Arc;
    sf::Vector2f arc_pos1, arc_pos2;
    bool arc_pos_c;
    bool pos_c;
    bool val_c;
    bool color_c;
    bool emph;
    bool show;
    bool reset_c;
    sf::String val;
    sf::Color color;
    Process()
    {
        arc_pos1 = arc_pos2 = sf::Vector2f(0,0);
        x = y = 0;
        arc_pos_c = false;
        Arc = nullptr;
        Cur = nullptr;
        pos_c = false;
        val_c = false;
        color_c = false;
        emph = false;
        show = false;
        reset_c = false;
    }
    void reset()
    {
        arc_pos1 = arc_pos2 = sf::Vector2f(0,0);
        x = y = 0;
        Cur = nullptr;
        Arc = nullptr;
        arc_pos_c = 0;
        pos_c = false;
        val_c = false;
        color_c = false;
        emph = false;
        show = false;
        val = "";
        color = sf::Color::Black;
        reset_c = false;
    }
};

class SingleExecute
{
    std::vector<Process> List;
    std::vector<Process> RevList;
    int step, order;
    sf::Clock clock;
    // Frontend::Pattern *current;

public:
    SingleExecute()
    {
        step = 0;
        order = 0;
    }
    void push_back(Process Tmp);
    void clear();
    int size();
    const Process &operator[](int id);
    void displayRev();
    void display();
    // void buildRev();
    // void stepforw(Frontend::Pattern &Cur, const sf::Event &event);
    // void stepback(Frontend::Pattern &Cur, const sf::Event &event);
    // void run(Frontend::Pattern &Cur, const sf::Event &event);
    void stepforw(const sf::Event &event);
    void stepback(const sf::Event &event);
    void run(const sf::Event &event);
    // void checking(const sf::Event &event);
};

class Execute
{
    std::vector<std::vector<Process>> List;
    std::vector<std::vector<Process>> RevList;
    int step, order;
    sf::Clock clock;
    // Frontend::Pattern *current;

public:
    Execute()
    {
        step = 0;
        order = 0;
    }
    void push_back(const std::vector<Process> &Tmp);
    void clear();
    int size();
    const std::vector<Process> &operator[](int id);
    void displayRev();
    void display();
    // void buildRev();
    void stepforw(const sf::Event &event);
    void stepback(const sf::Event &event);
    void run(const sf::Event &event);
    // void checking(const sf::Event &event);
};