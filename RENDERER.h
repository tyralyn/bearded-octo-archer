#ifndef RENDERER_H
#define RENDERER_H
#include <RAY.h>
#include <CAMERA.h>
#include <RAY.h>
#include <SCENE.h>
class RENDERER
{
public:
  RENDERER():
    _width(0),
    _height(0),
    _image(NULL)
  {

  }
  RENDERER(int width, int height):
    _width(width),
    _height(height),
    _image(NULL)
  {
    initialize();
  }
  ~RENDERER()
  {
    if(_image)
      delete[] _image;
  }
  VEC3F* image() { 
	return _image; 
  };
  
  //initialize the renderer: make new image color array, set camera values
  void initialize() {
    _image = new VEC3F[_width * _height];
    float aspect = 1.0 * _width / _height;
    _camera.setAspect(aspect);
  }
  
  //render scene
  void render(SCENE& scene) {
    /*for (int i = 0; i< _width * _height; i++) {
	_image[i]=VEC3F(1.0,1.0,0);
  }*/
	int count=0;
    float maxMag = 0;
    for(int y = 0; y < _height; y++){
      for(int x = 0; x < _width; x++){
        int id = y * _width + x;
		//_image[id]=VEC3F(1.0,1.0,0);
        _image[id] = 0;
        VEC3F point = _camera.pixelToWorldCoordinates(1.0 * x / _width, 1.0 * y / _height);
        VEC3F dir = normalize(point - _camera.eye());
        RAY ray(point, dir); 
        _image[id] = scene.computeColor(ray, count);
		//_image[id] = VEC3F(1.0,1.0,0);
		maxMag = max(maxMag, norm(_image[id]));
      }
    }
    //for(int x = 0; x < _width * _height; x++)
      //_image[x] *= 1.0 / maxMag;
  }

  //write image to ppm
  void writePPM(const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
      cout << " Couldn't open file " << filename << "! " << endl;
      return;
    }
    fprintf(file, "P6\n%d %d\n255\n", _width, _height);
    for (int y = 0; y < _height; y++)
      for (int x = 0; x < _width; x++) {
      int i = x + (_height - 1 - y) * _width;

      // map to the [0,255] range
      unsigned char red   = _image[i][0] * 255;
      unsigned char green = _image[i][1] * 255;
      unsigned char blue  = _image[i][2] * 255;
      // fprintf(file,"%u%u%u", red, green, blue);
      fwrite(&red, 1, 1, file);
      fwrite(&green, 1, 1, file);
      fwrite(&blue, 1, 1, file);
    }
    fclose(file);
    
    // output some success information
    cout << " Successfully write to " << filename << " with dimensions: " 
         << _width << " " << _height << endl;
  }

private:
  int _width;
  int _height;
  VEC3F* _image;
  CAMERA _camera;
};
#endif
