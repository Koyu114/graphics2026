#include <GLFW/glfw3.h>
#include <string>
#include <algorithm>

// 5×7 pixel font
const char* getLetter(char c)
{
    switch (c)
    {
        case 'H': return "10001"
                         "10001"
                         "10001"
                         "11111"
                         "10001"
                         "10001"
                         "10001";

        case 'e': return "00000"
                         "00000"
                         "01110"
                         "10001"
                         "11111"
                         "10000"
                         "01111";

        case 'l': return "01100"
                         "00100"
                         "00100"
                         "00100"
                         "00100"
                         "00100"
                         "01110";

        case 'o': return "00000"
                         "00000"
                         "01110"
                         "10001"
                         "10001"
                         "10001"
                         "01110";

        case 'W': return "10001"
                         "10001"
                         "10001"
                         "10101"
                         "10101"
                         "10101"
                         "01010";

        case 'r': return "00000"
                         "00000"
                         "10110"
                         "11001"
                         "10000"
                         "10000"
                         "10000";

        case 'd': return "00001"
                         "00001"
                         "01111"
                         "10001"
                         "10001"
                         "10001"
                         "01111";

        default: return nullptr;
    }
}

// Draw text using quads
void drawText(const std::string& text)
{
    float width = text.size() * 6.0f - 1.0f;

    glPushMatrix();
    glTranslatef(-width / 2.0f, -3.5f, 0.0f);

    glBegin(GL_QUADS);

    for (int i = 0; i < text.size(); i++)
    {
        const char* letter = getLetter(text[i]);

        if (!letter)
            continue;

        for (int row = 0; row < 7; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                if (letter[row * 5 + col] == '1')
                {
                    float x = i * 6.0f + col;
                    float y = 6.0f - row;

                    glVertex2f(x, y);
                    glVertex2f(x + 1, y);
                    glVertex2f(x + 1, y + 1);
                    glVertex2f(x, y + 1);
                }
            }
        }
    }

    glEnd();
    glPopMatrix();
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(
        640, 480, "Hello World", NULL, NULL
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        if (width == 0 || height == 0)
        {
            glfwPollEvents();
            continue;
        }

        glViewport(0, 0, width, height);

        // Keep the aspect ratio
        float size = std::min(width, height);
        float x = 40.0f * width / size;
        float y = 40.0f * height / size;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-x, x, -y, y, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Background
        glClearColor(0.06f, 0.06f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rotate around the Z axis
        float angle = glfwGetTime() * 45.0f;
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        // Text color
        glColor3f(0.4f, 0.87f, 1.0f);

        drawText("Hello World");

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}