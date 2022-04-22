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
 265;
 1.76466;7.90533;-3.11612;,
 4.10767;7.90533;-28.27367;,
 -3.23157;7.90533;-28.27367;,
 -0.88856;7.90533;-3.11612;,
 0.00000;14.82432;0.00000;,
 1.14182;14.30066;-1.14182;,
 0.00000;14.30066;-1.61477;,
 0.00000;14.82432;0.00000;,
 1.61477;14.30066;0.00000;,
 0.00000;14.82432;0.00000;,
 1.14182;14.30066;1.14182;,
 0.00000;14.82432;0.00000;,
 -0.00000;14.30066;1.61477;,
 0.00000;14.82432;0.00000;,
 -1.14182;14.30066;1.14182;,
 0.00000;14.82432;0.00000;,
 -1.61477;14.30066;-0.00000;,
 0.00000;14.82432;0.00000;,
 -1.14182;14.30066;-1.14182;,
 0.00000;14.82432;0.00000;,
 0.00000;14.30066;-1.61477;,
 2.10980;12.80940;-2.10980;,
 0.00000;12.80940;-2.98371;,
 2.98371;12.80940;0.00000;,
 2.10980;12.80940;2.10980;,
 -0.00000;12.80940;2.98371;,
 -2.10980;12.80940;2.10980;,
 -2.98371;12.80940;-0.00000;,
 -2.10980;12.80940;-2.10980;,
 0.00000;12.80940;-2.98371;,
 2.75658;10.57760;-2.75658;,
 0.00000;10.57760;-3.89840;,
 3.89840;10.57760;0.00000;,
 2.75658;10.57760;2.75658;,
 -0.00000;10.57760;3.89840;,
 -2.75658;10.57760;2.75658;,
 -3.89840;10.57760;-0.00000;,
 -2.75658;10.57760;-2.75658;,
 0.00000;10.57760;-3.89840;,
 2.98371;7.94500;-2.98371;,
 0.00000;7.94500;-4.21960;,
 4.21960;7.94500;0.00000;,
 2.98371;7.94500;2.98371;,
 -0.00000;7.94500;4.21960;,
 -2.98371;7.94500;2.98370;,
 -4.21960;7.94500;-0.00000;,
 -2.98371;7.94500;-2.98370;,
 0.00000;7.94500;-4.21960;,
 2.75658;5.31240;-2.75658;,
 0.00000;5.31240;-3.89840;,
 3.89840;5.31240;0.00000;,
 2.75658;5.31240;2.75658;,
 -0.00000;5.31240;3.89840;,
 -2.75658;5.31240;2.75658;,
 -3.89840;5.31240;-0.00000;,
 -2.75658;5.31240;-2.75658;,
 0.00000;5.31240;-3.89840;,
 2.10980;3.08059;-2.10980;,
 0.00000;3.08059;-2.98371;,
 2.98371;3.08059;0.00000;,
 2.10980;3.08059;2.10980;,
 -0.00000;3.08059;2.98371;,
 -2.10980;3.08059;2.10980;,
 -2.98371;3.08059;-0.00000;,
 -2.10980;3.08059;-2.10980;,
 0.00000;3.08059;-2.98371;,
 1.14182;1.58934;-1.14182;,
 0.00000;1.58934;-1.61477;,
 1.61477;1.58934;0.00000;,
 1.14182;1.58934;1.14182;,
 -0.00000;1.58934;1.61477;,
 -1.14182;1.58934;1.14182;,
 -1.61477;1.58934;-0.00000;,
 -1.14182;1.58934;-1.14182;,
 0.00000;1.58934;-1.61477;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 0.00000;1.06569;0.00000;,
 -0.78410;7.90533;3.83294;,
 -3.33586;7.90533;27.74516;,
 4.00310;7.90533;27.80920;,
 1.86902;7.90533;3.85610;,
 3.07785;7.90533;-1.32386;,
 16.66929;7.90533;-22.86860;,
 10.25025;7.90533;-26.42672;,
 0.75729;7.90533;-2.61018;,
 2.84446;7.90533;1.60296;,
 26.84524;7.90533;3.10926;,
 26.58912;7.90533;-4.22550;,
 2.75187;7.90533;-1.04865;,
 -1.94676;7.90533;-1.34939;,
 -25.94752;7.90533;-2.85569;,
 -25.69142;7.90533;4.47907;,
 -1.85416;7.90533;1.30222;,
 3.02134;7.90533;1.13269;,
 24.07644;7.90533;-13.20556;,
 19.60859;7.90533;-19.02815;,
 1.40617;7.90533;-0.97226;,
 -1.07691;7.90533;1.95701;,
 -15.04225;7.90533;23.26125;,
 -8.68628;7.90533;26.93084;,
 1.22083;7.90533;3.28363;,
 -0.97753;7.90533;-0.49818;,
 -22.27966;7.90533;13.47041;,
 -17.91407;7.90533;19.37007;,
 0.60065;7.90533;1.63464;,
 -1.19505;7.90533;-0.84610;,
 -18.81175;7.90533;-19.24595;,
 -23.81709;7.90533;-13.87836;,
 -3.00455;7.90533;1.09434;,
 -0.57991;7.90533;-2.18386;,
 -9.39854;7.90533;-26.08226;,
 -16.12907;7.90533;-23.15573;,
 -3.01307;7.90533;-1.12590;,
 1.42651;7.90533;2.91215;,
 22.48381;7.90533;17.24724;,
 26.26381;7.90533;10.95628;,
 2.79304;7.90533;0.63791;,
 -0.11004;7.90533;3.77278;,
 13.48467;7.90533;25.31544;,
 19.45965;7.90533;21.05351;,
 2.04998;7.90533;2.23203;,
 0.34053;11.72609;-36.34805;,
 12.78513;11.72609;-33.87827;,
 12.78513;4.16391;-33.87827;,
 0.34053;4.16391;-36.34805;,
 10.29622;11.72609;-27.05736;,
 0.34053;11.72609;-29.03317;,
 0.34053;4.16391;-29.03317;,
 10.29622;4.16391;-27.05736;,
 23.54901;11.72609;-26.80249;,
 23.54901;4.16391;-26.80249;,
 18.90734;11.72609;-21.39675;,
 18.90734;4.16391;-21.39675;,
 31.17849;11.72609;-16.07634;,
 31.17849;4.16391;-16.07634;,
 25.01090;11.72609;-12.81581;,
 25.01090;4.16391;-12.81581;,
 34.64311;11.72609;-3.14841;,
 34.64311;4.16391;-3.14841;,
 27.78255;11.72609;-2.47348;,
 27.78255;4.16391;-2.47348;,
 33.47495;11.72609;10.23527;,
 33.47495;4.16391;10.23527;,
 26.84808;11.72609;8.23346;,
 26.84808;4.16391;8.23346;,
 27.83183;11.72609;22.26717;,
 27.83183;4.16391;22.26717;,
 22.33357;11.72609;17.85899;,
 22.33357;4.16391;17.85899;,
 18.47585;11.72609;31.32235;,
 18.47585;4.16391;31.32235;,
 14.84880;11.72609;25.10310;,
 14.84880;4.16391;25.10310;,
 6.67061;11.72609;36.17778;,
 6.67061;4.16391;36.17778;,
 5.40459;11.72609;28.98750;,
 5.40459;4.16391;28.98750;,
 -5.98955;11.72609;36.17778;,
 -5.98955;4.16391;36.17778;,
 -4.72354;11.72609;28.98750;,
 -4.72354;4.16391;28.98750;,
 -17.79480;11.72609;31.32235;,
 -17.79480;4.16391;31.32235;,
 -14.16775;11.72609;25.10310;,
 -14.16775;4.16391;25.10310;,
 -27.15078;11.72609;22.26718;,
 -27.15078;4.16391;22.26718;,
 -21.65251;11.72609;17.85899;,
 -21.65251;4.16391;17.85899;,
 -32.79390;11.72609;10.23527;,
 -32.79390;4.16391;10.23527;,
 -26.16703;11.72609;8.23346;,
 -26.16703;4.16391;8.23346;,
 -33.96207;11.72609;-3.14842;,
 -33.96207;4.16391;-3.14842;,
 -27.10151;11.72609;-2.47349;,
 -27.10151;4.16391;-2.47349;,
 -30.49743;11.72609;-16.07635;,
 -30.49743;4.16391;-16.07635;,
 -24.32983;11.72609;-12.81582;,
 -24.32983;4.16391;-12.81582;,
 -22.86794;11.72609;-26.80251;,
 -22.86794;4.16391;-26.80251;,
 -18.22626;11.72609;-21.39675;,
 -18.22626;4.16391;-21.39675;,
 -12.10405;11.72609;-33.87828;,
 -12.10405;4.16391;-33.87828;,
 -9.61513;11.72609;-27.05737;,
 -9.61513;4.16391;-27.05737;,
 0.34053;11.72609;-36.34805;,
 0.34053;4.16391;-36.34805;,
 0.34053;11.72609;-29.03317;,
 0.34053;4.16391;-29.03317;,
 10.29622;11.72609;-27.05736;,
 12.78513;11.72609;-33.87827;,
 0.34053;4.16391;-36.34805;,
 12.78513;4.16391;-33.87827;,
 10.29622;4.16391;-27.05736;,
 0.34053;4.16391;-29.03317;,
 18.90734;11.72609;-21.39675;,
 23.54901;11.72609;-26.80249;,
 23.54901;4.16391;-26.80249;,
 18.90734;4.16391;-21.39675;,
 25.01090;11.72609;-12.81581;,
 31.17849;11.72609;-16.07634;,
 31.17849;4.16391;-16.07634;,
 25.01090;4.16391;-12.81581;,
 27.78255;11.72609;-2.47348;,
 34.64311;11.72609;-3.14841;,
 34.64311;4.16391;-3.14841;,
 27.78255;4.16391;-2.47348;,
 26.84808;11.72609;8.23346;,
 33.47495;11.72609;10.23527;,
 33.47495;4.16391;10.23527;,
 26.84808;4.16391;8.23346;,
 22.33357;11.72609;17.85899;,
 27.83183;11.72609;22.26717;,
 27.83183;4.16391;22.26717;,
 22.33357;4.16391;17.85899;,
 14.84880;11.72609;25.10310;,
 18.47585;11.72609;31.32235;,
 18.47585;4.16391;31.32235;,
 14.84880;4.16391;25.10310;,
 5.40459;11.72609;28.98750;,
 6.67061;11.72609;36.17778;,
 6.67061;4.16391;36.17778;,
 5.40459;4.16391;28.98750;,
 -4.72354;11.72609;28.98750;,
 -5.98955;11.72609;36.17778;,
 -5.98955;4.16391;36.17778;,
 -4.72354;4.16391;28.98750;,
 -14.16775;11.72609;25.10310;,
 -17.79480;11.72609;31.32235;,
 -17.79480;4.16391;31.32235;,
 -14.16775;4.16391;25.10310;,
 -21.65251;11.72609;17.85899;,
 -27.15078;11.72609;22.26718;,
 -27.15078;4.16391;22.26718;,
 -21.65251;4.16391;17.85899;,
 -26.16703;11.72609;8.23346;,
 -32.79390;11.72609;10.23527;,
 -32.79390;4.16391;10.23527;,
 -26.16703;4.16391;8.23346;,
 -27.10151;11.72609;-2.47349;,
 -33.96207;11.72609;-3.14842;,
 -33.96207;4.16391;-3.14842;,
 -27.10151;4.16391;-2.47349;,
 -24.32983;11.72609;-12.81582;,
 -30.49743;11.72609;-16.07635;,
 -30.49743;4.16391;-16.07635;,
 -24.32983;4.16391;-12.81582;,
 -18.22626;11.72609;-21.39675;,
 -22.86794;11.72609;-26.80251;,
 -22.86794;4.16391;-26.80251;,
 -18.22626;4.16391;-21.39675;,
 -9.61513;11.72609;-27.05737;,
 -12.10405;11.72609;-33.87828;,
 -12.10405;4.16391;-33.87828;,
 -9.61513;4.16391;-27.05737;;
 
 144;
 4;0,1,2,3;,
 3;4,5,6;,
 3;7,8,5;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 4;6,5,21,22;,
 4;5,8,23,21;,
 4;8,10,24,23;,
 4;10,12,25,24;,
 4;12,14,26,25;,
 4;14,16,27,26;,
 4;16,18,28,27;,
 4;18,20,29,28;,
 4;22,21,30,31;,
 4;21,23,32,30;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;26,27,36,35;,
 4;27,28,37,36;,
 4;28,29,38,37;,
 4;31,30,39,40;,
 4;30,32,41,39;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;35,36,45,44;,
 4;36,37,46,45;,
 4;37,38,47,46;,
 4;40,39,48,49;,
 4;39,41,50,48;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;44,45,54,53;,
 4;45,46,55,54;,
 4;46,47,56,55;,
 4;49,48,57,58;,
 4;48,50,59,57;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;58,57,66,67;,
 4;57,59,68,66;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;62,63,72,71;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 3;67,66,75;,
 3;66,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;70,71,79;,
 3;71,72,80;,
 3;72,73,81;,
 3;73,74,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;95,96,97,98;,
 4;99,100,101,102;,
 4;103,104,105,106;,
 4;107,108,109,110;,
 4;111,112,113,114;,
 4;115,116,117,118;,
 4;119,120,121,122;,
 4;123,124,125,126;,
 4;127,128,129,130;,
 4;131,132,133,134;,
 4;128,135,136,129;,
 4;137,131,134,138;,
 4;135,139,140,136;,
 4;141,137,138,142;,
 4;139,143,144,140;,
 4;145,141,142,146;,
 4;143,147,148,144;,
 4;149,145,146,150;,
 4;147,151,152,148;,
 4;153,149,150,154;,
 4;151,155,156,152;,
 4;157,153,154,158;,
 4;155,159,160,156;,
 4;161,157,158,162;,
 4;159,163,164,160;,
 4;165,161,162,166;,
 4;163,167,168,164;,
 4;169,165,166,170;,
 4;167,171,172,168;,
 4;173,169,170,174;,
 4;171,175,176,172;,
 4;177,173,174,178;,
 4;175,179,180,176;,
 4;181,177,178,182;,
 4;179,183,184,180;,
 4;185,181,182,186;,
 4;183,187,188,184;,
 4;189,185,186,190;,
 4;187,191,192,188;,
 4;193,189,190,194;,
 4;191,195,196,192;,
 4;197,193,194,198;,
 4;127,132,199,200;,
 4;201,202,203,204;,
 4;200,199,205,206;,
 4;202,207,208,203;,
 4;206,205,209,210;,
 4;207,211,212,208;,
 4;210,209,213,214;,
 4;211,215,216,212;,
 4;214,213,217,218;,
 4;215,219,220,216;,
 4;218,217,221,222;,
 4;219,223,224,220;,
 4;222,221,225,226;,
 4;223,227,228,224;,
 4;226,225,229,230;,
 4;227,231,232,228;,
 4;230,229,233,234;,
 4;231,235,236,232;,
 4;234,233,237,238;,
 4;235,239,240,236;,
 4;238,237,241,242;,
 4;239,243,244,240;,
 4;242,241,245,246;,
 4;243,247,248,244;,
 4;246,245,249,250;,
 4;247,251,252,248;,
 4;250,249,253,254;,
 4;251,255,256,252;,
 4;254,253,257,258;,
 4;255,259,260,256;,
 4;258,257,261,262;,
 4;259,263,264,260;,
 4;262,261,132,127;,
 4;263,201,204,264;;
 
 MeshMaterialList {
  1;
  144;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.351373;0.351373;0.351373;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  102;
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.844013;-0.536323;,
  0.379237;0.844013;-0.379237;,
  0.536323;0.844013;0.000000;,
  0.379237;0.844013;0.379237;,
  -0.000000;0.844013;0.536323;,
  -0.379237;0.844013;0.379237;,
  -0.536323;0.844013;-0.000000;,
  -0.379237;0.844013;-0.379237;,
  -0.000000;0.537910;-0.843002;,
  0.596092;0.537910;-0.596092;,
  0.843002;0.537910;0.000000;,
  0.596092;0.537910;0.596092;,
  -0.000000;0.537910;0.843002;,
  -0.596093;0.537910;0.596092;,
  -0.843002;0.537910;-0.000000;,
  -0.596093;0.537910;-0.596092;,
  -0.000000;0.253048;-0.967454;,
  0.684093;0.253048;-0.684093;,
  0.967454;0.253048;0.000000;,
  0.684093;0.253048;0.684093;,
  -0.000000;0.253048;0.967454;,
  -0.684093;0.253048;0.684093;,
  -0.967454;0.253048;0.000000;,
  -0.684093;0.253048;-0.684093;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;-0.253048;-0.967454;,
  0.684093;-0.253048;-0.684093;,
  0.967454;-0.253048;0.000000;,
  0.684093;-0.253048;0.684093;,
  -0.000000;-0.253048;0.967454;,
  -0.684093;-0.253048;0.684093;,
  -0.967454;-0.253048;0.000000;,
  -0.684093;-0.253048;-0.684093;,
  0.000000;-0.537912;-0.843001;,
  0.596092;-0.537912;-0.596092;,
  0.843001;-0.537912;0.000000;,
  0.596092;-0.537912;0.596092;,
  -0.000000;-0.537912;0.843001;,
  -0.596092;-0.537912;0.596092;,
  -0.843001;-0.537912;0.000000;,
  -0.596092;-0.537912;-0.596092;,
  0.000000;-0.844013;-0.536322;,
  0.379237;-0.844013;-0.379237;,
  0.536322;-0.844013;0.000000;,
  0.379237;-0.844013;0.379237;,
  -0.000000;-0.844013;0.536322;,
  -0.379237;-0.844013;0.379237;,
  -0.536322;-0.844013;-0.000000;,
  -0.379237;-0.844013;-0.379237;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.379009;0.000000;-0.925393;,
  0.694001;0.000000;-0.719974;,
  0.904728;0.000000;-0.425989;,
  0.996184;0.000000;-0.087279;,
  0.965665;0.000000;0.259792;,
  0.813795;0.000000;0.581152;,
  0.547717;0.000000;0.836664;,
  0.193867;0.000000;0.981028;,
  -0.193867;0.000000;0.981028;,
  -0.547717;0.000000;0.836664;,
  -0.813795;0.000000;0.581152;,
  -0.965665;0.000000;0.259792;,
  -0.996184;0.000000;-0.087279;,
  -0.904728;0.000000;-0.425990;,
  -0.694000;0.000000;-0.719975;,
  -0.379008;0.000000;-0.925393;,
  0.000000;0.000000;1.000000;,
  -0.379008;0.000000;0.925393;,
  -0.694001;0.000000;0.719974;,
  -0.904730;0.000000;0.425987;,
  -0.996184;0.000000;0.087280;,
  -0.965665;0.000000;-0.259790;,
  -0.813794;0.000000;-0.581153;,
  -0.547718;0.000000;-0.836663;,
  -0.193869;0.000000;-0.981027;,
  0.193869;0.000000;-0.981027;,
  0.547718;0.000000;-0.836663;,
  0.813794;0.000000;-0.581153;,
  0.965665;0.000000;-0.259791;,
  0.996184;0.000000;0.087281;,
  0.904729;0.000000;0.425988;,
  0.694001;0.000000;0.719974;,
  0.379007;0.000000;0.925394;,
  0.000000;-1.000000;-0.000000;;
  144;
  4;0,0,0,0;,
  3;1,3,2;,
  3;1,4,3;,
  3;1,5,4;,
  3;1,6,5;,
  3;1,7,6;,
  3;1,8,7;,
  3;1,9,8;,
  3;1,2,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,2,10,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,10,18,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,18,26,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,26,34,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,34,42,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,42,50,57;,
  3;50,51,58;,
  3;51,52,58;,
  3;52,53,58;,
  3;53,54,58;,
  3;54,55,58;,
  3;55,56,58;,
  3;56,57,58;,
  3;57,50,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;66,66,66,66;,
  4;67,68,68,67;,
  4;85,84,84,85;,
  4;68,69,69,68;,
  4;86,85,85,86;,
  4;69,70,70,69;,
  4;87,86,86,87;,
  4;70,71,71,70;,
  4;88,87,87,88;,
  4;71,72,72,71;,
  4;89,88,88,89;,
  4;72,73,73,72;,
  4;90,89,89,90;,
  4;73,74,74,73;,
  4;91,90,90,91;,
  4;74,75,75,74;,
  4;92,91,91,92;,
  4;75,76,76,75;,
  4;93,92,92,93;,
  4;76,77,77,76;,
  4;94,93,93,94;,
  4;77,78,78,77;,
  4;95,94,94,95;,
  4;78,79,79,78;,
  4;96,95,95,96;,
  4;79,80,80,79;,
  4;97,96,96,97;,
  4;80,81,81,80;,
  4;98,97,97,98;,
  4;81,82,82,81;,
  4;99,98,98,99;,
  4;82,83,83,82;,
  4;100,99,99,100;,
  4;83,67,67,83;,
  4;84,100,100,84;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;,
  4;66,66,66,66;,
  4;101,101,101,101;;
 }
 MeshTextureCoords {
  265;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.058824;0.000000;,
  0.058824;1.000000;,
  0.000000;1.000000;,
  0.058824;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.058824;1.000000;,
  0.117647;0.000000;,
  0.117647;1.000000;,
  0.117647;0.000000;,
  0.117647;1.000000;,
  0.176471;0.000000;,
  0.176471;1.000000;,
  0.176471;0.000000;,
  0.176471;1.000000;,
  0.235294;0.000000;,
  0.235294;1.000000;,
  0.235294;0.000000;,
  0.235294;1.000000;,
  0.294118;0.000000;,
  0.294118;1.000000;,
  0.294118;0.000000;,
  0.294118;1.000000;,
  0.352941;0.000000;,
  0.352941;1.000000;,
  0.352941;0.000000;,
  0.352941;1.000000;,
  0.411765;0.000000;,
  0.411765;1.000000;,
  0.411765;0.000000;,
  0.411765;1.000000;,
  0.470588;0.000000;,
  0.470588;1.000000;,
  0.470588;0.000000;,
  0.470588;1.000000;,
  0.529412;0.000000;,
  0.529412;1.000000;,
  0.529412;0.000000;,
  0.529412;1.000000;,
  0.588235;0.000000;,
  0.588235;1.000000;,
  0.588235;0.000000;,
  0.588235;1.000000;,
  0.647059;0.000000;,
  0.647059;1.000000;,
  0.647059;0.000000;,
  0.647059;1.000000;,
  0.705882;0.000000;,
  0.705882;1.000000;,
  0.705882;0.000000;,
  0.705882;1.000000;,
  0.764706;0.000000;,
  0.764706;1.000000;,
  0.764706;0.000000;,
  0.764706;1.000000;,
  0.823529;0.000000;,
  0.823529;1.000000;,
  0.823529;0.000000;,
  0.823529;1.000000;,
  0.882353;0.000000;,
  0.882353;1.000000;,
  0.882353;0.000000;,
  0.882353;1.000000;,
  0.941176;0.000000;,
  0.941176;1.000000;,
  0.941176;0.000000;,
  0.941176;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
