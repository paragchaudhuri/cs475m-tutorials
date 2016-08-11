#include<iostream>
#include <GL/glut.h>
#include<vector>

#ifndef _HNODE_HPP_
#define _HNODE_HPP_

void vertexcopy(float *src,float *dest);

// A simple class that represents a node in the hierarchy tree
class HNode {
private:
  float tx,ty,tz;
  float rx,ry,rz;
  int num_vertices;
  float **vertex_pos;
  float **vertex_col;

  std::vector<HNode*> children;
  HNode* parent;

public:
  HNode (HNode* parent, int num_vertices, float pos_v4[][4],  float col_v4[][4]);
  void add_child(HNode*);
  void render();
  void change_parameters(float tx,float ty,float tz,float rx,float ry,float rz);
  void render_tree();
  void inc_rx();
  void inc_ry();
  void inc_rz();
  void dec_rx();
  void dec_ry();
  void dec_rz();
};

#endif
