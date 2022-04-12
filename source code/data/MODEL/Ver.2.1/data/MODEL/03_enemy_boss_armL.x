xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 14;
 113.80285;0.00555;-20.53348;,
 0.17226;0.00555;-20.53348;,
 0.17226;18.15869;-10.05273;,
 113.80287;18.15869;-10.05273;,
 0.17226;18.15869;10.90878;,
 113.80287;18.15869;10.90878;,
 0.17226;0.00555;21.38953;,
 113.80285;0.00555;21.38953;,
 0.17226;-18.14774;10.90878;,
 113.80287;-18.14772;10.90878;,
 0.17226;-18.14774;-10.05273;,
 113.80287;-18.14772;-10.05273;,
 163.98224;0.00555;0.42803;,
 0.17226;0.00555;0.42803;;
 
 18;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,1,0;,
 3;12,0,3;,
 3;12,3,5;,
 3;12,5,7;,
 3;12,7,9;,
 3;12,9,11;,
 3;12,11,0;,
 3;13,2,1;,
 3;13,4,2;,
 3;13,6,4;,
 3;13,8,6;,
 3;13,10,8;,
 3;13,1,10;;
 
 MeshMaterialList {
  8;
  18;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.448800;0.401600;0.282400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.316800;0.316800;0.316800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.006400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Visual Studio 2015\\Projects\\3Dgame_11.08_Ver_01\\data\\TEXTURE\\gear.png";
   }
  }
  Material {
   0.483200;0.483200;0.483200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Visual Studio 2015\\Projects\\3Dgame_11.08_Ver_01\\data\\TEXTURE\\gear.png";
   }
  }
 }
 MeshNormals {
  16;
  0.385452;0.799106;-0.461364;,
  0.258328;0.189842;-0.947221;,
  0.258327;0.725397;-0.638017;,
  0.258327;0.915238;0.309203;,
  0.258328;0.189842;0.947221;,
  0.258328;-0.725395;0.638019;,
  0.258329;-0.915237;-0.309204;,
  0.000000;0.500001;-0.866025;,
  0.000000;1.000000;0.000000;,
  0.000000;0.500001;0.866025;,
  0.000000;-0.499998;0.866027;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.499998;-0.866027;,
  0.385452;0.000001;0.922728;,
  0.385453;-0.799105;-0.461365;;
  18;
  4;1,7,7,2;,
  4;8,8,8,3;,
  4;9,9,9,4;,
  4;10,10,10,5;,
  4;11,11,11,6;,
  4;13,13,13,13;,
  3;0,1,2;,
  3;0,2,3;,
  3;14,3,4;,
  3;14,4,5;,
  3;15,5,6;,
  3;15,6,1;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;;
 }
 MeshTextureCoords {
  14;
  0.303271;0.478656;,
  0.499307;0.435811;,
  0.499564;0.374104;,
  0.330317;0.436595;,
  0.499749;0.425066;,
  0.371873;0.447563;,
  0.499793;0.480614;,
  0.387175;0.485277;,
  0.499749;0.529189;,
  0.371873;0.520260;,
  0.499564;0.550522;,
  0.330317;0.524586;,
  0.326979;0.486104;,
  0.499682;0.470186;;
 }
}
