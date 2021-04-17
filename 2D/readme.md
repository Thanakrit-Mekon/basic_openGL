# Result

### Vertices primitive
this function call a GL_POINTS primitive by giving colors RGBA, coordinates (x ,y ,z) and vertices size.

```shell
drawsamplePoint(1, 1);
```
![openGL_sample_vertices_result](https://user-images.githubusercontent.com/65077907/115064012-9605ee00-9f16-11eb-9f79-3dce878d255e.png)

### Lines primitive
this function call a GL_LINES primitive by giving each vertice a colors RGBA, 2 coordinates (x1 ,y1 ,z1) (x2, y2, z2) and vertices size.
```shell
drawSampleLine();
```
![openGL_sample_line_result](https://user-images.githubusercontent.com/65077907/115064026-99997500-9f16-11eb-891c-875fea78aa97.png)

### Triangle primitive
Triangle primitive are likely to both primitives above but with 3 vertices, this function call GL_TRIANGLES primitive

```shell
drawSampleTriangle();
```
![openGL_sample_triangle_result](https://user-images.githubusercontent.com/65077907/115064032-9c946580-9f16-11eb-8a7b-3dacf495c59d.png)

### Plot streaming data
the combination of line and vertices and the changing of phase

```shell
drawSampleSinusoid(phaseShift);\n
phaseShift += 0.001f;
```
https://user-images.githubusercontent.com/65077907/115064037-a027ec80-9f16-11eb-9b87-545632a82d6a.mp4

### Represent 3D data in 2D
represent heatmap in 2D and changing in time domain.

```shell
drawGrid(5.0f, 1.0f, 0.1f);
sigma += 0.01f;
if (sigma > 1.0f) {
    sigma = 0.01;
}
sampleGaussian(sigma);
```
https://user-images.githubusercontent.com/65077907/115064066-af0e9f00-9f16-11eb-8ae6-53642a218d8a.mp4



