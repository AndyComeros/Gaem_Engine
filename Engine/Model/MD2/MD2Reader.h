#pragma once
#include <iostream>
#include <fstream>
#include <Graphics/Graphics.h>
#include <map>
#include <cmath>
#include <DrawItem.h>

struct md2Header
{
	int ident;        
	int version;      

	int skinwidth;    
	int skinheight;   

	int framesize;    

	int num_skins;    
	int num_vertices; 
	int num_st;       
	int num_tris;     
	int num_glcmds;   
	int num_frames;   

	int offset_skins; 
	int offset_st;    
	int offset_tris;  
	int offset_frames;
	int offset_glcmds;
	int offset_end;   

	void Print();
};

/* Vector */
typedef float vec3_t[3];

/* Texture name */
struct md2_skin_t
{
	char name[64];              
};

/* Texture coords */
struct md2_texCoord_t
{
	short s;
	short t;
};

/* Triangle info */
struct md2_triangle_t
{
	unsigned short vertex[3];   
	unsigned short st[3];       
};

/* Compressed vertex */
struct md2_vertex_t
{
	unsigned char v[3];         
	unsigned char normalIndex;  
};

/* Model frame */
struct md2_frame_t
{
	vec3_t scale;               
	vec3_t translate;           
	char name[16];              
	struct md2_vertex_t* verts; 
};

//normal and position vert
struct pos_normal_vert{
	glm::vec3 vertex;
	glm::vec3 normal;
};

struct md2_animation {
	int start;
	int end;
	float speed;
};


class md2_model_t : public DrawItem{
public:
	
	//constructor
	md2_model_t(const char* md2File,const char* textureFile);

	//update animation
	void Update(float deltaTime);
	
	//Set an animation cycle and its name
	void SetAnimation(const std::string& animName, int start, int end, float speed);

	//animate a specific animation cycle
	void Animate(md2_animation animation);
	void Animate(const std::string& animation);

	//render the current verts
	void Render(Camera* camera, Shader* shader, bool isElements, unsigned int primative);
	
	//print the header data
	void PrintHeader();
	
	//set how fast animations are played
	void SetAnimationSpeed(float speed);

private:
	//read in a header and create model data
	int ReadMD2Model(const char* filename);

	//create the inital model
	void CreateModel(int n);

	//liner interpolation function
	float lerp(float start, float end, float factor);	

	std::map<std::string,md2_animation> animations;

	md2Header header;
	md2_skin_t* skins;
	md2_texCoord_t* texcoords;
	md2_triangle_t* triangles;
	md2_frame_t* frames;

	//animation
	float animSpeed = 10.0f;
	int prevFrame = 0;
	float curInterpolation = 0.0f;
	int startFrame = 0;
	int endFrame = 0;

	//current interpolated verts
	pos_normal_vert* currentVerts;

	VAO vao;
	VBO vertvbo;
	VBO uvvbo;
	EBO ebo;
};