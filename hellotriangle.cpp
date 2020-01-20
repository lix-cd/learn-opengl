#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "iostream"

int main()
{
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // ���Ͻ�
        0.5f, -0.5f, 0.0f,  // ���½�
        -0.5f, -0.5f, 0.0f, // ���½�
        -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };

    unsigned int indices[] = { // ������0��ʼ
        0, 1, 3,
        1, 2 ,3
    };

    // ��ʼ��glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // ����OpenGL����ָ��
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ���������������
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ������ɫ�������ID
    unsigned int VBO;
    // ���ɶ��㻺�����
    glGenBuffers(1, &VBO);
    // ���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ���������ݸ��Ƶ������ڴ���
    // GL_STATIC_DRAW ���ݲ���򼸺�����ı�
    // GL_DYNAMAMIC_DRAW ���ݱ��ı�ܶ�
    // GL_STREAM_DRAW ����ÿ�λ��Ƶ�ʱ�򶼻ᱻ�ı�
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ʹ����ɫ�����Ա�д������ɫ��
    const char* shader_source = " \
       \n #version 330 core   \
       \n layout (location = 0) in vec3 aPos; \
       \n void main() \
       \n {            \
        \n gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
       \n }";
    // ������ɫ������
    unsigned int  vertexShader;
    // ����һ��������ɫ����������ɫ�����ͣ�������ɫ��ID
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shader_source, nullptr);
    glCompileShader(vertexShader);
    // ��ⶥ����ɫ���Ƿ񱻱���ɹ�
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    std::cout << success << std::endl;
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ʹ����ɫ�����Ա�дƬ����ɫ��
    // ���һ��4������������ʾ�����������ɫ
    // ����vec4���ĸ������ֱ��� ��������͸����
    const char* fragment_shader = " \
        \n #version 330 core \
        \n out vec4 FragColor; \
        \n \
        \n void main()       \
        \n{ \
        \n    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
        \n}";
    unsigned int fragment_shader_id;
    // ����һ��Ƭ����ɫ��
    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader, nullptr);
    // ������ɫ��
    glCompileShader(fragment_shader_id);
    // ����һ����ɫ���������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // ����ɫ�����ӵ���������ϲ�����
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragment_shader_id);
    glLinkProgram(shaderProgram);
    // ���������ɫ�������Ƿ�ʧ��
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        // ���ʧ�ܣ� ��ȡ������Ϣ�����
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
    // ʹ�øոմ����ĳ��������Ϊ���Ĳ������Լ����������
    glUseProgram(shaderProgram);
    // ��ɫ���������ӵ��������󣬾Ͳ���Ҫ��ɫ�������ˣ�����ɾ����
    glDeleteShader(vertexShader);
    glDeleteShader(fragment_shader_id);
    // ʹ��glVertexAttribPointer��֪OpenGL��ν�����������
    // ��һ������������0��ʼ��������
    // �ڶ��������Ƕ������ԵĴ�С����Ϊ����������vec3����3��ֵ��ɣ����Դ�С��3
    // ��������������������
    // �������ݱ�׼��
    // ����
    // ƫ����
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    //// ���ƶ������鵽��������OpenGLʹ�� ���Ȱ��ٸ��ƣ�
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //// 1.���ö�������ָ��
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //// 2.ʹ����ɫ������
    //glUseProgram(shaderProgram);
    //// 3.��������


    // ����һ��VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 1. ��VAO
    glBindVertexArray(VAO);
    // 2. �Ѷ������鸴�Ƶ���������OpenGLʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. �������ǵĶ������鵽һ�����������У���OpenGLʹ��
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        // ��һ��������ͼԪ������
        // �ڶ�����������������ʼ����
        // �����������ǻ��ƵĶ������
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_TRIANGLES, 4, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}