#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#pragma comment(lib,"gltools.lib")

GLShaderManager shaderManager;
GLMatrixStack modelViewMatrix;              //模型视图矩阵
GLMatrixStack projectionMatrix;             //投影矩阵
GLFrustum viewFrustum;                      //视景体
GLGeometryTransform transformPipeline;      //几何变换管线
GLTriangleBatch pyramidBatch;
GLFrame viewFrame;                          //参考帧,相当于世界相机

GLBatch floorBatch;
GLBatch ceilingBatch;
GLBatch leftWallBatch;
GLBatch rightWallBatch;

GLfloat viewZ = -65.0f;

#define TEXTURE_BRICK 0
#define TEXTURE_FLOOR 1
#define TEXTURE_CEILING 2
#define TEXTURE_COUNT 3
GLuint textures[TEXTURE_COUNT];
const char* szTextureFiles[TEXTURE_COUNT] = { "block5.tga","block6.tga","block4.tga" };

void ChangeSize(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    viewFrustum.SetPerspective(80.0f, (GLfloat)width / (GLfloat)height, 1.0f, 500.0f);

    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

    //设置变换管线以使用两个矩阵堆栈
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene(void)
{
    static CStopWatch rotTimer;
    static GLfloat vFloorColor[] = { 0.0f,1.0f,0.0f,1.0f };
    static GLfloat vTorusColor[] = { 1.0f,0.0f,0.0f,1.0f };
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    //保存当前的模型视图矩阵
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Translate(0.0f, 0.0f, viewZ);

    //这里使用默认光源进行着色，可以看到阴影
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformPipeline.GetModelViewProjectionMatrix(), 0);

    //画顶
    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FLOOR]);
    floorBatch.Draw();

    //画底
    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_CEILING]);
    ceilingBatch.Draw();

    //左右
    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
    leftWallBatch.Draw();
    rightWallBatch.Draw();

    modelViewMatrix.PopMatrix();

    //将在后台缓冲区进行渲染，然后在结束时交换到前台
    glutSwapBuffers();
    glutPostRedisplay();
}
void SetupRC()
{
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    //设置窗口背景颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //初始化着色器管理器
    shaderManager.InitializeStockShaders();

    //绑定贴图
    glGenTextures(TEXTURE_COUNT, textures);

    //为每张贴图生成mip贴图
    for (int i = 0; i < TEXTURE_COUNT; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        GLbyte* bytes = gltReadTGABits(szTextureFiles[i], &iWidth, &iHeight, &iComponents, &eFormat);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(GL_TEXTURE_2D);
        free(bytes);
    }

    GLfloat z;
    floorBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for (z = 60.0f; z >= 0.0f; z -= 10.0f)
    {
        floorBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
        floorBatch.Vertex3f(-10.0f, -10.0f, z);

        floorBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        floorBatch.Vertex3f(10.0f, -10.0f, z);

        floorBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        floorBatch.Vertex3f(-10.0f, -10.0f, z - 10.0f);

        floorBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        floorBatch.Vertex3f(10.0f, -10.0f, z - 10.0f);
    }
    floorBatch.End();

    ceilingBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for (z = 60.0f; z >= 0.0f; z -= 10.0f)
    {
        ceilingBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        ceilingBatch.Vertex3f(-10.0f, 10.0f, z - 10.0f);

        ceilingBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        ceilingBatch.Vertex3f(10.0f, 10.0f, z - 10.0f);

        ceilingBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
        ceilingBatch.Vertex3f(-10.0f, 10.0f, z);

        ceilingBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        ceilingBatch.Vertex3f(10.0f, 10.0f, z);
    }
    ceilingBatch.End();

    leftWallBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for (z = 60.0f; z >= 0.0f; z -= 10.0f)
    {
        leftWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        leftWallBatch.Vertex3f(-10.0f, -10.0f, z);

        leftWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        leftWallBatch.Vertex3f(-10.0f, 10.0f, z);

        leftWallBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        leftWallBatch.Vertex3f(-10.0f, -10.0f, z - 10.0f);

        leftWallBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        leftWallBatch.Vertex3f(-10.0f, 10.0f, z - 10.0f);
    }
    leftWallBatch.End();

    rightWallBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for (z = 60.0f; z >= 0.0f; z -= 10.0f)
    {
        rightWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        rightWallBatch.Vertex3f(10.0f, -10.0f, z);

        rightWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        rightWallBatch.Vertex3f(10.0f, 10.0f, z);

        rightWallBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        rightWallBatch.Vertex3f(10.0f, -10.0f, z - 10.0f);

        rightWallBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        rightWallBatch.Vertex3f(10.0f, 10.0f, z - 10.0f);
    }
    rightWallBatch.End();

    //移动物体的位置，值越大物体越远，值越小物体越近
    //viewFrame.MoveForward(50.0f);
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        viewZ += 0.5f;
    else if (key == GLUT_KEY_DOWN)
        viewZ -= 0.5f;

    glutPostRedisplay();
}

void ProcessMenu(int value)
{
    for (int i = 0; i < TEXTURE_COUNT; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        switch (value)
        {
        case 0:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        case 1:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;
        case 2:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            break;
        case 3:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            break;
        case 4:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            break;
        case 5:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            break;
        }
    }
    glutPostRedisplay();
}
void ShutdownRC(void)
{
    glDeleteTextures(TEXTURE_COUNT, textures);
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Effects Demo");

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("GL_NEAREST", 0);
    glutAddMenuEntry("GL_LINEAR", 1);
    glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST", 2);
    glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", 3);
    glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", 4);
    glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    SetupRC();
    glutMainLoop();
    ShutdownRC();
    return 0;
}