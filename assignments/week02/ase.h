#include <iostream>
using namespace std;

struct Vertex {          // vertex ����ü, x, y, z �� ��ġ���� ���´�.
	float x, y, z;
};

struct Face {            // face ����ü, vertex 3���� �ε��� ������ ���´�.
	int vertexIndex[3];
};
struct Normal {          // normal ����ü, �� face ������ �������� x, y, z ���� ���´�.
	float faceNormal[3];
//	float vertexNormal1[3];
//	float vertexNormal2[3];
//	float vertexNormal3[3];
};
struct Color {           // color ����ü,  mesh�� wireframe_color �� r, g, b ������ ���´�.
	float r, g, b;
};

class Mesh {            // mesh Ŭ����
public:
	FILE* fp;               // -> ASE ������ ���� �� �ʿ��� ����������
	char lineBuffer[256];   // -> �� �پ� �о� ���̱� ���� ����
	char stringBuffer[40];  // -> �� ���ڿ� �� �о� ���̱� ���� ����
	
	float max;

	int vertexNum;          // -> vertex ����
	int faceNum;            // -> face ����
	Vertex* vertexList;     // -> vertex ����Ʈ
	Face* faceList;         // -> face ����Ʈ
	Normal* normalList;     // -> normal ����Ʈ
	Color wireframeColor;   // -> mesh �� wireframe color


public:
	Mesh(){
		vertexNum = 0;
		faceNum = 0;
		wireframeColor.r = 0.0;
		wireframeColor.g = 0.0;
		wireframeColor.b = 0.0;
	}
	~Mesh(){
		if(vertexNum != 0)
			delete [] vertexList;
		if(faceNum != 0){
			delete [] faceList;
			delete [] normalList;
		}
	}
	void setColor (float _r, float _g, float _b){
		wireframeColor.r = _r;
		wireframeColor.g = _g;
		wireframeColor.b = _b;
	}
	void clearAse () {        // -> vertex, face, normal ����Ʈ�� �����Ҵ� �����ϴ� �Լ�
		if(vertexNum != 0)
			delete [] vertexList;
		if(faceNum != 0){
			delete [] faceList;
			delete [] normalList;
		}
	}
	void readAse (char* fileName) {         // -> ASE ���Ϸκ��� �����͸� �����ϴ� �Լ�
		float _x;
		float _y;
		float _z;
		int i = 0;
		int j = 0;
		int num = 0;

		if ((fp = fopen(fileName, "r")) == NULL){
			cout << "File is Not Found" << endl;
			return;
		}
		while(fgets(lineBuffer, 256, fp) != NULL)
		{
			sscanf(lineBuffer, "%s", stringBuffer);
			if(strcmp(stringBuffer, "*MESH") == 0){       //��*MESH����� ���ڰ� ���� ������ ��� ����
				fgets(lineBuffer, 256, fp);  // Read the Line  *TIMEVALUE  
				fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_NUMVERTEX
				sscanf(lineBuffer, "%s%d", stringBuffer, &vertexNum);
				vertexList = new Vertex[vertexNum];       // vertex ����Ʈ �����Ҵ� 

				fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_NUMFACES 
				sscanf(lineBuffer, "%s %d", stringBuffer, &faceNum);
				faceList = new Face[faceNum];           // face ����Ʈ �����Ҵ�
				normalList = new Normal[faceNum];       // normal ����Ʈ �����Ҵ� 

				fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEX_LIST  
				sscanf(lineBuffer, "%s", stringBuffer);
				if(strcmp(stringBuffer, "*MESH_VERTEX_LIST") == 0) {
					for(i=0; i<vertexNum; i++){          // vertex �� x, y, z ������ ���� 
						fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEX_LIST  
						//sscanf(lineBuffer, "%s%d%f%f%f", stringBuffer, &num, 
						//	&(vertexList[i].x), &(vertexList[i].y), &(vertexList[i].z));
						sscanf(lineBuffer, "%s%d%f%f%f", stringBuffer, &num, &_x, &_y, &_z);
						for(j=0; j<3; j++){
							if(max < _x)
								max = _x;
							if(max < _y)
								max = _y;
							if(max < _z)
								max = _z;
						}
					/*	vertexList[i].x = _x;
						vertexList[i].y = _y;
						vertexList[i].z = _z;*/
						vertexList[i].x = _x;
						vertexList[i].y = _z;
						vertexList[i].z = -1*_y;
					}
				}
				
				fgets(lineBuffer, 256, fp);  // Read the Line '}'
				fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_FACE_LIST   
				sscanf(lineBuffer, "%s", stringBuffer);
				if(strcmp(stringBuffer, "*MESH_FACE_LIST") == 0) {
					for(i=0; i<faceNum; i++){            // face �� vertex �ε��� ������ ����
						fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_FACE_LIST   
						sscanf(lineBuffer, "%s%s%s%d%s%d%s%d%s%d%s%d%s%d%s", 
							stringBuffer, stringBuffer, stringBuffer, 
							&(faceList[i].vertexIndex[0]), stringBuffer, 
							&(faceList[i].vertexIndex[1]), stringBuffer, 
							&(faceList[i].vertexIndex[2]), stringBuffer, 
							&num, stringBuffer, &num, stringBuffer, &num, stringBuffer);
					}
				}
				
				fgets(lineBuffer, 256, fp);  // Read the Line '}'
				fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_NUMCVERTEX   

				fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_NORMALS   
				sscanf(lineBuffer, "%s", stringBuffer);
				if(strcmp(stringBuffer, "*MESH_NORMALS") == 0) {    // normal �� �������� ������ ����
					for(i=0; i<faceNum; i++){
						fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_FACENORMAL   
						sscanf(lineBuffer, "%s%d%f%f%f", stringBuffer, &num, 
							&(normalList[i].faceNormal[0]), &(normalList[i].faceNormal[1]), &(normalList[i].faceNormal[2]));
						fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEXNORMAL 1 
						fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEXNORMAL 2 
						fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEXNORMAL 3
						
					//	fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEXNORMAL 1 
					//	sscanf(lineBuffer, "%s%d%f%f%f", stringBuffer, &num, 
					//		&(normalList[i].vertexNormal1[0]), &(normalList[i].vertexNormal1[1]), &(normalList[i].vertexNormal1[2]));
					//	fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEXNORMAL 2  
					//	sscanf(lineBuffer, "%s%d%f%f%f", stringBuffer, &num, 
					//		&(normalList[i].vertexNormal2[0]), &(normalList[i].vertexNormal2[1]), &(normalList[i].vertexNormal2[2]));
					//	fgets(lineBuffer, 256, fp);  // Read the Line  *MESH_VERTEXNORMAL 3   
					//	sscanf(lineBuffer, "%s%d%f%f%f", stringBuffer, &num, 
					//		&(normalList[i].vertexNormal3[0]), &(normalList[i].vertexNormal3[1]), &(normalList[i].vertexNormal3[2]));
					}
				}
/*
				while(fgets(lineBuffer, 256, fp) != NULL){    // Read the Line  *WIREFRAME_COLOR  
					sscanf(lineBuffer, "%s", stringBuffer);
					if(strcmp(stringBuffer, "*WIREFRAME_COLOR") == 0){    // mesh �� color ������ ����
						sscanf(lineBuffer, "%s%f%f%f", stringBuffer, 
							&(wireframeColor.r), &(wireframeColor.g), &(wireframeColor.b));
						break;
					}
				}*/
				break;
			}
		}

		fclose(fp);
	}
	/*
	void move(int direction){
		int i = 0;

		switch(direction){
		case 1:        // -z    move front
			for(i; i<vertexNum; i++)
				vertexList[i].z = vertexList[i].z - 0.1;
			break;
		case 2:        // +z    move back 
			for(i; i<vertexNum; i++)
				vertexList[i].z = vertexList[i].z + 0.1;
			break;
		case 3:        // -x    move left 
			for(i; i<vertexNum; i++)
				vertexList[i].x = vertexList[i].x - 0.1;
			break;
		case 4:        // +x    move right 
			for(i; i<vertexNum; i++)
				vertexList[i].x = vertexList[i].x + 0.1;
			break;
		}
	}*/
};
