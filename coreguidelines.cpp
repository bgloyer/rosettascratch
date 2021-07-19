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
        explicit WidgetUser(std::shared_ptr<widget> w) noexcept:
            m_widget{std::move(w)} {}
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

    void ChangeWidget2(const std::shared_ptr<widget>& w)
    {
        auto w2 = w;
        w->g = 876868;
        
    }


int maincg()
{
    auto s = std::make_shared<widget>(widget{5});
    
    WidgetUser  w(std::move(s));
    
    std::cout  << w.getValue();
    
    ChangeWidget(s);
    ChangeWidget2(s);
    
    std::cout << "\ns " << s->g << " w " << w.getValue();
    return 0;
}


// run with:
//  g++ -nostartfiles -Wl,--entry=start_there start-from-a-main-routine.cpp 
