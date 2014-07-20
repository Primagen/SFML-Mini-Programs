
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Click-and-Drag");
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
                    mDrag = false;
                    break;
                case sf::Event::MouseMoved:
                    mMousePos.x = event.mouseMove.x;
                    mMousePos.y = event.mouseMove.y;
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
