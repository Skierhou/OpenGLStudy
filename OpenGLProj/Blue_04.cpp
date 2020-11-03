//#include <iostream>
//
//#include <GLTools.h>	// OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <GLBatch.h>
//#include <GLGeometryTransform.h>
//#include <StopWatch.h>
//
//#include <math.h>
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//
//#pragma comment(lib,"gltools.lib")
//#pragma comment(lib,"opengl32.lib")
//
//GLShaderManager shaderManager;
//GLMatrixStack modelViewMatrix;              //模型视图矩阵
//GLMatrixStack projectionMatrix;             //投影矩阵
//GLFrustum viewFrustum;                      //视景体
//GLGeometryTransform transformPipeline;      //几何变换管线
//GLTriangleBatch torusBatch;
//GLTriangleBatch sphereBatch;
//GLFrame viewFrame;                          //参考帧,相当于世界相机
//
//#define NUM_SPHERE 50
//GLFrame spheres[NUM_SPHERE];
//
//void ChangeSize(int width, int height)
//{
//    glViewport(0, 0, width, height);
//    
//    viewFrustum.SetPerspective(35.0f, float(width) / float(height), 1.0f, 500.0f);
//    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
//
//    //设置变换管线以使用两个矩阵堆栈
//    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
//}
//
//void RenderScene(void)
//{
//    static CStopWatch rotTimer;
//    static GLfloat vFloorColor[] = { 0.0f,1.0f,0.0f,1.0f };
//    static GLfloat vTorusColor[] = { 1.0f,0.0f,0.0f,1.0f };
//    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
//
//	// Clear the window with current clearing color
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//
//	//保存当前的模型视图矩阵
//    modelViewMatrix.PushMatrix(viewFrame);
//
//    modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
//    modelViewMatrix.PushMatrix();
//
//    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
//    //这里使用默认光源进行着色，可以看到阴影
//    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
//
//    //画花托
//    torusBatch.Draw();
//
//    modelViewMatrix.PopMatrix();
//
//    GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
//    for (size_t i = 0; i < NUM_SPHERE; i++)
//    {
//        modelViewMatrix.PushMatrix();
//        modelViewMatrix.Rotate(yRot * -0.1f, 0.0f, 1.0f, 0.0f);
//        //变换当前绘制的坐标系
//        modelViewMatrix.MultMatrix(spheres[i]);
//        shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vGreen);
//        sphereBatch.Draw();
//        modelViewMatrix.PopMatrix();
//    }
//
//    // 还原以前的模型视图矩阵
//    modelViewMatrix.PopMatrix();
//
//    //将在后台缓冲区进行渲染，然后在结束时交换到前台
//    glutSwapBuffers();
//    glutPostRedisplay();
//}
//void SetupRC()
//{
//	shaderManager.InitializeStockShaders();
//
//	//设置窗口背景颜色
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//
//    //初始化着色器管理器
//    shaderManager.InitializeStockShaders();
//
//    //移动物体的位置，值越大物体越远，值越小物体越近
//    viewFrame.MoveForward(50.0f);
//
//    //创建一个花托批次，参数依次是：批次，外半径，内半径，片段数，堆叠数（在计算机中圆是正多边形，顶点数越多越像真正的圆）
//    gltMakeTorus(torusBatch, 1.0f, 0.3f, 52, 26);
//
//    gltMakeSphere(sphereBatch, 0.5f, 30.0f,30.0f);
//
//    for (size_t i = 0; i < NUM_SPHERE; i++)
//    {
//        spheres[i].SetOrigin((GLfloat)((rand() % 400) - 200) * 0.1f, 0, (GLfloat)((rand() % 400) - 200) * 0.1f);
//    }
//}
//
//int main(int argc, char* argv[])
//{
//	gltSetWorkingDirectory(argv[0]);
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("3D Effects Demo");
//
//	GLenum err = glewInit();
//	if (GLEW_OK != err)
//	{
//		/* Problem: glewInit failed, something is seriously wrong. */
//		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//		return 1;
//	}
//
//	glutReshapeFunc(ChangeSize);
//	glutDisplayFunc(RenderScene);
//
//	SetupRC();
//
//	glutMainLoop();
//    return 0;
//}
