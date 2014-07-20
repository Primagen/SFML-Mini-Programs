

/**
 * Last updated: 20 July 2014
 *
 * This is just a little program, using SFML,
 * to show a method to drag objects using the mouse.
 * Feel free to apply any of it to your project
 * if you happen to stumble upon this
 */

#include <SFML/Graphics.hpp>

#define MORE_THAN_ONE

/**
 * Uncomment this to only load one
 * draggable sf::RectangleShape.
 *
 * Else it will load 10 draggable rectangles.
 */
//#undef MORE_THAN_ONE

#ifdef MORE_THAN_ONE
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Click-and-Drag, multiple rectangles");
    sf::View mView = window.getView();

    /**
     * Uncomment following line to hide mouse
     * there is inevitable *slight* lag when using a drawable object as the cursor
     * instead of the OS's cursor itself
     */
    window.setMouseCursorVisible(false);

    //Draggable Rectangles:
    std::vector<sf::RectangleShape> rects;
    for (int i = 0; i < 10; i++)
    {
        sf::RectangleShape temp_rect;
        temp_rect.setPosition(sf::Vector2f(i*75.f, i*(0.12*i)*50.f));
        temp_rect.setSize(sf::Vector2f(100.f, 100.f));
        temp_rect.setFillColor(sf::Color::White);
        rects.push_back(temp_rect);
    }
    int mCurrRectIndex = -1;

    //Mouse Dot to indicate cursor:
    sf::RectangleShape mouse_RS;
     mouse_RS.setSize(sf::Vector2f(2.f, 2.f));
     mouse_RS.setFillColor(sf::Color::Red);

    sf::Vector2i mMousePos(0, 0);
    bool mClick = false;
    bool mDrag  = false;

    /**
     * Keeps track of the offset between mouse position,
     * and the position of the dragged rectangle
     */
    sf::Vector2f diff(0.f, 0.f);

    ///////////////////
    ///  Main loop  ///
    ///////////////////
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::MouseButtonPressed:
                    mClick = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    mClick = false;
                    mDrag  = false;
                    break;
                case sf::Event::MouseMoved:
                    mMousePos.x = event.mouseMove.x;
                    mMousePos.y = event.mouseMove.y;
                    break;
                case sf::Event::MouseLeft:
                    mClick = false;
                    mDrag  = false;
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        } // Event Loop

        //Update:
        mouse_RS.setPosition(static_cast<sf::Vector2f>(mMousePos));

        if (mClick)
        {
            //you could do: if [contains] OR mDrag -> ( mdrag = true, move rectangle )
            //an extra if or assignment won't do much anyway
            for (int i = 0; i < rects.size(); i++)
            {
                if (rects[i].getGlobalBounds().contains(window.mapPixelToCoords(mMousePos, mView))
                    && !mDrag) //Prevents dragging multiple at same time
                {
                    mDrag = true;
                    mCurrRectIndex = i;
                    break;
                }
            }

            if (mDrag)
            {
                /**
                 * diff vector is set to (0i, 0j) when
                 * item is no longer being dragged.
                 *
                 * This if-statement is to ensure the diff value
                 * stays constant throughout the drag
                 */
                if (diff.x == 0.f && diff.y == 0.f)
                {
                    diff.x = mMousePos.x - rects[mCurrRectIndex].getPosition().x;
                    diff.y = mMousePos.y - rects[mCurrRectIndex].getPosition().y;

                }
                rects[mCurrRectIndex].setPosition(mMousePos.x - diff.x,
                                                  mMousePos.y - diff.y);
            }
        }
        else
            diff = sf::Vector2f(0.f, 0.f);


        //Draw:
        window.clear();
        for (int i = 0; i < rects.size(); i++)
            window.draw(rects[i]);
        window.draw(mouse_RS);
        window.display();

    } // Main Loop
}

#else
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Click-and-Drag, single rectangle");
     window.setMouseCursorVisible(false);
    sf::View mView = window.getView();

    sf::RectangleShape rect;
     rect.setPosition(sf::Vector2f(100.f, 100.f));
     rect.setSize(sf::Vector2f(100.f, 100.f));
     rect.setFillColor(sf::Color::White);

    sf::RectangleShape mouse_RS;
     mouse_RS.setSize(sf::Vector2f(2.f, 2.f));
     mouse_RS.setFillColor(sf::Color::Red);

    sf::Vector2i mMousePos(0, 0);
    bool mClick = false;
    bool mDrag  = false;

    /**
     * Keeps track of the offset between mouse position,
     * and the position of the dragged rectangle
     */
    sf::Vector2f diff(0.f, 0.f);

    ///////////////////
    ///  Main loop  ///
    ///////////////////
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::MouseButtonPressed:
                    mClick = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    mClick = false;
                    mDrag  = false;
                    break;
                case sf::Event::MouseMoved:
                    mMousePos.x = event.mouseMove.x;
                    mMousePos.y = event.mouseMove.y;
                    break;
                case sf::Event::MouseLeft:
                    mClick = false;
                    mDrag  = false;
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        } // Event Loop

        //Update:
        mouse_RS.setPosition(static_cast<sf::Vector2f>(mMousePos));

        if (mClick)
        {
            //you could do: if [contains] OR mDrag -> ( mdrag = true, move rectangle )
            //an extra if or assignment won't do much anyway
            if (rect.getGlobalBounds().contains(window.mapPixelToCoords(mMousePos, mView)))
                mDrag = true;
            if (mDrag)
            {
                /**
                 * diff vector is set to (0i, 0j) when
                 * item is no longer being dragged.
                 *
                 * This if-statement is to ensure the diff value
                 * stays constant throughout the drag
                 */
                if (diff.x == 0.f && diff.y == 0.f)
                {
                    diff.x = mMousePos.x - rect.getPosition().x;
                    diff.y = mMousePos.y - rect.getPosition().y;

                }
                rect.setPosition(mMousePos.x - diff.x,
                                 mMousePos.y - diff.y);
            }
        }
        else
            diff = sf::Vector2f(0.f, 0.f);


        //Draw:
        window.clear();
        window.draw(rect);
        window.draw(mouse_RS);
        window.display();

    } // Main Loop
}
#endif
