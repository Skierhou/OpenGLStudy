//#include <GLTools.h>	// OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <GLBatch.h>
//#include <GLGeometryTransform.h>
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
//GLFrame             viewFrame;
//GLFrustum           viewFrustum;
//GLTriangleBatch     torusBatch;
//GLMatrixStack       modelViewMatrix;
//GLMatrixStack       projectionMatrix;
//GLGeometryTransform transformPipeline;
//GLShaderManager     shaderManager;
//
////�Ƿ����������޳�
//int iCull = 0;
////�Ƿ�ʼ��Ȳ���
//int iDepth = 0;
//
////����˵�ѡ��
//void ProcessMenu(int value) {
//    switch (value) {
//    case 1:
//        //������Ȳ���
//        iDepth = !iDepth;
//        break;
//    case 2:
//        //�����������޳�
//        iCull = !iCull;
//        break;
//    case 3:
//        //���ض������ģʽ
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        break;
//    case 4:
//        //���ض������ģʽ
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        break;
//    case 5:
//        //���ض���ε�ģʽ
//        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//        break;
//    }
//
//    //������Ⱦ
//    glutPostRedisplay();
//}
//
////��Ⱦ����
//void RenderScene(void) {
//    //���һ����һ���ض��Ļ�����
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    //�ж��Ƿ����������޳�
//    if (iCull)
//        glEnable(GL_CULL_FACE);
//    else
//        glDisable(GL_CULL_FACE);
//
//    //�ж��Ƿ�����Ȳ���
//    if (iDepth)
//        glEnable(GL_DEPTH_TEST);
//    else
//        glDisable(GL_DEPTH_TEST);
//
//    //���浱ǰ��ģ����ͼ����
//    modelViewMatrix.PushMatrix(viewFrame);
//
//    //����ʹ��Ĭ�Ϲ�Դ������ɫ�����Կ�����Ӱ
//    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
//
//    //������
//    torusBatch.Draw();
//
//    // ��ԭ��ǰ��ģ����ͼ����
//    modelViewMatrix.PopMatrix();
//
//    //���ں�̨������������Ⱦ��Ȼ���ڽ���ʱ������ǰ̨
//    glutSwapBuffers();
//}
//
////Ϊ������һ���Ե�����
//void SetupRC() {
//    //���ô��ڱ�����ɫ
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//
//    //��ʼ����ɫ��������
//    shaderManager.InitializeStockShaders();
//
//    //���ñ任������ʹ�����������ջ
//    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
//
//    //�ƶ������λ�ã�ֵԽ������ԽԶ��ֵԽС����Խ��
//    viewFrame.MoveForward(6.0f);
//
//    //����һ���������Σ����������ǣ����Σ���뾶���ڰ뾶��Ƭ�������ѵ������ڼ������Բ��������Σ�������Խ��Խ��������Բ��
//    gltMakeTorus(torusBatch, 1.0f, 0.3f, 52, 26);
//
//    //����Ĭ�ϵ��С
//    glPointSize(4.0f);
//}
//
////���ⰴ�������ܼ����߷����������
//void SpecialKeys(int key, int x, int y) {
//    //�ϡ��¡����Ұ�����3D ��ת
//    /*
//     * RotateWorld(float fAngle, float x, float y, float z)
//     * fAngle: ��ת����, x/y/z�����ĸ���������ת
//     * m3dDegToRad���Ƕ� -> ����
//     */
//    switch (key) {
//    case GLUT_KEY_UP:
//        viewFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
//        break;
//    case GLUT_KEY_DOWN:
//        viewFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
//        break;
//    case GLUT_KEY_LEFT:
//        viewFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
//        break;
//    case GLUT_KEY_RIGHT:
//        viewFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
//        break;
//    default:
//        break;
//    }
//
//    //������Ⱦ
//    glutPostRedisplay();
//}
//
////���ڴ�С�ı�ʱ�����µĿ�Ⱥ͸߶ȣ�����0,0���������ӿڵ����½����꣬w��h��������
//void ChangeSize(int width, int height) {
//    // ��ֹ��������ĳ���Ϊ0���µ�����
//    if (height == 0) height = 1;
//
//    //������ͼ����λ��
//    glViewport(0, 0, width, height);
//
//    // ����ͶӰ���󣬲��������뵽ͶӰ�����ջ��
//    viewFrustum.SetPerspective(35.0f, float(width) / float(height), 1.0f, 500.0f);
//    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
//}
//
////�������
//int main(int argc, char* argv[]) {
//    //���õ�ǰ����Ŀ¼�����MAC OS X
//    gltSetWorkingDirectory(argv[0]);
//
//    //��ʼ��GLUT��
//    glutInit(&argc, argv);
//
//    /*��ʼ����Ⱦģʽ�����б�־GLUT_DOUBLE��GLUT_RGBA��GLUT_DEPTH��GLUT_STENCIL�ֱ�ָ
//     ˫���崰�ڡ�RGBA��ɫģʽ����Ȳ��ԡ�ģ�建����*/
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
//
//    //��ʼ�����ڴ�С
//    glutInitWindowSize(800, 600);
//    //��������
//    glutCreateWindow("Geometry Test Program");
//
//    //ע��ص�����
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutSpecialFunc(SpecialKeys);
//
//    //�����˵�����һ����Ӧ����
//    glutCreateMenu(ProcessMenu);
//
//    //Ϊ�˵����ѡ��
//    glutAddMenuEntry("Toggle depth test", 1);
//    glutAddMenuEntry("Toggle cull backface", 2);
//    glutAddMenuEntry("Set Fill Mode", 3);
//    glutAddMenuEntry("Set Line Mode", 4);
//    glutAddMenuEntry("Set Point Mode", 5);
//
//    //�Ҽ������˵�
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//    //ȷ����������ĳ�ʼ����û�г����κ����⡣
//    GLenum err = glewInit();
//    if (GLEW_OK != err) {
//        fprintf(stderr, "glew error:%s\n", glewGetErrorString(err));
//        return 1;
//    }
//
//    //��ʼ������
//    SetupRC();
//
//    //�������ѭ��
//    glutMainLoop();
//    return 0;
//}
