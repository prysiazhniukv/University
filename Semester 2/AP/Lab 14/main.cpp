#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

float func(float x)
{
    return abs(sin(x)) + cos(abs(x));
}

// Find the min and max values of the function in the given range
void findMinMax(float xMin, float xMax, float& yMin, float& yMax) {
    yMin = func(xMin);
    yMax = yMin;
    for (float x = xMin; x <= xMax; x += 0.01f) {
        float y = func(x);
        if (y < yMin) yMin = y;
        if (y > yMax) yMax = y;
    }
}

int main()
{
    // User input for interval
    float minX, maxX;
    cout << "Enter the start value of x: ";
    cin >> minX;
    cout << "Enter the end value of x: ";
    cin >> maxX;
    if(minX > maxX)
        swap(minX, maxX);

    // Calculate y-axis range
    float minY, maxY;
    findMinMax(minX, maxX, minY, maxY);

    // SFML setup
    RenderWindow window(VideoMode(800, 600), "Function Graph");
    window.setFramerateLimit(60);

    // Camera settings
    View view(FloatRect(0, 0, 800, 600));
    float zoomKoef = 1.0f;

    // Create axes
    float zeroX = window.getSize().x * (-minX) / (maxX - minX);
    float zeroY = window.getSize().y * (maxY) / (maxY - minY);
    VertexArray Axes(Lines, 4);
    Axes[0].position = Vector2f(0, zeroY);
    Axes[1].position = Vector2f(window.getSize().x, zeroY);
    Axes[2].position = Vector2f(zeroX, 0);
    Axes[3].position = Vector2f(zeroX, window.getSize().y);
    for(int i = 0; i < 4; ++i)
        Axes[i].color = Color::White;

    // Create arrows
    VertexArray arrowX(Lines, 4);
    arrowX[0].position = Vector2f(window.getSize().x, zeroY);
    arrowX[1].position = Vector2f(window.getSize().x - 10, zeroY - 10);
    arrowX[2].position = Vector2f(window.getSize().x, zeroY);
    arrowX[3].position = Vector2f(window.getSize().x - 10, zeroY + 10);
    for (int i = 0; i < 4; ++i)
        arrowX[i].color = Color::White;

    VertexArray arrowY(Lines, 4);
    arrowY[0].position = Vector2f(zeroX, 0);
    arrowY[1].position = Vector2f(zeroX - 10, 10);
    arrowY[2].position = Vector2f(zeroX, 0);
    arrowY[3].position = Vector2f(zeroX + 10, 10);
    for (int i = 0; i < 4; ++i)
        arrowY[i].color = Color::White;

    // Load default font
    Font font;
    if (!font.loadFromFile("JetBrainsMonoNL-Regular.ttf"))
    {
        cerr << "Failed to load font file!" << endl;
        return 1;
    }

    // Create text for x and y axis
    Text xText("X", font, 14);
    xText.setPosition(window.getSize().x - 10, zeroY - 30);
    xText.setFillColor(Color::White);

    Text yText("Y", font, 14);
    yText.setPosition(zeroX + 10, 5);
    yText.setFillColor(Color::White);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Zoom in/out by keyboard
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Equal || event.key.code == Keyboard::Add)
                {
                    zoomKoef *= 0.8f; // Zoom in
                }
                else if (event.key.code == Keyboard::Hyphen || event.key.code == Keyboard::Subtract)
                {
                    zoomKoef *= 1.2f;    // Zoom out
                    if (zoomKoef > 1.0f)
                        zoomKoef = 1.0f;
                }
                view.setSize(window.getSize().x * zoomKoef, window.getSize().y * zoomKoef);
            }
            // Movement with arrow keys
            if (event.type == Event::KeyPressed)
            {
                float offsetX = 0.0f;
                float offsetY = 0.0f;
                if (event.key.code == Keyboard::Left)
                {
                    offsetX = -20.0f * zoomKoef;
                }
                else if (event.key.code == Keyboard::Right)
                {
                    offsetX = 20.0f * zoomKoef;
                }
                else if (event.key.code == Keyboard::Up)
                {
                    offsetY = -20.0f * zoomKoef;
                }
                else if (event.key.code == Keyboard::Down)
                {
                    offsetY = 20.0f * zoomKoef;
                }

                view.move(offsetX, offsetY);
            }
        }

        // Set the view
        window.setView(view);

        // Clear the window with black color
        window.clear(Color::Black);

        // Draw axes
        window.draw(Axes);
        window.draw(arrowX);
        window.draw(arrowY);
        window.draw(xText);
        window.draw(yText);

        // Draw ticks and values on x-axis
        int numTicksX = 10 / zoomKoef; // Adjust number of ticks based on zoom factor
        float intervalX = (maxX - minX) / numTicksX;
        for (int i = 0; i <= numTicksX; ++i)
        {
            // Draw ticks
            VertexArray tick(Lines, 2);
            tick[0].position = Vector2f((window.getSize().x / numTicksX) * i, zeroY - 5);
            tick[1].position = Vector2f((window.getSize().x / numTicksX) * i, zeroY + 5);
            tick[0].color = Color::White;
            tick[1].color = Color::White;
            window.draw(tick);

            // Draw values
            float valueX = minX + intervalX * i;
            Text text;
            text.setFont(font);
            text.setString(to_string(valueX));
            text.setCharacterSize(12);
            text.setFillColor(Color::White);
            text.setString(to_string(valueX).substr(0, to_string(valueX).find('.') + 3));
            text.setPosition((window.getSize().x / numTicksX) * i - 10, zeroY + 10);
            window.draw(text);
        }

        // Draw ticks and values on y-axis
        int numTicksY = 10 / zoomKoef; // Adjust number of ticks based on zoom factor
        float intervalY = ((maxY - minY) / numTicksY);
        for (int i = 0; i <= numTicksY; ++i)
        {
            // Draw ticks
            VertexArray tick(Lines, 2);
            tick[0].position = Vector2f(zeroX + 5, window.getSize().y - (window.getSize().y / numTicksY) * i - 40);
            tick[1].position = Vector2f(zeroX - 5, window.getSize().y - (window.getSize().y / numTicksY) * i - 40);
            tick[0].color = Color::White;
            tick[1].color = Color::White;
            window.draw(tick);

            // Draw values
            float valueY = minY + intervalY * i;
            Text text;
            text.setFont(font);
            text.setString(to_string(valueY));
            text.setCharacterSize(12);
            text.setFillColor(Color::White);
            text.setString(to_string(valueY).substr(0, to_string(valueY).find('.') + 3));
            text.setPosition(zeroX + 10, window.getSize().y - (window.getSize().y / numTicksY) * i - 50);
            window.draw(text);
        }

        // Draw the function graph
        VertexArray graph(LineStrip, window.getSize().x);
        for (int i = 0; i < window.getSize().x; ++i)
        {
            float x = minX + (maxX - minX) * i / window.getSize().x;
            float y = window.getSize().y * (1 - (func(x) - minY) / (maxY - minY)) - 40;
            graph[i].position = Vector2f(i, y);
            graph[i].color = Color::Red;
        }
        window.draw(graph);

        // Calculate position for info box
        Vector2f infoPosition = view.getCenter() - view.getSize() / 2.0f;
        infoPosition.x += 10;
        infoPosition.y += 10;

        // Draw information on the screen
        string funcName = "Function: y = |sin(x)| + cos(|x|)";
        string scale = to_string(zoomKoef);
        scale = "Scale: " + scale.substr(0, scale.find('.') + 3);
        string offsetXstr = to_string(view.getCenter().x - window.getSize().x / 2);
        offsetXstr = "OffsetX: " + offsetXstr.substr(0, offsetXstr.find('.') + 2);
        string offsetYstr = to_string((int)(window.getSize().y / 2 - view.getCenter().y));
        offsetYstr = "OffsetY: " + offsetYstr;

        // Display information on the screen
        Text text;
        text.setFont(font);
        text.setString(funcName + "\n" + scale + "\n" + offsetXstr + "\n" + offsetYstr);
        text.setCharacterSize(12);
        text.setFillColor(Color::White);
        text.setPosition(infoPosition);
        window.draw(text);

        window.display();
    }
    return 0;
}
