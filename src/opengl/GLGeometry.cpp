
#include "opengl/GLGeometry.h"
#include "Geometry.h"

namespace three {

  GLGeometry::GLGeometry(Geometry * source)
    : RenderGeometry(source),
      vertexBuffer(0),
      normalBuffer(0),
      colorBuffer(0),
      indexBuffer(0),
      faceCount(0)
  {
    sourceGeometry->__renderGeometry = this;
  }

}