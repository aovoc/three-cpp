
#include "base/Window.h"
#include "base/Scene.h"
#include "base/Camera.h"
#include "base/Mesh.h"
#include "base/Camera.h"
#include "base/PerspectiveCamera.h"
#include "material/DefaultMaterials.h"
#include "base/Texture.h"
#include "loader/ImageUtils.h"
#include "base/CubeGeometry.h"
#include "opengl/GLRenderer.h"
#include "base/Code.h"

#include <iostream>

using namespace three;

class CubeDemo : public Window
{
  public:
    CubeDemo()
      : Window(1024, 768)
    {
      setTitle("Cube Example");

      scene = new Scene();

      camera = new PerspectiveCamera(70, 1024.0 / 768.0, 1, 1000);
      camera->position.z = -5;
      camera->position.y = 2;
      camera->lookAt(Vector3(0, 0, 0));
      scene->add(camera);

      Geometry * geometry = new CubeGeometry(2, 2, 2);
      MeshBasicMaterial * material = new MeshBasicMaterial();
      material->map = ImageUtils::loadTexture("assets/textures/crate.png");
      material->diffuse = Color(1, 1, 1);
      material->useTextureMap = true;
      material->gammaCorrection = true;

      mesh = new Mesh(geometry, material);
      scene->add(mesh);

      renderer = new GLRenderer();
    }

    void resize(int width, int height)
    {
      renderer->setSize(width, height);
      camera->aspect = width / (float)height;
      camera->updateProjectionMatrix();
    }

    bool update(double dt)
    {
      mesh->rotation.x += dt * 0.05;
      mesh->rotation.y += dt * 0.1;
      mesh->matrixWorldNeedsUpdate = true;

      return !isKeyDown(Key::Esc);
    }

    void paint()
    {
      renderer->render(scene, camera);
    }

  private:
    Renderer * renderer;
    Scene * scene;
    PerspectiveCamera * camera;
    Mesh * mesh;
};


int main(int argc, char * argv[])
{
  CubeDemo demo;
  demo.run();
  return 0;
}
