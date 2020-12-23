xof 0303txt 0032
template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Mesh {
 96;
 1.002000;0.504700;-0.420000;,
 0.502000;0.504700;-0.630000;,
 0.502000;1.504700;-0.630000;,
 1.002000;1.504700;-0.420000;,
 1.002000;0.504700;0.000000;,
 1.002000;1.504700;0.000000;,
 -0.498000;0.504700;-0.630000;,
 -0.998000;0.504700;-0.420000;,
 -0.998000;1.504700;-0.420000;,
 -0.498000;1.504700;-0.630000;,
 0.502000;0.504700;-0.630000;,
 0.502000;1.504700;-0.630000;,
 0.502000;0.504700;0.210000;,
 1.002000;0.504700;0.000000;,
 1.002000;1.504700;0.000000;,
 0.502000;1.504700;0.210000;,
 -0.498000;0.504700;0.210000;,
 -0.498000;1.504700;0.210000;,
 -0.998000;0.504700;0.000000;,
 -0.998000;1.504700;0.000000;,
 -0.998000;1.504700;0.000000;,
 -0.998000;1.504700;-0.420000;,
 -0.998000;0.504700;-0.420000;,
 -0.998000;0.504700;0.000000;,
 0.114100;0.523000;0.309400;,
 0.114100;0.523000;0.161900;,
 0.114100;1.523000;0.161900;,
 0.114100;1.523000;0.309400;,
 0.114100;1.523000;0.309400;,
 0.114100;1.523000;0.161900;,
 -0.114100;1.523000;0.161900;,
 -0.114100;1.523000;0.309400;,
 -0.114100;1.523000;0.309400;,
 -0.114100;1.523000;0.161900;,
 -0.114100;0.523000;0.161900;,
 -0.114100;0.523000;0.309400;,
 -0.114100;0.523000;0.309400;,
 -0.114100;0.523000;0.161900;,
 0.114100;0.523000;0.161900;,
 0.114100;0.523000;0.309400;,
 -0.114100;1.523000;0.309400;,
 -0.114100;0.523000;0.309400;,
 0.114100;0.523000;0.309400;,
 0.114100;1.523000;0.309400;,
 -0.114100;1.523000;0.161900;,
 0.114100;1.523000;0.161900;,
 0.114100;0.523000;0.161900;,
 -0.114100;0.523000;0.161900;,
 -0.500000;1.137100;0.309400;,
 0.500000;1.137100;0.309400;,
 0.500000;1.137100;0.161900;,
 -0.500000;1.137100;0.161900;,
 0.500000;1.137100;0.309400;,
 0.500000;0.908800;0.309400;,
 0.500000;0.908800;0.161900;,
 0.500000;1.137100;0.161900;,
 0.500000;0.908800;0.309400;,
 -0.500000;0.908800;0.309400;,
 -0.500000;0.908800;0.161900;,
 0.500000;0.908800;0.161900;,
 -0.500000;0.908800;0.309400;,
 -0.500000;1.137100;0.309400;,
 -0.500000;1.137100;0.161900;,
 -0.500000;0.908800;0.161900;,
 0.500000;0.908800;0.309400;,
 0.500000;1.137100;0.309400;,
 -0.500000;1.137100;0.309400;,
 -0.500000;0.908800;0.309400;,
 0.500000;0.908800;0.161900;,
 -0.500000;0.908800;0.161900;,
 -0.500000;1.137100;0.161900;,
 0.500000;1.137100;0.161900;,
 0.502000;1.504700;-0.630000;,
 0.502000;2.004700;-0.420000;,
 1.002000;1.504700;-0.420000;,
 -0.498000;1.504700;-0.630000;,
 -0.498000;2.004700;-0.420000;,
 -0.498000;2.004700;0.000000;,
 0.502000;2.004700;0.000000;,
 1.002000;1.504700;0.000000;,
 0.502000;1.504700;0.210000;,
 -0.998000;1.504700;-0.420000;,
 -0.998000;1.504700;0.000000;,
 -0.498000;1.504700;0.210000;,
 0.502000;0.004700;-0.420000;,
 0.502000;0.504700;-0.630000;,
 1.002000;0.504700;-0.420000;,
 -0.498000;0.004700;-0.420000;,
 -0.498000;0.504700;-0.630000;,
 -0.998000;0.504700;-0.420000;,
 -0.498000;0.004700;0.000000;,
 -0.998000;0.504700;0.000000;,
 1.002000;0.504700;0.000000;,
 0.502000;0.004700;0.000000;,
 0.502000;0.504700;0.210000;,
 -0.498000;0.504700;0.210000;;
 68;
 3;0,1,2;,
 3;2,3,0;,
 3;4,0,3;,
 3;3,5,4;,
 3;6,7,8;,
 3;8,9,6;,
 3;10,6,9;,
 3;9,11,10;,
 3;12,13,14;,
 3;14,15,12;,
 3;16,12,15;,
 3;15,17,16;,
 3;18,16,17;,
 3;17,19,18;,
 3;20,21,22;,
 3;22,23,20;,
 3;24,25,26;,
 3;26,27,24;,
 3;28,29,30;,
 3;30,31,28;,
 3;32,33,34;,
 3;34,35,32;,
 3;36,37,38;,
 3;38,39,36;,
 3;40,41,42;,
 3;42,43,40;,
 3;44,45,46;,
 3;46,47,44;,
 3;48,49,50;,
 3;50,51,48;,
 3;52,53,54;,
 3;54,55,52;,
 3;56,57,58;,
 3;58,59,56;,
 3;60,61,62;,
 3;62,63,60;,
 3;64,65,66;,
 3;66,67,64;,
 3;68,69,70;,
 3;70,71,68;,
 3;72,73,74;,
 3;73,72,75;,
 3;75,76,73;,
 3;73,76,77;,
 3;77,78,73;,
 3;74,73,78;,
 3;78,79,74;,
 3;79,78,80;,
 3;81,76,75;,
 3;76,81,82;,
 3;82,77,76;,
 3;83,77,82;,
 3;77,83,80;,
 3;80,78,77;,
 3;84,85,86;,
 3;85,84,87;,
 3;87,88,85;,
 3;89,88,87;,
 3;89,87,90;,
 3;90,91,89;,
 3;84,86,92;,
 3;92,93,84;,
 3;84,93,90;,
 3;90,87,84;,
 3;93,92,94;,
 3;93,94,95;,
 3;95,90,93;,
 3;95,91,90;;

 MeshNormals {
  96;
  0.809700;-0.319700;-0.492100;,
  0.189900;-0.189900;-0.963300;,
  0.189900;0.189900;-0.963300;,
  0.809700;0.319700;-0.492100;,
  0.809700;-0.319700;0.492100;,
  0.809700;0.319700;0.492100;,
  -0.189900;-0.189900;-0.963300;,
  -0.809700;-0.319700;-0.492100;,
  -0.809700;0.319700;-0.492100;,
  -0.189900;0.189900;-0.963300;,
  0.189900;-0.189900;-0.963300;,
  0.189900;0.189900;-0.963300;,
  0.189900;-0.189900;0.963300;,
  0.809700;-0.319700;0.492100;,
  0.809700;0.319700;0.492100;,
  0.189900;0.189900;0.963300;,
  -0.189900;-0.189900;0.963300;,
  -0.189900;0.189900;0.963300;,
  -0.809700;-0.319700;0.492100;,
  -0.809700;0.319700;0.492100;,
  -0.809700;0.319700;0.492100;,
  -0.809700;0.319700;-0.492100;,
  -0.809700;-0.319700;-0.492100;,
  -0.809700;-0.319700;0.492100;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.189900;0.189900;-0.963300;,
  0.319700;0.809700;-0.492100;,
  0.809700;0.319700;-0.492100;,
  -0.189900;0.189900;-0.963300;,
  -0.319700;0.809700;-0.492100;,
  -0.319700;0.809700;0.492100;,
  0.319700;0.809700;0.492100;,
  0.809700;0.319700;0.492100;,
  0.189900;0.189900;0.963300;,
  -0.809700;0.319700;-0.492100;,
  -0.809700;0.319700;0.492100;,
  -0.189900;0.189900;0.963300;,
  0.319700;-0.809700;-0.492100;,
  0.189900;-0.189900;-0.963300;,
  0.809700;-0.319700;-0.492100;,
  -0.319700;-0.809700;-0.492100;,
  -0.189900;-0.189900;-0.963300;,
  -0.809700;-0.319700;-0.492100;,
  -0.319700;-0.809700;0.492100;,
  -0.809700;-0.319700;0.492100;,
  0.809700;-0.319700;0.492100;,
  0.319700;-0.809700;0.492100;,
  0.189900;-0.189900;0.963300;,
  -0.189900;-0.189900;0.963300;;
  68;
  3;0,1,2;,
  3;2,3,0;,
  3;4,0,3;,
  3;3,5,4;,
  3;6,7,8;,
  3;8,9,6;,
  3;10,6,9;,
  3;9,11,10;,
  3;12,13,14;,
  3;14,15,12;,
  3;16,12,15;,
  3;15,17,16;,
  3;18,16,17;,
  3;17,19,18;,
  3;20,21,22;,
  3;22,23,20;,
  3;24,25,26;,
  3;26,27,24;,
  3;28,29,30;,
  3;30,31,28;,
  3;32,33,34;,
  3;34,35,32;,
  3;36,37,38;,
  3;38,39,36;,
  3;40,41,42;,
  3;42,43,40;,
  3;44,45,46;,
  3;46,47,44;,
  3;48,49,50;,
  3;50,51,48;,
  3;52,53,54;,
  3;54,55,52;,
  3;56,57,58;,
  3;58,59,56;,
  3;60,61,62;,
  3;62,63,60;,
  3;64,65,66;,
  3;66,67,64;,
  3;68,69,70;,
  3;70,71,68;,
  3;72,73,74;,
  3;73,72,75;,
  3;75,76,73;,
  3;73,76,77;,
  3;77,78,73;,
  3;74,73,78;,
  3;78,79,74;,
  3;79,78,80;,
  3;81,76,75;,
  3;76,81,82;,
  3;82,77,76;,
  3;83,77,82;,
  3;77,83,80;,
  3;80,78,77;,
  3;84,85,86;,
  3;85,84,87;,
  3;87,88,85;,
  3;89,88,87;,
  3;89,87,90;,
  3;90,91,89;,
  3;84,86,92;,
  3;92,93,84;,
  3;84,93,90;,
  3;90,87,84;,
  3;93,92,94;,
  3;93,94,95;,
  3;95,90,93;,
  3;95,91,90;;
 }

 MeshTextureCoords {
  96;
  0.406000;0.247900;,
  0.417800;0.247900;,
  0.417800;0.236100;,
  0.406000;0.236100;,
  0.394200;0.247900;,
  0.394200;0.236100;,
  0.406000;0.247900;,
  0.417800;0.247900;,
  0.417800;0.236100;,
  0.406000;0.236100;,
  0.394200;0.247900;,
  0.394200;0.236100;,
  0.406000;0.247900;,
  0.417800;0.247900;,
  0.417800;0.236100;,
  0.406000;0.236100;,
  0.394200;0.247900;,
  0.394200;0.236100;,
  0.382400;0.247900;,
  0.382400;0.236100;,
  0.406000;0.236100;,
  0.394200;0.236100;,
  0.394200;0.247900;,
  0.406000;0.247900;,
  0.359100;0.669100;,
  0.359100;0.698000;,
  0.330200;0.698000;,
  0.330200;0.669100;,
  0.359100;0.669100;,
  0.359100;0.698000;,
  0.330200;0.698000;,
  0.330200;0.669100;,
  0.359100;0.669100;,
  0.359100;0.698000;,
  0.330200;0.698000;,
  0.330200;0.669100;,
  0.359100;0.669100;,
  0.359100;0.698000;,
  0.330200;0.698000;,
  0.330200;0.669100;,
  0.359100;0.669100;,
  0.359100;0.698000;,
  0.330200;0.698000;,
  0.330200;0.669100;,
  1.952600;2.021600;,
  2.952600;2.021600;,
  2.952600;1.021600;,
  1.952600;1.021600;,
  0.359100;0.669100;,
  0.330200;0.669100;,
  0.330200;0.698000;,
  0.359100;0.698000;,
  0.359100;0.669100;,
  0.330200;0.669100;,
  0.330200;0.698000;,
  0.359100;0.698000;,
  0.359100;0.669100;,
  0.330200;0.669100;,
  0.330200;0.698000;,
  0.359100;0.698000;,
  0.359100;0.669100;,
  0.330200;0.669100;,
  0.330200;0.698000;,
  0.359100;0.698000;,
  0.359100;0.669100;,
  0.330200;0.669100;,
  0.330200;0.698000;,
  0.359100;0.698000;,
  1.952600;2.021600;,
  1.952600;1.021600;,
  2.952600;1.021600;,
  2.952600;2.021600;,
  0.408700;0.198700;,
  0.408700;0.212700;,
  0.422600;0.212700;,
  0.394700;0.198700;,
  0.394700;0.212700;,
  0.394700;0.226700;,
  0.408700;0.226700;,
  0.422600;0.226700;,
  0.408700;0.240600;,
  0.380700;0.212700;,
  0.380700;0.226700;,
  0.394700;0.240600;,
  0.391300;0.242300;,
  0.391300;0.231400;,
  0.380400;0.242300;,
  0.402300;0.242300;,
  0.402300;0.231400;,
  0.413200;0.242300;,
  0.402300;0.253300;,
  0.413200;0.253300;,
  0.380400;0.253300;,
  0.391300;0.253300;,
  0.391300;0.264200;,
  0.402300;0.264200;;
 }

 MeshMaterialList {
  2;
  68;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;

  Material {
   0.800000;0.800000;0.800000;1.000000;;
   0.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;

   TextureFilename {
    "";
   }
  }

  Material {
   0.733800;0.654700;0.500000;1.000000;;
   0.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;

   TextureFilename {
    "tx_colorpicker.jpg";
   }
  }
 }
}