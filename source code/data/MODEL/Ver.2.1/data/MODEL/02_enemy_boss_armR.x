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
 -113.90737;0.00555;-20.53348;,
 -113.90740;18.15869;-10.05273;,
 -0.27686;18.15869;-10.05273;,
 -0.27686;0.00555;-20.53348;,
 -113.90740;18.15869;10.90878;,
 -0.27686;18.15869;10.90878;,
 -113.90737;0.00555;21.38953;,
 -0.27686;0.00555;21.38953;,
 -113.90740;-18.14772;10.90878;,
 -0.27686;-18.14774;10.90878;,
 -113.90740;-18.14772;-10.05273;,
 -0.27686;-18.14774;-10.05273;,
 -164.08679;0.00555;0.42803;,
 -0.27686;0.00555;0.42803;;
 
 18;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,0,3,11;,
 3;12,1,0;,
 3;12,4,1;,
 3;12,6,4;,
 3;12,8,6;,
 3;12,10,8;,
 3;12,0,10;,
 3;13,3,2;,
 3;13,2,5;,
 3;13,5,7;,
 3;13,7,9;,
 3;13,9,11;,
 3;13,11,3;;
 
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
  -0.385452;0.799106;-0.461364;,
  -0.258328;0.189843;-0.947220;,
  -0.258327;0.725397;-0.638017;,
  -0.258327;0.915238;0.309203;,
  -0.258327;0.189842;0.947221;,
  -0.258328;-0.725395;0.638019;,
  -0.258328;-0.915237;-0.309204;,
  0.000000;0.500001;-0.866025;,
  0.000000;1.000000;0.000000;,
  0.000000;0.500001;0.866025;,
  -0.000000;-0.499998;0.866027;,
  -0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;-0.499998;-0.866027;,
  -0.385452;0.000001;0.922728;,
  -0.385453;-0.799105;-0.461365;;
  18;
  4;1,2,7,7;,
  4;8,3,8,8;,
  4;9,4,9,9;,
  4;10,5,10,10;,
  4;11,6,11,11;,
  4;13,13,13,13;,
  3;0,2,1;,
  3;0,3,2;,
  3;14,4,3;,
  3;14,5,4;,
  3;15,6,5;,
  3;15,1,6;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;;
 }
 MeshTextureCoords {
  14;
  0.696775;0.478673;,
  0.669745;0.436639;,
  0.500701;0.374105;,
  0.501113;0.435812;,
  0.628200;0.447588;,
  0.500403;0.425066;,
  0.612898;0.485282;,
  0.500332;0.480614;,
  0.628200;0.520250;,
  0.500403;0.529189;,
  0.669745;0.524568;,
  0.500701;0.550522;,
  0.673063;0.486111;,
  0.500512;0.470186;;
 }
}
