////////////////////////////////////////////////////////
//
// ply model reading sample program
//
// Han-Wei Shen
//
////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include "ply.h"

typedef struct Vertex {
  float x, y, z;
  float nx, ny, nz;
} Vertex;

typedef struct Face {
  unsigned int count;
  unsigned int *vertices;
  float nx, ny, nz;
} Face;

char* string_list[] = {
  "x", "y", "z", "nx", "ny", "nz", "vertex_indices"
};

float cx, cy, cz; 
float x_min, x_max, y_min, y_max, z_min, z_max; 

Vertex** vertices = 0;
Face** faces = 0;
unsigned int vertexcount;
unsigned int facecount;
int vertexnormals = 0;
int facenormals = 0;

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
void store_ply(PlyFile* input, Vertex ***vertices, Face ***faces,
	       unsigned int* vertexcount, unsigned int* facecount,
	       int* vertexnormals, int* facenormals) {
  int i, j;

  // go through the element types
  for(i = 0; i < input->num_elem_types; i = i + 1) {
    int count;
    
    // setup the element for reading and get the element count
    char* element = setup_element_read_ply(input, i, &count);

    // get vertices
    if(strcmp("vertex", element) == 0) {
      *vertices = (Vertex**)malloc(sizeof(Vertex) * count);
      *vertexcount = count;

      // run through the properties and store them
      for(j = 0; j < input->elems[i]->nprops; j = j + 1) {
	PlyProperty* property = input->elems[i]->props[j];
	PlyProperty setup;

	if(strcmp("x", property->name) == 0 &&
	   property->is_list == PLY_SCALAR) {

	  setup.name = string_list[0];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Vertex, x);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	}
	else if(strcmp("y", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[1];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Vertex, y);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	}
	else if(strcmp("z", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[2];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Vertex, z);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	}
	else if(strcmp("nx", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[3];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Vertex, nx);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	  *vertexnormals = 1;
	}
	else if(strcmp("ny", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[4];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Vertex, ny);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	  *vertexnormals = 1;
	}
	else if(strcmp("nz", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[5];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Vertex, nz);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	  *vertexnormals = 1;
	}
	// dunno what it is
	else {
	  fprintf(stderr, "unknown property type found in %s: %s\n",
		  element, property->name);
	}
      }

      // do this if you want to grab the other data
      // list_pointer = get_other_properties_ply
      //                (input, offsetof(Vertex, struct_pointer));

      // copy the data
      for(j = 0; j < count; j = j + 1) {
	(*vertices)[j] = (Vertex*)malloc(sizeof(Vertex));
	
	get_element_ply(input, (void*)((*vertices)[j]));
      }
    }
    // get faces
    else if(strcmp("face", element) == 0) {
      *faces = (Face**)malloc(sizeof(Face) * count);
      *facecount = count;

      // run through the properties and store them
      for(j = 0; j < input->elems[i]->nprops; j = j + 1) {
	PlyProperty* property = input->elems[i]->props[j];
	PlyProperty setup;

	if(strcmp("vertex_indices", property->name) == 0 &&
	   property->is_list == PLY_LIST) {

	  setup.name = string_list[6];
	  setup.internal_type = Uint32;
	  setup.offset = offsetof(Face, vertices);
	  setup.count_internal = Uint32;
	  setup.count_offset = offsetof(Face, count);

	  setup_property_ply(input, &setup);
	}
	else if(strcmp("nx", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[3];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Face, nx);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	  *facenormals = 1;
	}
	else if(strcmp("ny", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[4];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Face, ny);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	  *facenormals = 1;
	}
	else if(strcmp("nz", property->name) == 0 &&
		property->is_list == PLY_SCALAR) {

	  setup.name = string_list[5];
	  setup.internal_type = Float32;
	  setup.offset = offsetof(Face, nz);
	  setup.count_internal = 0;
	  setup.count_offset = 0;

	  setup_property_ply(input, &setup);
	  *facenormals = 1;
	}
	// dunno what it is
	else {
	  fprintf(stderr, "unknown property type found in %s: %s\n",
		  element, property->name);
	}
      }
	
      // do this if you want to grab the other data
      // list_pointer = get_other_properties_ply
      //                (input, offsetof(Face, struct_pointer));
      
      // copy the data
      for(j = 0; j < count; j = j + 1) {
	(*faces)[j] = (Face*)malloc(sizeof(Face));
	
	get_element_ply(input, (void*)((*faces)[j]));
      }
    }
    // who knows?
    else {
      fprintf(stderr, "unknown element type found: %s\n", element);
    }
  }

  // if you want to grab the other data do this
  // get_other_element_ply(input);
}

////////////////////////////////////////////////////////////
//    Find the geometry center of the input model 
////////////////////////////////////////////////////////////
void find_center (float& cx, float& cy, float& cz, 
		  float& minx, float& maxx, float&miny, 
		  float &maxy, float &minz, float & maxz)
{
  float x, y, z; 
  float min_x=9999, max_x=-9999, min_y=9999, max_y=-9999; 
  float min_z=9999, max_z=-9999; 

  x = y= z = 0; 
  for(int i = 0; i < vertexcount; i++) {
    x += vertices[i]->x; 
    y += vertices[i]->y; 
    z += vertices[i]->z; 
    if (min_x >vertices[i]->x) min_x = vertices[i]->x; 
    if (max_x <vertices[i]->x) max_x = vertices[i]->x; 
    if (min_y >vertices[i]->y) min_y = vertices[i]->y; 
    if (max_y <vertices[i]->y) max_y = vertices[i]->y; 
    if (min_z >vertices[i]->z) min_z = vertices[i]->z; 
    if (max_z <vertices[i]->z) max_z = vertices[i]->z; 
  }
  cx = x / (float) vertexcount; 
  cy = y / (float) vertexcount; 
  cz = z / (float) vertexcount; 
  minx = min_x; maxx = max_x; 
  miny = min_y; maxy = max_y; 
  minz = min_z; maxz = max_z; 
}

///////////////////////////////////////////////////////////////

int main(int argc, char** argv) 
{

  PlyFile* input;

  // get the ply structure and open the file
  input = read_ply(stdin);

  // read in the data
  store_ply(input, 
	    &vertices, &faces, 
	    &vertexcount, &facecount,
	    &vertexnormals, &facenormals);

  // close the file
  close_ply(input);

  find_center(cx, cy, cz, x_min, x_max, 
	      y_min, y_max, z_min, z_max); 
  printf("geometry center = %f %f %f \n", cx, cy, cz); 
  printf("geometry bound = x: %f %f y: %f %f z: %f %f\n", 
	 x_min, x_max, y_min, y_max, z_min, z_max); 
}


