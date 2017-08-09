#include "Grid.h"
#include "math.h"
#include "Primitive.h"
#include "ply.h"

typedef enum 
{
	flat,
	smooth
}TriangleType;

Grid::Grid()
	:AggregatePrimitive(),
	nx(0),
	ny(0),
	nz(0)
{
}

Grid::Grid(Mesh* mesh_ptr)
	: AggregatePrimitive(),
	nx(0), ny(0), nz(0), meshPtr(mesh_ptr)
{
}

Grid::~Grid(){

}

void Grid::setupCells(){
	Vector3 p0 = minCoordinates();
	Vector3 p1 = maxCoordinates();
	bbox.x0 = p0.x; bbox.y0 = p0.y; bbox.z0 = p0.z;
	bbox.x1 = p1.x; bbox.y1 = p1.y; bbox.z1 = p1.z;

	int numOfObjects = objects.size();
	float wx = p1.x - p0.x;
	float wy = p1.y - p0.y;
	float wz = p1.z - p0.z;
	float multiplier = 2.0;   //about 8 times more cells than objects
	float s = std::pow(wx*wy*wz/numOfObjects,0.3333333);
	nx = multiplier*wx / s + 1;
	ny = multiplier*wy / s + 1;
	nz = multiplier*wz / s + 1;
	int numCells = nx*ny*nz;
	cells.reserve(numOfObjects);
	for (int j = 0; j < numCells; j++)
	{
		cells.push_back(nullptr);
	}
	std::vector<int> counts;
	counts.reserve(numCells);
	for (int j = 0; j < numCells; j++)
		counts.push_back(0);
	BBox objBbox;
	int index;
	for (auto j = objects.begin(); j != objects.end(); j++)
	{
		objBbox = (*j)->getBoundingBox();
		int ixmin = clamp((objBbox.x0 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymin = clamp((objBbox.y0 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmin = clamp((objBbox.z0 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
		int ixmax = clamp((objBbox.x1 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymax = clamp((objBbox.y1 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmax = clamp((objBbox.z1 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

		for (int iz = izmin; iz < izmax; iz++){
			for (int iy = iymin; iy <= iymax; iy++){
				for (int ix = ixmin; ix <= ixmax; ix++) {
					index = ix + nx * iy + nx * ny * iz;

					if (counts[index] == 0)
					{
						cells[index] = *j;
						counts[index] += 1;
					}
					else{
						if (counts[index] == 1)
						{
							auto aggregateptr = std::make_shared<AggregatePrimitive>();
							aggregateptr->addObject(cells[index]);
							aggregateptr->addObject(*j);
							cells[index] = aggregateptr;
							counts[index] += 1;
						}
						else{
							//忘记这里是要写啥了!
							//太久没看了,在说吧!
							counts[index] += 1;
						}
					}
				}
			}
		}
	}
	objects.erase(objects.begin(),objects.end());
	counts.erase(counts.begin(),counts.end());
}

Vector3 Grid::minCoordinates(){
	BBox bbox;
	Vector3 p0(MAXNUMBER,MAXNUMBER,MAXNUMBER);
	for (auto i = objects.begin(); i != objects.begin(); i++)
	{
		bbox = (*i)->getBoundingBox();
		if (bbox.x0 < p0.x)
			p0.x = bbox.x0;
		if (bbox.y0 < p0.y)
			p0.y = bbox.y0;
		if (bbox.z0 < p0.z)
			p0.z = bbox.z0;
	}
	p0.x -= MINNUMBER; p0.y -= MINNUMBER; p0.z -= MINNUMBER;
	return p0;
}
Vector3 Grid::maxCoordinates(){
	BBox bbox;
	Vector3 p0(MINNUMBER, MINNUMBER, MINNUMBER);
	for (auto i = objects.begin(); i != objects.begin(); i++)
	{
		bbox = (*i)->getBoundingBox();
		if (bbox.x0 > p0.x)
			p0.x = bbox.x0;
		if (bbox.y0 > p0.y)
			p0.y = bbox.y0;
		if (bbox.z0 > p0.z)
			p0.z = bbox.z0;
	}
	p0.x -= MINNUMBER; p0.y -= MINNUMBER; p0.z -= MINNUMBER;
	return p0;
}
BBox Grid::getBoundingBox(){
	return bbox;
}
bool Grid::intersectP(Ray& ray, float* thit, Intersection* in){
	return false;
}
bool Grid::shadowIntersect(Ray& ray){
	return false;
}

void Grid::read_ply_file(char* file_name, const int triangle_type){
	// Vertex definition 

	typedef struct Vertex {
		float x, y, z;      // space coordinates       
	} Vertex;

	// Face definition. This is the same for all files but is placed here to keep all the definitions together

	typedef struct Face {
		unsigned char nverts;    // number of vertex indices in list
		int* verts;              // vertex index list 
	} Face;
	// list of property information for a vertex
	// this varies depending on what you are reading from the file
	PlyProperty vert_props[] = {
			{ "x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, x), 0, 0, 0, 0 },
			{ "y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, y), 0, 0, 0, 0 },
			{ "z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, z), 0, 0, 0, 0 }
	};

	// list of property information for a face. 
	// there is a single property, which is a list
	// this is the same for all files

	PlyProperty face_props[] = {
			{ "vertex_indices", PLY_INT, PLY_INT, offsetof(Face, verts),
			1, PLY_UCHAR, PLY_UCHAR, offsetof(Face, nverts) }
	};

	// local variables

	int 			i, j;
	PlyFile*		ply;
	int 			nelems;		// number of element types: 2 in our case - vertices and faces
	char**			elist;
	int 			file_type;
	float 			version;
	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;
	Vertex**		vlist;
	Face**			flist;
	char*			elem_name;
	int				num_comments;
	char**			comments;
	int 			num_obj_info;
	char**			obj_info;


	// open a ply file for reading

	ply = ply_open_for_reading(file_name, &nelems, &elist, &file_type, &version);
	for ( i = 0; i < nelems; i++)
	{
		elem_name = elist[i];
		plist = ply_get_element_description(ply, elem_name, &num_elems, &nprops);
		if (equal_strings("vertex", elem_name)) {
			// set up for getting vertex elements
			// the three properties are the vertex coordinates

			ply_get_property(ply, elem_name, &vert_props[0]);
			ply_get_property(ply, elem_name, &vert_props[1]);
			ply_get_property(ply, elem_name, &vert_props[2]);

			// reserve mesh elements

			meshPtr->num_vertices = num_elems;
			meshPtr->vertices.reserve(num_elems);
			// grab all the vertex elements
			for (j = 0; j < num_elems; j++) {
				Vertex* vertex_ptr = new Vertex;

				// grab an element from the file

				ply_get_element(ply, (void *)vertex_ptr);
				meshPtr->vertices.push_back(Vector3(vertex_ptr->x, vertex_ptr->y, vertex_ptr->z));
				delete vertex_ptr;
			}
		}
		if (equal_strings("face", elem_name)) {
			// set up for getting face elements
			ply_get_property(ply, elem_name, &face_props[0]);   // only one property - a list
			meshPtr->num_triangles = num_elems;
			objects.reserve(num_elems);  // triangles will be stored in Compound::objects
			// the following code stores the face numbers that are shared by each vertex
			meshPtr->vertexFaces.reserve(meshPtr->num_vertices);
			vector<int> faceList;

			for (j = 0; j < meshPtr->num_vertices; j++)
				meshPtr->vertexFaces.push_back(faceList); // store empty lists so that we can use the [] notation below
			// grab all the face elements

			int count = 0; // the number of faces read
			
			for (j = 0; j < num_elems; j++) {
				// grab an element from the file 

				Face* face_ptr = new Face;

				ply_get_element(ply, (void *)face_ptr);
				
				// construct a mesh triangle of the specified type
				
				if (triangle_type == flat) {
				}
				if (triangle_type == smooth) {
				}
			}
			if (triangle_type == flat)
				meshPtr->vertexFaces.erase(meshPtr->vertexFaces.begin(), meshPtr->vertexFaces.end());
		}
	}
	// grab and print out the comments in the file
	ply_close(ply);
}
void Grid::read_falt_triangles(char* filename){
	read_ply_file(filename, flat);
}
void Grid::read_smooth_triangles(char* filename){
	read_ply_file(filename,smooth);
}
