#include "Object3D.h"
#include <math.h>
#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations

Object3D::Object3D(const char* file_name,GLuint* shader_programme){
	this-> shader_programme=shader_programme;
	//assert(tools::load_mesh(file_name, &vao, &numvertices));
	glUseProgram (*shader_programme);
	mat_location = glGetUniformLocation (*shader_programme, "model");
	assert(load_mesh(file_name));
	M=glm::mat4();
	R=glm::mat4();
	T=glm::mat4();
	pos=glm::vec3();
	scale=glm::vec3(1.0f,1.0f,1.0f);
	rotation=glm::vec3();
	enabled=true;
	update();
}

int Object3D::getnumVertices(){
	return this->numvertices;
}

GLuint Object3D::getVao(){
	return this->vao;
}

void Object3D::move(float x,float y,float z){
	pos.x+=x;
	pos.y+=y;
	pos.z+=z;
}

void Object3D::move_forward(float d){
	float newX=d*cos(rotation.y);
	float newZ=d*sin(rotation.y);
	pos.x-=newX;
	pos.z-=newZ;
}

void Object3D::move_backward(float d){
	pos.x+=d*cos(rotation.y);
	pos.z+=d*sin(rotation.y);
}

void Object3D::setPos(float x,float y,float z){
	pos.x=x;
	pos.y=y;
	pos.z=z;
}

void Object3D::set_scale(float x,float y,float z){
	scale.x=x;
	scale.y=y;
	scale.z=z;
}

void Object3D::rotate(float x,float y,float z){
	rotation.x=fmod(rotation.x+x,2.0f*M_PI);
	rotation.y=fmod(rotation.y+y,2.0f*M_PI);
	rotation.z=fmod(rotation.z+z,2.0f*M_PI);
}

 void Object3D::update(){
	M=glm::mat4();
	M=glm::translate(M,pos);
	M=glm::scale(M,scale);
	M=glm::rotate(M,-rotation.y,glm::vec3(0.0f,1.0f,0.0f));
	
}

void Object3D::render(){
	/*
	glUniformMatrix4fv (mat_location, 1, GL_FALSE, glm::value_ptr(M));
	glBindVertexArray(getVao());
	glDrawArrays(GL_TRIANGLES,0,getnumVertices());
	*/
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->vao);
    glBindTexture(GL_TEXTURE_2D, tex);
	glUniformMatrix4fv(mat_location, 1, GL_FALSE, glm::value_ptr(M));
    glDrawElements(GL_TRIANGLES, FFACTOR*numFaces, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}



bool Object3D::load_mesh(const char* file_name){
	const aiScene* scene = aiImportFile (file_name, aiProcess_Triangulate);
	if (!scene) {
		fprintf (stderr, "ERROR: reading mesh %s\n", file_name);
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0];
	
	this->numvertices=mesh->mNumVertices;
	this->numFaces   =mesh->mNumFaces;
	FTYPE=GL_TRIANGLES;
	FFACTOR=0;

	GLfloat* points = NULL; // array of vertex points
	GLfloat* normals = NULL; // array of vertex normals
	GLfloat* texcoords = NULL; // array of texture coordinates
    GLuint * indices = NULL;
    if (mesh->HasPositions()) {
    	points = (GLfloat*)malloc (getnumVertices() * 3 * sizeof (GLfloat));
		for (int i = 0; i < getnumVertices(); i++) {
			const aiVector3D* vp = &(mesh->mVertices[i]);
			points[i * 3] = (GLfloat)vp->x;
			points[i * 3 + 1] = (GLfloat)vp->y;
			points[i * 3 + 2] = (GLfloat)vp->z;
		}
    }

	if (mesh->HasNormals ()) {
		normals = (GLfloat*)malloc (getnumVertices() * 3 * sizeof (GLfloat));
		for (int i = 0; i < getnumVertices(); i++) {
			const aiVector3D* vn = &(mesh->mNormals[i]);
			normals[i * 3] = (GLfloat)vn->x;
			normals[i * 3 + 1] = (GLfloat)vn->y;
			normals[i * 3 + 2] = (GLfloat)vn->z;
		}
	}

	if (mesh->HasTextureCoords (0)) {
		texcoords = (GLfloat*)malloc (getnumVertices() * 2 * sizeof (GLfloat));
		for (int i = 0; i < getnumVertices(); i++) {
			const aiVector3D* vt = &(mesh->mTextureCoords[0][i]);
			texcoords[i * 2] = (GLfloat)vt->x;
			texcoords[i * 2 + 1] = (GLfloat)vt->y;
		}
	}

	if (mesh->HasFaces()) {
        this->FFACTOR=mesh->mFaces[0].mNumIndices;
		indices = (GLuint*)malloc(numFaces * FFACTOR * sizeof (GLuint));
		for (int i = 0; i < numFaces; ++i) {
		    for (int j = 0; j < FFACTOR; ++j) {
               indices[FFACTOR*i + j] = mesh->mFaces[i].mIndices[j]; 
            }
		}
	}

	//this->makevao(points, normals, texcoords, indices);

//making vao

	glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
  
    if(&points){
        glGenBuffers (1, &vbo);
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        glBufferData ( GL_ARRAY_BUFFER, 3 * numvertices * sizeof(GLfloat), points, GL_STATIC_DRAW);
    	
        if(indices){
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numFaces * FFACTOR, indices, GL_STATIC_DRAW);
        }
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (0);
        
    }
  
    if(normals){
        glGenBuffers (1, &nbo);
        glBindBuffer (GL_ARRAY_BUFFER, nbo);
        glBufferData ( GL_ARRAY_BUFFER, 3 * numvertices * sizeof (GLfloat), normals, GL_STATIC_DRAW);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (1);
    }
    if(texcoords){
        glGenBuffers (1, &tbo);
        glBindBuffer (GL_ARRAY_BUFFER, tbo);
        glBufferData ( GL_ARRAY_BUFFER, 2 * numvertices * sizeof (GLfloat), texcoords, GL_STATIC_DRAW);
        glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (2);
    }
    glBindVertexArray(0);


	free(points);
    free(normals);
    free(texcoords);
    free(indices);
	aiReleaseImport (scene);
	printf ("mesh loaded\n");

	return true;
}