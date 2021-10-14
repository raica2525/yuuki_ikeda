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
 301;
 0.00000;89.92514;-8.26514;,
 5.84434;89.92514;-5.84434;,
 5.84434;-39.19943;-5.84434;,
 0.00000;-39.19943;-8.26514;,
 8.26514;89.92514;0.00000;,
 8.26514;-39.19943;-0.00000;,
 5.84434;89.92514;5.84434;,
 5.84434;-39.19943;5.84434;,
 0.00000;89.92514;8.26514;,
 0.00000;-39.19943;8.26514;,
 -5.84434;89.92514;5.84434;,
 -5.84434;-39.19943;5.84434;,
 -8.26514;89.92514;0.00000;,
 -8.26514;-39.19943;0.00000;,
 -5.84434;89.92514;-5.84434;,
 -5.84434;-39.19943;-5.84434;,
 0.00000;89.92514;-8.26514;,
 0.00000;-39.19943;-8.26514;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;89.92514;0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-39.19943;-0.00000;,
 0.00000;-35.93666;-0.00000;,
 4.40431;-37.17561;-4.40431;,
 0.00000;-37.17561;-6.22864;,
 0.00000;-35.93666;-0.00000;,
 6.22864;-37.17561;0.00000;,
 0.00000;-35.93666;-0.00000;,
 4.40431;-37.17561;4.40431;,
 0.00000;-35.93666;-0.00000;,
 -0.00000;-37.17561;6.22864;,
 0.00000;-35.93666;-0.00000;,
 -4.40431;-37.17561;4.40431;,
 0.00000;-35.93666;-0.00000;,
 -6.22864;-37.17561;-0.00000;,
 0.00000;-35.93666;-0.00000;,
 -4.40431;-37.17561;-4.40431;,
 0.00000;-35.93666;-0.00000;,
 0.00000;-37.17561;-6.22864;,
 8.13811;-40.70390;-8.13810;,
 0.00000;-40.70390;-11.50902;,
 11.50902;-40.70390;0.00000;,
 8.13811;-40.70390;8.13811;,
 -0.00000;-40.70390;11.50902;,
 -8.13811;-40.70390;8.13810;,
 -11.50902;-40.70390;-0.00000;,
 -8.13811;-40.70390;-8.13810;,
 0.00000;-40.70390;-11.50902;,
 10.63295;-45.98421;-10.63295;,
 0.00000;-45.98421;-15.03727;,
 15.03727;-45.98421;0.00000;,
 10.63295;-45.98421;10.63295;,
 -0.00000;-45.98421;15.03727;,
 -10.63296;-45.98421;10.63295;,
 -15.03727;-45.98421;-0.00000;,
 -10.63296;-45.98421;-10.63295;,
 0.00000;-45.98421;-15.03727;,
 11.50902;-52.21289;-11.50902;,
 0.00000;-52.21289;-16.27621;,
 16.27621;-52.21289;0.00000;,
 11.50902;-52.21289;11.50902;,
 -0.00000;-52.21289;16.27621;,
 -11.50902;-52.21289;11.50902;,
 -16.27621;-52.21289;-0.00000;,
 -11.50902;-52.21289;-11.50902;,
 0.00000;-52.21289;-16.27621;,
 10.63295;-58.44142;-10.63295;,
 0.00000;-58.44142;-15.03727;,
 15.03727;-58.44142;0.00000;,
 10.63295;-58.44142;10.63295;,
 -0.00000;-58.44142;15.03727;,
 -10.63296;-58.44142;10.63295;,
 -15.03727;-58.44142;-0.00000;,
 -10.63296;-58.44142;-10.63295;,
 0.00000;-58.44142;-15.03727;,
 8.13811;-63.72186;-8.13810;,
 0.00000;-63.72186;-11.50902;,
 11.50902;-63.72186;0.00000;,
 8.13811;-63.72186;8.13811;,
 -0.00000;-63.72186;11.50902;,
 -8.13811;-63.72186;8.13810;,
 -11.50902;-63.72186;-0.00000;,
 -8.13811;-63.72186;-8.13810;,
 0.00000;-63.72186;-11.50902;,
 4.40431;-67.25009;-4.40431;,
 0.00000;-67.25009;-6.22864;,
 6.22864;-67.25009;0.00000;,
 4.40431;-67.25009;4.40431;,
 -0.00000;-67.25009;6.22864;,
 -4.40431;-67.25009;4.40431;,
 -6.22864;-67.25009;-0.00000;,
 -4.40431;-67.25009;-4.40431;,
 0.00000;-67.25009;-6.22864;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;-68.48892;-0.00000;,
 0.00000;69.93922;-30.66495;,
 0.00000;325.30713;0.00000;,
 20.62848;69.93922;-21.68341;,
 0.00000;325.30713;0.00000;,
 29.17302;69.93922;0.00000;,
 0.00000;325.30713;0.00000;,
 20.62848;69.93922;21.68341;,
 0.00000;325.30713;0.00000;,
 -0.00000;69.93922;30.66495;,
 0.00000;325.30713;0.00000;,
 -20.62848;69.93922;21.68340;,
 0.00000;325.30713;0.00000;,
 -29.17302;69.93922;-0.00000;,
 0.00000;325.30713;0.00000;,
 -20.62848;69.93922;-21.68340;,
 0.00000;325.30713;0.00000;,
 0.00000;69.93922;-30.66495;,
 0.00000;69.93922;0.00000;,
 0.00000;69.93922;-30.66495;,
 20.62848;69.93922;-21.68341;,
 29.17302;69.93922;0.00000;,
 20.62848;69.93922;21.68341;,
 -0.00000;69.93922;30.66495;,
 -20.62848;69.93922;21.68340;,
 -29.17302;69.93922;-0.00000;,
 -20.62848;69.93922;-21.68340;,
 30.55199;291.61438;0.00000;,
 31.67055;294.31476;0.00000;,
 22.39446;294.31476;-22.39446;,
 21.60351;291.61438;-21.60351;,
 34.37098;295.43323;0.00000;,
 24.30396;295.43323;-24.30396;,
 37.07144;294.31476;0.00000;,
 26.21346;294.31476;-26.21346;,
 38.18998;291.61438;0.00000;,
 27.00443;291.61438;-27.00443;,
 37.07144;288.91400;0.00000;,
 26.21346;288.91400;-26.21346;,
 34.37098;287.79541;0.00000;,
 24.30396;287.79541;-24.30396;,
 31.67055;288.91400;0.00000;,
 22.39446;288.91400;-22.39446;,
 30.55199;291.61438;0.00000;,
 21.60351;291.61438;-21.60351;,
 -0.00000;294.31476;-31.67055;,
 -0.00000;291.61438;-30.55199;,
 -0.00000;295.43323;-34.37098;,
 -0.00000;294.31476;-37.07144;,
 -0.00000;291.61438;-38.18998;,
 -0.00000;288.91400;-37.07144;,
 -0.00000;287.79541;-34.37098;,
 -0.00000;288.91400;-31.67055;,
 -0.00000;291.61438;-30.55199;,
 -22.39446;294.31476;-22.39446;,
 -21.60351;291.61438;-21.60351;,
 -24.30396;295.43323;-24.30396;,
 -26.21346;294.31476;-26.21346;,
 -27.00443;291.61438;-27.00443;,
 -26.21346;288.91400;-26.21346;,
 -24.30396;287.79541;-24.30396;,
 -22.39446;288.91400;-22.39446;,
 -21.60351;291.61438;-21.60351;,
 -31.67055;294.31476;0.00000;,
 -30.55199;291.61438;0.00000;,
 -34.37098;295.43323;0.00000;,
 -37.07144;294.31476;0.00000;,
 -38.18998;291.61438;0.00000;,
 -37.07144;288.91400;0.00000;,
 -34.37098;287.79541;0.00000;,
 -31.67055;288.91400;0.00000;,
 -30.55199;291.61438;0.00000;,
 -22.39445;294.31476;22.39446;,
 -21.60351;291.61438;21.60352;,
 -24.30395;295.43323;24.30396;,
 -26.21346;294.31476;26.21347;,
 -27.00443;291.61438;27.00443;,
 -26.21346;288.91400;26.21347;,
 -24.30395;287.79541;24.30396;,
 -22.39445;288.91400;22.39446;,
 -21.60351;291.61438;21.60352;,
 0.00000;294.31476;31.67055;,
 0.00000;291.61438;30.55199;,
 0.00000;295.43323;34.37098;,
 0.00000;294.31476;37.07144;,
 0.00000;291.61438;38.18998;,
 0.00000;288.91400;37.07144;,
 0.00000;287.79541;34.37098;,
 0.00000;288.91400;31.67055;,
 0.00000;291.61438;30.55199;,
 22.39446;294.31476;22.39446;,
 21.60351;291.61438;21.60351;,
 24.30396;295.43323;24.30396;,
 26.21346;294.31476;26.21347;,
 27.00443;291.61438;27.00443;,
 26.21346;288.91400;26.21347;,
 24.30396;287.79541;24.30396;,
 22.39446;288.91400;22.39446;,
 21.60351;291.61438;21.60351;,
 31.67055;294.31476;0.00000;,
 30.55199;291.61438;0.00000;,
 34.37098;295.43323;0.00000;,
 37.07144;294.31476;0.00000;,
 38.18998;291.61438;0.00000;,
 37.07144;288.91400;0.00000;,
 34.37098;287.79541;0.00000;,
 31.67055;288.91400;0.00000;,
 30.55199;291.61438;0.00000;,
 23.45516;230.63007;0.00000;,
 24.31389;232.70329;0.00000;,
 17.19253;232.70329;-17.19253;,
 16.58530;230.63007;-16.58530;,
 26.38706;233.56207;0.00000;,
 18.65846;233.56207;-18.65846;,
 28.46021;232.70329;0.00000;,
 20.12441;232.70329;-20.12441;,
 29.31897;230.63007;0.00000;,
 20.73162;230.63007;-20.73162;,
 28.46021;228.55698;0.00000;,
 20.12441;228.55698;-20.12441;,
 26.38706;227.69829;0.00000;,
 18.65846;227.69829;-18.65846;,
 24.31389;228.55698;0.00000;,
 17.19253;228.55698;-17.19253;,
 23.45516;230.63007;0.00000;,
 16.58530;230.63007;-16.58530;,
 -0.00000;232.70329;-24.31389;,
 -0.00000;230.63007;-23.45516;,
 -0.00000;233.56207;-26.38706;,
 -0.00000;232.70329;-28.46021;,
 -0.00000;230.63007;-29.31897;,
 -0.00000;228.55698;-28.46021;,
 -0.00000;227.69829;-26.38706;,
 -0.00000;228.55698;-24.31389;,
 -0.00000;230.63007;-23.45516;,
 -17.19253;232.70329;-17.19253;,
 -16.58530;230.63007;-16.58530;,
 -18.65846;233.56207;-18.65846;,
 -20.12441;232.70329;-20.12441;,
 -20.73162;230.63007;-20.73162;,
 -20.12441;228.55698;-20.12441;,
 -18.65846;227.69829;-18.65846;,
 -17.19253;228.55698;-17.19253;,
 -16.58530;230.63007;-16.58530;,
 -24.31389;232.70329;0.00000;,
 -23.45516;230.63007;0.00000;,
 -26.38706;233.56207;0.00000;,
 -28.46021;232.70329;0.00000;,
 -29.31897;230.63007;0.00000;,
 -28.46021;228.55698;0.00000;,
 -26.38706;227.69829;0.00000;,
 -24.31389;228.55698;0.00000;,
 -23.45516;230.63007;0.00000;,
 -17.19253;232.70329;17.19253;,
 -16.58530;230.63007;16.58531;,
 -18.65846;233.56207;18.65846;,
 -20.12441;232.70329;20.12441;,
 -20.73161;230.63007;20.73162;,
 -20.12441;228.55698;20.12441;,
 -18.65846;227.69829;18.65846;,
 -17.19253;228.55698;17.19253;,
 -16.58530;230.63007;16.58531;,
 0.00000;232.70329;24.31389;,
 0.00000;230.63007;23.45516;,
 0.00000;233.56207;26.38706;,
 0.00000;232.70329;28.46021;,
 0.00000;230.63007;29.31897;,
 0.00000;228.55698;28.46021;,
 0.00000;227.69829;26.38706;,
 0.00000;228.55698;24.31389;,
 0.00000;230.63007;23.45516;,
 17.19253;232.70329;17.19253;,
 16.58530;230.63007;16.58531;,
 18.65846;233.56207;18.65846;,
 20.12441;232.70329;20.12441;,
 20.73162;230.63007;20.73162;,
 20.12441;228.55698;20.12441;,
 18.65846;227.69829;18.65846;,
 17.19253;228.55698;17.19253;,
 16.58530;230.63007;16.58531;,
 24.31389;232.70329;0.00000;,
 23.45516;230.63007;0.00000;,
 26.38706;233.56207;0.00000;,
 28.46021;232.70329;0.00000;,
 29.31897;230.63007;0.00000;,
 28.46021;228.55698;0.00000;,
 26.38706;227.69829;0.00000;,
 24.31389;228.55698;0.00000;,
 23.45516;230.63007;0.00000;;
 
 232;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 3;34,35,36;,
 3;37,38,35;,
 3;39,40,38;,
 3;41,42,40;,
 3;43,44,42;,
 3;45,46,44;,
 3;47,48,46;,
 3;49,50,48;,
 4;36,35,51,52;,
 4;35,38,53,51;,
 4;38,40,54,53;,
 4;40,42,55,54;,
 4;42,44,56,55;,
 4;44,46,57,56;,
 4;46,48,58,57;,
 4;48,50,59,58;,
 4;52,51,60,61;,
 4;51,53,62,60;,
 4;53,54,63,62;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;61,60,69,70;,
 4;60,62,71,69;,
 4;62,63,72,71;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;70,69,78,79;,
 4;69,71,80,78;,
 4;71,72,81,80;,
 4;72,73,82,81;,
 4;73,74,83,82;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;79,78,87,88;,
 4;78,80,89,87;,
 4;80,81,90,89;,
 4;81,82,91,90;,
 4;82,83,92,91;,
 4;83,84,93,92;,
 4;84,85,94,93;,
 4;85,86,95,94;,
 4;88,87,96,97;,
 4;87,89,98,96;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;91,92,101,100;,
 4;92,93,102,101;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 3;97,96,105;,
 3;96,98,106;,
 3;98,99,107;,
 3;99,100,108;,
 3;100,101,109;,
 3;101,102,110;,
 3;102,103,111;,
 3;103,104,112;,
 3;113,114,115;,
 3;115,116,117;,
 3;117,118,119;,
 3;119,120,121;,
 3;121,122,123;,
 3;123,124,125;,
 3;125,126,127;,
 3;127,128,129;,
 3;130,131,132;,
 3;130,132,133;,
 3;130,133,134;,
 3;130,134,135;,
 3;130,135,136;,
 3;130,136,137;,
 3;130,137,138;,
 3;130,138,131;,
 4;139,140,141,142;,
 4;140,143,144,141;,
 4;143,145,146,144;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;142,141,157,158;,
 4;141,144,159,157;,
 4;144,146,160,159;,
 4;146,148,161,160;,
 4;148,150,162,161;,
 4;150,152,163,162;,
 4;152,154,164,163;,
 4;154,156,165,164;,
 4;158,157,166,167;,
 4;157,159,168,166;,
 4;159,160,169,168;,
 4;160,161,170,169;,
 4;161,162,171,170;,
 4;162,163,172,171;,
 4;163,164,173,172;,
 4;164,165,174,173;,
 4;167,166,175,176;,
 4;166,168,177,175;,
 4;168,169,178,177;,
 4;169,170,179,178;,
 4;170,171,180,179;,
 4;171,172,181,180;,
 4;172,173,182,181;,
 4;173,174,183,182;,
 4;176,175,184,185;,
 4;175,177,186,184;,
 4;177,178,187,186;,
 4;178,179,188,187;,
 4;179,180,189,188;,
 4;180,181,190,189;,
 4;181,182,191,190;,
 4;182,183,192,191;,
 4;185,184,193,194;,
 4;184,186,195,193;,
 4;186,187,196,195;,
 4;187,188,197,196;,
 4;188,189,198,197;,
 4;189,190,199,198;,
 4;190,191,200,199;,
 4;191,192,201,200;,
 4;194,193,202,203;,
 4;193,195,204,202;,
 4;195,196,205,204;,
 4;196,197,206,205;,
 4;197,198,207,206;,
 4;198,199,208,207;,
 4;199,200,209,208;,
 4;200,201,210,209;,
 4;203,202,211,212;,
 4;202,204,213,211;,
 4;204,205,214,213;,
 4;205,206,215,214;,
 4;206,207,216,215;,
 4;207,208,217,216;,
 4;208,209,218,217;,
 4;209,210,219,218;,
 4;220,221,222,223;,
 4;221,224,225,222;,
 4;224,226,227,225;,
 4;226,228,229,227;,
 4;228,230,231,229;,
 4;230,232,233,231;,
 4;232,234,235,233;,
 4;234,236,237,235;,
 4;223,222,238,239;,
 4;222,225,240,238;,
 4;225,227,241,240;,
 4;227,229,242,241;,
 4;229,231,243,242;,
 4;231,233,244,243;,
 4;233,235,245,244;,
 4;235,237,246,245;,
 4;239,238,247,248;,
 4;238,240,249,247;,
 4;240,241,250,249;,
 4;241,242,251,250;,
 4;242,243,252,251;,
 4;243,244,253,252;,
 4;244,245,254,253;,
 4;245,246,255,254;,
 4;248,247,256,257;,
 4;247,249,258,256;,
 4;249,250,259,258;,
 4;250,251,260,259;,
 4;251,252,261,260;,
 4;252,253,262,261;,
 4;253,254,263,262;,
 4;254,255,264,263;,
 4;257,256,265,266;,
 4;256,258,267,265;,
 4;258,259,268,267;,
 4;259,260,269,268;,
 4;260,261,270,269;,
 4;261,262,271,270;,
 4;262,263,272,271;,
 4;263,264,273,272;,
 4;266,265,274,275;,
 4;265,267,276,274;,
 4;267,268,277,276;,
 4;268,269,278,277;,
 4;269,270,279,278;,
 4;270,271,280,279;,
 4;271,272,281,280;,
 4;272,273,282,281;,
 4;275,274,283,284;,
 4;274,276,285,283;,
 4;276,277,286,285;,
 4;277,278,287,286;,
 4;278,279,288,287;,
 4;279,280,289,288;,
 4;280,281,290,289;,
 4;281,282,291,290;,
 4;284,283,292,293;,
 4;283,285,294,292;,
 4;285,286,295,294;,
 4;286,287,296,295;,
 4;287,288,297,296;,
 4;288,289,298,297;,
 4;289,290,299,298;,
 4;290,291,300,299;;
 
 MeshMaterialList {
  1;
  232;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/x/Rust.jpg";
   }
  }
 }
 MeshNormals {
  201;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.924734;-0.380614;,
  0.269135;0.924734;-0.269135;,
  0.380614;0.924734;0.000000;,
  0.269135;0.924734;0.269135;,
  -0.000000;0.924734;0.380614;,
  -0.269135;0.924734;0.269135;,
  -0.380614;0.924734;0.000000;,
  -0.269135;0.924734;-0.269135;,
  -0.000000;0.709231;-0.704976;,
  0.498494;0.709231;-0.498494;,
  0.704976;0.709231;0.000000;,
  0.498494;0.709231;0.498494;,
  -0.000000;0.709231;0.704976;,
  -0.498494;0.709231;0.498494;,
  -0.704976;0.709231;0.000000;,
  -0.498494;0.709231;-0.498493;,
  -0.000000;0.384554;-0.923103;,
  0.652732;0.384553;-0.652732;,
  0.923103;0.384553;0.000000;,
  0.652732;0.384553;0.652732;,
  -0.000000;0.384554;0.923103;,
  -0.652732;0.384553;0.652732;,
  -0.923103;0.384553;0.000000;,
  -0.652732;0.384553;-0.652732;,
  -0.000000;-0.000002;-1.000000;,
  0.707107;-0.000002;-0.707107;,
  1.000000;-0.000002;0.000000;,
  0.707107;-0.000002;0.707107;,
  -0.000000;-0.000002;1.000000;,
  -0.707107;-0.000002;0.707107;,
  -1.000000;-0.000002;0.000000;,
  -0.707107;-0.000002;-0.707107;,
  -0.000000;-0.384550;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384550;-0.000000;,
  0.652733;-0.384550;0.652733;,
  -0.000000;-0.384550;0.923104;,
  -0.652733;-0.384550;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652733;-0.384550;-0.652733;,
  -0.000000;-0.709230;-0.704978;,
  0.498495;-0.709230;-0.498494;,
  0.704978;-0.709230;-0.000000;,
  0.498494;-0.709230;0.498495;,
  -0.000000;-0.709230;0.704978;,
  -0.498495;-0.709230;0.498494;,
  -0.704978;-0.709230;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  -0.000000;-0.924739;-0.380601;,
  0.269126;-0.924739;-0.269126;,
  0.380601;-0.924739;-0.000000;,
  0.269126;-0.924739;0.269126;,
  -0.000000;-0.924739;0.380601;,
  -0.269126;-0.924739;0.269126;,
  -0.380601;-0.924739;-0.000000;,
  -0.269126;-0.924739;-0.269126;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;0.119225;-0.992867;,
  0.714642;0.116296;-0.689755;,
  0.993538;0.113501;0.000000;,
  0.714642;0.116296;0.689755;,
  -0.000000;0.119225;0.992867;,
  -0.714642;0.116296;0.689755;,
  -0.993538;0.113501;0.000000;,
  -0.714642;0.116296;-0.689755;,
  -1.000000;0.000000;-0.000000;,
  -0.698858;0.715260;0.000000;,
  -0.000001;1.000000;0.000000;,
  0.698857;0.715261;0.000000;,
  1.000000;0.000000;0.000000;,
  0.698872;-0.715247;0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.698873;-0.715246;0.000000;,
  -0.494167;0.715260;0.494167;,
  -0.000001;1.000000;0.000001;,
  0.494166;0.715262;-0.494166;,
  0.707107;0.000000;-0.707107;,
  0.494177;-0.715248;-0.494177;,
  -0.000001;-1.000000;0.000001;,
  -0.494178;-0.715246;0.494178;,
  0.000000;0.000000;1.000000;,
  0.000000;0.715260;0.698858;,
  0.000000;1.000000;0.000001;,
  0.000000;0.715262;-0.698857;,
  -0.000000;-0.715247;-0.698871;,
  -0.000000;-1.000000;0.000001;,
  0.000000;-0.715246;0.698873;,
  0.494167;0.715260;0.494167;,
  0.000001;1.000000;0.000001;,
  -0.494166;0.715262;-0.494166;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;-0.715248;-0.494177;,
  0.000001;-1.000000;0.000001;,
  0.494178;-0.715246;0.494178;,
  1.000000;0.000000;-0.000000;,
  0.698858;0.715260;-0.000000;,
  0.000001;1.000000;-0.000000;,
  -0.698857;0.715261;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.698872;-0.715247;0.000000;,
  0.000001;-1.000000;0.000000;,
  0.698873;-0.715246;-0.000000;,
  0.707107;0.000000;-0.707107;,
  0.494167;0.715260;-0.494168;,
  0.000001;1.000000;-0.000001;,
  -0.494166;0.715261;0.494167;,
  -0.707107;0.000000;0.707107;,
  -0.494177;-0.715247;0.494177;,
  0.000001;-1.000000;-0.000001;,
  0.494178;-0.715246;-0.494178;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.715260;-0.698858;,
  0.000000;1.000000;-0.000001;,
  0.000000;0.715261;0.698857;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.715247;0.698872;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-0.715246;-0.698873;,
  -0.707107;0.000000;-0.707107;,
  -0.494167;0.715260;-0.494167;,
  -0.000001;1.000000;-0.000001;,
  0.494167;0.715261;0.494167;,
  0.707107;0.000000;0.707107;,
  0.494177;-0.715247;0.494177;,
  -0.000001;-1.000000;-0.000001;,
  -0.494178;-0.715246;-0.494178;,
  -1.000000;-0.000012;-0.000000;,
  -0.698883;0.715236;-0.000000;,
  -0.000001;1.000000;-0.000000;,
  0.698883;0.715237;0.000000;,
  1.000000;-0.000012;0.000000;,
  0.698860;-0.715258;0.000000;,
  -0.000001;-1.000000;-0.000000;,
  -0.698861;-0.715258;-0.000000;,
  -0.707107;-0.000012;0.707107;,
  -0.494185;0.715236;0.494185;,
  -0.000000;1.000000;0.000000;,
  0.494185;0.715237;-0.494185;,
  0.707107;-0.000012;-0.707107;,
  0.494169;-0.715258;-0.494169;,
  -0.000000;-1.000000;0.000000;,
  -0.494169;-0.715258;0.494169;,
  0.000000;-0.000012;1.000000;,
  0.000000;0.715236;0.698883;,
  0.000000;1.000000;0.000001;,
  -0.000000;0.715237;-0.698882;,
  -0.000000;-0.000012;-1.000000;,
  -0.000000;-0.715258;-0.698860;,
  0.000000;-1.000000;0.000001;,
  0.000000;-0.715258;0.698861;,
  0.707107;-0.000012;0.707107;,
  0.494185;0.715236;0.494185;,
  0.000000;1.000000;0.000000;,
  -0.494185;0.715237;-0.494185;,
  -0.707107;-0.000012;-0.707107;,
  -0.494169;-0.715258;-0.494169;,
  0.000000;-1.000000;0.000000;,
  0.494169;-0.715258;0.494169;,
  1.000000;-0.000012;-0.000000;,
  0.698883;0.715236;-0.000000;,
  0.000001;1.000000;0.000000;,
  -0.698883;0.715236;0.000000;,
  -1.000000;-0.000012;0.000000;,
  -0.698860;-0.715258;0.000000;,
  0.000001;-1.000000;-0.000000;,
  0.698861;-0.715257;-0.000000;,
  0.707107;-0.000012;-0.707107;,
  0.494185;0.715236;-0.494185;,
  0.000000;1.000000;-0.000000;,
  -0.494185;0.715236;0.494185;,
  -0.707107;-0.000012;0.707107;,
  -0.494169;-0.715258;0.494169;,
  0.000000;-1.000000;-0.000000;,
  0.494169;-0.715257;-0.494170;,
  -0.000000;-0.000012;-1.000000;,
  -0.000000;0.715236;-0.698883;,
  -0.000000;1.000000;-0.000001;,
  -0.000000;0.715237;0.698882;,
  -0.000000;-0.000012;1.000000;,
  -0.000000;-0.715258;0.698860;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-0.715257;-0.698861;,
  -0.707107;-0.000012;-0.707107;,
  -0.494185;0.715236;-0.494185;,
  -0.000000;1.000000;-0.000000;,
  0.494185;0.715236;0.494185;,
  0.707107;-0.000012;0.707107;,
  0.494169;-0.715258;0.494169;,
  -0.000000;-1.000000;-0.000000;,
  -0.494169;-0.715257;-0.494169;;
  232;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;10,12,11;,
  3;10,13,12;,
  3;10,14,13;,
  3;10,15,14;,
  3;10,16,15;,
  3;10,17,16;,
  3;10,18,17;,
  3;10,11,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,11,19,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,19,27,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,27,35,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,35,43,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,43,51,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;58,51,59,66;,
  3;59,60,67;,
  3;60,61,67;,
  3;61,62,67;,
  3;62,63,67;,
  3;63,64,67;,
  3;64,65,67;,
  3;65,66,67;,
  3;66,59,67;,
  3;68,69,69;,
  3;69,69,70;,
  3;70,71,71;,
  3;71,71,72;,
  3;72,73,73;,
  3;73,73,74;,
  3;74,75,75;,
  3;75,75,68;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;76,77,84,6;,
  4;77,78,85,84;,
  4;78,79,86,85;,
  4;79,80,87,86;,
  4;80,81,88,87;,
  4;81,82,89,88;,
  4;82,83,90,89;,
  4;83,76,6,90;,
  4;6,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,1,94;,
  4;87,88,95,1;,
  4;88,89,96,95;,
  4;89,90,97,96;,
  4;90,6,91,97;,
  4;91,92,98,4;,
  4;92,93,99,98;,
  4;93,94,100,99;,
  4;94,1,101,100;,
  4;1,95,102,101;,
  4;95,96,103,102;,
  4;96,97,104,103;,
  4;97,91,4,104;,
  4;4,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,4,105,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,105,113,120;,
  4;113,114,122,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,118,126,125;,
  4;118,119,127,126;,
  4;119,120,128,127;,
  4;120,113,121,128;,
  4;121,122,130,129;,
  4;122,123,131,130;,
  4;123,124,132,131;,
  4;124,125,133,132;,
  4;125,126,134,133;,
  4;126,127,135,134;,
  4;127,128,136,135;,
  4;128,121,129,136;,
  4;129,130,77,76;,
  4;130,131,78,77;,
  4;131,132,79,78;,
  4;132,133,80,79;,
  4;133,134,81,80;,
  4;134,135,82,81;,
  4;135,136,83,82;,
  4;136,129,76,83;,
  4;137,138,146,145;,
  4;138,139,147,146;,
  4;139,140,148,147;,
  4;140,141,149,148;,
  4;141,142,150,149;,
  4;142,143,151,150;,
  4;143,144,152,151;,
  4;144,137,145,152;,
  4;145,146,154,153;,
  4;146,147,155,154;,
  4;147,148,156,155;,
  4;148,149,157,156;,
  4;149,150,158,157;,
  4;150,151,159,158;,
  4;151,152,160,159;,
  4;152,145,153,160;,
  4;153,154,162,161;,
  4;154,155,163,162;,
  4;155,156,164,163;,
  4;156,157,165,164;,
  4;157,158,166,165;,
  4;158,159,167,166;,
  4;159,160,168,167;,
  4;160,153,161,168;,
  4;161,162,170,169;,
  4;162,163,171,170;,
  4;163,164,172,171;,
  4;164,165,173,172;,
  4;165,166,174,173;,
  4;166,167,175,174;,
  4;167,168,176,175;,
  4;168,161,169,176;,
  4;169,170,178,177;,
  4;170,171,179,178;,
  4;171,172,180,179;,
  4;172,173,181,180;,
  4;173,174,182,181;,
  4;174,175,183,182;,
  4;175,176,184,183;,
  4;176,169,177,184;,
  4;177,178,186,185;,
  4;178,179,187,186;,
  4;179,180,188,187;,
  4;180,181,189,188;,
  4;181,182,190,189;,
  4;182,183,191,190;,
  4;183,184,192,191;,
  4;184,177,185,192;,
  4;185,186,194,193;,
  4;186,187,195,194;,
  4;187,188,196,195;,
  4;188,189,197,196;,
  4;189,190,198,197;,
  4;190,191,199,198;,
  4;191,192,200,199;,
  4;192,185,193,200;,
  4;193,194,138,137;,
  4;194,195,139,138;,
  4;195,196,140,139;,
  4;196,197,141,140;,
  4;197,198,142,141;,
  4;198,199,143,142;,
  4;199,200,144,143;,
  4;200,193,137,144;;
 }
 MeshTextureCoords {
  301;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
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
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;;
 }
}
