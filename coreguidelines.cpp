#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>

    struct widget
    {
        widget() {g =99;}
        widget(int g) {this->g = g;}
        int g;
    };

    class WidgetUser
    {
    public:
        WidgetUser(std::shared_ptr<widget> w) :
            m_widget{w} {}
        // ...
        
        // ...
        
        int getValue()
        {
            return m_widget->g;
        }
        
    private:
        std::shared_ptr<widget> m_widget;
    };

    void ChangeWidget(std::shared_ptr<widget>& w)
    {
        w = std::make_shared<widget>(widget{});
    }


int main()
{
    auto s = std::make_shared<widget>(widget{5});
    
    WidgetUser  w(s);
    
    std::cout  << w.getValue();
    
    ChangeWidget(s);
    
    std::cout << "\ns " << s->g << " w " << w.getValue(); 
}


// run with:
//  g++ -nostartfiles -Wl,--entry=start_there start-from-a-main-routine.cpp 
