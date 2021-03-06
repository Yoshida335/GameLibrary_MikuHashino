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
 47;
 0.07430;0.59503;2.32348;,
 -0.47357;3.23714;1.34246;,
 -1.76853;1.49570;1.34246;,
 0.07430;0.59503;2.32348;,
 -1.07130;-1.10639;1.34246;,
 0.07430;0.59503;2.32348;,
 0.92088;-1.96703;1.34246;,
 0.07430;0.59503;2.32348;,
 2.19709;-0.23063;1.34510;,
 0.07430;0.59503;2.32348;,
 1.49986;2.37146;1.34510;,
 0.07430;0.59503;2.32348;,
 -0.47357;3.23714;1.34246;,
 -0.44307;3.12330;-1.48161;,
 -2.00872;1.09123;-1.39749;,
 -1.34200;-1.39701;-1.39749;,
 1.02993;-2.37401;-1.48161;,
 2.89421;-0.26193;-1.48161;,
 2.22748;2.22631;-1.48161;,
 -0.44307;3.12330;-1.48161;,
 -0.36826;2.84415;-5.33937;,
 -1.90342;0.73912;-5.25525;,
 -1.31149;-1.46996;-5.25525;,
 1.07050;-2.52537;-5.33937;,
 3.21128;-0.25809;-5.33937;,
 2.61935;1.95100;-5.33937;,
 -0.36826;2.84415;-5.33937;,
 -0.05131;1.82599;-9.19711;,
 -1.11353;0.61437;-12.80129;,
 -0.77191;-0.66056;-12.80129;,
 0.75381;-1.17875;-9.19711;,
 1.98109;0.07710;-9.19711;,
 1.63947;1.35204;-9.19711;,
 -0.05131;1.82599;-9.19711;,
 0.59855;2.43438;-16.91150;,
 -2.15019;1.77208;-17.87464;,
 -1.18957;-1.81300;-17.87464;,
 1.52206;-1.01221;-16.91150;,
 2.83615;-0.73431;-14.63513;,
 1.87553;2.85077;-14.63513;,
 0.59855;2.43438;-16.91150;,
 0.95794;0.55945;-17.29098;,
 0.95794;0.55945;-17.29098;,
 0.95794;0.55945;-17.29098;,
 0.95794;0.55945;-17.29098;,
 0.95794;0.55945;-17.29098;,
 0.95794;0.55945;-17.29098;;
 
 36;
 3;0,1,2;,
 3;3,2,4;,
 3;5,4,6;,
 3;7,6,8;,
 3;9,8,10;,
 3;11,10,12;,
 4;1,13,14,2;,
 4;2,14,15,4;,
 4;4,15,16,6;,
 4;6,16,17,8;,
 4;8,17,18,10;,
 4;10,18,19,12;,
 4;13,20,21,14;,
 4;14,21,22,15;,
 4;15,22,23,16;,
 4;16,23,24,17;,
 4;17,24,25,18;,
 4;18,25,26,19;,
 4;20,27,28,21;,
 4;21,28,29,22;,
 4;22,29,30,23;,
 4;23,30,31,24;,
 4;24,31,32,25;,
 4;25,32,33,26;,
 4;27,34,35,28;,
 4;28,35,36,29;,
 4;29,36,37,30;,
 4;30,37,38,31;,
 4;31,38,39,32;,
 4;32,39,40,33;,
 3;34,41,35;,
 3;35,42,36;,
 3;36,43,37;,
 3;37,44,38;,
 3;38,45,39;,
 3;39,46,40;;
 
 MeshMaterialList {
  2;
  36;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\uroko.jpg";
   }
  }
  Material {
   0.800000;0.021600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  49;
  -0.018385;-0.004927;0.999819;,
  -0.097811;0.328525;0.939417;,
  -0.698760;-0.051409;0.713506;,
  -0.612122;-0.515330;0.599785;,
  0.079555;-0.333418;0.939417;,
  0.646833;0.049551;0.761020;,
  0.584950;0.280504;0.761019;,
  -0.798602;0.600019;-0.047027;,
  -0.981626;0.190688;0.007021;,
  -0.752268;-0.654583;0.074920;,
  -0.388540;-0.918377;0.074974;,
  0.964512;-0.221645;0.143496;,
  0.729074;0.680496;0.073332;,
  -0.759894;0.640972;-0.108242;,
  -0.972493;0.215268;-0.088981;,
  -0.729126;-0.679980;-0.077478;,
  -0.318906;-0.943766;-0.087211;,
  0.962486;-0.240892;-0.124866;,
  0.710610;0.690582;-0.134645;,
  -0.469136;0.881483;0.053834;,
  -0.954597;0.297772;0.008693;,
  -0.965723;-0.258769;0.020453;,
  0.254465;-0.963834;-0.079190;,
  0.942539;-0.317910;-0.102730;,
  0.822639;0.549518;-0.145927;,
  -0.315436;0.936113;0.155540;,
  -0.548384;0.824950;0.136864;,
  -0.956817;-0.256381;0.137006;,
  0.241658;-0.965296;0.099016;,
  0.476074;-0.872371;0.111003;,
  0.915455;0.259329;-0.307718;,
  0.602173;0.156081;-0.782960;,
  -0.797250;0.603062;-0.026621;,
  -0.383809;-0.914680;0.126692;,
  0.769532;-0.620137;0.152481;,
  0.755055;-0.648047;0.099635;,
  0.360438;0.932783;0.000352;,
  0.331512;0.943114;-0.025236;,
  0.724844;-0.678468;-0.119512;,
  0.287767;0.947927;-0.136469;,
  -0.126091;-0.990288;-0.058564;,
  0.271301;0.936750;-0.221123;,
  -0.008160;-0.996703;0.080720;,
  0.922944;0.231235;-0.307742;,
  -0.061362;0.984583;0.163800;,
  0.581377;0.266997;-0.768579;,
  0.238126;0.148368;-0.959835;,
  0.283259;-0.020519;-0.958824;,
  0.640492;0.044783;-0.766658;;
  36;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,1;,
  4;32,7,8,32;,
  4;2,8,9,3;,
  4;3,9,10,33;,
  4;34,35,11,34;,
  4;5,11,12,6;,
  4;36,12,37,36;,
  4;7,13,14,8;,
  4;8,14,15,9;,
  4;9,15,16,10;,
  4;35,38,17,11;,
  4;11,17,18,12;,
  4;12,18,39,37;,
  4;13,19,20,14;,
  4;14,20,21,15;,
  4;15,40,22,16;,
  4;38,22,23,17;,
  4;17,23,24,18;,
  4;18,24,41,39;,
  4;19,25,26,20;,
  4;20,27,27,21;,
  4;40,42,28,22;,
  4;22,28,29,23;,
  4;23,43,30,24;,
  4;44,44,25,19;,
  3;45,31,46;,
  3;46,31,47;,
  3;47,31,48;,
  3;48,31,43;,
  3;43,31,30;,
  3;30,31,45;;
 }
 MeshTextureCoords {
  47;
  0.083330;0.000000;,
  0.000000;0.166670;,
  0.166670;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;;
 }
}
